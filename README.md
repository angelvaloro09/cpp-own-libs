# cppownlibs

Cuatro librerías C++ reutilizables, con la declaración en `include/cppownlibs/*.hpp`
y la definición en `src/*.cpp`. `util` es la base: `conv`, `ord` y `arr` dependen de ella
(CMake la enlaza automáticamente).

| Librería | Header | Namespace | Contenido |
|----------|--------|-----------|-----------|
| `util` | `<cppownlibs/util.hpp>` | `util` | `swap`, `median_of_three`, `abs_unsigned`, `bit_length`, `append_int`, `copy_range` |
| `conv` | `<cppownlibs/conv.hpp>` | `conv` | decimal ⇄ binario |
| `ord`  | `<cppownlibs/ord.hpp>`  | `ord`  | bubble sort, quick sort |
| `arr`  | `<cppownlibs/arr.hpp>`  | `arr`  | `to_string`, `print_array`, `operator+` para vectores |

Las funciones trabajan con `int`. Donde corresponde hay sobrecargas para `std::vector<int>`
y para C-style arrays (`int arr[], int tam`). Requiere C++11 o superior.

## Usar en otro proyecto

### Opción 1: CMake con `add_subdirectory`

```cmake
add_subdirectory(extern/cppownlibs)   # copia o submódulo git

add_executable(app main.cpp)
target_link_libraries(app PRIVATE cppownlibs::conv cppownlibs::ord cppownlibs::arr cppownlibs::util)
```

Enlazar solo las que se usen; `util` se arrastra sola con `conv`, `ord` y `arr`.

### Opción 2: CMake con `FetchContent`

```cmake
include(FetchContent)
FetchContent_Declare(cppownlibs
    GIT_REPOSITORY https://github.com/angelvaloro09/cpp-own-libs.git
    GIT_TAG        v4.0.0)   # o main para la última versión
FetchContent_MakeAvailable(cppownlibs)

target_link_libraries(app PRIVATE cppownlibs::ord)
```

### Opción 3: instalar y usar `find_package`

```sh
cmake -S cppownlibs -B build
cmake --build build
cmake --install build --prefix C:/libs/cppownlibs      # o /usr/local
```

```cmake
find_package(cppownlibs REQUIRED)    # con -DCMAKE_PREFIX_PATH=C:/libs/cppownlibs
target_link_libraries(app PRIVATE cppownlibs::conv)
```

### Opción 4: sin CMake (g++ / clang++)

Compilar el `.cpp` de cada librería usada, más `util.cpp`, junto con tu código:

```sh
g++ -std=c++11 -O2 -Icppownlibs/include main.cpp cppownlibs/src/ord.cpp cppownlibs/src/arr.cpp cppownlibs/src/util.cpp -o main
```

## API

### `util`

```cpp
#include <cppownlibs/util.hpp>

util::swap(a, b);                      // intercambia dos int (seguro si a y b son el mismo objeto)
util::median_of_three(9, 1, 5);        // 5
util::abs_unsigned(-5);                // 5u  (seguro con INT_MIN)
util::bit_length(255u);                // 8   (0 -> 0)

std::string s = "n=";
util::append_int(s, -42);              // s == "n=-42", sin strings temporales

int src[] = {1, 2, 3}, dst[3];
util::copy_range(src, 3, dst);         // copia n enteros; los rangos no deben solaparse
```

`swap`, `median_of_three`, `abs_unsigned` y `bit_length` son `inline`: se declaran en `util.hpp`
y se definen en `util.inl` (que `util.hpp` incluye), para que los ordenamientos puedan inlinearlas.
`append_int` y `copy_range` se definen en `src/util.cpp`.

### `conv`

```cpp
#include <cppownlibs/conv.hpp>

std::string conv::dec_to_bin(int n);                  // 69 -> "1000101", 0 -> "0", -5 -> "-101"
int         conv::bin_to_dec(const std::string &bin); // "1101" -> 13
```

`bin_to_dec` no valida la cadena: cualquier caracter distinto de `'1'` cuenta como 0.

