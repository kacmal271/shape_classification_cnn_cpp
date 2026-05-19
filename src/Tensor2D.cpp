#include "Tensor2D.h"

//*****************************************************************************

void Tensor2D::reshape(size_t newWidth,
                       size_t newDepth)
{
  size_t newSize { newWidth * newDepth };

  if (newSize != values.size())
  {
    throw 1;
  }

  width = newWidth;
  depth = newDepth;
}

//*****************************************************************************

void Tensor2D::transpose_width_depth()
{
  vectorNeuronType local_values {};

  for (size_t d = 0; d < depth; d++)
  {
    for (size_t w = 0; w < width; w++)
    {
      size_t w_offset = w * depth;

      NeuronType rowfirst_neuron { values[w_offset + d] };

      local_values.push_back(rowfirst_neuron);
    } // width
  } // depth

  // changing bytes layout
  values = local_values;

  // gotta change addressing
  reshape(depth, width);
}

//*****************************************************************************

Tensor1D Tensor2D::copyDepth(size_t widthIndex) const
{
  vectorNeuronType values_local {
    values.begin() + (widthIndex * depth),
    values.begin() + (widthIndex * depth) + depth
  };

  return { Tensor1D { values_local, { depth } } };
}

//*****************************************************************************

size_t Tensor2D::size() const
{
  return width * this->Tensor1D::size();
}

//*****************************************************************************

Tensor2D Tensor2D::operator* (Tensor2D const & right) const
{
  // matrix multiplication

  return *this;
}

//*****************************************************************************

Tensor2D::Tensor2D(vectorNeuronType values, vectorSizeT dims)
  : Tensor1D(values, dims)
{
  if (dims.size() < 2)
  {
    throw 1;
  }

  width = dims[dims.size() - 2];
}

//*****************************************************************************

size_t Tensor2D::copyWidth() const
{
  return width;
}
