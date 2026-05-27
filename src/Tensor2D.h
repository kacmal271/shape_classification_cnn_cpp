#ifndef TENSOR2D_H
#define TENSOR2D_H

#include "./Tensor1D.h"
#include "./Extended/Vector.h"

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

    Tensor2D copySubplane(size_t x, size_t width, size_t z, size_t depth) const;

    bool isSubspace(size_t x, size_t width, size_t z, size_t depth) const;

    Tensor1D copySubdepth(size_t z, size_t depth) const = delete;

    Tensor::NeuronType dot(Tensor1D const & right) const = delete;

    virtual void transpose_width_depth();

    void pad(size_t count, NeuronType value = NeuronType {});

  protected:

    bool isPlaneCompatible(Tensor2D const & plane) const;

  private:

    bool isPlaneMultipliable(Tensor2D const & plane) const;

    void pushDepth(Tensor1D depth);

    void reshape(size_t newWidth,
                 size_t newDepth);
};

#endif // TENSOR2D_H
