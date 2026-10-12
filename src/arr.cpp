#include "cppownlibs/arr.hpp"

#include <iostream>

#include "cppownlibs/util.hpp"

namespace arr
{

std::string to_string(const int arr[], int tam)
{
    std::string vec = "{";
    if (tam > 0)
    {
        util::append_int(vec, arr[0]);
        for (int i = 1; i < tam; ++i)
        {
            vec += ", ";
            util::append_int(vec, arr[i]);
        }
    }
    vec += "}";
    return vec;
}

std::string to_string(const std::vector<int> &v)
{
    return to_string(v.data(), static_cast<int>(v.size()));
}

void print_array(const int arr[], int tam)
{
    // '\n' en vez de std::endl: no vacía el búfer en cada línea.
    for (int i = 0; i < tam; i++)
    {
        std::cout << "Elemento [" << (i + 1) << "]: " << arr[i] << '\n';
    }
}

void print_array(const std::vector<int> &v)
{
    print_array(v.data(), static_cast<int>(v.size()));
}

std::vector<int> operator+(const std::vector<int> &a, const std::vector<int> &b)
{
    // Una sola asignación con el tamaño final, luego se copia cada rango.
    const int na = static_cast<int>(a.size());
    const int nb = static_cast<int>(b.size());
    std::vector<int> res(a.size() + b.size());
    util::copy_range(a.data(), na, res.data());
    util::copy_range(b.data(), nb, res.data() + na);
    return res;
}

} // namespace arr
