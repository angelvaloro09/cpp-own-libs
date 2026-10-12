#include "cppownlibs/conv.hpp"

#include "cppownlibs/util.hpp"

namespace conv
{

std::string dec_to_bin(int n)
{
    if (n == 0)
        return "0";

    const bool neg = n < 0;
    unsigned u = util::abs_unsigned(n);

    // Se cuentan los bits para crear el string de una vez y rellenarlo desde el final.
    std::string s(static_cast<std::size_t>(util::bit_length(u) + (neg ? 1 : 0)), '0');
    int i = static_cast<int>(s.size()) - 1;
    for (; u; u >>= 1)
        s[static_cast<std::size_t>(i--)] = static_cast<char>('0' + (u & 1u));
    if (neg)
        s[0] = '-';
    return s;
}

int bin_to_dec(const std::string &binario)
{
    // Horner: cada dígito desplaza el acumulado un bit a la izquierda.
    // unsigned para que el desbordamiento esté definido.
    unsigned resultado = 0;
    for (char c : binario)
        resultado = (resultado << 1) | (c == '1' ? 1u : 0u);
    return static_cast<int>(resultado);
}

} // namespace conv
