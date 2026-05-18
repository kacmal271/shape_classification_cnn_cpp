#ifndef FUNCTION_TEST_H
#define FUNCTION_TEST_H

#include "../testing/UnitTest.h"

inline void test(Testing::UnitTest *_test)
{
  _test->test();

  delete _test;
}

#endif // FUNCTION_TEST_H
