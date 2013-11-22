#pragma once
#include <fstream>
#include <string>
#include <streambuf>

using namespace std;

class IFileHandle : public ifstream {
public:
	IFileHandle(string filename) : ifstream() {
		exceptions ( ifstream::failbit);
		open(filename);	
		exceptions ( NULL );
	}

	virtual ~IFileHandle() {
		close();
	}

	string getAsString(){
		string str;

		return str.assign((std::istreambuf_iterator<char>(*this)), std::istreambuf_iterator<char>());
	}
};
