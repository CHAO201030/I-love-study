#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Matrix
{
private:
    int _dim;
    vector<vector<int>> _matrix;
    
public:
    Matrix(int dim = 2);
    Matrix(vector<vector<int>> & matrix);
    ~Matrix();
    void print() const;

public:
    friend Matrix operator+(const Matrix & lhs, const Matrix & rhs);
    friend Matrix operator-(const Matrix & lhs, const Matrix & rhs);
    friend Matrix operator*(const Matrix & lhs, const Matrix & rhs);

};

Matrix::Matrix(int dim)
{
    cout << "Matrix constructor : dimension = " << dim << endl;

    _dim = dim;
    for(int i = 0; i < dim; i++)
    {
        vector<int> temp(dim);
        _matrix.push_back(temp);
    }
}

Matrix::Matrix(vector<vector<int>> & matrix)
{
    _dim = matrix.size();
    cout << "Matrix constructor : dimension = " << _dim << endl;

    int temp = _dim;
    for(auto & i : matrix)
    {
        for(auto j : i)
        {
            i.push_back(j);
            temp--;
            if(temp == 0)break;
        }
        _matrix.push_back(i);
        temp = _dim;
    }
}

Matrix::~Matrix()
{
    // cout << "~Matrix()" << endl;
}

void Matrix::print() const
{
    int temp = _dim;
    for(auto & i : _matrix)
    {
        for(auto & j : i)
        {
            cout << setw(4) << right << j << " ";
            temp--;
            if(temp == 0)break;
        }
        cout << endl;
        temp = _dim;
    }
}

Matrix operator+(const Matrix & lhs, const Matrix & rhs)
{
    vector<vector<int>> temps;

    int row = 0;
    int col = 0;

    while(row < lhs._dim)
    {
        vector<int> temp;

        while(col < lhs._dim)
        {
            temp.push_back(lhs._matrix[row][col] + rhs._matrix[row][col]);
            col++;
        }

        temps.push_back(temp);
        
        row++;
        col = 0;
    }

    return Matrix(temps);
}

Matrix operator-(const Matrix & lhs, const Matrix & rhs)
{
    vector<vector<int>> temps;

    int row = 0;
    int col = 0;

    while(row < lhs._dim)
    {
        vector<int> temp;

        while(col < lhs._dim)
        {
            temp.push_back(lhs._matrix[row][col] - rhs._matrix[row][col]);
            col++;
        }

        temps.push_back(temp);
        
        row++;
        col = 0;
    }

    return Matrix(temps);
}

Matrix operator*(const Matrix & lhs, const Matrix & rhs)
{
    vector<vector<int>> temps;

    int row = 0;
    int col = 0;
    int pos = 0;

    for(row = 0; row < lhs._dim; row++)
    {
        vector<int> temp;

        for(col = 0; col < lhs._dim; col++)
        {
            int val = 0;

            for(pos = 0; pos < lhs._dim; pos++)
            {
                val += lhs._matrix[row][pos] * rhs._matrix[pos][col];
            }

            temp.push_back(val);
        }
        
        temps.push_back(temp);
    }

    return Matrix(temps);
}

int main(void)
{
    vector<vector<int>> temp1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> temp2 = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

    Matrix m1(temp1);
    Matrix m2(temp2);

    m1.print();

    cout << endl;

    m2.print();

    Matrix m3 = m1 + m2;
    m3.print();

    Matrix m4 = m1 - m2;
    m4.print();

    Matrix m5 = m1 * m2;
    m5.print();
}