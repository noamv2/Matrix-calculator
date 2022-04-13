#pragma once
#include <vector>
#include <iostream>
#include <string>
using std::vector;


namespace zich{}

class Matrix{

    // globaly overloaded operators
    friend std::ostream & operator<<(std::ostream & os, const Matrix &m);
    friend Matrix operator>>(std::istream & is,  Matrix &m);
    friend Matrix operator*(double scalar, const Matrix & m);
    friend Matrix operator*(const Matrix & m, double scalar );
    friend Matrix operator*(const Matrix & m, const Matrix & m2);
    
    


    private:
        vector<vector<double>> mat;
        
    public:
        size_t rowsNum, colsNum;
        Matrix(vector<double> vals, size_t rows, size_t cols );
        Matrix(vector<double> vals, int rows, int cols );
        Matrix(const Matrix &m);
        
        
        
        // overloaded operators
        //addtion and substraction
        void  operator+=(const Matrix &rhs);
        void  operator-=(const Matrix &rhs);
        Matrix operator+(const Matrix &);
        Matrix operator-(const Matrix &);
        Matrix operator-();
        Matrix operator+();
        Matrix operator--();
        Matrix operator--(int);
        Matrix operator++();
        Matrix operator++(int);

        //comparsions
        bool operator==(const Matrix &m) const;
        bool operator!=(const Matrix &m);
        bool operator>=(const Matrix &m);
        bool operator<=(const Matrix &m);
        bool operator<(const Matrix &m);
        bool operator>(const Matrix &m);
        
        // mult
        Matrix operator*=(double scalar);
        void operator*=(const Matrix &m);

        // methods
        bool isSameDim(const Matrix &) const;
        double get(size_t,size_t) const;
        double sum() const;

};

