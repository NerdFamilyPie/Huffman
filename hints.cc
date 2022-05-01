#include <iostream>
#include <iomanip>
#include <fstream>
#include <sys/stat.h>
#include <cstdlib>
#include "node.h"
#include "heap.h"
#include "binarywriter.h"
#include "binaryreader.h"
using namespace std;

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

void encode(Node *current,Node *arr, string str="") {
	//YOU: Recursively iterate through the trie, adding "0" to the end of str 
	// when you go left, and a "1" to the end when you go right.
	//Save str into the node's .enc member variable when you hit a leaf.
}

void decode(string,string,string);

int main() {
	while (cin) {
		string filename;
		cin >> filename;
		if (!cin || cin.eof()) break;
		if (filename == "QUIT" || filename == "quit") break;

		//Run decryption if the file ends in .enc, like hamlet.enc
		int pos = filename.find(".enc"); //FIXME: this will match any .enc in the filename, not just the end
		if (pos > 0) {
			string dictname = filename.substr(0,filename.length()-4)+".dict";
			string outsname = filename.substr(0,filename.length()-4)+".out"; //Will ideally be the same as the original file
			decode(filename,dictname,outsname);
			continue;
		}

		ifstream file(filename);
		if(!file) {
			cout << "Error opening file.\n";
			continue;
		}

		//PHASE 1 - Histogram filename
		Node arr[256];
		noskipws(file);
		while (file) {
			char temp;
			file >> temp; //Equivalent to .get() since we have noskipws on
			if (!file || file.eof() || temp == EOF) break;
			arr[(unsigned char)temp].count++;
		}
		file.close();

		//Add data and optionally print
		for (int i = 0; i < 256; i++) {
			arr[i].data = i; //Copy the ASCII code in
			//if (arr[i].count > 0) cout << "arr[" << char(i) << "] : " << arr[i].count << endl;
		}

		//PHASE 2 - Heapify it
		Heap<Node> my_heap;
		for (int i = 0; i < 256; i++) {
			if (arr[i].count > 0) my_heap.push(arr[i]);
		}

		//Sanity Check
		if (my_heap.size() < 2) {
			cout << "Sorry, this code will only work if there's at least two kinds of letters.\n";
			exit(EXIT_FAILURE);
		}

		//PHASE 3 - Construct a binary trie
		Node *root = NULL; 
		while(my_heap.size() > 1) {
            //cout << "Reading top of priority queue:\n";
            //cout << my_heap.top().data << ":" << my_heap.top().count << endl;
            Node *first = new Node; //Allocate new memory
            *first = my_heap.top(); //Copy the top of the heap into the new memory
            my_heap.pop(); //Delete the top of the heap
            //cout << my_heap.top().data << ":" << my_heap.top().count << endl;
            Node *second = new Node;
            *second = my_heap.top();
            my_heap.pop();
            Node *combine = new Node;
            combine->count = ; //YOU: What should this intermediate node's count be?
            //cout << "New Node: " << combine->data << " - " << combine->count << endl;
            combine->left = ; //YOU: What should the left pointer point to?
            combine->right = ; //YOU: What should the right pointer point to?
            my_heap.push(*combine); //Copy the new node into the heap
            root = combine; //Move the root pointer up to the newest node
		}

		//PHASE 4 - Generate encoding strings
		if (!root) {
			cerr << "Trie generation failed!\n";
			exit(EXIT_FAILURE);
		}
		encode(root,arr); //YOU: Recursively encode array, write it up above

		//PHASE 5 - Write out dictionary
		ofstream dict(filename+".dict");
		for (int i = 0; i < 256; i++) 
			if (arr[i].count > 0)
				; //YOU: Write code to output "character: encoding", like "Q: 110111"
		dict.close();

		//PHASE 6 - Write out encoded file
		//Use ./binaryview.sh to view the encoded files
		BinaryWriter outs(filename+".enc");
		file.open(filename);
		noskipws(file);
		while (file) {
			char temp;
			file >> temp;
			//cout << "Read: " << temp << endl;
			if (!file || file.eof() || temp == EOF) break;
			unsigned char temp2 = temp;
			outs << arr[temp2].enc;
		}
		outs.close();

		//PHASE 7 - Calculate compression ratios
		int O = filesize(filename);
		int D = filesize(filename+".dict");
		int E = filesize(filename+".enc");
		cout.precision(3);
		cout << "Compression Ratio: " << O/double(D+E) << endl;
	}
}

//Extra Credit Section - decode the encrypted file
void decode(string encname, string dictname, string outsname) {
	BinaryReader br(encname,dictname,outsname);
	br.decode(); //Let it decode the entire file, let's not worry about doing it one >> at a time for performance reasons
}
