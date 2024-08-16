#pragma once

#include <iostream>
#include <string>
using namespace std;
namespace checkers {
	static bool checkIfCinPass(string errorMsg) {
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << errorMsg << endl;
			return false;
		}
		return true;
	}
	static bool checkIfNumberInRange(unsigned short const& lowerLimit, unsigned short const& upperLimit, unsigned short const& num) {
		if (num >= lowerLimit && num <= upperLimit)	return true;
		else {
			cerr << "The number should be between "
				<< to_string(lowerLimit)
				<< " and "
				<< to_string(upperLimit)
				<< endl;
			return false;
		}
	}
}