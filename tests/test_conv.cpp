#include <cppownlibs/conv.hpp>

#include <climits>

#include "check.hpp"

int main()
{
    CHECK(conv::dec_to_bin(0) == "0");
    CHECK(conv::dec_to_bin(1) == "1");
    CHECK(conv::dec_to_bin(69) == "1000101");
    CHECK(conv::dec_to_bin(255) == "11111111");
    CHECK(conv::dec_to_bin(-5) == "-101");
    CHECK(conv::dec_to_bin(INT_MAX) == std::string(31, '1'));
    CHECK(conv::dec_to_bin(INT_MIN) == "-1" + std::string(31, '0'));

    CHECK(conv::bin_to_dec("") == 0);
    CHECK(conv::bin_to_dec("0") == 0);
    CHECK(conv::bin_to_dec("1101") == 13);
    CHECK(conv::bin_to_dec("0001101") == 13);
    CHECK(conv::bin_to_dec("1000101") == 69);
    CHECK(conv::bin_to_dec(std::string(31, '1')) == INT_MAX);

    for (int n : {1, 2, 7, 69, 255, 123456, INT_MAX})
        CHECK(conv::bin_to_dec(conv::dec_to_bin(n)) == n);
    return 0;
}
