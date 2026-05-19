#ifndef BATCHTENSOR_H
#define BATCHTENSOR_H

#include <memory>

#include "./Extended/Vector.h"
#include "./Tensor3D.h"

class BatchTensor : public Tensor3D
{
  protected:

    size_t batchSize {};

  public:

    BatchTensor(vectorNeuronType values, vectorSizeT dims);

    NeuronType & operator() (
      size_t batchIndex,
      size_t heightIndex,
      size_t widthIndex,
      size_t depthIndex);

    size_t size() const override;

    void transpose_width_depth() override;

    Tensor3D copySubspace(size_t batchIndex) const;

    Tensor2D copySubspace(size_t batchIndex,
                          size_t heightIndex) const;

    Tensor1D copySubspace(size_t batchIndex,
                          size_t heightIndex,
                          size_t widthIndex) const;

    size_t copyBatchSize() const;

    // = delete in child (when no longer makes sense)
    //   still accessible through reference/pointer
    //     GrandParent & gp = child
    //     gp.copyPlane()
    Tensor2D copyPlane(size_t heightIndex) const = delete;

    void pushCube(Tensor3D image);

    void reshape(size_t newBatchSize,
                 size_t newHeight,
                 size_t newWidth,
                 size_t newDepth);

  private:

    bool isCubeCompatible(Tensor3D const & cube) const;

};

#endif // BATCHTENSOR_H
