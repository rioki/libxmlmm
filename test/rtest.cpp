
#include "rtest.h"

#include <vector>
#include <iostream>

namespace rtest
{
    std::vector<impl::Test*> tests;
    
    int run()
    {
        unsigned int failed = 0;
        for (unsigned int i = 0; i < tests.size(); i++)
        {
            try
            {
                tests[i]->run();
            }
            catch (impl::Failure& failure)
            {
                std::cerr << failure.file << "(" << failure.line << "): error: " << failure.msg << std::endl;
                failed++;
            }
            catch (std::exception& ex)
            {
                std::cerr << tests[i]->file << "(" << tests[i]->line << "): error: " << ex.what() << std::endl;
                failed++;
            }
            catch (...)
            {
                std::cerr << tests[i]->file << "(" << tests[i]->line << "): error: Test " << tests[i]->name << " crashed." << std::endl;
                failed++;
            }
        }
        
        unsigned int succeded = tests.size() - failed;
        std::cerr << succeded << " of " << tests.size() << " tests succeded." << std::endl;
                
        return failed == 0 ? 0 : -1;
    }

    namespace impl
    {
        Failure::Failure(const char* f, unsigned int l, const std::string& m)
        {
            file = f;
            line = l;
            msg  = m;
        }

        Test::Test(const char* n, const char* f, unsigned int l)
        {
            name = n;
            file = f;
            line = l;
            tests.push_back(this);
        }
    }
}
