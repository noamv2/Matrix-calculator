#include <algorithm>
#include <string>
#include <sstream>
#include "Matrix.hpp"
#include "helpers.hpp"

// constructors

//Used to handle dimention in ints, dellegating to the size_t constructor
Matrix::Matrix(vector<double> vals, int rows, int cols )
:Matrix(std::move(vals),static_cast<size_t>(checkPositive(rows)), static_cast<size_t>(checkPositive(cols))){
    
}

Matrix::Matrix(vector<double> vals, size_t rows, size_t cols):
    rowsNum{rows}, colsNum{cols}{

    //check dimentions are legal
    if(vals.size() != rows * cols){
        throw "Invalid dimensions";
    }
    
    for(int i = 0 ; i < rows; i++){
        this->mat.push_back(vector<double> (cols));
    }
    for(size_t i = 0 ; i < rows * cols; i++){
        
        this->mat.at(i / cols).at(i % cols) = vals.at(i);
    }


}
Matrix::Matrix(const Matrix &m) // copy constructor
    :rowsNum{m.rowsNum},colsNum{m.colsNum} {
    this->mat = m.mat;    
    
}

//Overloaded operators (Class members)
 void Matrix::operator+=(const Matrix &rhs){
    
    if(!isSameDim(rhs)){
        throw "Invalid operation";
    }
    
    for(size_t i = 0 ;i < rowsNum; i ++){
        for (size_t j = 0; j < colsNum; j++){
            mat.at(i).at(j) += rhs.mat.at(i).at(j);
        }
        
    }
    
}

 void Matrix::operator-=(const Matrix &rhs){
    
    if(!isSameDim(rhs)){
        throw "Invalid operation";
    }
    
    for(size_t i = 0 ;i < rowsNum; i ++){
        for (size_t j = 0; j < colsNum; j++){
            mat.at(i).at(j) -= rhs.mat.at(i).at(j);
        }
        
    }
    
}

Matrix Matrix::operator+(const Matrix &rhs){
    if(!isSameDim(rhs)){
        throw "Invalid operation";
    }

    std::vector<double> res(rowsNum * colsNum);

    for(size_t i = 0 ;i < rowsNum * colsNum; i ++){
        res.at(i) = this->mat.at(i / rowsNum).at(i % colsNum) + rhs.mat.at(i / rowsNum).at(i % colsNum);
    }
    
    return Matrix {res, rowsNum, colsNum};
}

Matrix Matrix::operator-(const Matrix &rhs){
    if(!isSameDim(rhs)){
        throw "Invalid operation";
    }

    std::vector<double> res(rowsNum * colsNum);

    for(size_t i = 0 ;i < rowsNum * colsNum; i ++){
        res.at(i) = this->mat.at(i / rowsNum).at(i % colsNum) - rhs.mat.at(i / rowsNum).at(i % colsNum);
    }
    
    return Matrix {res, rowsNum, colsNum};
}

Matrix Matrix::operator-(){

    std::vector<double> res(rowsNum * colsNum);

    for(size_t i = 0 ;i < rowsNum * colsNum; i ++){
        res.at(i) = -1 * (this->mat.at(i / rowsNum).at(i % colsNum));
    }
    
    return Matrix {res, rowsNum, colsNum};

}

Matrix Matrix::operator+(){

    std::vector<double> res(rowsNum * colsNum);

    for(size_t i = 0 ;i < rowsNum * colsNum; i ++){
        res.at(i) =  +(this->mat.at(i / rowsNum).at(i % colsNum));
    }
    
    return Matrix {res, rowsNum, colsNum};

}

Matrix Matrix:: operator--(){

    for(size_t i =0; i < rowsNum; i++){
        for (size_t k = 0 ; k < colsNum; k++){
            mat.at(i).at(k)--;
        }
    }
    return *this;
}

Matrix Matrix:: operator--(int){

    Matrix tmp {*this};

    for(size_t i =0; i < rowsNum; i++){
        for (size_t k = 0 ; k < colsNum; k++){
            mat.at(i).at(k)--;
        }
    }
    return tmp;
}

