#include <charconv>
#include <iomanip>
#include <iostream>
#include <string_view>
#include <system_error>
 
void show_to_chars(auto... format_args)
{
    const size_t buf_size = 10;
    char buf[buf_size]{};
    std::to_chars_result result = std::to_chars(buf, buf + buf_size, format_args...);
 
    if (result.ec != std::errc())
        std::cout << std::make_error_code(result.ec).message() << '\n';
    else
    {
        std::string_view str(buf, result.ptr - buf);
        std::cout << std::quoted(str) << '\n';
    }
}
 
int main()
{
    show_to_chars(42);
    show_to_chars(+3.14159F);
    show_to_chars(-3.14159, std::chars_format::fixed);
    show_to_chars(-3.14159, std::chars_format::scientific, 3);
    show_to_chars(3.1415926535, std::chars_format::fixed, 10);
}