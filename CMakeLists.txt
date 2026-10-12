cmake_minimum_required(VERSION 3.16)
project(cppownlibs VERSION 4.0.0 LANGUAGES CXX)

option(CPPOWNLIBS_BUILD_TESTS "Compilar tests" ${PROJECT_IS_TOP_LEVEL})

# Cuatro librerías: util (base) y conv, ord, arr, que dependen de util.
foreach(lib util conv ord arr)
    add_library(cppownlibs_${lib} src/${lib}.cpp)
    add_library(cppownlibs::${lib} ALIAS cppownlibs_${lib})
    target_include_directories(cppownlibs_${lib} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
    target_compile_features(cppownlibs_${lib} PUBLIC cxx_std_11)
    set_target_properties(cppownlibs_${lib} PROPERTIES EXPORT_NAME ${lib})
endforeach()
foreach(lib conv ord arr)
    target_link_libraries(cppownlibs_${lib} PUBLIC cppownlibs_util)
endforeach()

# Instalación: cmake --install build --prefix <ruta>
include(GNUInstallDirs)
install(DIRECTORY include/cppownlibs DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS cppownlibs_util cppownlibs_conv cppownlibs_ord cppownlibs_arr
    EXPORT cppownlibsTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT cppownlibsTargets
    NAMESPACE cppownlibs::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cppownlibs)
install(FILES cmake/cppownlibsConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cppownlibs)

if(CPPOWNLIBS_BUILD_TESTS)
    enable_testing()
    foreach(lib util conv ord arr)
        add_executable(test_${lib} tests/test_${lib}.cpp)
        target_link_libraries(test_${lib} PRIVATE cppownlibs::${lib})
        if(MSVC)
            target_compile_options(test_${lib} PRIVATE /W4)
        else()
            target_compile_options(test_${lib} PRIVATE -Wall -Wextra -Wpedantic)
        endif()
        add_test(NAME ${lib} COMMAND test_${lib})
    endforeach()
endif()
