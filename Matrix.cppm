// Matrix.h : Include file for standard system include files,
// or project specific include files.
module;
export module Matrix;

import std;

export template<class T>
class Matrix
{
public:
    Matrix(size_t rows, size_t columns) 
      : m_data(new T[rows * columns]),
        m_rows(rows),
        m_columns(columns)
    {
        for (size_t pos = 0; pos < m_rows * m_columns; pos++)
        {
            m_data[pos] = 0;
        }
    }

    Matrix(const Matrix& m) noexcept
      : m_data(new double[m.m_rows * m.m_columns]),
        m_rows(m.m_rows),
        m_columns(m.m_columns)
    {
        for (size_t pos = 0; pos < m_rows * m_columns; pos++)
        {
            m_data[pos] = m.m_data[pos];
        }
    }

    Matrix(Matrix&& m) noexcept
      : m_data(m.m_data),
        m_rows(m.m_rows),
        m_columns(m.m_columns)
    {
        m.m_data = nullptr;
        m.m_rows = 0;
        m.m_columns = 0;
    }

    ~Matrix()
    {
        delete[] m_data;
    }

    Matrix& operator=(const Matrix& m)
    {
        if (this != &m)
        {
            delete[] m_data;

            m_rows = m.m_rows;
            m_columns = m.m_columns;

            m_data = new T[m_rows * m_columns];

            for (size_t pos = 0; pos < m_rows * m_columns; pos++)
            {
                m_data[pos] = m.m_data[pos];
            }
        }

        return *this;
    }
    
    Matrix& operator=(Matrix&& m) noexcept
    {
        std::swap(m_data, m.m_data);
        std::swap(m_rows, m.m_rows);
        std::swap(m_columns, m.m_columns);
        return *this;
    }

    Matrix operator+(const Matrix& m) const
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

    Matrix operator*(const T& d) const
    {
        Matrix result(m_rows, m_columns);

        for (size_t pos = 0; pos < m_rows * m_columns; pos++)
        {
            result.m_data[pos] = m_data[pos] * d;
        }

        return result;
    }

    friend Matrix operator*(const T& d, const Matrix& m)
    {
        return m * d;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m)
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

    T& operator()(size_t row, size_t col) { return m_data[pos(row, col)]; }
    const T& operator()(size_t row, size_t col) const { return m_data[pos(row, col)]; }

    T max() const
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

private:
    size_t pos(size_t row, size_t column) const { return row * m_columns + column; }

private:
    T* m_data;
    size_t m_rows;
    size_t m_columns;
};
