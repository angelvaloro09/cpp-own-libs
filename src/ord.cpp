#include "cppownlibs/ord.hpp"

#include "cppownlibs/util.hpp"

namespace ord
{

void bubble_sort(int arr[], int tam)
{
    // Lo que queda desde el último intercambio ya está ordenado:
    // la siguiente pasada solo llega hasta ahí.
    int fin = tam;
    while (fin > 1)
    {
        int ultimo = 0;
        for (int j = 1; j < fin; j++)
        {
            if (arr[j - 1] > arr[j])
            {
                util::swap(arr[j - 1], arr[j]);
                ultimo = j;
            }
        }
        fin = ultimo;
    }
}

void bubble_sort(std::vector<int> &v)
{
    bubble_sort(v.data(), static_cast<int>(v.size()));
}

namespace
{

const int UMBRAL = 16; // tramos de hasta UMBRAL + 1 elementos se ordenan por inserción

void insertion_sort(int arr[], int izq, int der)
{
    for (int i = izq + 1; i <= der; i++)
    {
        int x = arr[i];
        int j = i - 1;
        while (j >= izq && arr[j] > x)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = x;
    }
}

// Ordena arr[izq..der] (ambos incluidos).
void quick_sort_range(int arr[], int izq, int der)
{
    while (der - izq >= UMBRAL)
    {
        int piv = util::median_of_three(arr[izq], arr[izq + (der - izq) / 2], arr[der]);

        // Partición en 3 vías: [izq, lt) < piv, [lt, gt] == piv, (gt, der] > piv
        int lt = izq, i = izq, gt = der;
        while (i <= gt)
        {
            if (arr[i] < piv)
            {
                util::swap(arr[lt], arr[i]);
                lt++;
                i++;
            }
            else if (arr[i] > piv)
            {
                util::swap(arr[i], arr[gt]);
                gt--;
            }
            else
            {
                i++;
            }
        }

        // Recursión sobre el lado menor; el mayor sigue en el bucle (pila O(log n)).
        if (lt - izq < der - gt)
        {
            quick_sort_range(arr, izq, lt - 1);
            izq = gt + 1;
        }
        else
        {
            quick_sort_range(arr, gt + 1, der);
            der = lt - 1;
        }
    }
    insertion_sort(arr, izq, der);
}

} // namespace

void quick_sort(int arr[], int tam)
{
    quick_sort_range(arr, 0, tam - 1);
}

void quick_sort(std::vector<int> &v)
{
    quick_sort(v.data(), static_cast<int>(v.size()));
}

} // namespace ord
