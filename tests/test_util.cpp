#include <cppownlibs/util.hpp>

#include <climits>
#include <vector>

#include "check.hpp"

int main()
{
    // swap
    int x = 1, y = 2;
    util::swap(x, y);
    CHECK(x == 2 && y == 1);
    util::swap(x, x); // mismo objeto: no debe cambiar
    CHECK(x == 2);

    // median_of_three: las 6 permutaciones y casos con repetidos
    int p[6][3] = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};
    for (auto &t : p)
        CHECK(util::median_of_three(t[0], t[1], t[2]) == 2);
    CHECK(util::median_of_three(5, 5, 5) == 5);
    CHECK(util::median_of_three(1, 1, 9) == 1);
    CHECK(util::median_of_three(9, 1, 1) == 1);
    CHECK(util::median_of_three(1, 9, 9) == 9);
    CHECK(util::median_of_three(-3, 0, 7) == 0);

    // abs_unsigned
    CHECK(util::abs_unsigned(0) == 0u);
    CHECK(util::abs_unsigned(5) == 5u);
    CHECK(util::abs_unsigned(-5) == 5u);
    CHECK(util::abs_unsigned(INT_MAX) == static_cast<unsigned>(INT_MAX));
    CHECK(util::abs_unsigned(INT_MIN) == 2147483648u);

    // bit_length
    CHECK(util::bit_length(0u) == 0);
    CHECK(util::bit_length(1u) == 1);
    CHECK(util::bit_length(2u) == 2);
    CHECK(util::bit_length(255u) == 8);
    CHECK(util::bit_length(256u) == 9);
    CHECK(util::bit_length(UINT_MAX) == static_cast<int>(sizeof(unsigned) * CHAR_BIT));

    // append_int
    std::string s = "n=";
    util::append_int(s, 0);
    util::append_int(s, 42);
    util::append_int(s, -7);
    util::append_int(s, INT_MAX);
    util::append_int(s, INT_MIN);
    CHECK(s == "n=042-72147483647-2147483648");

    // copy_range
    const int src[] = {1, 2, 3, 4};
    int dst[] = {0, 0, 0, 0, 0};
    util::copy_range(src, 4, dst);
    CHECK(dst[0] == 1 && dst[3] == 4 && dst[4] == 0);
    util::copy_range(src, 0, dst + 4); // n = 0 no toca nada
    CHECK(dst[4] == 0);
    return 0;
}
