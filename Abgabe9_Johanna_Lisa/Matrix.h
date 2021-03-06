#ifndef BIOINFO_MATRIX_H
#define BIOINFO_MATRIX_H

#include <vector>

class Matrix {
  
public: 
    
    using Array = std::vector<double>; //row
    using Matrixtype = std::vector<Array>; //column
    
    /**
     * default constructor 
     */
    Matrix(int size_s,int size_p);
    
    /**
     * sets the given value at pos Dij
     */
    void setValue(int i, int j, double value);
    
    /**
     * returns the value at pos Dij
     */
    double getValue(int i, int j);
    
private:
    
    Matrixtype matrix_;
};

Matrix::Matrix(int size_s, int size_p) {
    matrix_.resize(size_p);
    //with resize we have something in our arrays so we have no undefined behavior in getValue
    for (int i = 0; i < size_p; i++) {
        Matrix::Array a;
        a.resize(size_s);
        matrix_[i]=a;
    }
}

void Matrix::setValue(int i, int j, double value) {
    matrix_[i][j] = value;
}

double Matrix::getValue(int i, int j) {
    return matrix_[i][j];
}

#endif
