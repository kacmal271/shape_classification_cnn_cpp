#ifndef TENSOR_H
#define TENSOR_H

#include <vector>
#include <memory>

#include "./Helper/declarations.h"

class Tensor
{
  public:

    using NeuronType = int;

    using vectorNeuronType = std::vector<NeuronType>;

  protected:

    vectorNeuronType values {};

  public:

    Tensor(vectorNeuronType values) : values(values) {};

    // required by: std::unique_ptr
    // otherwise: undefined behavior
    virtual ~Tensor() = default;

    NeuronType & operator[] (size_t index);

    virtual size_t size() const = 0;

    vectorNeuronType const & readValues() const;

    vectorNeuronType::iterator begin();
    vectorNeuronType::iterator end();

};

#endif // TENSOR_H
