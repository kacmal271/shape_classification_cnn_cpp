#include "TensorTest.h"

using namespace Testing;

//*****************************************************************************

void TensorTest::test()
{
  ConsoleInterface console;

  // testing: operator()

  console.log("*** testing: operator()");

  BatchTensor batch { std::vector<Tensor::NeuronType>(32, 0), {1, 4, 4, 2} };

  batch(0, 1, 2, 0) = 1;

  console.log(batch(0, 1, 2, 0));

  // testing: copyDepth

  console.log("*** testing: copyDepth");

  batch(0, 3, 3, 0) = 4;
  batch(0, 3, 3, 1) = 8;

  Tensor1D depth { batch.copySubspace(0, 3, 3) };

  console.log(depth[0], false);
  console.log(", ", false);
  console.log(depth[1]);

  // testing: transpose_width_depth (in debugger -> Locals)

  console.log("*** testing: transpose_width_depth");

  BatchTensor images { Tensor::vectorNeuronType {

                       1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,

                       13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,

                       100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200,

                       1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400

                     }, {2, 4, 3, 2} };

  console.log("before transposition (0, 4, 0, 1): ", false);
  console.log(images(0, 4, 0, 1));

  images.transpose_width_depth();

  console.log("after transposition (0, 4, 1, 0): ", false);
  console.log(images(0, 4, 1, 0));
}
