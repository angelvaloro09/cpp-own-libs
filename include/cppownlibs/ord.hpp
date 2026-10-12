// ord: algoritmos de ordenamiento (in-place, de menor a mayor). Usa util::swap.
#ifndef CPPOWNLIBS_ORD_HPP
#define CPPOWNLIBS_ORD_HPP

#include <vector>

namespace ord
{

// Estable. O(n^2) peor caso, O(n) si ya está ordenado.
void bubble_sort(int arr[], int tam);
void bubble_sort(std::vector<int> &v);

// No estable. O(n log n) promedio. Eficiente con valores repetidos.
void quick_sort(int arr[], int tam);
void quick_sort(std::vector<int> &v);

} // namespace ord

#endif // CPPOWNLIBS_ORD_HPP
