//#pragma once
#include "BigIntLib.h"
#include <chrono>

using namespace std::chrono;

int main() 
{
	int n = 0;
	while (n != -1)
	{
		cout << "enter a non negative integer (n <= 999999999) to find its factorial,\n or -1 to quit: ";
		cin >> n;
		if (n != -1)
		{
			n = static_cast<ullint>(n);
			BigInt F = 1;
			auto start = chrono::system_clock::now();
	
				 F = factorial(n);
			
			auto end = chrono::system_clock::now();
			chrono::duration<double> elapsed_seconds = end - start;
			
			//F.printB();
			//F.printContent();
			cout << endl;
			cout << n << "! in " << elapsed_seconds.count() << " seconds\n";
			cout << endl;
			cout << n << "!" << " has " << F.length() << " many digits " << endl;
			cout << "See MyFactorial.txt file for the result." << endl;
			cout << string(50, '*') << endl;
			
			F.printB_tofile("MyFactorial.txt");
		}
	}

	//system("pause");
	return 0;
}
