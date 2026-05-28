#include "Tensor.h"

//*****************************************************************************

Tensor::vectorNeuronType::const_iterator Tensor::begin() const
{
  return values.cbegin();
}

//*****************************************************************************

Tensor::vectorNeuronType::const_iterator Tensor::end() const
{
  return values.cend();
}

//*****************************************************************************

void Tensor::fit(size_t & dimension,
                 size_t tensor_dimension,
                 size_t tensor_dimension_offset) const
{
  // 5 - 1 = 4
  size_t max_value { tensor_dimension - tensor_dimension_offset };

  // 3 > 4
  if (dimension > max_value)
  {
    dimension = max_value;
  }

  // 3
}

//*****************************************************************************

Tensor::NeuronType const & Tensor::operator[] (size_t index) const
{
  if (index < 0 || index > values.size())
  {
    throw 1;
  }

  return values[index];
}

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
