#include <functional>
#include <iostream>
#include <memory>
 
struct Foo
{
    void display_greeting()
    {
        std::cout << "Hello, world.\n";
    }
 
    void display_number(int i)
    {
        std::cout << "number: " << i << '\n';
    }
 
    int add_xy(int x, int y)
    {
        return data + x + y;
    }
 
    template<typename... Args> int add_many(Args... args)
    {
        return data + (args + ...);
    }
 
    auto add_them(auto... args) // C++20 required
    {
        return data + (args + ...);
    }
 
    int data = 7;
};
 
int main()
{
    auto f = Foo{};
 
    auto greet = std::mem_fn(&Foo::display_greeting);
    greet(f);
 
    auto print_num = std::mem_fn(&Foo::display_number);
    print_num(f, 42);
 
    auto access_data = std::mem_fn(&Foo::data);
    std::cout << "data: " << access_data(f) << '\n';
 
    auto add_xy = std::mem_fn(&Foo::add_xy);
    std::cout << "add_xy: " << add_xy(f, 1, 2) << '\n';
 
    auto u = std::make_unique<Foo>();
    std::cout << "access_data(u): " << access_data(u) << '\n';
    std::cout << "add_xy(u, 1, 2): " << add_xy(u, 1, 2) << '\n';
 
    auto add_many = std::mem_fn(&Foo::add_many<short, int, long>);
    std::cout << "add_many(u, ...): " << add_many(u, 1, 2, 3) << '\n';
 
    auto add_them = std::mem_fn(&Foo::add_them<short, int, float, double>);
    std::cout << "add_them(u, ...): " << add_them(u, 5, 7, 10.0f, 13.0) << '\n';
}