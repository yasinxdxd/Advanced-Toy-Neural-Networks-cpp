#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <initializer_list>

template<class T>
class Matrix
{
public:
    Matrix(int numRows, int numCols);
    Matrix(std::initializer_list<std::vector<T>>);

    ~Matrix();

    void setValue(int r, int c, T value);
    T getValue(int r, int c);
    int getNumRows(){return this->Rows;}
    int getNumCols(){return this->Cols;}
    void randomize();
    std::vector<T> toArray() const;
    static Matrix<T> fromArray(std::vector<T> arr)
    {
        Matrix<T> result(arr.size(), 1);

        for(int i = 0; i<result.Rows; i++)
            result.setValue(i,0,arr[i]);

        return result;
    }
    void printToConsole() const;
    T getRandomNumber(T p1, T p2);
    T getSum() const;
    Matrix<T> transpose() const;

private:
///Private Functions:
/////////////////////////

///Variables:
    int Rows;
    int Cols;
    std::vector<std::vector<T>> values;

public:
///Operators Overloading for Objects:
    Matrix operator+(const Matrix& m) const;
    Matrix operator+(const T& d) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator-(const T& d) const;
    Matrix operator*(const Matrix& m) const;
    Matrix operator*(const T& d) const;
    Matrix operator%(const Matrix& m) const;///HADAMARD PRODUCT :)

};

#endif // MATRIX_H
