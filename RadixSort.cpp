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
#define MAIN_RadixSort
#endif

#ifndef FUNC_RadixSort
#define FUNC_RadixSort

#include "utils.h"
#include "CountingSort.cpp"

template <typename T>
class GetBit {
	public:
		GetBit(size_t b): bit(b) {}
		size_t operator()(T x) { return (x >> bit) & 1; }
		size_t bit; 
}; 

template <typename T>
void RadixSort(std::vector<T>& A, size_t b) {
	std::vector<T> B(A.size(), 0); 
	for (size_t i = 0; i < b; i++) {
		CountingSort(A, B, 2, GetBit<T>(i)); 
		std::copy(B.begin(), B.end(), A.begin()); 
	}
}
#endif

#ifdef MAIN_RadixSort

#include <cmath>
#include "InsertSort.cpp"

int main(int argc, char *argv[]) {
	std::vector<int> a; 
	const size_t n = get_argv(argc, argv, 1, 10); 
	const int k = get_argv(argc, argv, 2, int(log(n) / log(2))); 
	const size_t compute = get_argv(argc, argv, 3, 3); 
	random_integers(a, 0, pow(2, k) - 1, n); 
	std::vector<int> b(a); 
	if (compute >> 0 & 1) {
		InsertSort(a); 
		output_integers(a); 
	}
	if (compute >> 1 & 1) {
		RadixSort(b, k); 
		output_integers(b); 
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (a == b) << std::endl; 
	}
	return 0; 
}
#endif

