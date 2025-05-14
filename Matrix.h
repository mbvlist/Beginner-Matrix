// Matrix.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iosfwd>

class Matrix
{
public:
    Matrix(size_t rows, size_t columns);
    Matrix(const Matrix& m);
    Matrix(Matrix&& m);
    ~Matrix();

    Matrix& operator=(const Matrix& m);
    Matrix& operator=(Matrix&& m);

    Matrix operator+(const Matrix& m) const;
    Matrix operator*(double d) const;

    friend Matrix operator*(double d, const Matrix& m);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    double& operator()(size_t row, size_t col) { return m_data[pos(row, col)]; }
    const double& operator()(size_t row, size_t col) const { return m_data[pos(row, col)]; }

private:
    size_t pos(size_t row, size_t column) const { return row * m_columns + column; }

private:
    double* m_data;
    size_t m_rows;
    size_t m_columns;
};
