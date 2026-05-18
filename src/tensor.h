#ifndef TENSOR_H
#define TENSOR_H

#include "./helper/declarations.h"

class Tensor
{
  private:

    size_t batchSize {};

    size_t height {};

    size_t width {};

    size_t depth {};

    std::vector<NeuronType> values {};

  public:

    Tensor(vectorNeuronType values,
           vectorSizeT dims);

    NeuronType & operator() (size_t bI, size_t hI, size_t wI, size_t dI);

    void reshape(size_t newBatchSize,
                 size_t newHeight,
                 size_t newWidth,
                 size_t newDepth);

    Tensor copyDepth(size_t batchIndex,
                     size_t heightIndex,
                     size_t widthIndex);

    void transpose_width_depth();

    //*****************************************************************************

    constexpr size_t plane_size()
    {
      return width * depth;
    }

    //*****************************************************************************

    constexpr size_t cube_size()
    {
      return height * plane_size();
    }

};

#endif // TENSOR_H
