//
// Created by Jary Chen on 2/6/23.
//

#include "Matrix.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
//default
Matrix::Matrix() {
    rows = 0;
    cols = 0;
    data = NULL; //sets to a NULL pointer
}

//with RxC plus fill value
Matrix::Matrix(unsigned int rowscount, unsigned int colscount, double fillvalue) {
    if ((rowscount == 0) or (colscount == 0)){
        rows = 0;
        cols = 0;
        data = NULL;
    }
    else {
        rows = rowscount;
        cols = colscount;
        data = new double*[rows];
        for (int r = 0; r < rows; r++){
            data[r] = new double[cols];
            for (int c = 0; c < cols; c++){
                data[r][c] = fillvalue;
            }
        }
    }
}


//copy
Matrix::Matrix(const Matrix &m2) {
    rows = m2.num_rows();
    cols = m2.num_cols();
    double v;
    data = new double*[rows];
    for (int r = 0; r < rows; r++){
        data[r] = new double[cols];
        for (int c = 0; c < m2.num_cols(); c++){
            m2.get(r, c, v);
            data[r][c] = v;
        }
    }
}


//set function
bool Matrix::set(int r, int c, double v){
    if ((r+1> rows ) or (c+1> cols)){ //return false if out of bound
        return false;
    }
    data[r][c] = v;
    return true;
}


//get function
bool Matrix::get(int r, int c, double &variable) const {
    if ((r+1 > rows ) or (c+1 > cols)){ // return false if out of bound
        return false;
    }
    variable = data[r][c];
    return true;
}


//multiply_by_coefficient function
void Matrix::multiply_by_coefficient(double n){
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            data[r][c] = data[r][c] * n;
        }
    }
}


//get row function
double *Matrix::get_row(unsigned int n) const {
    if (n+1 > rows){
        return nullptr;
    }
    double *dc = new double[cols];
    for (int i = 0; i < cols; i++){
        dc[i] = data[n][i]; //value of that row index
    }
    return dc;
}


//get col function
double *Matrix::get_col(unsigned int n) const {
    if (n+1 > cols){
        return nullptr;
    }
    double *dc = new double[rows];
    for (int i = 0; i < rows; i++){
        dc[i] = *data[i]; //value of that column index
    }
    return dc;
}


//swap row function
bool Matrix::swap_row(unsigned int r1, unsigned int r2) {
    if ((r1+1 > rows) or (r2+1 > rows)){
        return false;
    }

    double* tmp = data[r2];
    data[r2] = data[r1];
    data[r1] = tmp;
    return true;
}


//add function
bool Matrix::add(const Matrix &m2) {
    if ((rows == m2.num_rows()) and (cols == m2.num_cols())){
        double v;
        for (int r = 0; r < rows; r++){
            for (int c = 0; c < cols; c++){
                m2.get(r, c, v);
                data[r][c] = data[r][c] + v; //plus
            }
        }
        return true;
    }
    // if dimensions not the same
    return false;
}


//subtract function
bool Matrix::subtract(const Matrix &m2) {
    if ((rows == m2.num_rows()) and (cols == m2.num_cols())){
        double v;
        for (int r = 0; r < rows; r++){
            for (int c = 0; c < cols; c++){
                m2.get(r, c, v);
                data[r][c] = data[r][c] - v; //minus
            }
        }

        return true;
    }
    // if dimensions not the same
    return false;
}


//transpose function
void Matrix::transpose() {
    int nr = cols;
    int nc = rows;
    double **temp = new double*[nr];
    for (int r = 0; r < nr; r++){
        temp[r] = new double[nc];
        for (int c = 0; c < nc; c++){
            temp[r][c] = data[c][r];
        }
    }

    //delete old version
    this ->clear();

    //equal to the new version
    data = temp;
    rows = nr;
    cols = nc;
}


//quarter function
Matrix *Matrix::quarter() {
    Matrix *mq = new Matrix[4];
    int ir = (rows/2) + (rows%2); //to set the size of the 4 quadrants
    int ic = (cols/2) + (cols%2);
    Matrix ul(ir, ic, 0);
    Matrix ur(ir, ic, 0);
    Matrix ll(ir, ic, 0);
    Matrix lr(ir, ic, 0);
    int nr = ir;
    int nc = ic;
    if (cols%2 == 1){// if cols is odd nc--
        nc--;
    }
    if (rows%2 == 1){ // if rows are odd nr--
        nr--;
    }

    for (int r = 0; r < ir; r++){
        for (int c = 0; c < ic; c++){
            ul.set(r, c, data[r][c]);
        }
    }
    mq[0] = ul;

    for (int r = 0; r < ir; r++){
        for (int c = 0; c < ic; c++){
            ur.set(r, c, data[r][c+nc]);
        }
    }
    mq[1] = ur;

    for (int r = 0; r < ir; r++){
        for (int c = 0; c < ic; c++){
            ll.set(r, c, data[r+nr][c]);
        }
    }
    mq[2] = ll;

    for (int r = 0; r < ir; r++){
        for (int c = 0; c < ic; c++){
            lr.set(r, c, data[r+nr][c+nc]);
        }
    }
    mq[3] = lr;

    return mq;
}


