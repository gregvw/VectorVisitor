#include <iostream>
#include <cmath>

#include "AbstractVector.hpp"
#include "StdVector.hpp"
#include "ElementAccessor.hpp"

int main( int argc, char *argv[] ) {

  using namespace std;
  using RealT = double;

  size_t dim(3);

  // Make a unique pointer to a std::vector<double> called xp
  auto x_up = make_unique<vector<RealT>>(dim); 
  auto y_up = make_unique<vector<RealT>>(dim);  
  auto z_up = make_unique<vector<RealT>>(dim);  

  (*x_up)[0] = 1.0;  (*y_up)[0] = 10.0;   
  (*x_up)[1] = 2.0;  (*y_up)[1] = -2.5;
  (*x_up)[2] = 3.0;  (*y_up)[2] =  4.0;

  // xp is now owned by x. We are not allowed to do anything further with it 
  // inside this scope, without implementing a deleter for x that releases
  // ownership
  StdVector<RealT> x(move(x_up));
  StdVector<RealT> y(move(y_up));

  auto q1 = x.clone();
  auto q2 = x.clone();
  auto temp = x.clone();

  // First orthogonal basis vector
  q1->set(x);
  q1->scale(1./sqrt(x.dot(x)));

  q2->set(*q1);
  q2->scale( -q1->dot(y) );
  q2->plus(y);
  q2->scale( 1./sqrt(q2->dot(*q2) ) );

  auto z = x.clone();
  z->set(y);
  z->plus(x);
  z->plus(x);

  RealT c1 = z->dot(*q1);
  RealT c2 = z->dot(*q2);

  auto z1 = z->clone();
  z1->set(*q1);
  z1->scale(-c1);

  auto z2 = z->clone();
  z2->set(*q2);
  z2->scale(-c2);

  cout << "Applying the Visitor Design Pattern to"  << endl;
  cout << "vector inheritance                    "  << endl;
  cout << "                                      "  << endl;
  cout << "Test of orthogonal decomposition      "  << endl;
  cout << "span(q1,q2) = span(x,y)               "  << endl;
  cout << "                                      "  << endl;
  cout << "z            = 2x+y                   "  << endl;
  cout << "||z||        = "  << sqrt(z->dot(*z))    << endl;
  cout << "(z,q1)       = "  << c1                  << endl;
  cout << "(z,q2)       = "  << c2                  << endl;
  cout << "z1           = (z,q1)q1               "  << endl;
  cout << "z2           = (z,q2)q2               "  << endl;
    
  z->plus(*z1);
  z->plus(*z2);
  cout << "||z-z1-z2||  = "   << sqrt(z->dot(*z)) << endl;

  return 0;
}

