#include "UnitTest.h"

using namespace Testing;

//*****************************************************************************

std::string UnitTest::boolToFail(bool isFailed)
{
  return isFailed ? "failed" : "success";
}
