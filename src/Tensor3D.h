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

    Tensor3D copySubcube(size_t y, size_t height,
                         size_t x, size_t width,
                         size_t z = 0, size_t depth = -1) const;

    Tensor2D copyPlane(size_t heightIndex) const;

    Tensor2D createPlane(NeuronType value) const;

    bool isSubspace(size_t y, size_t height,
                    size_t x, size_t width,
                    size_t z, size_t depth) const;

    Tensor2D copySubplane(size_t x, size_t width,
                          size_t z, size_t depth) const = delete;

    Tensor1D copyDepth(size_t widthIndex) const = delete;

    void pad(size_t count, NeuronType value = NeuronType {});

    // alternative name: replaceAtWith
    void replaceAt(size_t heightIndex, Tensor2D const & plane);

  protected:

    bool isCubeCompatible(Tensor3D const & cube) const;

  private:

    void pushPlane(Tensor2D plane);

    void reshape(size_t newHeight,
                 size_t newWidth,
                 size_t newDepth);
};

#endif // TENSOR3D_H
