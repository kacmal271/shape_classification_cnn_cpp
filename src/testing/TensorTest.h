#ifndef TENSORTEST_H
#define TENSORTEST_H

#include "./UnitTest.h"
#include "../tensor.h"

namespace Testing
{

  class TensorTest : public UnitTest
  {
    public:

      TensorTest() = default;

      void test() override;
  };

} // namespace Testing

#endif // TENSORTEST_H
