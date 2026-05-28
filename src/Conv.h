#ifndef CONV_H
#define CONV_H

#include "Layer.h"

class Conv : public Layer
{
  protected:

    BatchTensor filters {};

    int step_size { 1 };

    int filter_size { 3 };

    int padding_size { 1 };

    int filters_count { 1 };

  public:

    Conv();

    void convolve();

};

#endif // CONV_H
