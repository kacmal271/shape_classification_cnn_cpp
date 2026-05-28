#ifndef OPERATION_H
#define OPERATION_H

#include "./BatchTensor.h"

///
/// \brief The Operation class manages the input and output tensors
///
class Operation
{
  protected:

    BatchTensor input {};
    BatchTensor output {};

  public:

    Operation();
};

#endif // OPERATION_H
