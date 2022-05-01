#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <cstdlib>
#include "node.h"
#include "heap.h"
#include "binarywriter.h"

//This function will tell you how large a file is on disk
//This will let you calculate your compression ratio
int filesize(string str) {
	struct stat results;
	if (stat(str.c_str(), &results) == 0)
		return results.st_size;
	else {
		cerr << "Stat failed.\n";
		return 0;
		//exit(EXIT_FAILURE);
	}
}

int main() {
	while (cin) {
		string filename;
		cin >> filename;
		if (!cin || cin.eof()) break;
		if (filename == "QUIT" || filename == "quit") break;

		//PHASE 1 - Histogram filename

		//Heap arr[256];


		//PHASE 2 - Heapify it


		//PHASE 3 - Construct a binary trie


		//PHASE 4 - Generate encoding strings


		//PHASE 5 - Write out dictionary
		ofstream dict("output.dict");

		//Write out the dictionary here

		dict.close();


		//PHASE 6 - Write out encoded file
		//Use ./binaryview.sh to view the encoded files
		BinaryWriter outs("output.enc");

		//Some sample encoded strings we write out
		//Comment these out
		outs << "1111000010101010";
		outs << "1111111100000001";

		outs.close();

		//PHASE 7 - Calculate compression ratios
		int O = filesize(filename);
		int D = filesize("output.dict");
		int E = filesize("output.enc");
		cout << "Compression Ratio: " << O/double(D+E) << endl;

	}
}
