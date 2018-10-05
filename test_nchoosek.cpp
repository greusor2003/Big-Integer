//#pragma once
#include "BigIntLib.h"
#include <chrono>

using namespace std;

int main()
{
	cout << "Computing the number of subsets of k elements chosen from n distinct elements:" << endl;
	ullint n;
	ullint k;

	cout << "n = "; cin >> n;
	cout << "k = "; cin >> k;

	auto start = chrono::system_clock::now();

	BigInt N = nchoosek(n, k);

	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	//N.printB();
	N.printB_tofile("combinations_result.txt");
	cout << " combinations(" << n << "," << k << ") in" << endl;
	cout << elapsed_seconds.count() << " seconds\n";

	cout << "number of digits: " << N.length() << endl;
	cout << "result in combinations_result.txt" << endl;
	system("pause");
	return 0;
}




