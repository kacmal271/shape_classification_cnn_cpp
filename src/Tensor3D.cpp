#include "Tensor3D.h"

//*****************************************************************************

void Tensor3D::reshape(size_t newHeight,
                       size_t newWidth,
                       size_t newDepth)
{
  size_t newSize { newHeight * newWidth * newDepth };

  if (newSize != values.size())
  {
    throw 1;
  }

  height = newHeight;
  width = newWidth;
  depth = newDepth;
}

//*****************************************************************************

Tensor2D Tensor3D::copyPlane(size_t heightIndex) const
{
  auto plane_size { this->Tensor2D::size() };

  vectorNeuronType values_local {
    values.begin() + (heightIndex * plane_size),
    values.begin() + (heightIndex * plane_size) + plane_size
  };

  return { Tensor2D { values_local, { width, depth } } };
}

//*****************************************************************************

size_t Tensor3D::size() const
{
  return height * this->Tensor2D::size();
}

//*****************************************************************************

Tensor3D::Tensor3D(vectorNeuronType values, vectorSizeT dims)
  : Tensor2D(values, dims)
{
  if (dims.size() < 3)
  {
    throw 1;
  }

  height = dims[dims.size() - 3];
}

//*****************************************************************************

void Tensor3D::transpose_width_depth()
{
  for (size_t h = 0; h < height; h++)
  {
    size_t plane_size { this->Tensor2D::size() };

    size_t h_offset = h * plane_size;

    vectorNeuronType::iterator start  { values.begin() + h_offset };
    vectorNeuronType::iterator end    { values.begin() + h_offset + plane_size };

    vectorNeuronType valuesSubset { start, end };

    Tensor2D plane { valuesSubset, { width, depth } };

    plane.transpose_width_depth();

    Extended::Vector::replace<NeuronType>(
      values, h_offset, h_offset + plane_size, plane.readValues()
      );
  }

  reshape(height, depth, width);
}

//*****************************************************************************

size_t Tensor3D::copyHeight() const
{
  return height;
}
