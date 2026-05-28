#include "TensorTest.h"

using namespace Testing;

//*****************************************************************************

void TensorTest::test()
{
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

  console.log(std::to_string(depth[0]) + ", " + std::to_string(depth[1]));

  // testing: transpose_width_depth (in debugger -> Locals)

  console.log("*** testing: transpose_width_depth", true);

  BatchTensor images {  Tensor::vectorNeuronType {

                        1, 2,    3, 4,     5, 6,
                        7, 8,    9, 10,    11, 12,
                        13, 14,  15, 16,   17, 18,
                        19, 20,  21, 22,   23, 24,

                        100, 200,    300, 400,     500, 600,
                        700, 800,    900, 1000,    1100, 1200,
                        1300, 1400,  1500, 1600,   1700, 1800,
                        1900, 2000,  2100, 2200,   2300, 2400

                      }, { 2, 4, 3, 2 } };

  console.log("before transposition (0, 3, 0, 1): " +
              std::to_string(images(0, 3, 0, 1)));

  images.transpose_width_depth();

  console.log("after transposition (0, 3, 1, 0): " +
              std::to_string(images(0, 3, 1, 0)));

  console.log("*** matrix multiplication", true);

  Tensor2D left   { images.copySubspace(0, 0) };
  Tensor2D right  { images.copySubspace(0, 1) };

  // left and right have to be multipliable
  right.transpose_width_depth();

  Tensor2D activation { left * right };

  console.log("first dot product of images(0, 0) and images(0, 1)");
  console.log("we assume it is an example input tensor * filters");
  console.log(std::to_string(left[0]) + " * " +
              std::to_string(right[0]) + " + " +
              std::to_string(left[3])  + " * " +
              std::to_string(right[2]) + " = " +
              std::to_string(activation[0]));

  // reshaping back into Tensor3D

  size_t dimension { static_cast<size_t>(std::sqrt(activation.copyWidth())) };

  Tensor3D activation_image {
    activation.readValues(),
    { dimension, dimension, activation.copyDepth() }
  };

  console.log("plane matrix is reshaped back into a 3D activation tensor");
  console.log("of dimensions: (" + std::to_string(activation_image.copyHeight()) +
              ", " + std::to_string(activation_image.copyWidth()) +
              ", " + std::to_string(activation_image.copyDepth()) +
              ")");

  // testing: BatchTensor::pad -> cascades Tensor3D::pad -> Tensor2D

  console.log("**** BatchTensor::pad", true);

  BatchTensor two_images  { Tensor::vectorNeuronType {

                            1, 2,    3, 4,     5, 6,
                            7, 8,    9, 10,    11, 12,
                            13, 14,  15, 16,   17, 18,

                            100, 200,    300, 400,     500, 600,
                            700, 800,    900, 1000,    1100, 1200,
                            1300, 1400,  1500, 1600,   1700, 1800

                          }, {2, 3, 3, 2} };

  two_images.pad(1);

  console.log("First few pixels:");

  for (int i = 0; i < 2; i++)
  {
    console.log("two_images(0, 0, 0, " + std::to_string(i) +
                "): " + std::to_string(two_images(0, 0, 0, i)));
  }

  for (int i = 0; i < 2; i++)
  {
    console.log("two_images(0, 0, 1, " + std::to_string(i) +
                "): " + std::to_string(two_images(0, 0, 1, i)));
  }

  for (int i = 0; i < 2; i++)
  {
    console.log("two_images(0, 1, 1, " + std::to_string(i) +
                "): " + std::to_string(two_images(0, 1, 1, i)));
  }

  // testing: Tensor3D::subcube

  console.log("**** BatchTensor::copySubcube", true);

  Tensor3D first { two_images.copySubcube(0, 0, 3, 0, 3) };

  console.log("copySubcube(0, 0, 3, 0, 3) -> first depth:");

  for (int i = 0; i < first.copyDepth(); i++)
  {
    console.log(first.readValues()[i]);
  }

  Tensor3D second { two_images.copySubcube(0, 1, 2, 1, 2) };

  console.log("copySubcube(0, 1, 2, 1, 2) -> second depth:");

  for (int i = 0; i < second.copyDepth(); i++)
  {
    console.log(second.readValues()[i]);
  }

  // try
  // {
  //   console.log("copySubcube(0, INT_MAX, 2, 0, 2) -> first depth:");
  //   two_images.copySubcube(0, INT_MAX, 2, 0, 2);
  // }
  // catch (int ex)
  // {
  //   console.log("caught exception for cube overflow");
  // }

  // testing: Tensor3D::operator+(Vector1)

  console.log("**** Tensor3D::operator+(Vector1)", true);

  Tensor3D addend3D { {

                      1, 2, 3, 4, 5, 6,

                      7, 8, 9, 10, 11, 12

                    }, { 2, 3, 2 } };

  Tensor1D addend1D { { 1, 100 }, { 2 } };

  Tensor3D sum { addend3D + addend1D };

  console.log("addend3D + addend1D (first two depths):");

  console.log(

    std::to_string(sum[0]) + ", " +
    std::to_string(sum[1]) + ", " +
    std::to_string(sum[2]) + ", " +
    std::to_string(sum[3])
    );

}
