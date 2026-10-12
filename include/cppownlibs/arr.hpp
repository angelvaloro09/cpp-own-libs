// arr: funciones auxiliares para vectores y C-style arrays.
#ifndef CPPOWNLIBS_ARR_HPP
#define CPPOWNLIBS_ARR_HPP

#include <string>
#include <vector>

namespace arr
{

// Ej: {6, 9, 3} -> "{6, 9, 3}"
std::string to_string(const std::vector<int> &v);
std::string to_string(const int arr[], int tam);

// Imprime "Elemento [i]: valor" por línea (i desde 1) en std::cout.
void print_array(const std::vector<int> &v);
void print_array(const int arr[], int tam);

// Concatena dos vectores. Requiere `using arr::operator+;` (ADL no lo encuentra).
std::vector<int> operator+(const std::vector<int> &a, const std::vector<int> &b);

} // namespace arr

#endif // CPPOWNLIBS_ARR_HPP
