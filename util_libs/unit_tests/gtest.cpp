//------------------------------------------------------------------------------
/// \file   gtest.cpp
/// \date   Feb 15, 2012
/// \author dbardon
/// \brief
//------------------------------------------------------------------------------

#include <iostream>

#include "gtest/gtest.h"

#define ENABLE_TRACES

void testtraces( const char * str, va_list args )
{
#ifdef ENABLE_TRACES
  vprintf(str, args);
#endif
}

const unsigned gtestfilterlength = 512;
char gtestfilter[512];
int gtestargc;
char **gtestargv;

void defineNegativeFilter(int argc, char **argv, const char * expr)
{
    // Search for existing --gtest_filter
    bool hasGtestFilter = false;
    for(int i=0 ; i<argc ; i++)
        if(!strncmp("--gtest_filter", argv[i], 14))
            hasGtestFilter = true;

    // Define number of arguments
    gtestargc = hasGtestFilter ? argc : argc+1;
    gtestargv = new char * [gtestargc+1];
    printf("allocate %i\n", gtestargc);

    // Append to --gtest_filter parameter
    for(int i=0 ; i< argc ; i++)
    {
        if(!strncmp("--gtest_filter", argv[i], 14))
        {
            strncat(gtestfilter, argv[i], gtestfilterlength);
            strncat(gtestfilter, ":", gtestfilterlength);
            strncat(gtestfilter, expr, gtestfilterlength);
            gtestargv[i] = gtestfilter;
        }
        else
        {
            gtestargv[i] = argv[i];
        }
    }

    // If --gtest_filter parameter does not exist, create it
    if(!hasGtestFilter)
    {
        strncat(gtestfilter, "--gtest_filter=", gtestfilterlength);
        strncat(gtestfilter, expr, gtestfilterlength);
        gtestargv[gtestargc-1] = gtestfilter;
    }
}

GTEST_API_ int main(int argc, char **argv)
{
  std::cout << "Running CMC unit tests\n";

  testing::InitGoogleTest(&gtestargc, gtestargv);
  return RUN_ALL_TESTS();
}



