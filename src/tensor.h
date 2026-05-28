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
    NeuronType const & operator[] (size_t index) const;

    virtual size_t size() const = 0;

    vectorNeuronType const & readValues() const;

    void fit(size_t & dimension,
             size_t tensor_dimension,
             size_t tensor_dimension_offset) const;

    vectorNeuronType::iterator begin();
    vectorNeuronType::iterator end();

    vectorNeuronType::const_iterator begin() const;
    vectorNeuronType::const_iterator end() const;

};

#endif // TENSOR_H
