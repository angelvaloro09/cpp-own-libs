#include <cppownlibs/arr.hpp>

#include <climits>
#include <iostream>
#include <sstream>
#include <vector>

#include "check.hpp"

using arr::operator+;

int main()
{
    int a[] = {6, 9, 3};
    std::vector<int> v = {6, 9, 3};

    CHECK(arr::to_string(v) == "{6, 9, 3}");
    CHECK(arr::to_string(a, 3) == "{6, 9, 3}");
    CHECK(arr::to_string(a, 2) == "{6, 9}");
    CHECK(arr::to_string(a, 0) == "{}");
    CHECK(arr::to_string(std::vector<int>{}) == "{}");
    CHECK(arr::to_string(std::vector<int>{0, -1, 10, 12345}) == "{0, -1, 10, 12345}");
    CHECK(arr::to_string(std::vector<int>{INT_MIN, INT_MAX}) == "{-2147483648, 2147483647}");

    // print_array escribe en std::cout: se redirige para comprobarlo
    std::ostringstream os;
    std::streambuf *old = std::cout.rdbuf(os.rdbuf());
    arr::print_array(a, 2);
    arr::print_array(std::vector<int>{7});
    std::cout.rdbuf(old);
    CHECK(os.str() == "Elemento [1]: 6\nElemento [2]: 9\nElemento [1]: 7\n");

    CHECK((v + std::vector<int>{1, 2}) == (std::vector<int>{6, 9, 3, 1, 2}));
    CHECK((std::vector<int>{} + v) == v);
    CHECK((v + std::vector<int>{}) == v);
    CHECK((std::vector<int>{} + std::vector<int>{}).empty());
    return 0;
}
