#include "Tensor1D.h"

//*****************************************************************************

size_t Tensor1D::size() const
{
  return depth;
}

//*****************************************************************************

Tensor1D::Tensor1D(vectorNeuronType values, vectorSizeT dims)
  : Tensor(values)
{
  if (dims.size() < 1)
  {
    throw 1;
  }

  depth = dims[dims.size() - 1];
}

//*****************************************************************************

size_t Tensor1D::copyDepth() const
{
  return depth;
}
