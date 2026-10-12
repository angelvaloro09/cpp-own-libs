#include "cppownlibs/util.hpp"

namespace util
{

void append_int(std::string &s, int n)
{
    char buf[12]; // "-2147483648" = 11 caracteres
    int pos = 12;
    unsigned u = abs_unsigned(n);
    do
    {
        buf[--pos] = static_cast<char>('0' + (u % 10u));
        u /= 10u;
    } while (u);
    if (n < 0)
        buf[--pos] = '-';
    s.append(buf + pos, static_cast<std::size_t>(12 - pos));
}

void copy_range(const int *source, int n, int *dest)
{
    for (int i = 0; i < n; ++i)
        dest[i] = source[i];
}

} // namespace util
