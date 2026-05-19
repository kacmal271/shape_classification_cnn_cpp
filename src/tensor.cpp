#include "Tensor.h"

//*****************************************************************************

Tensor::NeuronType & Tensor::operator[] (size_t index)
{
  if (index < 0 || index > values.size())
  {
    throw 1;
  }

  return values[index];
}

//*****************************************************************************

Tensor::vectorNeuronType const & Tensor::readValues() const
{
  return values;
}

//*****************************************************************************

Tensor::vectorNeuronType::iterator Tensor::begin()
{
  return values.begin();
}

//*****************************************************************************

Tensor::vectorNeuronType::iterator Tensor::end()
{
  return values.end();
}