### `ord`

Los dos algoritmos ordenan **in-place**, de menor a mayor.

```cpp
#include <cppownlibs/ord.hpp>

int a[] = {6, 9, 1, 2, 7, 3};
std::vector<int> v = {5, 3, 8};

ord::bubble_sort(a, 6);   // C-style array
ord::bubble_sort(v);      // vector
ord::quick_sort(a, 6);
ord::quick_sort(v);

ord::quick_sort(a, 4);    // solo ordena los primeros 4 elementos
```

Para conservar el original, copiar antes:

```cpp
std::vector<int> s = v;
ord::quick_sort(s);
```

| Función | Estable | Complejidad |
|---------|---------|-------------|
| `bubble_sort` | sí | O(n²); O(n) si ya está ordenado |
| `quick_sort`  | no | O(n log n) promedio; maneja bien valores repetidos; pila O(log n) |

Un array C que decayó a puntero (p. ej. parámetro `int arr[]`) pierde su tamaño:
hay que pasar `tam` explícitamente.

### `arr`

```cpp
#include <cppownlibs/arr.hpp>

int a[] = {6, 9, 3};
std::vector<int> v = {1, 2};

arr::to_string(v);        // "{1, 2}"
arr::to_string(a, 3);     // "{6, 9, 3}"

arr::print_array(v);      // Elemento [1]: 1 / Elemento [2]: 2  (a std::cout)
arr::print_array(a, 3);

using arr::operator+;     // necesario: ADL no encuentra operadores de otro namespace para std::vector
auto c = v + v;           // {1, 2, 1, 2}
```

## Tests

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Los tests solo se compilan cuando este repo es el proyecto principal;
desactivar con `-DCPPOWNLIBS_BUILD_TESTS=OFF`.
`test_ord` compara contra `std::sort` con distintos tamaños y niveles de duplicados.

## Origen y renombres

| Original | Ahora |
|----------|-------|
| `bin(int)` | `conv::dec_to_bin` |
| `decimal(string, int)` | `conv::bin_to_dec(string)` (se elimina `tamanio`) |
| `bubble_sort(int[], int)` | `ord::bubble_sort` (+ sobrecarga `vector`) |
| `quick_sort(const vector&)` → vector | `ord::quick_sort` → `void`, in-place (+ sobrecarga C-array) |
| `swap(int&, int&)` | `util::swap` |
| `vec_to_string` | `arr::to_string` (+ sobrecarga C-array) |
| `imp_arr` | `arr::print_array` (+ sobrecarga `vector`) |
| `operator+(vector, vector)` | `arr::operator+` |

Funciones auxiliares extraídas a `util`: `median_of_three` (pivote de `quick_sort`),
`abs_unsigned` y `bit_length` (de `dec_to_bin`), `append_int` (de `to_string`) y
`copy_range` (de `operator+`).

## Optimizaciones aplicadas (sin funciones de la biblioteca estándar)

| Función | Cambio |
|---------|--------|
| `conv::bin_to_dec` | Método de Horner con desplazamiento de bits en vez de `pow` (sin `double`, sin `tamanio`) |
| `conv::dec_to_bin` | Se cuentan los bits (`util::bit_length`), se crea el string una vez y se rellena desde el final con `& 1` y `>> 1` (antes: prepend O(n²) y un `to_string` por bit). Ahora `0 → "0"` y soporta negativos |
| `ord::bubble_sort` | Cada pasada llega solo hasta el último intercambio de la anterior |
| `ord::quick_sort` | In-place (sin vectores auxiliares ni copias), pivote mediana de 3, partición en 3 vías (O(n) con duplicados), insertion sort para tramos pequeños, recursión solo sobre el lado menor |
| `arr::to_string` | Conversión de enteros propia (`util::append_int`) sobre un buffer; sin strings temporales por elemento |
| `arr::print_array` | `'\n'` en vez de `std::endl` (no vacía el búfer en cada línea) |
| `arr::operator+` | Una sola asignación con el tamaño final y copia con `util::copy_range` |
