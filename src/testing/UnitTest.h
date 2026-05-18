#ifndef UNITTEST_H
#define UNITTEST_H

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

///
/// UnitTest

#include "../ConsoleInterface.h"
#include "../helper/declarations.h"

namespace Testing
{
  class UnitTest
  {
    public:

      virtual void test() = 0;

      virtual ~UnitTest() = default;
  };
}

#endif // UNITTEST_H