Matrix Matrix:: operator++(){

    for(size_t i =0; i < rowsNum; i++){
        for (size_t k = 0 ; k < colsNum; k++){
            mat.at(i).at(k)++;
        }
    }
    return *this;
}
Matrix Matrix:: operator++(int){
    
    Matrix tmp {*this};
    for(size_t i =0; i < rowsNum; i++){
        for (size_t k = 0 ; k < colsNum; k++){
            mat.at(i).at(k)++;
        }
    }
    
    return tmp;
}

bool Matrix:: operator==(const Matrix &m) const{

    
    if(!isSameDim(m)){
        throw "Invalid operation";
    }
    if(this == &m){
        return true;
    }

    for(size_t i = 0 ; i <m.rowsNum; i++){
        for (size_t j = 0; j < m.colsNum ; j++)
        {
            if(this->get(i,j) != m.get(i,j)){
                return false;
            }
        }
        
    }

    return true;
}
bool Matrix:: operator!=(const Matrix &m){
    
    if(!isSameDim(m)){
        throw "Invalid operation";
    }
    if(this == &m){
        return false;
    }

    for(size_t i = 0 ; i <m.rowsNum; i++){
        for (size_t j = 0; j < m.colsNum ; j++)
        {
            if(this->get(i,j) != m.get(i,j)){
                return true;
            }
        }
        
    }

    return false;
}

bool Matrix:: operator<=(const Matrix &m){
    
    if(!isSameDim(m)){
        throw "Invalid operation";
    }
    if(this == &m){
        return true;
    }
    if(this->operator==(m)){
        return true;
    }
    return sum() < m.sum();
}

bool Matrix:: operator>=(const Matrix &m){
    
    if(!isSameDim(m)){
        throw "Invalid operation";
    }
    if(this == &m){
        return true;
    }

    if(this->operator==(m)){
        return true;
    }
    return sum() > m.sum();
}

bool Matrix:: operator<(const Matrix &m){
    if(!isSameDim(m)){
        throw "Invalid operation";
    }
    if(this == &m){
        return false;
    }
    return sum() < m.sum();
}

bool Matrix:: operator>(const Matrix &m){

    if(!isSameDim(m)){
        throw "Invalid operation";
    }
    if(this == &m){
        return false;
    }
    return sum() > m.sum();
}

Matrix Matrix::operator*=(double scalar){

    for(size_t i = 0 ; i < rowsNum; i++){
        for(size_t j = 0; j < colsNum; j++){
            this->mat.at(i).at(j) *= scalar;
        }
    }
    return *this;
}

void Matrix::operator*=(const Matrix &m){
    if( m.rowsNum != this->colsNum){
        throw "Invalid operation for given dimentions";
    }
    std::vector<double> res;
    

    for(size_t i = 0 ; i < this->rowsNum; i++){
        for(size_t j = 0; j < m.colsNum; j++){
            res.push_back(0);
            for(size_t k = 0; k < this->colsNum; k++){
                res.back() += this->get(i,k) * m.get(k, j);
            }
        }
    }
    
    this->colsNum = m.colsNum;
    this->mat.clear(); //delete old values

    // insert the updated values
    for(int i = 0 ; i < rowsNum; i++){
        this->mat.push_back(vector<double> (colsNum));
    }
    for(size_t i = 0 ; i < rowsNum * colsNum; i++){
        
        this->mat.at(i / colsNum).at(i % colsNum) = res.at(i);
    }

}
// Globaly overloaded operators

std::ostream & operator<<(std::ostream &os, const Matrix &m){
    
    for(size_t i = 0 ; i <m.rowsNum; i++){
        os<<"[";
        for(size_t j = 0 ; j < m.colsNum -1; j++){
            os<<m.mat.at(i).at(j)<<" ";
        }
        os<<m.mat.at(i).at(m.colsNum -1);
        os<<"]";
        if(i == m.rowsNum -1){
            break;
        }
        os<<std::endl;
    }
    return os;
}

