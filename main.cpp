//#pragma once
#include "BigIntLib.h"
#include <chrono>

int main()
{
	std::string str1, str2;
	cout << "enter one big integer, B =  " << endl;
	cin >> str1;

	BigInt B = str1;

	cout << "enter another big integer, C =  " << endl;
	cin >> str2;
	cout << endl;

	BigInt C = str2;

	cout << "B < C: " << (B < C) << endl;
	cout << "B = C: " << (B == C) << endl;
	
	BigInt M = B;
	
	auto start = chrono::system_clock::now();

	B.Kara(C);

	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;

	B.printB();
	cout << string(25, '*') << endl;
	cout << "Karatsuba mutiplication in " << elapsed_seconds.count() << " seconds\n";
	cout << string(25, '*') << endl;

	start = chrono::system_clock::now();

	M *= C;

	end = chrono::system_clock::now();
	elapsed_seconds = end - start;

	M.printB();
	cout << string(25, '*') << endl;
	cout << " Regular multiplication in " << elapsed_seconds.count() << " seconds\n";
	cout << string(25, '*') << endl;
	
	BigInt A = str1;
	start = chrono::system_clock::now();

	A += C;

	end = chrono::system_clock::now();
	elapsed_seconds = end - start;

	A.printB();
	cout << "adding in " << elapsed_seconds.count() << " seconds\n";
	cout << string(25, '*') << endl;

	BigInt S = str1;
	start = chrono::system_clock::now();

	S -= C;

	end = chrono::system_clock::now();
	elapsed_seconds = end - start;

	S.printB();
	cout << "subtracting in " << elapsed_seconds.count() << " seconds\n";
	cout << string(25, '*') << endl;

	BigInt D = str1;
	start = chrono::system_clock::now();

	D /= C;

	end = chrono::system_clock::now();
	elapsed_seconds = end - start;

	D.printB();
	cout << "dividing in " << elapsed_seconds.count() << " seconds\n";
	cout << string(25, '*') << endl;

	BigInt R = str1;
	start = chrono::system_clock::now();

	R %= C;

	end = chrono::system_clock::now();
	elapsed_seconds = end - start;

	R.printB();
	cout << "remainder in " << elapsed_seconds.count() << " seconds\n";
	cout << string(25, '*') << endl;

	//system("pause");
	return 0;
}
