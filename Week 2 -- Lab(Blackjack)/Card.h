#pragma once
#include <ctime>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

class Card
{
private:
	//Class Attributes
	char suit;
	char face;
	short value;

	static bool randomizerSeeded;

public:
	//Constructor and Destructor
	Card();
	~Card();
	string toString();
	bool flipAceToOne();

	inline char getSuit() { return suit; }
	inline char getFace() { return face; }
	inline short getValue() { return value; }
};

