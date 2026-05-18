#include "tensor.h"

//*****************************************************************************

Tensor::Tensor(vectorNeuronType values,
               vectorSizeT dims)
  : values(values)
{
  if (dims.size() < 4)
  {
    // [todo]
    throw 1;
  }

  batchSize = dims.at(0);

  height = dims.at(1);

  width = dims.at(2);

  depth = dims.at(3);
};

//*****************************************************************************

NeuronType & Tensor::operator() (size_t bI, size_t hI, size_t wI, size_t dI)
{
  bI *= cube_size();
  hI *= plane_size();
  wI *= depth;

  return values[bI + hI + wI + dI];
}

//*****************************************************************************

// rule 1: dont delete values
// rule 2: assert values fit into new dims

void Tensor::reshape(
  size_t newBatchSize,
  size_t newHeight,
  size_t newWidth,
  size_t newDepth)
{
  size_t newSize { newBatchSize * newHeight * newWidth * newDepth };

  if (newSize != batchSize * cube_size())
  {
    // [todo]
    throw 2;
  }

  batchSize = newBatchSize;
  height = newHeight;
  width = newWidth;
  depth = newDepth;
}

//*****************************************************************************

Tensor Tensor::copyDepth(size_t batchIndex,
                         size_t heightIndex,
                         size_t widthIndex)
{
  vectorNeuronType depthVector {};

  using iteratorType = vectorNeuronType::iterator;

  size_t offsetBatch { batchIndex * cube_size() };
  size_t offsetHeight { heightIndex * plane_size() };
  size_t offsetWidth { widthIndex * depth };

  size_t offset = offsetBatch + offsetHeight + offsetWidth;

  iteratorType ite = values.begin() + offset;

  for (size_t i = 0; i < depth; i++)
  {
    depthVector.push_back(*(ite + i));
  }

  return Tensor { depthVector, { 1, 1, 1, depth } };
}

//*****************************************************************************

void Tensor::transpose_width_depth ()
{
  // copy this->values -> local_values
  // overwrite this->values

  // swap: [batch, height, width, depth]
  // into: [batch, height, depth, width]

  vectorNeuronType local_values {};

  size_t b, h, d, w;
  size_t b_offset, h_offset, w_offset;

  for (b = 0; b < batchSize; b++)
  {
    b_offset = b * cube_size();

    for (h = 0; h < height; h++)
    {
      h_offset = h * plane_size();

      for (d = 0; d < depth; d++)
      {
        for (w = 0; w < width; w++)
        {
          w_offset = w * depth;

          NeuronType next_rowfirst_neuron { values[
            b_offset + h_offset + w_offset + d
          ] };

          local_values.push_back(next_rowfirst_neuron);
        } // width
      } // depth
    } // height
  } // batch

  values = local_values;

  reshape(batchSize, height, depth, width);
}
