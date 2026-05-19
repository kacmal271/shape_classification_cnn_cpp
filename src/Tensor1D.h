#ifndef TENSOR1D_H
#define TENSOR1D_H

#include "Tensor.h"

class Tensor1D : public Tensor
{

  protected:

    size_t depth {};

  public:

    Tensor1D(vectorNeuronType values, vectorSizeT dims);

    size_t size() const override;

    size_t copyDepth() const;
};

#endif // TENSOR1D_H
