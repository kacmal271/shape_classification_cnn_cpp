#ifndef TENSOR3D_H
#define TENSOR3D_H

#include "./Extended/Vector.h"
#include "./Tensor2D.h"

class Tensor3D : public Tensor2D
{

  protected:

    size_t height {};

  public:

    // visibility for: Tensor3D, BatchTensor
    using Tensor1D::copyDepth;

    Tensor3D(vectorNeuronType values, vectorSizeT dims);

    void transpose_width_depth() override;

    size_t size() const override;

    size_t copyHeight() const;

    Tensor2D copyPlane(size_t heightIndex) const;

    Tensor1D copyDepth(size_t widthIndex) const = delete;

    void reshape(size_t newHeight,
                 size_t newWidth,
                 size_t newDepth);
};

#endif // TENSOR3D_H
