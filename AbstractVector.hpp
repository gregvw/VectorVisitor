#pragma once

#include <memory>

template<class> class Element;

template<class... T> void ignore(T &&... ) {}

/* Interface class knows nothing about how 
   an element might be accessed. Only knows
   that there is something called an element.
*/

template <class Real>
class AbstractVector {
public:

  virtual ~AbstractVector() {}

  virtual void set( const AbstractVector &x ) = 0;

  virtual void plus( const AbstractVector &x ) = 0;

  virtual void scale( const Real alpha ) = 0;

  virtual Real dot( const AbstractVector &x ) const = 0;

  virtual std::unique_ptr<AbstractVector> clone() const = 0;

  virtual Real next( Element<Real>& element ) const {
    ignore(element);
    return Real(0); 
  } 

};


