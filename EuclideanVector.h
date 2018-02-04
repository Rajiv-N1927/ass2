#include <stdlib.h>
#include <vector>
#include <list>
#include <initializer_list>
#include <cmath>

//namespace evec {
  class EuclideanVector {

  public:
    //Default constructor
    EuclideanVector() : dimension(1) {
      vec = new double{0.0};
    }
    //Main constructor
    EuclideanVector(int dim) {
      vec = new double[dim];
      dimension = dim;
      setVal(0.0);
    }
    //Delegates main constructor, sets dimension and initial values
    EuclideanVector(int dim, double init) : EuclideanVector(dim) {
      setVal(init);
    }
    /*Delegates main constructor, sets dimension and values for initialization
    list*/
    EuclideanVector(std::initializer_list<double> arr) :
      EuclideanVector(arr.size()) {
      setVal(arr);
    }
    //Generic iterator type
    template<typename T>
    EuclideanVector(T beg, T end) {
      int dim = 0, a = 0;
      for ( auto t = beg; t != end; t++, dim++ );
      vec = new double[dim];
      dimension = dim;
      for ( auto t = beg; t != end; t++, a++) {
        this->vec[a] = *t;
      }
    }

    //Move Constructor
    EuclideanVector(EuclideanVector&& e) : dimension(e.dimension), norm(e.norm)
    {
      std::cout << "Move constructor called" << std::endl;
      this->vec = new double[this->dimension];
      for ( int a = 0; a < this->dimension; a++ ) {
        this->vec[a] = e.vec[a];
      }
      e.vec = nullptr;
      e.dimension = 0;
      e.norm = 0;
    }

    //Copy Constructor
    EuclideanVector(const EuclideanVector& e) :
      dimension(e.dimension), norm(e.norm)
    {
      std::cout << "Copy called" << std::endl;
      this->vec = new double[this->dimension];
      for ( int a = 0; a < this->dimension; a++ ) {
        this->vec[a] = e.vec[a];
      }
    }

    //destructor
    ~EuclideanVector() {
      if ( vec ) {
        delete[] vec;
      }
      this->dimension = 0;
      this->norm = 0;
    }

    //Overload operators
    //Copy assignment operator
    EuclideanVector& operator=(const EuclideanVector &vecother) {
      if ( this != &vecother ) {
        if ( this->vec ) delete [] this->vec;
        this->vec = vecother.vec;
        this->dimension = vecother.dimension;
        this->norm = vecother.norm;
      }
      return *this;
    }
    //Move assignment operator
    EuclideanVector& operator=(EuclideanVector &&vecother) {
      if ( this != &vecother ) {
        std::cout << "Move assignment operator called" << std::endl;
        if ( this->vec ) delete[] this->vec;
        this->vec = vecother.vec;
        this->dimension = vecother.dimension;
        vecother.vec = nullptr;
        vecother.dimension = 0;
        vecother.norm = 0;

      }
      return *this;
    }
    //Overloaded Operations
    // e.g. a+=b
    EuclideanVector& operator+=(const EuclideanVector& eVec) {
      this->norm = 0;
      if ( eVec.dimension == this->dimension ) {
        for ( int a = 0; a < this->dimension; a++ ) {
          this->vec[a] += eVec.vec[a];
        }
      }
      return *this;
    }
    // e.g. a-=b
    EuclideanVector& operator-=(const EuclideanVector& eVec) {
      this->norm = 0;
      if ( eVec.dimension == this->dimension ) {
        for ( int a = 0; a < this->dimension; a++ ) {
          this->vec[a] -= eVec.vec[a];
        }
      }
      return *this;
    }
    // e.g. a*=b
    EuclideanVector& operator*=(double scalar) {
      this->norm = 0;
      for ( int a = 0; a < this->dimension; a++ ) {
        this->vec[a] *= scalar;
      }
      return *this;
    }
    // e.g. a/=b
    EuclideanVector& operator/=(double scalar) {
      this->norm = 0;
      for ( int a = 0; a < this->dimension; a++ ) {
        this->vec[a] /= scalar;
      }
      return *this;
    }
    //get and set values
    double& operator[](int pos) {
      this->norm = 0;
      return this->vec[pos];
    }

    //Nonmember functions

    //----------------bool statement-------------//
      bool& operator==(const EuclideanVector& eVec) {
        bool toret = true;
        bool *tof = &toret;
        if ( this->dimension == eVec.dimension ) {
          for ( int a = 0; a < this->dimension; a++ ) {
            if ( this->vec[a] != eVec.vec[a] ) {
              *tof = false;
              break;
            }
          }
        } else *tof = false;

        return *tof;
      }

      bool& operator!=(const EuclideanVector& eVec) {
        bool toret = false;
        bool *tof = &toret;
        if ( this->dimension == eVec.dimension ) {
          for ( int a = 0; a < this->dimension; a++ ) {
            if ( this->vec[a] != eVec.vec[a] ) {
              *tof = true;
              break;
            }
          }
        } else *tof = true;

        return *tof;
      }

    //------------ADDING vectors-----------//
    EuclideanVector& operator+(const EuclideanVector& eVec) {
      EuclideanVector *toRet;
      if ( eVec.dimension == this->dimension ) {
        toRet = new EuclideanVector(this->dimension);
        for ( int a = 0; a < this->dimension; a++ ) {
          toRet->vec[a] = this->vec[a] + eVec.vec[a];
        }
      }
      return *toRet;
    }
    //---------Subtracting vectors-------//
    EuclideanVector& operator-(const EuclideanVector& eVec) {
      EuclideanVector *toRet;
      if ( eVec.dimension == this->dimension ) {
        toRet = new EuclideanVector(this->dimension);
        for ( int a = 0; a < this->dimension; a++ ) {
          toRet->vec[a] = this->vec[a] - eVec.vec[a];
        }
      }  else toRet = nullptr;
      return *toRet;
    }
    //----------------Dot product---------------//
      double& operator*(const EuclideanVector& eVec) {
      double val = 0;
      double *dotprod = &val;
      if ( eVec.dimension == this->dimension ) {
        for ( int a = 0; a < this->dimension; a++ ) {
          *dotprod += (this->vec[a] * eVec.vec[a]);
        }
      }
      return *dotprod;
    }

    //--------------Scalar Multiplication-------------//
    EuclideanVector& operator*(double val) {
      EuclideanVector *toRet;
      toRet = new EuclideanVector(this->dimension);
      for ( int a = 0; a < this->dimension; a++ ) {
        toRet->vec[a] = val * this->vec[a];
      }
      return *toRet;
    }

    friend EuclideanVector& operator*(double val, const EuclideanVector& e) {
      EuclideanVector *toRet;
      toRet = new EuclideanVector(e.dimension);
      for ( int a = 0; a < e.dimension; a++ ) {
        toRet->vec[a] = val * e.vec[a];
      }
      return *toRet;
    }

    //-------------Scalar Division----------//
    EuclideanVector& operator/(double val) {
      EuclideanVector *toRet;
      toRet = new EuclideanVector(this->dimension);
      for ( int a = 0; a < this->dimension; a++ ) {
        toRet->vec[a] = this->vec[a] / val;
      }
      return *toRet;
    }
    //--------------Ostream Overload------------//
    friend std::ostream& operator<< (std::ostream& stream,
      const EuclideanVector& eVec) {
        stream << "[";
        for ( int a = 0; a < eVec.dimension; a++ ) {
          stream << eVec.vec[a];
          if ( a < eVec.dimension - 1 ) stream << " ";
        }
        stream << "]";
      return stream;
    }
    //Typecasting operators
    //vector typecast
    operator std::vector<double>() const {
      std::vector<double> eVec;
      for ( int a = 0; a < this->dimension; a++ ) {
        eVec.push_back(this->vec[a]);
      }
      return eVec;
    }
    //list typecast
    operator std::list<double>() const {
      std::list<double> eVec;
      for ( int a = 0; a < this->dimension; a++ ) {
        eVec.push_back(this->vec[a]);
      }
      return eVec;
    }
    //getters, setters, printers
    unsigned int getNumDimensions() const {return dimension;}
    double get( unsigned int vecDim ) const {
      return ((vecDim <= this->dimension) && (vecDim >= 1) ?
                    this->vec[vecDim-1] : 0);
    }

    //----Getting the norm of the vector----//
    double getEuclideanNorm() const {
      if ( this->norm == 0 ) {
        for ( int a = 0; a < this->dimension; a++ ) {
          this->norm += (this->vec[a] * this->vec[a]);
        }
        this->norm = sqrt(this->norm);
      }
      return this->norm;
    }
    //--------------------------------------//

    //-----Returning normalised vector-----//
    EuclideanVector createUnitVector() const {
      EuclideanVector retVec(this->dimension);
      for ( int a = 0; a < this->dimension; a++ ) {
        retVec.vec[a] = this->vec[a];
      }
      double retNorm = retVec.getEuclideanNorm();
      for ( int a = 0; a < retVec.dimension; a++ ) {
        retVec.vec[a] /= retNorm;
      }
      retVec.norm = 0;
      return retVec;
    }
    //--------------------------------------//
    void printVec() const;
  //Encapsulation
  private:
    double *vec;
    int dimension;
    mutable double norm = 0;
    void setVal(double val);
    void setVal(std::initializer_list<double> arr);
  };


  //Friend functions
  EuclideanVector& operator*(double, const EuclideanVector&);
  std::ostream& operator<< (std::ostream&, const EuclideanVector& );

  //other functions
  void EuclideanVector::printVec() const {
    std::cout << "Printing vector" << std::endl;
    for ( int a = 0; a < dimension; a++ ) {
      std::cout << vec[a] << " ";
    }
    std::cout << std::endl;
  }

  void EuclideanVector::setVal(double val) {
    for ( int a = 0; a < dimension; a++ ) {
      vec[a] = val;
    }
  }

  void EuclideanVector::setVal(std::initializer_list<double> arr) {
    std::initializer_list<double>::iterator it;
    int a;
    for ( a = 0, it = arr.begin(); it != arr.end() || a < dimension; it++, a++) {
      vec[a] = *it;
    }
  }
//}
