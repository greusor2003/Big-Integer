#pragma once
#include "BigInt.h"

BigInt factorial(ullint);
// returns the factorial of int

BigInt nchoosek(ullint, ullint);
// returns the binomial coefficient; both arguments are non negative integers, the first >= the second 