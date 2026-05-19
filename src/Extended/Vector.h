#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

namespace Extended
{

  class Vector
  {
    public:

      template <typename T>
      using vectorConstIterator = std::vector<T>::const_iterator;

      //*****************************************************************************

      // STL iterators belong to ONE specific container instance
      //   sharing iterators between an object and its copy is UB
      //   watch for: copying as a function argument

      template <typename T>
      static void replace(std::vector<T> & target,
                          size_t start,
                          size_t end,
                          std::vector<T> const & replacement)
      {
        target.erase(target.begin() + start, target.begin() + end);

        target.insert(target.begin() + start,
                      replacement.begin(),
                      replacement.end());
      }
  };

} // namespace Extended

#endif // VECTOR_H