Matrix operator>>(std::istream & is, Matrix &m){


    std::string rows;
    std:getline(is,rows);
    
    
    
    size_t pos_start = 0;
    size_t pos_end = 0;
    size_t backup_pos_end = 0;
    std::string token;
    vector<std::string> res;

    while ((pos_end = rows.find (", ", pos_start)) != std::string::npos) {
        token = rows.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + 2;
        res.push_back (token);
        backup_pos_end = pos_end; // to keep track of the index of the last token
    }
    res.push_back(rows.substr(backup_pos_end +2, std::string::npos)); // adds the last row

    if(res.empty()){
        throw "Illegal input";
    }
    //clear current matrix values
    m.mat.clear();
    //checks that all of the rows are the same size
    size_t row_size = checkLegalMatRow(res.at(0)).size();
    for(auto const & s: res){
        
        std::vector<double> r = checkLegalMatRow(s);
        if( r.size() != row_size){
            throw "Illegal input";
        }
        m.mat.push_back(r);

    }
    m.rowsNum = m.mat.size();
    m.colsNum = row_size;
    return m;
}

Matrix operator*(double scalar, const Matrix &m){

    std::vector<double> res(m.rowsNum * m.colsNum);

    for(size_t i = 0 ;i < m.rowsNum * m.colsNum; i ++){
        res.at(i) = scalar * (m.mat.at(i / m.rowsNum).at(i % m.colsNum));
    }
    
    return Matrix {res, m.rowsNum, m.colsNum};

}

Matrix operator*(const Matrix &m, double scalar){

    std::vector<double> res;

    for(size_t i = 0 ; i <m.rowsNum; i++){
        for(size_t j = 0 ; j< m.colsNum; j++){
            double d = scalar * m.get(i,j);
            res.push_back(d) ;
        }
    }
    
    return Matrix {res, m.rowsNum, m.colsNum};

}


Matrix operator*(const Matrix &m, const Matrix &m2){

    if( m.colsNum != m2.rowsNum){
        throw "Invalid operation for given dimentions";
    }
    std::vector<double> res;

    for(size_t i = 0 ; i < m.rowsNum; i++){
        for(size_t j = 0; j < m2.colsNum; j++){
            res.push_back(0);
            for(size_t k = 0; k < m.colsNum; k++){
                res.back() += m.get(i,k) * m2.get(k, j);
            }
        }
    }

    
    return Matrix {res, m.rowsNum, m2.colsNum};

}

// methods

bool Matrix::isSameDim(const Matrix &b) const{
    return rowsNum == b.rowsNum && b.colsNum == colsNum;
}

double Matrix::get(size_t r, size_t c) const{
    return this->mat.at(r).at(c);
}

double Matrix:: sum() const{

    double s = 0;
    for(auto const &vec: mat){
        for(auto arg: vec){
            s += arg;
        }
    }
    return s;
}

int checkPositive(int n){
    //throws exception if number is non positive
    if(n <= 0){
        throw "Invalid dimensions";
    }

    return n;
}

std::vector<double> checkLegalMatRow(std::string const & row){
    // check that string is correctly represt a row in matrix object
    // correct form : [1 5 2 3]
    //@return: number of elemnts in the row
    if(row.size() <= 2){ // min row is 3 chars
        throw "Illegal input";
    }
    std::string LegalChars = "1234567890 []";
    //make sure only legal chars present in the string
    int lbracket = 0;
    int rbracket = 0;
    for(auto c: row){
        if(row.find(c) == std::string::npos){
            throw "Illegal input";
        }
        if(c == '['){
            lbracket++;
        }
        if(c == ']'){
            rbracket++;
        }
    }
    //we should have exactly on bracket of each type
    if(lbracket != 1 || rbracket != 1){
        throw "Invalid input";
    }

    if(row.at(0) != '[' || row.at(row.size() -1) != ']'){
        throw "Illegal input";
    }
    
    std::stringstream s;
    s << row.substr(1,row.size() -1); // drop the square brackets
    
    std::string str;
    double num = 0;
    
    


    std::vector<double> vals;
    while(!s.eof()){
        s>>str;
        if(std::stringstream(str) >> num){//extracting the number
            vals.push_back(num);
        }
        str = "";
    }

    return vals; 
}

