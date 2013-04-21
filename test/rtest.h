
#ifndef _RTEST_H_
#define _RTEST_H_

#include <stdexcept>
#include <sstream>
#include <cmath>

namespace rtest
{
    int run();

    namespace impl
    {
        struct Failure
        {
            const char*  file;
            unsigned int line;
            std::string  msg;

            Failure(const char* file, unsigned int line, const std::string& msg);
        };

        struct Test 
        {
            const char*  name;
            const char*  file;
            unsigned int line;

            Test(const char* name, const char* file, unsigned int line);

            virtual void run() = 0;
        };
    }
}

#define SUITE(NAME) namespace NAME ## _suite

#define TEST(NAME)                                                                                 \
    struct Test_ ## NAME : public ::rtest::impl::Test                                              \
    {                                                                                              \
        Test_ ## NAME()                                                                            \
        : Test(#NAME, __FILE__, __LINE__) {}                                                       \
                                                                                                   \
        void run();                                                                                \
                                                                                                   \
    } test_ ## NAME;                                                                               \
                                                                                                   \
    void Test_ ## NAME ::run()                                                                     
                                                                                                   
#define TEST_FIXTURE(FIXTURE, NAME)                                                                \
    struct Helper_ ## NAME : public FIXTURE                                                        \
    {                                                                                              \
        void run();                                                                                \
    };                                                                                             \
                                                                                                   \
    struct Test_ ## NAME : public ::rtest::impl::Test                                              \
    {                                                                                              \
        Test_ ## NAME()                                                                            \
        : Test(#NAME, __FILE__, __LINE__) {}                                                       \
                                                                                                   \
        void run()                                                                                 \
        {                                                                                          \
            Helper_ ## NAME fixture;                                                               \
            fixture.run();                                                                         \
        }                                                                                          \
    } test_ ## NAME;                                                                               \
                                                                                                   \
    void Helper_ ## NAME ::run()

#define CHECK(COND)                                                                                \
    if (!(COND))                                                                                   \
    {                                                                                              \
        throw ::rtest::impl::Failure(__FILE__, __LINE__, #COND " failed.");                        \
    }

#define CHECK_EQUAL(A, B)                                                                          \
    if (! (A == B))                                                                                \
    {                                                                                              \
        std::stringstream buff;                                                                    \
        buff << "Expected " << A << " but got " << B << ".";                                       \
        throw ::rtest::impl::Failure(__FILE__, __LINE__, buff.str());                              \
    }

#define CHECK_CLOSE(A, B, EPS)                                                                     \
    if (std::abs(A - B) < EPS)                                                                     \
    {                                                                                              \
        std::stringstream buff;                                                                    \
        buff << "Expected " << A << " +- " << EPS << " but got " << B << ".";                      \
        throw ::rtest::impl::Failure(__FILE__, __LINE__, buff.str());                              \
    }

#define CHECK_THROW(EXPR, OBJ)                                                                     \
    try                                                                                            \
    {                                                                                              \
        EXPR;                                                                                      \
        throw ::rtest::impl::Failure(__FILE__, __LINE__, "'" #EXPR "' did not throw '" #OBJ "'."); \
    }                                                                                              \
    catch (OBJ)                                                                                    \
    {                                                                                              \
        /* OK */                                                                                   \
    }


#endif
