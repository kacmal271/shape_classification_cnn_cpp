#ifndef FUNCTION_TEST_H
#define FUNCTION_TEST_H

#include "../QHelper/QConsoleInterface.h"
#include "../Testing/UnitTest.h"

inline void test(Testing::UnitTest *_test)
{
  try
  {

    _test->test();
  }
  catch (int ex)
  {
    if (ex == 2)
    {
      console.log("(!) SOME FEATURE IS NOT IMPLEMENTED");
    }
  }

  delete _test;
}

#endif // FUNCTION_TEST_H
