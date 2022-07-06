#ifndef __SIMPLE_ANY_H__
#define __SIMPLE_ANY_H__

#include <memory>
#include <type_traits>
#include <typeinfo>

#include <glog/logging.h>

using namespace std;

class SimpleAny {
public:
  // ctor and dtor
  SimpleAny() = default;
  ~SimpleAny() = default;

  // copy ctor and copy assignment
  SimpleAny(const SimpleAny &other) {
    if (other.data_ptr_) {
      data_ptr_ = other.data_ptr_->Clone();
    }
  }
  SimpleAny &operator=(const SimpleAny &other) {
    data_ptr_ = move(SimpleAny(other).data_ptr_);
    return *this;
  }

  // move ctor and copy assignment
  SimpleAny(SimpleAny &&other) : data_ptr_(move(other.data_ptr_)) {}
  SimpleAny &operator=(SimpleAny &&other) {
    data_ptr_ = move(other.data_ptr_);
    return *this;
  }

  // template ctor and copy assignment using data
  template <typename T> using DecayType = typename decay<T>::type;
  template <typename T,
            typename enable_if<!is_same<DecayType<T>, SimpleAny>::value,
                               bool>::type = true>
  SimpleAny(T &&data) {
    data_ptr_.reset(new InternalDataImpl<DecayType<T>>(forward<T>(data)));
  }
  template <typename T,
            typename enable_if<!is_same<DecayType<T>, SimpleAny>::value,
                               bool>::type = true>
  SimpleAny &operator=(T &&data) {
    data_ptr_.reset(new InternalDataImpl<DecayType<T>>(forward<T>(data)));
    return *this;
  }

  bool Empty() const { return data_ptr_ == nullptr; }
  const type_info &GetType() const {
    return (!Empty()) ? data_ptr_->GetType() : typeid(void);
  }

  template <typename T> 
  void ChkType() const {
    if (GetType().hash_code() != typeid(T).hash_code()) {
      LOG(FATAL) << "Can not cast " << GetType().name() << " to "
                 << typeid(T).name();
    }
  }


  template <typename T> 
  void ChkBind() const {
    if (Empty()) {
      LOG(FATAL) << "No data binding!";
    }
  }

  template <typename T> 
  const T &Cast() const {
    ChkType<T>();
    ChkBind<T>();
    return static_cast<const InternalDataImpl<T> *>(data_ptr_.get())->data_;
  }
  template <typename T> 
  T &Cast() {
    ChkType<T>();
    ChkBind<T>();
    return static_cast<InternalDataImpl<T> *>(data_ptr_.get())->data_;
  }

private:
  struct InternalData {
    InternalData() = default;
    virtual ~InternalData() = default;

    virtual const type_info &GetType() const = 0;
    virtual unique_ptr<InternalData> Clone() const = 0;
  };

  template <typename T> 
  struct InternalDataImpl : public InternalData {
    T data_;

    InternalDataImpl(const T &data) : data_(data) { cout << "aaa" << endl; }
    InternalDataImpl(T &&data) : data_(move(data)) { cout << "bbb" << endl; }

    virtual const type_info &GetType() const override { return typeid(T); }
    virtual unique_ptr<InternalData> Clone() const override {
      return unique_ptr<InternalDataImpl>(new InternalDataImpl<T>(data_));
    }
  };

private:
  unique_ptr<InternalData> data_ptr_;
};

template <typename T> 
const T &any_cast(const SimpleAny &any) {
  return any.Cast<T>();
}

template <typename T> 
T &any_cast(SimpleAny &any) { 
  return any.Cast<T>(); 
}

#endif // __SIMPLE_ANY_H__