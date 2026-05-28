#ifndef UNITTEST_H
#define UNITTEST_H

#include <string>

namespace Testing
{
  class UnitTest
  {
    public:

      virtual void test() = 0;

      virtual ~UnitTest() = default;

      std::string boolToFail(bool isFail);
  };
}

#endif // UNITTEST_H
