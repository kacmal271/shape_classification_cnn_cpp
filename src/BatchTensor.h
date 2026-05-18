#ifndef BATCHTENSOR_H
#define BATCHTENSOR_H

#include "Tensor.h"

class BatchTensor : public Tensor3D
{
  protected:

    size_t batchSize {};

};

#endif // BATCHTENSOR_H
