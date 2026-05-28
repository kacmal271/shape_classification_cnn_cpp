#include "Tensor3D.h"

//*****************************************************************************

Tensor3D Tensor3D::operator+(Tensor1D const & vector) const
{
  if ( ! isDepthCompatible(vector))
  {
    throw 1;
  }

  Tensor3D incremented { *this };

  for (size_t y = 0; y < height; y++)
  {
    Tensor2D incremented_plane { copyPlane(y) + vector };

    incremented.replaceAt(y, incremented_plane);
  }

  return incremented;
}

//*****************************************************************************

bool Tensor3D::isSubspace(size_t y, size_t height,
                          size_t x, size_t width,
                          size_t z, size_t depth) const
{
  return 0 <= y && y + height <= this->height &&
         Tensor2D::isSubspace(x, width, z, depth);
}

//*****************************************************************************

Tensor3D Tensor3D::copySubcube(size_t y, size_t height,
                               size_t x, size_t width,
                               size_t z, size_t depth) const
{
  if ( ! isSubspace(y, height, x, width, z, depth))
  {
    // [todo] throw std::out_of_range

    throw 1;
  }

  Tensor3D subcube {
    vectorNeuronType {},
    { 0, width, depth }
  };

  for (size_t h = 0; h < height; h++)
  {
    Tensor2D plane { copyPlane(y + h) };

    Tensor2D subplane { plane.copySubplane(x, width, z, depth) };

    subcube.pushPlane(subplane);
  }

  return subcube;
}

//*****************************************************************************

void Tensor3D::replaceAt(size_t heightIndex, Tensor2D const & plane)
{
  if ( ! isPlaneCompatible(plane))
  {
    throw 2;
  }

  Extended::Vector::replace(
    values,
    heightIndex * Tensor2D::size(),
    heightIndex * Tensor2D::size() + Tensor2D::size(),
    plane.readValues());
}

//*****************************************************************************

Tensor2D Tensor3D::createPlane(NeuronType value) const
{
  size_t size_ { width * depth };

  return
    {
      vectorNeuronType ( size_, value ),
      { width, depth }
    };
}

//*****************************************************************************

void Tensor3D::pushPlane(Tensor2D plane)
{
  if ( ! isPlaneCompatible(plane))
  {
    throw 1;
  }

  values.insert(values.end(), plane.begin(), plane.end());

  height++;
}

//*****************************************************************************

void Tensor3D::pad(size_t count, NeuronType value)
{
  size_t height_padded  { height + 2 * count };
  size_t width_padded   { width + 2 * count };

  size_t size_padded { height_padded * width_padded * depth };

  Tensor3D cube_padded
    {
      vectorNeuronType ( size_padded, value ),
      { height_padded, width_padded, depth }
    };

  for (size_t h = 0; h < height; h++)
  {
    Tensor2D plane { copyPlane(h) };

    plane.pad(count, value);

    cube_padded.replaceAt(h + count, plane);
  }

  *this = cube_padded;
}

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

bool Tensor3D::isCubeCompatible(Tensor3D const & cube) const
{
  // operator&& looks for -> 1st false and returns
  return cube.copyDepth() == depth &&
         cube.copyWidth() == width &&
         cube.copyHeight() == height;
}

//*****************************************************************************

size_t Tensor3D::copyHeight() const
{
  return height;
}
