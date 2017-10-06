#pragma once

#include <memory>
#include <vector>

// Forward declarations
template<class> class AbstractVector;
template<class> class Element;

template<class Real>     
class StdVector : public AbstractVector<Real> {
public:

  using size_type = typename std::vector<Real>::size_type;

  // This class calls the Element function for the 
  // derived type
  Real next( Element<Real>& element ) const {
    return element.getNext(*this);  
  }

  StdVector( std::unique_ptr<std::vector<Real>> vec ) : 
    vec_( std::move(vec) ) {}

  virtual ~StdVector() {}

  void set( const AbstractVector<Real>& x ) {
    Element<Real> element(*this);
    for( size_type i=0; i<vec_->size(); ++i ) 
      (*vec_)[i] = x.next(element);  
  }

  void plus( const AbstractVector<Real>& x ) {
    Element<Real> element(*this);
    for( size_type i=0; i<vec_->size(); ++i ) 
      (*vec_)[i] += x.next(element);  
  }

  Real dot( const AbstractVector<Real>& x ) const {
    Element<Real> element(*this);
    Real result(0);
    for( size_type i=0; i<vec_->size(); ++i ) {  
      result += (*vec_)[i]*x.next(element);
    }
    return result;
  }
 
  void scale( Real alpha ) {
    for( auto &e : *vec_ ) e *= alpha;
  }

  std::unique_ptr<AbstractVector<Real>> clone() const {
    using namespace std;
    auto vec_clone = make_unique<vector<Real>>( vec_->size() );
    return move( make_unique<StdVector<Real>>( move(vec_clone) ) );
  }

  // Not in base class, but Element visitor let's us use them indirectly
  Real& operator[] ( size_type i ) { return (*vec_)[i]; }
  const Real& operator[] ( size_type i ) const { return (*vec_)[i]; }


private:

  std::unique_ptr<std::vector<Real>> vec_;
  
};


