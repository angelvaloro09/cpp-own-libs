// util: funciones auxiliares de propósito general.
#ifndef CPPOWNLIBS_UTIL_HPP
#define CPPOWNLIBS_UTIL_HPP

#include <string>

namespace util
{

// Intercambia dos enteros. Es seguro si ambos son el mismo objeto.
inline void swap(int &a, int &b);

// Mediana de tres valores. Ej: (9, 1, 5) -> 5.
inline int median_of_three(int a, int b, int c);

// Valor absoluto como unsigned. Seguro con INT_MIN. Ej: -5 -> 5u.
inline unsigned abs_unsigned(int n);

// Cantidad de bits necesarios para representar `u`. Ej: 0 -> 0, 1 -> 1, 255 -> 8, 256 -> 9.
inline int bit_length(unsigned u);

// Agrega el entero `n` en decimal al final de `s`, sin strings temporales.
void append_int(std::string &s, int n);

// Copia `n` enteros de `source` a `dest`. Los rangos no deben solaparse.
void copy_range(const int *source, int n, int *dest);

} // namespace util

// Definiciones de las funciones inline (separadas para mantener este header solo con declaraciones).
#include "util.inl"

#endif // CPPOWNLIBS_UTIL_HPP
