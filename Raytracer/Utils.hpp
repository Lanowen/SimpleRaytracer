#pragma once

#include <string>
#include <sstream>

using namespace std;

class Utils{
public:
	template<class T>
	static T parseString(string s){
		T temp;
		stringstream ss;

		ss << s;
		ss >> temp;

		return temp;
	}
};