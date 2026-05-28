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
    switch (ex)
    {
      case 2:

        console.log("(!) SOME FEATURE IS NOT IMPLEMENTED");
        break;

      case 1:

        console.log("(!) LOGIC ERROR");
        break;

    }

    delete _test;
  }

  delete _test;
}

#endif // FUNCTION_TEST_H