//clear function
void Matrix::clear() {
    if (data == NULL){ //checks if the data is cleared already
        return;
    }

    for (int i = 0; i < rows; i++){
        delete [] data[i];
    }
    delete [] data;
    data = NULL; //makes the cleared data to NULL
    rows = 0;
    cols = 0;
}

// operator =
Matrix &Matrix::operator=(const Matrix &m2) {
    this-> clear(); //erease the left matrix to set as m2

    rows = m2.num_rows();
    cols = m2.num_cols();
    double v;
    this-> data = new double*[m2.num_rows()];
    for (int r = 0; r < rows; r++){
        this-> data[r] = new double[m2.num_cols()];
        for (int c = 0; c < cols; c++){
            m2.get(r, c, v);
            this->set(r, c, v);
        }
    }
    return *this;
}

void Matrix::resize(unsigned int r, unsigned int c, double fillvalue) {
    if ((rows == r) and (cols == c)){ // can't resize something the same size
        return;
    }

    double **temp = new double*[r];
    for (int i = 0; i < r; i++){
        temp[i] = new double[c];
    }

    //if r and c are less than rows/cols
    if ((r < rows) and (c < cols)){
        for (int j = 0; j < r; j++){
            for (int k = 0; k < c; k++){
                temp[j][k] = this->data[j][k];
            }
        }
    }

    //if c is less than ir equal to cols but r is greater than rows
    if ((r > rows) and (c <= cols)){
        for (int j = 0; j < r; j++){ // fill everything first
            for (int k = 0; k < c; k++){
                temp[j][k] = fillvalue;
            }
        }

        for (int j = 0; j < rows; j++){
            for (int k = 0; k < c; k++){
                temp[j][k] = this->data[j][k];
            }
        }
    }

    //if r is less than ir equal to rows but c is greater than cols
    if ((r <= rows) and (c > cols)){ // fill value first
        for (int j = 0; j < r; j++){
            for (int k = 0; k < c; k++){
                temp[j][k] = fillvalue;
            }
        }

        for (int j = 0; j < r; j++){
            for (int k = 0; k < cols; k++){
                temp[j][k] = this->data[j][k];
            }
        }
    }

    //if both greater
    if ((r > rows) and (c > cols)){
        for (int j = 0; j < r; j++){ // fill values first
            for (int k = 0; k < c; k++){
                temp[j][k] = fillvalue;
            }
        }

        for (int j = 0; j < rows; j++){
            for (int k = 0; k < cols; k++){
                temp[j][k] = this->data[j][k];
            }
        }
    }
    this->clear();
    data = temp;
    rows = r;
    cols = c;

}


// operator <<
ostream &operator<<(ostream &out, const Matrix &m) {
    out << "\n";
    out << m.num_rows() << " x " << m.num_cols() << " matrix:" << "\n";
    out << "[ ";

    double v;
    for (int r = 0; r < m.num_rows(); r++){
        for (int c = 0; c < m.num_cols(); c++){
            m.get(r, c, v);
            out << v << ' ';
        }
        if (r < m.num_rows() - 1){
            out << "\n  ";
        }
    }
    out << "]\n";
    return out;
}

//operator ==
bool operator==(const Matrix &m1, const Matrix &m2) {
    //checks if the rows and col are the same first
    if ((m1.num_rows() == m2.num_rows()) and (m1.num_rows() == m2.num_cols())){
        double v;
        double v2;
        for (int r = 0; r < m2.num_rows(); r++){
            for (int c = 0; c < m2.num_cols(); c++){
                m1.get(r, c, v);
                m2.get(r, c, v2);
                if (v == v2){
                    continue;
                }
                else{ // if one of them are not the same return false
                    return false;
                }
            }
        }
        // if none of them hit the else statement it returns true
        return true;
    }
    // if rows and col are not the same return false
    return false;
}

//operator !=
bool operator!=(const Matrix &m1, const Matrix &m2) {
    //checks if the rows and col are the same first
    if ((m1.num_rows() == m2.num_rows()) and (m1.num_rows() == m2.num_cols())){
        double v;
        double v2;
        for (int r = 0; r < m2.num_rows(); r++){
            for (int c = 0; c < m2.num_cols(); c++){
                m1.get(r, c, v);
                m2.get(r, c, v2);
                if (v == v2){
                    continue;
                }
                else{ // if one of them are not the same return true
                    return true;
                }
            }
        }
        // if none of them hit the else statement it returns false
        return false;
    }
    // if rows and col are not the same return true
    return true;
}














