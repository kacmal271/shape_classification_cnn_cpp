#ifndef TENSORTEST_H
#define TENSORTEST_H

#include "./UnitTest.h"
#include "../BatchTensor.h"
#include "../QHelper/QConsoleInterface.h"

namespace Testing
{
  ///
  /// \brief The TensorTest class
  ///
  /// functions are in the "negative" logic
  ///
  /// returning true -> means test failed
  ///
  class TensorTest : public UnitTest
  {
    private:

      BatchTensor tensor {  Tensor::vectorNeuronType {

                            1   , 2   , 3   , 4   , 5   , 6   , 7   , 8   ,
                            9   , 10  , 11  , 12  , 13  , 14  , 15  , 16  ,
                            17  , 18  , 19  , 20  , 21  , 22  , 23  , 24  ,
                            25  , 26  , 27  , 28  , 29  , 30  , 31  , 32  ,

                            100 , 200 , 300 , 400 , 500 , 600 , 700 , 800 ,
                            900 , 1000, 1100, 1200, 1300, 1400, 1500, 1600,
                            1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400,
                            2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200,

                            // square images
                          }, { 2, 4, 4, 2 } };

    public:

      TensorTest() = default;

      void test() override;

      ///
      /// \brief test_operator_90
      /// \return bool Flag to indicate if the test failed
      ///
      bool test_operator_90() const;

      bool test_copy_subspace() const;

      bool test_transpose_width_depth() const;

      bool test_operator_8() const;

      bool test_pad() const;

      bool test_subcube() const;

      bool test_operator_plus() const;

  };

} // namespace Testing

#endif // TENSORTEST_H
