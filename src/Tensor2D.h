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

    Tensor2D() = default;

    Tensor2D(vectorNeuronType values, vectorSizeT dims);

    ///
    /// \brief operator * Matrix multiplication
    ///
    /// Left matrix is parsed width-by-width
    ///
    /// -> first neuron is in front-top on the left
    ///
    /// -> second neuron is front-top to the right of the first
    ///
    /// Right matrix is parsed depth-by-depth
    ///
    /// \param right
    ///
    /// \return Tensor2D Result of matrix multiplication
    ///
    /// \note Matrices are horizontal planes (x-z)
    ///
    /// not vertical like we are used to in mathematics
    ///
    /// this is due to Tensorflow-indexing style: BHWD
    ///
    Tensor2D operator*(Tensor2D const & right) const;

    Tensor2D operator+(Tensor1D const & vector) const;

    NeuronType const& operator()(size_t widthIndex,
                                 size_t depthIndex,
                                 size_t offset = 0) const;

    NeuronType& operator()(size_t widthIndex,
                           size_t depthIndex,
                           size_t offset = 0);

    size_t size() const override;

    size_t copyWidth() const;

    bool isSubspace(size_t x, size_t width, size_t z, size_t depth) const;

    Tensor1D copyDepth(size_t widthIndex) const;

    Tensor2D copySubplane(size_t x, size_t width, size_t z, size_t depth) const;

    Tensor1D copySubdepth(size_t z, size_t depth) const = delete;

    Tensor::NeuronType dot(Tensor1D const & right) const = delete;

    virtual void transpose_width_depth();

    void replaceAt(size_t widthIndex, Tensor1D const & vector);

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
