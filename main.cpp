#include "Matrix.h"

#include <iostream>

int main(int argc, char* argv)
{
	std::cout << "Starting Matrix test" << std::endl;
    Matrix m1(2, 3);

    m1(0, 0) = 0; m1(0, 1) = 1; m1(0, 2) = 2;
    m1(1, 0) = 0; m1(1, 1) = 1; m1(1, 2) = 2;

    Matrix m2(2, 3);

    m2(0, 0) = 0; m2(0, 1) = 1; m2(0, 2) = 2;
    m2(1, 0) = 0; m2(1, 1) = 1; m2(1, 2) = 2;

    std::cout << m1 << "===\n" << m2 << std::endl;

    Matrix m3 = m1 + m2;
    Matrix m4 = 3 * m1;
    Matrix m5 = m4;

    std::cout << m3 << "===\n" << m5 << std::endl;

    m1 = m3;
    m2 = m4;

    std::cout << m1 << "===\n" << m2 << std::endl;

	return 0;
}