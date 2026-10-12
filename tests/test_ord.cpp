#include <cppownlibs/ord.hpp>

#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

#include "check.hpp"

// Compara contra std::sort con distintos tamaños y rangos de valores
// (rango chico = muchos duplicados).
template <class Sorter>
void comparar_con_std(Sorter sort)
{
    std::mt19937 rng(12345);
    for (int tam : {0, 1, 2, 3, 16, 17, 18, 50, 100, 1000})
    {
        for (int rango : {2, 10, 1000000})
        {
            std::vector<int> v(static_cast<std::size_t>(tam));
            for (int &x : v)
                x = static_cast<int>(rng() % static_cast<unsigned>(rango)) - rango / 2;
            std::vector<int> esperado = v;
            std::sort(esperado.begin(), esperado.end());
            sort(v);
            CHECK(v == esperado);
        }
    }

    std::vector<int> asc(500), desc(500), iguales(500, 7);
    for (int i = 0; i < 500; ++i)
    {
        asc[static_cast<std::size_t>(i)] = i;
        desc[static_cast<std::size_t>(i)] = 500 - i;
    }
    sort(asc);
    sort(desc);
    sort(iguales);
    CHECK(std::is_sorted(asc.begin(), asc.end()));
    CHECK(std::is_sorted(desc.begin(), desc.end()));
    CHECK(iguales == std::vector<int>(500, 7));
}

int main()
{
    comparar_con_std([](std::vector<int> &v) { ord::bubble_sort(v); });
    comparar_con_std([](std::vector<int> &v) { ord::quick_sort(v); });

    // C-style arrays
    int a[] = {6, 9, 1, 2, 7, 3};
    ord::bubble_sort(a, 6);
    CHECK(std::is_sorted(std::begin(a), std::end(a)));
    int b[] = {6, 9, 3, 4, 2, 5, 7, -1, -100, 10};
    ord::quick_sort(b, 10);
    CHECK(std::is_sorted(std::begin(b), std::end(b)));
    CHECK(b[0] == -100 && b[9] == 10);

    // tam = 0 no toca nada
    int vacio[1] = {42};
    ord::bubble_sort(vacio, 0);
    ord::quick_sort(vacio, 0);
    CHECK(vacio[0] == 42);

    // sub-rango: solo se ordenan los primeros 4
    int c[] = {4, 3, 2, 1, 0, -1};
    ord::quick_sort(c, 4);
    CHECK(c[0] == 1 && c[3] == 4 && c[4] == 0 && c[5] == -1);

    // entradas grandes: iguales y ordenadas no deben degradar ni desbordar la pila
    std::vector<int> grande(200000, 1);
    ord::quick_sort(grande);
    std::vector<int> grande2(200000);
    for (std::size_t i = 0; i < grande2.size(); ++i)
        grande2[i] = static_cast<int>(i);
    ord::quick_sort(grande2);
    CHECK(std::is_sorted(grande2.begin(), grande2.end()));
    return 0;
}
