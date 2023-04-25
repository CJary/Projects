//
// Created by Jary Chen on 2/6/23.
//

#ifndef HW3_MATRIX_H
#define HW3_MATRIX_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class Matrix {
private:
    int rows;
    int cols;
    double **data;
public:
    //default
    Matrix();

    // with RxC plus fill value
    Matrix(unsigned int rowscount, unsigned int colscount, double fillvalue);

    //copy
    Matrix(const Matrix& m2);

    //Destructor
    ~Matrix() {clear();}

    //getters
    int num_rows() const{
        return rows;
    }

    int num_cols() const{
        return cols;
    }

    //setter
    double* get_row(unsigned int n) const;
    double* get_col(unsigned int n) const;

    void multiply_by_coefficient(double n);
    void transpose();
    Matrix* quarter();
    void clear();
    bool swap_row(unsigned int r1, unsigned int r2);

    bool set(int r, int c, double v);
    bool get(int r, int c, double &variable) const;
    bool add(const Matrix &m2);
    bool subtract(const Matrix &m2);

    //extra credit
    void resize(unsigned int r, unsigned int c, double fillvalue);

    //member operator
    Matrix& operator=(const Matrix& m2);

};

// non-member operator function
bool operator==(const Matrix& m1, const Matrix& m2);
bool operator!=(const Matrix& m1, const Matrix& m2);
ostream& operator<< (ostream& out, const Matrix& m);

#endif //HW3_MATRIX_H
