//Kevin Gallegos 1858764 PA8
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
	ifstream in;
	ofstream out;

	if (argc != 3) {
		cerr << "Error: Wrong amount of arguments, please do: <input file> <output file>" << endl;
	}
	in.open(argv[1]);
	if (!in.is_open()) {
		cerr << "Unable to open: " << argv[1] << endl;
	}
	out.open(argv[2]);
	if (!out.is_open()) {
		cerr << "Unable to write to file " << argv[2] << endl;
	}

	int lines = 0;
	string s;

	Dictionary D;
	while (getline(in, s)) {
		D.setValue(s, lines+1);
		lines++;
	}

	out<<D<<endl;

	out<<D.pre_string()<<endl;


	in.close();
	out.close();
	exit(EXIT_SUCCESS);
}
