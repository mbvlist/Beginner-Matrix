#include "matrix.h"

#include <iostream>

Matrix::Matrix(size_t rows, size_t columns)
    : m_data(new double[rows * columns]),
    m_rows(rows),
    m_columns(columns)
{
    for (size_t pos = 0; pos < m_rows * m_columns; pos++)
    {
        m_data[pos] = 0;
    }
}

Matrix::Matrix(const Matrix& m)
    : m_data(new double[m.m_rows * m.m_columns]),
    m_rows(m.m_rows),
    m_columns(m.m_columns)
{
    for (size_t pos = 0; pos < m_rows * m_columns; pos++)
    {
        m_data[pos] = m.m_data[pos];
    }
}

Matrix::Matrix(Matrix&& m)
    : m_data(m.m_data),
    m_rows(m.m_rows),
    m_columns(m.m_columns)
{
    m.m_data = nullptr;
    m.m_rows = 0;
    m.m_columns = 0;
}

Matrix::~Matrix()
{
    delete[] m_data;
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if (this != &m)
    {
        delete[] m_data;

        m_rows = m.m_rows;
        m_columns = m.m_columns;

        m_data = new double[m_rows * m_columns];

        for (size_t pos = 0; pos < m_rows * m_columns; pos++)
        {
            m_data[pos] = m.m_data[pos];
        }
    }

    return *this;
}

Matrix& Matrix::operator=(Matrix&& m)
{
    std::swap(m_data, m.m_data);
    std::swap(m_rows, m.m_rows);
    std::swap(m_columns, m.m_columns);
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const
{
    if (m_rows != m.m_rows || m_columns != m.m_columns)
    {
        throw std::exception(); // TODO: define exception type
    }

    Matrix result(m_rows, m_columns);

    for (size_t pos = 0; pos < m_rows * m_columns; pos++)
    {
        result.m_data[pos] = m_data[pos] + m.m_data[pos];
    }

    return result;
}

Matrix Matrix::operator*(double d) const
{
    Matrix result(m_rows, m_columns);

    for (size_t pos = 0; pos < m_rows * m_columns; pos++)
    {
        result.m_data[pos] = m_data[pos] * d;
    }

    return result;
}

Matrix operator*(double d, const Matrix& m)
{
    return m * d;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (size_t row = 0; row < m.m_rows; row++)
    {
        for (size_t col = 0; col < m.m_columns; col++)
        {
            os << m(row, col) << ", ";
        }

        os << std::endl;
    }

    return os;
}
