#include "Tensor2D.h"

//*****************************************************************************

bool Tensor2D::isSubspace(size_t x, size_t width, size_t z, size_t depth) const
{
  return 0 <= x && x + width <= this->width &&
         Tensor1D::isSubspace(z, depth);
}

//*****************************************************************************

void Tensor2D::pushDepth(Tensor1D depth)
{
  if ( ! isDepthCompatible(depth))
  {
    throw 1;
  }

  values.insert(values.end(), depth.begin(), depth.end());

  width++;
}

//*****************************************************************************

Tensor2D Tensor2D::copySubplane(size_t x, size_t width,
                                size_t z, size_t depth) const
{
  if ( ! isSubspace(x, width, z, depth))
  {
    // [todo] throw std::out_of_range

    throw 1;
  }

  Tensor2D subplane {
    vectorNeuronType {},
    { 0, depth }
  };

  for (size_t w = 0; w < width; w++)
  {
    Tensor1D depth_tensor { copyDepth(x + w) };

    Tensor1D subdepth { depth_tensor.copySubdepth(z, depth) };

    subplane.pushDepth(subdepth);
  }

  return subplane;
}

//*****************************************************************************

void Tensor2D::pad(size_t count, NeuronType value)
{
  size_t width_padded { width + 2 * count };

  size_t size_padded { width_padded * depth };

  Tensor2D plane_padded
    {
      vectorNeuronType ( size_padded, value ),
      { width_padded, depth }
    };

  Extended::Vector::replace(
    plane_padded.values,
    depth * count, // depth * 1
    depth * count + values.size(),
    values);

  *this = plane_padded;
}

//*****************************************************************************

bool Tensor2D::isPlaneMultipliable(Tensor2D const & plane) const
{
  return width == plane.depth;
}

//*****************************************************************************

bool Tensor2D::isPlaneCompatible(Tensor2D const & plane) const
{
  // operator&& looks for -> 1st false and returns
  return plane.copyDepth() == depth &&
         plane.copyWidth() == width;
}

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
  if ( ! isPlaneMultipliable(right))
  {
    throw 1;
  }

  Tensor2D left { *this };

  Tensor2D activations {
    vectorNeuronType(right.width * left.depth, NeuronType {}),
    { right.width, left.depth}
  };

  // transposition -> makes -> multiplied vectors -> parallel to one another
  left.transpose_width_depth();

  for (size_t lw = 0; lw < left.width; lw++)
  {
    for (size_t rw = 0; rw < right.width; rw++)
    {
      Tensor1D leftDepth  { left  .copyDepth(lw) };
      Tensor1D rightDepth { right .copyDepth(rw) };

      NeuronType dotProduct { leftDepth.dot(rightDepth) };

      // lw -> depth OFFSET transposed into width
      // rw -> width OFFSET ( * depth transposed into width )
      activations[lw + rw * left.width] = dotProduct;
    }
  }

  return activations;
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
