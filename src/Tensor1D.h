#ifndef TENSOR1D_H
#define TENSOR1D_H

#include "Tensor.h"

class Tensor1D : public Tensor
{

  protected:

    size_t depth {};

  public:

    Tensor1D() = default;

    Tensor1D(vectorNeuronType values, vectorSizeT dims);

    Tensor1D operator+(Tensor1D const & vector) const;

    NeuronType const& operator()(size_t depthIndex,
                                 size_t offset = 0) const;

    NeuronType& operator()(size_t depthIndex,
                           size_t offset = 0);

    size_t size() const override;

    size_t copyDepth() const;

    Tensor::NeuronType dot(Tensor1D const & right) const;

    Tensor1D copySubdepth(size_t z, size_t depth) const;

    bool isSubspace(size_t z, size_t depth) const;

  protected:

    bool isDepthCompatible(Tensor1D const & depth) const;
};

#endif // TENSOR1D_H
