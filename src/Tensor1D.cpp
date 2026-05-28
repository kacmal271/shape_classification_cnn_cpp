#include "Tensor1D.h"

//*****************************************************************************

Tensor1D Tensor1D::operator+(Tensor1D const & vector) const
{
  if ( ! isDepthCompatible(vector))
  {
    throw 1;
  }

  Tensor1D incremented { *this };

  for (size_t z = 0; z < depth; z++)
  {
    incremented[z] += vector[z];
  }

  return incremented;
}

//*****************************************************************************

bool Tensor1D::isSubspace(size_t z, size_t depth) const
{
  return 0 <= z && z + depth <= this->depth;
}

//*****************************************************************************

Tensor1D Tensor1D::copySubdepth(size_t z, size_t depth) const
{
  if ( ! isSubspace(z, depth))
  {
    throw 1;
  }

  return {
    vectorNeuronType (values.begin() + z, values.begin() + z + depth),
    { depth }
  };
}

//*****************************************************************************

bool Tensor1D::isDepthCompatible(Tensor1D const & depth) const
{
  return this->depth == depth.depth;
}

//*****************************************************************************

Tensor::NeuronType Tensor1D::dot(Tensor1D const & right) const
{
  if ( ! isDepthCompatible(right))
  {
    throw 1;
  }

  NeuronType dotProduct {};

  for (size_t i = 0; i < values.size(); i++)
  {
    dotProduct += values[i] * right[i];
  }

  return dotProduct;
}

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
