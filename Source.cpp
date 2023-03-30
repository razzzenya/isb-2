#include <iostream>
#include <vector>
#include <ctime>
#include <math.h>
#include <fstream>

using namespace std;

void frequency_bit_test(const vector<int>& bit_sequence) {
	double N = bit_sequence.size();
	double sum = 0;

	for (auto i : bit_sequence) {
		if (i == 1) { ++sum; }
		else { --sum; }
	}
	double S_n = (1 / sqrt(N)) * sum;
	double P_value = erfc(S_n / sqrt(2));

	cout << P_value << endl;
}

void test_for_identical_consecutive_bits(const vector<int>& bit_sequence) {
	double e_sum = 0, N = bit_sequence.size();
	for (auto i : bit_sequence) { e_sum += i; }
	double percentage = (1 / N) * e_sum;
	
	if (abs(percentage - 0.5) > 2 / sqrt(N)) { 
		cout << "P value equals 0" << endl;
		return; 
	}

	double V_n = 0;
	for (int i = 0; i < N - 1; ++i) {
		if (bit_sequence[i] != bit_sequence[i + 1]) { ++V_n; }
	}

	double P_value = erfc(abs(V_n - 2 * N * percentage * (1 - percentage)) / (2 * sqrt(2 * N) * percentage * (1 - percentage)));
	cout << P_value << endl;

}

void longest_sequence_of_units(const vector<int>& bit_sequence) {
	vector<int>amount_of_units;
	int index = 0;
	while (true) {
		if (index == 128) { break; }

		vector<int> tmp;
		for (int i = index; i < index + 8; ++i) {
			tmp.push_back(bit_sequence[i]);
		}

		int max = 0 , cur = 0;
		for (auto i : tmp) {
			if (i == 1) { ++cur; }
			else {
				if (cur > max) { max = cur; }
				cur = 0;
			}
		}
		
		amount_of_units.push_back(max);

		index += 8;
	}

	int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
	for (auto i : amount_of_units) {
		if (i <= 1) { ++v1; }
		if (i == 2) { ++v2; }
		if (i == 3) { ++v3; }
		if (i >= 4) { ++v4; }
	}

	vector <int> v_array = { v1, v2 ,v3 ,v4 };
	vector<double> pi_array = { 0.2148 ,0.3672, 0.2305 ,0.1875 };
	double X = 0;
	for (int i = 0; i < 4; ++i) {
		X += (pow(v_array[i] - 16*pi_array[i], 2)) / (16 * pi_array[i]);
	}

	cout << X << endl;
}


int main(){
	srand(time(NULL));
	vector<int> bit_sequence;

	for (size_t i = 0; i < 128; ++i) {
		bit_sequence.push_back(rand() % 2);
	}

	for (auto i : bit_sequence) {
		cout << i;
	}
	cout << endl;

	ofstream out;
	out.open("result.txt");
	if (out.is_open()) {
		for (auto i : bit_sequence) {
			out << i;
		}
	}

	frequency_bit_test(bit_sequence); // Frequency bit test
	test_for_identical_consecutive_bits(bit_sequence); //Test for identical consecutive bits
	longest_sequence_of_units(bit_sequence);//Test for the longest sequence of units
	return 0;
}