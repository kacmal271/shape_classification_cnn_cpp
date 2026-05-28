#ifndef LAYER_H
#define LAYER_H

#include "Operation.h"
#include "BatchTensor.h"

///
/// \brief The Layer class manages the local gradient calculations
///
class Layer : public Operation
{
  protected:

    BatchTensor localGradients {};

  public:

    Layer();

    virtual void initialize() = 0;

    virtual BatchTensor forward() = 0;

    virtual BatchTensor backward() = 0;
};

#endif // LAYER_H
