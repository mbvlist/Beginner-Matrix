#include "Matrix.h"

#include <iostream>

Matrix<int> test_function()
{
    Matrix<int> m(2, 3);
    m(0, 0) = 55; m(0, 1) = 56; m(0, 2) = 57;
    m(1, 0) = 65; m(1, 1) = 66; m(1, 2) = 67;
    return m;
}

int main(int argc, char* argv)
{
	std::cout << "Starting Matrix test" << std::endl;

    Matrix<double> m1(2, 3);
    m1(0, 0) =  0; m1(0, 1) =  1; m1(0, 2) =  2;
    m1(1, 0) = 10; m1(1, 1) = 11; m1(1, 2) = 12;

    Matrix<double> m2(2, 3);
    m2(0, 0) =  100; m2(0, 1) =  200; m2(0, 2) =  300;
    m2(1, 0) = 1100; m2(1, 1) = 1200; m2(1, 2) = 1300;

    std::cout << "===\nm1:\n" << m1 << "===\nm2:\n" << m2 << std::endl;

    Matrix<double> m3 = m1 + m2;
    Matrix<double> m4 = 3 * m1;
    Matrix<double> const &m5 = m4;

    //forbidden: m5(1, 1) = 42;
    std::cout << "===\nm1+m2:\n" << m3 << "===\nm1*3:\n" << m5 << std::endl;

    m1 = m3;
    m2 = std::move(m4);

    std::cout << "addition assigned to m1:\n" << m1 << "===\nmultiplied assigned to m2:\n" << m2 <<"\nm4 after move: \n"<<m4 << std::endl;

    Matrix<int> m6 = Matrix(std::move(test_function()));
    std::cout << "result of test_function: \n" << m6 << std::endl;

	return 0;
}