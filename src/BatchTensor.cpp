#include "BatchTensor.h"

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

  // (not: explicit) Tensor3D()
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

Tensor::NeuronType & BatchTensor::operator() (size_t batchIndex,
                                            size_t heightIndex,
                                            size_t widthIndex,
                                            size_t depthIndex)
{
  batchIndex  *= this->Tensor3D::size();
  heightIndex *= this->Tensor2D::size();
  widthIndex  *= this->Tensor1D::size();

  return values[batchIndex + heightIndex + widthIndex + depthIndex];
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

bool BatchTensor::isCubeCompatible(Tensor3D const & cube) const
{
  // operator&& looks for -> 1st false and returns
  return cube.copyDepth() == depth &&
         cube.copyWidth() == width &&
         cube.copyHeight() == height;
}

//*****************************************************************************

size_t BatchTensor::copyBatchSize() const
{
  return batchSize;
}
