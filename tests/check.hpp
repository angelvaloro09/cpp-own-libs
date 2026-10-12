#ifndef CPPOWNLIBS_TEST_CHECK_HPP
#define CPPOWNLIBS_TEST_CHECK_HPP

#include <cstdlib>
#include <iostream>

#define CHECK(cond)                                                              \
    do                                                                           \
    {                                                                            \
        if (!(cond))                                                             \
        {                                                                        \
            std::cerr << __FILE__ << ":" << __LINE__ << " CHECK failed: " #cond  \
                      << std::endl;                                              \
            std::exit(1);                                                        \
        }                                                                        \
    } while (0)

#define CHECK_THROWS(expr, exc)                                                  \
    do                                                                           \
    {                                                                            \
        bool thrown_ = false;                                                    \
        try                                                                      \
        {                                                                        \
            (void)(expr);                                                        \
        }                                                                        \
        catch (const exc &)                                                      \
        {                                                                        \
            thrown_ = true;                                                      \
        }                                                                        \
        CHECK(thrown_);                                                          \
    } while (0)

#endif
