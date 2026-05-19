#ifndef TENSOR2D_H
#define TENSOR2D_H

#include "Tensor1D.h"

class Tensor2D : public Tensor1D
{

  protected:

    size_t width {};

  public:

    // visibility for: Tensor2D
    using Tensor1D::copyDepth;

    Tensor2D(vectorNeuronType values, vectorSizeT dims);

    Tensor2D operator* (Tensor2D const & right) const;

    size_t size() const override;

    Tensor1D copyDepth(size_t widthIndex) const;

    size_t copyWidth() const;

    virtual void transpose_width_depth();

    void reshape(size_t newWidth,
                 size_t newDepth);
};

#endif // TENSOR2D_H
