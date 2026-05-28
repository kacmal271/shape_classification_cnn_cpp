#include "TensorTest.h"

using namespace Testing;

//*****************************************************************************

bool TensorTest::test_operator_plus() const
{
  Tensor3D addend3D { tensor.copySubspace(0) };

  Tensor1D addend1D {
    { 10000, 20000 },
    { 2 }
  };

  Tensor3D sum { addend3D + addend1D };

  for (size_t h = 0; h < sum.copyHeight(); h++)
  {
    for (size_t w = 0; w < sum.copyWidth(); w++)
    {
      if (sum(h, w, 0) < 10000)
      {
        return true;
      }

      if (sum(h, w, 1) < 20000)
      {
        return true;
      }
    }
  }

  return false;
}

//*****************************************************************************

bool TensorTest::test_subcube() const
{
  Tensor3D subcube { tensor.copySubcube(0, 1, 2, 1, 2) };

  for (size_t d = 0; d < subcube.copyDepth(); d++)
  {
    Tensor1D depth { tensor.copySubspace(0, 1, 1) };

    if (depth[d] != subcube(0, 0, d))
    {
      return true;
    }
  }

  Tensor3D heightSubcube { tensor.copySubcube(0, 0, INT_MAX, 0, 2) };

  if (heightSubcube.copyHeight() != tensor.copyHeight())
  {
    return true;
  }

  return false;
}

//*****************************************************************************

bool TensorTest::test_pad() const
{
  BatchTensor unit { tensor };

  unit.pad(1, 999);

  if (unit.copyHeight() != tensor.copyHeight() + 2)
  {
    return true;
  }

  if (unit.copyWidth() != tensor.copyWidth() + 2)
  {
    return true;
  }

  for (size_t b = 0; b < unit.copyBatchSize(); b++)
  {
    for (size_t h = 0; h < unit.copyHeight(); h++)
    {
      if (0 < h && h < unit.copyHeight() - 1)
      {
        continue;
      }

      for (size_t w = 0; w < unit.copyWidth(); w++)
      {
        if (0 < w && w < unit.copyWidth() - 1)
        {
          continue;
        }

        for (size_t d = 0; d < unit.copyDepth(); d++)
        {
          if (unit(b, h, w, d) != 999)
          {
            return true;
          }
        }
      }
    }
  }

  return false;
}

//*****************************************************************************

bool TensorTest::test_operator_8() const
{
  Tensor2D left   { tensor.copySubspace(0, 0) };
  Tensor2D right  { tensor.copySubspace(0, 1) };

  // left and right have to be multipliable

  left.transpose_width_depth();

  Tensor2D activation { left * right };

  Tensor::NeuronType dotProduct
    {
      left(0, 0) * right(0, 0) +
      left(1, 0) * right(0, 1)
    };

  if (dotProduct != activation(0, 0))
  {
    return true;
  }

  return false;
}

//*****************************************************************************

bool TensorTest::test_transpose_width_depth() const
{
  BatchTensor unit { tensor };

  unit.transpose_width_depth();

  return tensor(0, 3, 0, 1) != unit(0, 3, 1, 0);
}

//*****************************************************************************

bool TensorTest::test_copy_subspace() const
{
  BatchTensor unit { tensor };

  unit(0, 3, 2, 0) = 4;
  unit(0, 3, 2, 1) = 8;

  Tensor1D depth { unit.copySubspace(0, 3, 2) };

  if (depth.size() != tensor.copyDepth())
  {
    return true;
  }

  if (depth(0) != 4)
  {
    return true;
  }

  if (depth(1) != 8)
  {
    return true;
  }

  return false;
}

//*****************************************************************************

bool TensorTest::test_operator_90() const
{
  BatchTensor unit { tensor };

  unit(0, 1, 2, 0) = 999999;

  return tensor(0, 1, 2, 0) == unit(0, 1, 2, 0);
}

//*****************************************************************************

void TensorTest::test()
{
  console.log("*** testing: class Tensor", true);

  console.log("testing: " + boolToFail(test_operator_90()) + "\t for: operator()");
  console.log("testing: " + boolToFail(test_copy_subspace()) + "\t for: copySubspace()");
  console.log("testing: " + boolToFail(test_transpose_width_depth()) + "\t for: transpose_width_depth()");
  console.log("testing: " + boolToFail(test_operator_8()) + "\t for: test_operator_8()");
  console.log("testing: " + boolToFail(test_pad()) + "\t for: test_pad()");
  console.log("testing: " + boolToFail(test_subcube()) + "\t for: test_subcube()");
  console.log("testing: " + boolToFail(test_operator_plus()) + "\t for: test_operator_plus()");

}
