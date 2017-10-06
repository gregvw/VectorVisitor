#pragma once 

#include <iostream>

// Forward declarations
template<class> class StdVector;


union IndexType {
  // List of all possible index types we might use
  std::size_t stdvec;
};


template<class Real> 
class Element {
public:

  // One constructor per derived vector to allocate index variable
  Element( const StdVector<Real>& x ) { index.stdvec = 0; } 

  Real getNext( const StdVector<Real>& x ) { 
    Real value = x[index.stdvec];
    index.stdvec++; 
    return value; 
  }

private:

 IndexType index;

};
