#pragma once
#include <cassert>
#include <cmath>
#include <iostream>
#include <cinttypes>
#include <vector>
#include <string>


typedef unsigned long long int ullint;

using namespace std;

class BigInt
{
public:

	BigInt(long long int);
	// constructor

	BigInt(vector<ullint>);
	// constructor

	BigInt(string);
	// constructor

	vector<ullint> getBigInt() const;
	// returns content

	static ullint getbase();
	// returns base

	short int getsign() const;
	// returns the sign of the big integer

	//BigInt& operator = (const BigInt&);
	// assignment operator

	BigInt& operator *= (const long long int);
	// multiplication by a signed integer

	BigInt& operator += (const BigInt&);
	// addition of BigInt to BigInt

	BigInt& operator -= (const BigInt&);
	// subtraction of BigInt from BigInt

	BigInt& operator *= (const BigInt&);
	// multiplication by BigInt (standard algorithm)

	BigInt& Kara(const BigInt& B);
	// wrapping of kara()

	BigInt& operator /= (const BigInt&);
	// returns quotient of division (standard algorithm).
	// !!! the used sign convention is so that the abs(remainder)
	// equals the remainder obtained if the operands were both positive.
	// the quotient IS NOT the floor function of the fraction when signs
	// of the operands are different .

	BigInt& operator %= (const BigInt&);
	// returns remainder of division (standard algorithm)

	bool operator < (const BigInt&);
	// inequality operator 

	bool operator == (const BigInt&);
	// equality test

	void divInt(const BigInt&, BigInt*, BigInt*);

	void printB();
	//prints the decimal form of the big integer represented by content

	void printB_tofile(const char*);
	//prints to the file whose name is pointed by the argument

	void printContent();
	// prints content

	ullint length();
	// returns the number of digits of BigInt's integral form representation
	// as printed out by printB()

private:

	vector<ullint> content;
	// 0 <= elements <= base-1

	short int sign;

	const static ullint base = 1000000000;
	// must be a power of 10 
	// pow(10,9) is max 

	const static unsigned int lbase = 9; //hardcoding
	// #of zeros in base

	const static int kara_depth = 217; //empirical value; hardcodeded; =1 for pure Karatsuba
	// # of digits below which Karatsuba's alg switches to regular multiplication

	void read_str(const string & str);
	// transforms string of characters (represententing digits) to vector of ullint

	void mult(vector<ullint>&, const ullint&);
	// updates by multiplication by a non negative integer

	vector<ullint> add_vec(const vector<ullint>&, const vector<ullint>&);
	// returns the componentwise sum of the parameters as if they were BigInt.content

	vector<ullint> subt_vec(const vector<ullint>&, const vector<ullint>&, bool* flag);
	// updates the first parameter by subtracting the second vector componentwise if the size 
	// of the first parameter >= the size of the second 

	void kara(vector<ullint>&, vector<ullint>&, vector<ullint>&);
	// Karatsuba multiplication of the first 2 args; result = the third arg

	void div1(const vector<ullint>&, const vector<ullint>&, ullint*, vector<ullint>*);
	// classic division algorithm: first argument is divided by the second when sizes permit;
	// the vectors are used as BigInt.content; ullint* argument is the one digit quotient of 
	// the division
};


bool infer( const vector<ullint>&, const vector<ullint>& );
// true if first arg < second arg as BigInt.content

void push_zeros_top( vector<ullint>&, size_t );
// auxiliary function --inserts size_t many zeros at the top of vector

void pad_zeros_tosize( vector<ullint>& , vector<ullint>& );
// auxiliary function -- adds zersos to the top of the shorter arg until its size equals the other's

void split_half( const vector<ullint>&, vector<ullint>&, vector<ullint>& );
// the last two args are changed so that each becomes one half of the first arg

