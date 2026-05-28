#include "BatchTensor.h"

//*****************************************************************************

Tensor3D BatchTensor::copySubcube(size_t batchIndex,
                                  size_t y, size_t height,
                                  size_t x, size_t width,
                                  size_t z, size_t depth) const
{
  // what, max, offset
  fit(height, this->height, y);
  fit(width , this->width , x);
  fit(depth , this->depth , z);

  Tensor3D cube { copySubspace(batchIndex) };

  return cube.copySubcube(y, height, x, width, z, depth);
}

//*****************************************************************************

void BatchTensor::pad(size_t count, NeuronType value)
{
  size_t height_padded { height + 2 * count };
  size_t width_padded  { width + 2 * count };

  BatchTensor batch_padded {
    vectorNeuronType {},
    { 0, height_padded, width_padded, depth }
  };

  for (size_t b = 0; b < batchSize; b++)
  {
    Tensor3D cube { copySubspace(b) };

    cube.pad(count, value);

    batch_padded.pushCube(cube);
  }

  *this = batch_padded;
}

//*****************************************************************************

size_t BatchTensor::size() const
{
  return batchSize * this->Tensor3D::size();
}

//*****************************************************************************

Tensor3D BatchTensor::copySubspace(size_t batchIndex) const
{
  auto cube_size { this->Tensor3D::size() };

  vectorNeuronType values_local {
    values.begin() + (batchIndex * cube_size),
    values.begin() + (batchIndex * cube_size) + cube_size
  };

  // (not: explici5) Tensor3D()
  return { Tensor3D { values_local, { height, width, depth } } };
}

//*****************************************************************************

Tensor2D BatchTensor::copySubspace(size_t batchIndex,
                                   size_t heightIndex) const
{
  Tensor3D && cube { std::move(copySubspace(batchIndex)) };

  return cube.copyPlane(heightIndex);
}

//*****************************************************************************

Tensor1D BatchTensor::copySubspace(size_t batchIndex,
                                   size_t heightIndex,
                                   size_t widthIndex) const
{
  Tensor2D && plane { std::move(copySubspace(batchIndex, heightIndex)) };

  return plane.copyDepth(widthIndex);
}

//*****************************************************************************

BatchTensor::BatchTensor(vectorNeuronType values, vectorSizeT dims)
  : Tensor3D(values, dims)
{
  if (dims.size() < 4)
  {
    throw 1;
  }

  batchSize = dims[dims.size() - 4];
}

//*****************************************************************************

Tensor::NeuronType const& BatchTensor::operator()(size_t batchIndex,
                                                  size_t heightIndex,
                                                  size_t widthIndex,
                                                  size_t depthIndex) const
{
  if (batchIndex >= batchSize)
  {
    throw 1;
  }

  batchIndex *= Tensor3D::size();

  return Tensor3D::operator()(batchIndex + heightIndex, widthIndex, depthIndex);
}

//*****************************************************************************

Tensor::NeuronType& BatchTensor::operator()(size_t batchIndex,
                                            size_t heightIndex,
                                            size_t widthIndex,
                                            size_t depthIndex)
{
  if (batchIndex >= batchSize)
  {
    throw 1;
  }

  batchIndex *= Tensor3D::size();

  return Tensor3D::operator()(heightIndex, widthIndex, depthIndex, batchIndex);
}

//*****************************************************************************

void BatchTensor::pushCube(Tensor3D image)
{
  if ( ! isCubeCompatible(image))
  {
    throw 1;
  }

  values.insert(values.end(), image.begin(), image.end());

  batchSize++;
}

//*****************************************************************************

void BatchTensor::reshape(size_t newBatchSize,
                          size_t newHeight,
                          size_t newWidth,
                          size_t newDepth)
{
  size_t newSize { newBatchSize * newHeight * newWidth * newDepth };

  if (newSize != values.size())
  {
    throw 1;
  }

  batchSize = newBatchSize;
  height = newHeight;
  width = newWidth;
  depth = newDepth;
}

//*****************************************************************************

void BatchTensor::transpose_width_depth()
{
  // swap: [batch, height, width, depth]
  // into: [batch, height, depth, width]

  for (size_t b = 0; b < batchSize; b++)
  {
    size_t cube_size { this->Tensor3D::size() };

    size_t b_offset = b * cube_size;

    vectorNeuronType::iterator start  { values.begin() + b_offset };
    vectorNeuronType::iterator end    { values.begin() + b_offset + cube_size };

    vectorNeuronType valuesSubset { start, end };

    Tensor3D image { valuesSubset, { height, width, depth } };

    image.transpose_width_depth();

    Extended::Vector::replace<NeuronType>(
      values, b_offset, b_offset + cube_size, image.readValues()
      );
  }

  reshape(batchSize, height, depth, width);
}


//*****************************************************************************

size_t BatchTensor::copyBatchSize() const
{
  return batchSize;
}
