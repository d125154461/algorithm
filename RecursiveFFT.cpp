//  
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
//  Copyright (C) 2018  lxylxy123456
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as
//  published by the Free Software Foundation, either version 3 of the
//  License, or (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//  
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  

#ifndef MAIN
#define MAIN
#define MAIN_RecursiveFFT
#endif

#ifndef FUNC_RecursiveFFT
#define FUNC_RecursiveFFT

#include "utils.h"

#include "SquareMatrixMultiply.cpp"

template <typename T>
class Complex {
	public:
		Complex(): real(0), imag(0) {}
		Complex(T x): real(x), imag(0) {}
		Complex(T x, T y): real(x), imag(y) {}
		Complex<T> operator+(const Complex<T>& rhs) const {
			return Complex<T>(real + rhs.real, imag + rhs.imag); 
		}
		Complex<T> operator-(const Complex<T>& rhs) const {
			return Complex<T>(real - rhs.real, imag - rhs.imag); 
		}
		Complex<T> operator*(const Complex<T>& rhs) const {
			return Complex<T>(real * rhs.real - imag * rhs.imag, 
								real * rhs.imag + imag * rhs.real); 
		}
		Complex<T>& operator*=(const Complex<T>& rhs) {
			T r = real * rhs.real - imag * rhs.imag; 
			T i = real * rhs.imag + imag * rhs.real; 
			real = r; 
			imag = i; 
			return *this; 
		}
		Complex<T>& operator/=(const T& rhs) {
			real /= rhs; 
			imag /= rhs; 
			return *this; 
		}
		friend std::ostream& operator<<(std::ostream& os, const Complex<T>& r) {
			if (abs(r.imag) > 0.0000000001)
				return os << r.real << " + " << r.imag << " i"; 
			else
				return os << r.real; 
		}
		T real, imag; 
}; 

template <typename T>
Complex<T> expi(T x) {
	return Complex<T>(cos(x), sin(x)); 
}

template <typename T>
Matrix<T> RecursiveFFT(Matrix<T>& a, bool neg = false) {
	const size_t n = a.rows; 
	if (n == 1)
		return a; 
	assert(n % 2 == 0); 
	T wn = expi((neg ? -1 : 1) * 2 * M_PI / n); 
	T w = 1; 
	Matrix<T> a0(n / 2, 1), a1(n / 2, 1); 
	for (size_t i = 0; i < n; i += 2) {
		a0.data.push_back(a[i]); 
		a1.data.push_back(a[i + 1]); 
	}
	Matrix<T> y0 = RecursiveFFT(a0, neg); 
	Matrix<T> y1 = RecursiveFFT(a1, neg); 
	Matrix<T> y(n, 1, 0); 
	for (size_t k = 0; k < n / 2; k++) {
		y[k][0] = y0[k][0] + w * y1[k][0]; 
		y[k + n/2][0] = y0[k][0] - w * y1[k][0]; 
		w *= wn; 
	}
	return y; 
}

template <typename T>
Matrix<T> InverseFFT(Matrix<T>& a) {
	const size_t n = a.rows; 
	Matrix<T> ans = RecursiveFFT(a, true); 
	for (size_t i = 0; i < n; i++)
		ans[i][0] /= n; 
	return ans; 
}

template <typename T>
Matrix<T> PolynomialMultiply(Matrix<T>& a, Matrix<T>& b) {
	const size_t n = a.rows; 
	assert(n == b.rows); 
	Matrix<T> n0(n, 1, 0); 
	Matrix<T> aa = a.concat_v(n0); 
	Matrix<T> bb = b.concat_v(n0); 
	Matrix<T> fa = RecursiveFFT(aa); 
	Matrix<T> fb = RecursiveFFT(bb); 
	Matrix<T> fc(2 * n, 1, 0); 
	for (size_t i = 0; i < 2 * n; i++)
		fc[i][0] = fa[i][0] * fb[i][0]; 
	return InverseFFT(fc); 
}
#endif

#ifdef MAIN_RecursiveFFT
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 16); 
	std::vector<int> int_a, int_b; 
	random_integers(int_a, -n, n, n); 
	random_integers(int_b, -n, n, n); 
	using T = Complex<double>; 
	std::vector<T> buf_a(n), buf_b(n); 
	for (size_t i = 0; i < int_a.size(); i++)
		buf_a[i] = int_a[i]; 
	for (size_t i = 0; i < int_a.size(); i++)
		buf_b[i] = int_b[i]; 
	Matrix<T> a(n, 1, buf_a); 
	std::cout << a << std::endl; 
	Matrix<T> b(n, 1, buf_b); 
	std::cout << b << std::endl; 
	Matrix<T> c = PolynomialMultiply(a, b); 
	std::cout << c << std::endl; 
	return 0; 
}
#endif

