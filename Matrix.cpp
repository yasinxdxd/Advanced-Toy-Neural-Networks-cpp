#include "Matrix.h"

template<class T>
Matrix<T>::Matrix(int numRows, int numCols)
{
    this->Rows=numRows;
    this->Cols=numCols;
    //push 0 to matrix's all element.
    for(int x = 0; x<this->Rows; x++)
    {
        std::vector<T> vec;
        for(int y = 0; y<this->Cols; y++)
        {
            vec.push_back(0);
        }
        this->values.push_back(vec);
    }
}

template<class T>
Matrix<T>::Matrix(std::initializer_list<std::vector<T>> l)
{
    this->Rows=l.size();
    this->Cols=l.begin()->size();
    for(int x = 0; x<this->Rows; x++)
    {
        this->values.insert(values.end(),l.begin(),l.end());
    }
}

template<class T>
Matrix<T>::~Matrix()
{
    //dtor
}

template<class T>
void Matrix<T>::setValue(int r, int c, T value)
{

    this->values.at(r).at(c) = value;

}

template<class T>
T Matrix<T>::getValue(int r, int c)
{
    return this->values.at(r).at(c);
}

template<class T>
void Matrix<T>::randomize()
{
    double p1=-1;
    double p2=1;
    for(int x = 0; x<this->Rows; x++)
    {
        std::vector<T> vec;
        for(int y = 0; y<this->Cols; y++)
        {
            T r = this->getRandomNumber(p1, p2);
            this->setValue(x,y,r);
        }
        this->values.push_back(vec);
    }
}

template<class T>
std::vector<T> Matrix<T>::toArray() const
{
    std::vector<T> arr;
    for(int i=0; i<this->Cols; i++)
    {
        for(int j=0; j<this->Rows; j++)
        {
            arr.push_back(this->values.at(i).at(j));
        }
    }
    return arr;
}

//template<class T>
//static Matrix<T> fromArray(std::vector<T> arr)
//{
//    Matrix<T> result(arr.size(), 1);
//
//    for(int i = 0; i<result.Rows; i++)
//        result.setValue(i,0,arr[i]);
//
//    return result;
//}

template<class T>
void Matrix<T>::printToConsole() const
{
    for(int x = 0; x<this->Rows; x++)
    {
        for(int y = 0; y<this->Cols; y++)
        {
            std::cout<<this->values.at(x).at(y)<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
//    std::cout<<std::endl;
//    std::cout<<std::endl;
}

template<class T>
T Matrix<T>::getSum() const
{
    T sum=0;

    for(int x = 0; x<this->Rows; x++)
    {
        for(int y = 0; y<this->Cols; y++)
        {
            sum += this->values[x][y];
        }
    }

    return sum;

}

template<class T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> result(this->Cols,this->Rows);

    for(int x = 0; x<this->Rows; x++)
    {
        for(int y = 0; y<this->Cols; y++)
        {
            result.values.at(y).at(x) = this->values.at(x).at(y);
        }
    }
    return result;
}


  ///*//////////////////////////////////////////////*///
 ///*///////////////PRIVATE FUNCTIONS//////////////*///
///*//////////////////////////////////////////////*///


template<class T>
T Matrix<T>::getRandomNumber(T p1, T p2)
{
    static std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dist(p1, p2);

    return dist(gen);
}




  ///*///////////////////////////////////////////////*///
 ///*//////////////OPERATOR OVERLOADING/////////////*///
///*///////////////////////////////////////////////*///

template<class T>
Matrix<T> Matrix<T>::operator+ (const Matrix& m) const
{
    Matrix<T> result(this->Rows, this->Cols);
    for(int x = 0; x<this->Rows; x++)
    {
        for(int y = 0; y<this->Cols; y++)
        {
            result.values.at(x).at(y)=this->values.at(x).at(y) + m.values.at(x).at(y);
        }
    }
    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator+ (const T& d) const
{
    Matrix<T> result(this->Rows, this->Cols);
    for(int x = 0; x<this->Rows; x++)
    {
        for(int y = 0; y<this->Cols; y++)
        {
            result.values.at(x).at(y)=this->values.at(x).at(y)+d;
        }
    }
    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator- (const Matrix& m) const
{
    Matrix<T> result(this->Rows, this->Cols);
    for(int x = 0; x<this->Rows; x++)
    {
        for(int y = 0; y<this->Cols; y++)
        {
            result.values.at(x).at(y)=this->values.at(x).at(y) - m.values.at(x).at(y);
        }
    }
    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator- (const T& d) const
{
    Matrix<T> result(this->Rows, this->Cols);
    for(int x = 0; x<this->Rows; x++)
    {
        for(int y = 0; y<this->Cols; y++)
        {
            result.values.at(x).at(y)=this->values.at(x).at(y)-d;
        }
    }
    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator* (const Matrix& m) const
{
    Matrix<T> result(this->Rows, m.Cols);
    T sum=0;
    int commonNumber = this->Cols || m.Rows;
    if(this->Cols==m.Rows)
    {
        for(int x = 0; x<result.Rows; x++)
        {
            for(int y = 0; y<result.Cols; y++)
            {
                sum=0;
                for(int k = 0; k<commonNumber; k++)
                {
                    sum+=this->values.at(x).at(k)*m.values.at(k).at(y);
                }
                result.values.at(x).at(y)=sum;
            }
        }
    }
    else
    {
        std::cout<<"the number of columns of the 1st matrix must equal to the number of rows of the 2nd one."<<std::endl;
    }

    return result;
}



template<class T>
Matrix<T> Matrix<T>::operator* (const T& d) const
{
    Matrix<T> result(this->Rows, this->Cols);
    for(int x = 0; x<this->Rows; x++)
    {
        for(int y = 0; y<this->Cols; y++)
        {
            result.values.at(x).at(y)=this->values.at(x).at(y)*d;
        }
    }
    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator% (const Matrix& m) const///HADAMARD PRODUCT
{
    Matrix<T> result(this->Rows, this->Cols);
    for(int x = 0; x<this->Rows; x++)
    {
        for(int y = 0; y<this->Cols; y++)
        {
            result.values.at(x).at(y)=this->values.at(x).at(y) * m.values.at(x).at(y);
        }
    }
    return result;
}


  ///*///////////////////////////////////////////////*///
 ///*//////////////OPERATOR OVERLOADING/////////////*///
///*///////////////////////////////////////////////*///

