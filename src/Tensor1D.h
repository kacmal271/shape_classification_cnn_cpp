#ifndef TENSOR1D_H
#define TENSOR1D_H

#include "Tensor.h"

class Tensor1D : public Tensor
{

  protected:

    size_t depth {};

  public:

    using Tensor::Tensor;
};

#endif // TENSOR1D_H
