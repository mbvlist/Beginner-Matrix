#include "matrix.h"

#include <iostream>
#include <iomanip>

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

Matrix::Matrix(const Matrix& m) noexcept
    : m_data(new double[m.m_rows * m.m_columns]),
    m_rows(m.m_rows),
    m_columns(m.m_columns)
{
    for (size_t pos = 0; pos < m_rows * m_columns; pos++)
    {
        m_data[pos] = m.m_data[pos];
    }
}

Matrix::Matrix(Matrix&& m) noexcept
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

Matrix& Matrix::operator=(Matrix&& m) noexcept
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
    // TODO determine sane length based on string representation of all values
    size_t length = 4;
    for (size_t row = 0; row < m.m_rows; row++)
    {
        for (size_t col = 0; col < m.m_columns; col++)
        {
            os << std::setw(length) << m(row, col) << ", ";
        }

        os << std::endl;
    }

    return os;
}

double Matrix::max() const
{
    if (m_rows == 0 || m_columns == 0)
    {
        throw std::exception("Matrix was created without values (no rows or no columns)");
    }
    double max_found = m_data[0];
    for (size_t pos = 0; pos < m_rows * m_columns; pos++)
    {
        max_found = std::max(max_found, m_data[pos]);
    }
    return max_found;
}