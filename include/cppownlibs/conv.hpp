// conv: conversión decimal <-> binario.
#ifndef CPPOWNLIBS_CONV_HPP
#define CPPOWNLIBS_CONV_HPP

#include <string>

namespace conv
{

// Decimal -> binario. Ej: 69 -> "1000101", 0 -> "0", -5 -> "-101".
std::string dec_to_bin(int n);

// Binario -> decimal. Ej: "1101" -> 13. Cualquier caracter distinto de '1' cuenta como 0.
int bin_to_dec(const std::string &binario);

} // namespace conv

#endif // CPPOWNLIBS_CONV_HPP
