#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

class BinaryWriter {
	private:
		vector<bool> vec;
		ofstream outs;
	public:
		BinaryWriter(string new_name) : vec() , outs(new_name) {
			if (!outs.is_open()) {
				cerr << "Error opening file " << new_name << endl;
				exit(EXIT_FAILURE);
			}
		}
		void close() {
			outs << vec.size() << endl; //First write number of bits
			for (unsigned int i = 0; i <= vec.size()/8; i++) { //Then write all bytes
				unsigned char out = 0;
				for (int j = 0; j < 8; j++) {
					if (i*8+j < vec.size()) {
						if (vec.at(i*8+j)) {
							out |= 1<<(7-j);
						}
					}
				}
				if (i*8 != vec.size()) 
					outs << out;
			}
			outs.close();
		}
		BinaryWriter& operator<<(string enc) {
			for (auto i : enc) {
				if (i != '1' && i != '0') {
					cerr << "You are trying to write a non binary digit to BinaryWriter\n";
					exit(EXIT_FAILURE);
				}
				if (i == '1') 
					vec.push_back(true);
				else
					vec.push_back(false);
			}
			return *this;
		}
};


