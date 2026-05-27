#ifndef UNITTEST_H
#define UNITTEST_H

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

///
/// UnitTest

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
