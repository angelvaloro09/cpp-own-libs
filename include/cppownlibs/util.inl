// Definiciones inline de util.hpp. No incluir directamente: incluir <cppownlibs/util.hpp>.
#ifndef CPPOWNLIBS_UTIL_INL
#define CPPOWNLIBS_UTIL_INL

namespace util
{

inline void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

inline int median_of_three(int a, int b, int c)
{
    if (a < b)
    {
        if (b < c)
            return b;
        return a < c ? c : a;
    }
    if (a < c)
        return a;
    return b < c ? c : b;
}

inline unsigned abs_unsigned(int n)
{
    // Negación en unsigned: segura incluso para INT_MIN.
    return n < 0 ? 0u - static_cast<unsigned>(n) : static_cast<unsigned>(n);
}

inline int bit_length(unsigned u)
{
    int bits = 0;
    for (; u; u >>= 1)
        ++bits;
    return bits;
}

} // namespace util

#endif // CPPOWNLIBS_UTIL_INL
