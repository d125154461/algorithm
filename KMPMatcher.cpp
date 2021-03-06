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
#define MAIN_KMPMatcher
#endif

#ifndef FUNC_KMPMatcher
#define FUNC_KMPMatcher

#include "utils.h"

#include "NaiveStringMatcher.cpp"

template <typename T>
std::vector<size_t> ComputePrefixFunction(const std::vector<T>& P) {
	size_t m = P.size(); 
	std::vector<size_t> pi; 
	pi.push_back(0); 
	pi.push_back(0); 
	size_t k = 0; 
	for (size_t q = 2; q <= m; q++) {
		while (k && P[k] != P[q - 1])
			k = pi[k]; 
		if (P[k] == P[q - 1])
			k++; 
		pi.push_back(k); 
	}
	return pi; 
}

template <typename T>
void KMPMatcher(const std::vector<T>& S, const std::vector<T>& P, 
				std::vector<size_t>& ans) {
	size_t n = S.size(), m = P.size(); 
	std::vector<size_t> pi = ComputePrefixFunction(P); 
	size_t q = 0; 
	for (size_t i = 0; i < n; i++) {
		while (q && P[q] != S[i])
			q = pi[q]; 
		if (P[q] == S[i])
			q++; 
		if (q == m) {
			ans.push_back(i - m + 1); 
			q = pi[q]; 
		}
	}
}
#endif

#ifdef MAIN_KMPMatcher
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 40); 
	const size_t m = get_argv(argc, argv, 2, 3); 
	const size_t d = get_argv(argc, argv, 3, 2); 
	const size_t compute = get_argv(argc, argv, 4, 1); 
	std::vector<char> S, P; 
	random_integers<char>(S, 'a', 'a' + d, n); 
	random_integers<char>(P, 'a', 'a' + d, m); 
	output_integers(S, ""); 
	output_integers(P, ""); 
	std::vector<size_t> ans; 
	KMPMatcher(S, P, ans); 
	output_integers(ans); 
	if (compute) {
		std::vector<size_t> ans1; 
		NaiveStringMatcher(S, P, ans1); 
		output_integers(ans1); 
		std::cout << std::boolalpha << (ans == ans1) << std::endl; 
	}
	return 0; 
}
#endif

