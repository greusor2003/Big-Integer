//#pragma once
#include "BigInt.h"
#include <fstream> // for printing to file
//#include <algorithm>

/* costructors*/
BigInt::BigInt(long long int value)
{
	if (value < 0)
	{
		auto v = static_cast<ullint>(abs(value));
		assert(v < base);
		sign = -1;
		content = vector<ullint>(1, v);
	}
	else
	{
		auto v = static_cast<ullint>(value);
		assert(v < base);
		sign = 1;
		content = vector<ullint>(1, v);
	}
}


BigInt::BigInt(string str)
{
	if (str[0] == '-')
	{
		this->read_str(str.substr(1, str.size() - 1));

		if (content[0] == 0 && content.size() == 1)
			sign = 1;
		else
			sign = -1;
	}
	else
	{
		this->read_str(str);
		sign = 1;
	}
}


BigInt::BigInt(vector<ullint> v)
{
	sign = 1;
	if (not v.empty())
	{
		while (v.back() == 0)
			v.pop_back(); // insures no 0 digits at the top of BigInt

		if (v.empty())
			content = vector<ullint>(1, 0);
		else
			content = v;
	}
	else
		content = vector<ullint>(1, 0);
}


/* accessors */

vector<ullint> BigInt::getBigInt() const
{
	return content;
}


ullint BigInt::getbase()
{
	return base;
}


short int BigInt::getsign() const
{
	assert(sign == 1 || sign == -1);
	return sign;
}


/* private member methods  */

void BigInt::read_str(const string & str)
{
	const auto len = static_cast<size_t>(lbase);
	// the power of the base

	auto sz = str.size();

	auto q = sz / len;
	auto r = sz % len;

	for (auto k = 1; k <= q; k++)
	{
		ullint x = stoi(str.substr(sz - k * len, len));
		content.push_back(x);
	}

	if (r != 0)
	{
		content.push_back(static_cast<ullint> (stoi(str.substr(0, r))));
	}
}

vector<ullint> BigInt::add_vec(const vector<ullint>& a, const vector<ullint>& b)
{
	auto u = a;
	auto v = b;

	auto s1 = u.size();
	auto s2 = v.size();

	ullint carry = 0;

	if (s1 < s2)
	{
		u.swap(v);
		return add_vec(u, v);
	}
	else
	{
		for (auto k = 0; k < s2; k++)
		{
			u[k] += v[k] += carry;

			if (u[k] >= base)
			{
				u[k] -= base;
				carry = 1;
			}
			else
				carry = 0;
		}
		if (s1 > s2)
		{
			size_t k = s2;

			while (carry == 1 && k < s1)
			{
				u[k] += carry;

				if (u[k] > base)
				{
					u[k] -= base;
					k++;
				}
				else
					carry = 0;
			}
		}
		if (carry == 1)
			u.push_back(carry);
	}

	return u;
}


vector<ullint> BigInt::subt_vec(const vector<ullint>& a, const vector<ullint>& b, bool* flag)
{
	auto u = a;
	auto v = b;

	auto s1 = u.size();
	auto s2 = v.size();

	auto carry = 0;

	if (s1 < s2)
	{
		*flag = true; // changes state when vector::swap occurs
		u.swap(v);
		return subt_vec(u, v, flag);
	}
	else
	{
		if (s1 == s2)
		{
			auto k = s1 - 1;
			while (u[k] <= v[k] && k >= 0)
			{
				if (u[k] < v[k])
				{
					u.swap(v);
					*flag = true;
					break;
				}
				else
					k--;
			}
		} // s1 > s2

		for (auto k = 0; k < s2; k++)
		{
			auto r = static_cast<int>(u[k] - v[k] - carry);
			if (r >= 0)
			{
				u[k] = static_cast<ullint>(r);
				carry = 0;
			}
			else
			{
				u[k] = base + r;
				carry = 1;
			}
		}

		auto k = s2;

		while (carry != 0 && k < s1)
		{
			auto uc = static_cast<int>(u[k]);
			uc -= carry;
			//u[k] -= carry;
			if (uc < 0) //u[k] < 0
			{
				uc += base;
				//u[k] += base;
				u[k] = static_cast<ullint>(uc);
				k++;
			}
			else
			{
				carry = 0;
				u[k] = static_cast<ullint>(uc);
			}
		}
	}
	return u;
}


void BigInt::mult(vector<ullint>& a, const ullint& rhs )
{
	
	ullint prod=0;
    ullint q=0;
    ullint r=0;
		
	for (auto i = a.begin(); i != a.end(); i++)
	{
		prod = *i * rhs + q;
		*i = prod % base; 
		q = prod / base;
	}
         
	if (q > 0)
        	a.push_back(q);		
}


void push_zeros_top(vector<ullint>& u, size_t n)
{
	vector<ullint> vec(n, 0);
	u.insert(u.begin(), vec.begin(), vec.end());
}


void pad_zeros_tosize(vector<ullint>& u, vector<ullint>& v)
{
	if (u.size() < v.size())
		push_zeros_top(u, v.size() - u.size());
	if (u.size() > v.size())
		push_zeros_top(v, u.size() - v.size());
	// does nothing if u.size() == v.size()
}

void split_half(const vector<ullint>& v, vector<ullint>& v1, vector<ullint>& v2)
{
	auto k = v.size() / 2;
	if (k > 0)
	{
		v1.assign(v.begin(), v.begin() + k);
		v2.assign(v.begin() + k, v.end());
	}	
}

bool infer(const vector<ullint>& u, const vector<ullint>& v)
{
	if (u.size() > v.size())
		return false;

	if (u.size() < v.size())
		return true;

	auto N = u.size() - 1;

	auto s = 0;
	while (s <= N && u[N - s] >= v[N - s])
	{
		if (u[N - s] > v[N - s])
			return false;
		else
			s++;
	}

	if (s == N + 1)
		return false;
	else
		return true;
}


void BigInt::div1(const vector<ullint>& D, const vector<ullint>& d, ullint* q, vector<ullint>* r)
{
	vector<ullint> delta(d);
	auto n = delta.size() - 1;

	assert((D.size() == n + 1 || D.size() == n + 2));

	if (infer(D, d))
	{
		*q = 0;
		*r = D;
	}
	else
	{
		ullint X = 0; // must turn positive next
		bool flag = false; // for using subt_vec(vector, vector, bool*)
		auto bet = static_cast<ullint>(base / 2);
		if (delta[n] >= bet)
		{
			if (D.size() == n + 1)
			{
				*q = 1;
				*r = subt_vec(D, d, &flag);
			}

			if (D.size() == n + 2 and D[n + 1] < delta[n]) 
			{
				X = static_cast<ullint>((D[n + 1] * base + D[n]) / delta[n]); // d[n] != 0 
				auto y = delta;
				mult(y, X);
				while (infer(D, y))
				{
					y = delta;
					X--;
					mult(y, X);
				}
				*q = X;
				*r = subt_vec(D, y, &flag);
			}
		}
		else // delta[n] < bet
		{
			auto x = static_cast<ullint>(bet / d[n] + 1);
			auto y = delta;
			mult(y, x);
			while (y.size() > d.size())
			{
				y = delta;
				x--;
				mult(y, x);
			}

			auto z = D;
			mult(z, x);

			auto M = z.size() - 1;
			auto N = y.size() - 1;

			//ullint X = 0; // must change to positive values by subsequent instructions

			if (M == N)
				X = static_cast<ullint>(z[M] / y[N]);

			if (M == N + 1)
			{ // D[n] < d[n] -- assured by external call
				X = static_cast<ullint>((z[M] * base + z[M - 1]) / y[N]);
			}

			auto u = y;
			mult(y, X);
			while (infer(z, y))
			{
				X--;
				y = u;
				mult(y, X);
			}

			*q = X;
			mult(delta, X);
			*r = subt_vec(D, delta, &flag);
		}
	}
}


void BigInt::kara(vector<ullint>& u, vector<ullint>& v, vector<ullint>& r)
{	
	
	auto diff = (long long int)u.size() - (long long int)v.size();

	if (diff != 0)
		pad_zeros_tosize(u, v);

	if (u.size() == 1) // v.size() must be =1 too
	{
		ullint last = u[0] * v[0];
		
		if (last < base)
			r = vector<ullint>(1, last);
		else
		{
			r = vector<ullint>(1, last % base);
			r.push_back(last / base);			
		}
	}
	else
	{
		if ((long long int)u.size() / 2 < diff or (long long int)u.size() < kara_depth) // switch to the classical alg
		{
			BigInt X(u);
			BigInt Y(v);
			X *= Y;
			r = X.getBigInt();
			
			if (diff != 0)
				r.assign(r.begin() + abs(diff), r.end());
	
		}
		else
		{
			auto n = u.size();
			auto k = u.size() / 2;

			vector<ullint> u1, v1, u2, v2, u11, u22, add1, add2, mid;
			
			BigInt B(1U); //used to make vectors of the type BigInt::content

			split_half(u, u1, u2);
			split_half(v, v1, v2);

			kara(u1, v1, u11);
			B = BigInt(u11);
			u11 = B.getBigInt();
			
			kara(u2, v2, u22);
			B = BigInt(u22);
			u22 = B.getBigInt();
			
			add1 = add_vec(u1, u2);
			add2 = add_vec(v1, v2);
			
			kara(add1, add2, mid);
			B = BigInt(mid);
			mid = B.getBigInt();
			
			bool flag(false);

			auto sub1 = subt_vec(mid, u22, &flag);

			mid = subt_vec(sub1, u11, &flag);
			
			push_zeros_top(u22, 2 * k);
			push_zeros_top(mid, k);

			auto a1 = add_vec(u22, mid);
			r = add_vec(a1, u11);

			if (diff != 0)
				r.assign(r.begin() + abs(diff), r.end());
		}
	}
	
}


/* public and friend member methods */

bool BigInt::operator < (const BigInt& B)
{
	if (sign < B.sign)
		return true;
	else
	{
		if (sign > B.sign)
			return false;
		else //sign == B.sign
		{
			if (infer(content, B.content))
				if (sign == 1)
				{
					return true;
				}
				else
					return false;

			else
				if (sign == 1)
					return false;
				else
					return true;
		}
	}

}


bool BigInt::operator == (const BigInt& B)
{
	if (sign != B.sign)
		return false;
	else
	{
		if (content == B.content)
			return true;
		else
			return false;
	}
}


BigInt& BigInt::operator *= (const long long int rhs)
{
	if (rhs < 0)
	{
		sign *= -1;
		mult(content, static_cast<ullint>(-rhs));
	}
	else
		mult(content, static_cast<ullint>(rhs));

	return *this;
}


BigInt& BigInt::operator += (const BigInt& B)
{
	assert(sign == 1 || sign == -1);
	auto v = B.getBigInt();

	bool b = false;

	if (sign == B.getsign())
	{
		BigInt S = add_vec(content, v);
		S.sign = sign;
		*this = S;
		return *this;
	}
	else
	{
		BigInt S = subt_vec(content, v, &b);

		if (infer(content, v))
			if (B.getsign() == -1)
			{
				S.sign = -1;
				*this = S;
				return *this;
			}
			else
			{
				*this = S;
				return *this;
			}
		else
			if (B.getsign() == 1)
			{
				S.sign = -1;
				*this = S;
				return *this;
			}
			else
			{
				*this = S;
				return *this;
			}
	}
}


BigInt& BigInt::operator -= (const BigInt& B)
{
	auto X = B;
	X.sign = -1;
	*this += X;
	return *this;
}


BigInt& BigInt::operator *= (const BigInt& B)
// classic alg
{
	auto n = B.getBigInt().size();

	vector<ullint> p = content , s = content, v = B.getBigInt();
	
	mult(content, v[0]);

	for (size_t k = 1; k < n; k++)
	{
		mult(p, v[k]);
		push_zeros_top(p, k);
		content = add_vec(content, p);
		p = s;
	}

	sign *= B.getsign();
	return *this;
}



BigInt& BigInt::Kara(const BigInt& B)
{
	vector<ullint> v = B.getBigInt();
    vector<ullint> res(content.size()+v.size(),0); 	
	kara(content, v, res);
	sign *= B.getsign();
	content = BigInt(res).getBigInt();
	
	return *this;
}



BigInt& BigInt::operator /= (const BigInt& B)
{
	BigInt Q = 0;
	BigInt R = 0;
	divInt(B, &Q, &R);

	if (sign == B.getsign())
		Q.sign = 1;
	else
		Q.sign = -1;

	*this = Q;

	return *this;
}


BigInt& BigInt::operator %= (const BigInt& B)
{
	BigInt Q = 0;
	BigInt R = 0;
	divInt(B, &Q, &R);

	if (sign == -1)
		R.sign = -1;

	*this = R;

	return *this;
}


void BigInt::divInt(const BigInt& B, BigInt* Q, BigInt* R)
{
	// recursive function.
	// if divInt is used alone the quotient Q and the remainder R of the division by B
	// are correctly returned only if input Q = 0;

	assert(B.content != vector<ullint>(1, 0));

	auto quot = Q->content;
	auto rest = R->content;
	ullint q = 0;
	auto temp = content;

	auto n = B.content.size() - 1;

	auto m = temp.size() - 1;

	if (m == n or (m == n + 1 and temp.back() < B.content.back()))
	{
		div1(temp, B.content, &q, &rest);
		quot.insert(quot.begin(), q);
		*R = rest; //top zeros in rest discarded
		*Q = quot;
	}
	else
	{
		if (m > n)
		{
			vector<ullint> x;
			vector<ullint> y;
			x.assign(temp.end() - n - 1, temp.end());
			y.assign(temp.begin(), temp.end() - n - 1);

			if (infer(x, B.content))
			{
				temp.assign(temp.end() - n - 2, temp.end());
				y.pop_back();
			}
			else
				temp = x;

			div1(temp, B.content, &q, &rest);
			quot.insert(quot.begin(), q);

			*R = rest; //top zeros in rest discarded
			*Q = quot;

			if (m - temp.size() + 1 > 0)
			{
				(R->content).insert((R->content).begin(), y.begin(), y.end());
				BigInt T = R->content;
				T.divInt(B, Q, R);
			}

		}
		else // m < n
		{
			*Q = 0;
			*R = content;
		}
	}
}


void BigInt::printContent()
{
	for (auto i = content.size() - 1; i != -1; i--)
		cout << content[i] << " ";

	cout << endl;
}


void BigInt::printB()
{
	auto for_print = content;
	vector<ullint> test; // for the number of zeros to print ahead each content[i] < base

	if (not for_print.empty())
	{
		for (auto k = 0; k != lbase - 1; k++)
			test.push_back(static_cast<ullint>(pow(10, lbase - 1 - k)));

		if (sign == 1)
			cout << for_print.back();
		else
			cout << "-" << for_print.back();


		for (auto i = for_print.size() - 2; i != -1; i--)
		{
			auto k = 0;

			while (for_print[i] < test[k] && k < test.size())
			{
				cout << 0;
				k++;
			}

			cout << for_print[i];
		}
	}
	else
		cout << 0;

	cout << endl;
}

void BigInt::printB_tofile(const char* fname)
{
	ofstream fout(fname);

	if (not fout)
	{
		cout << "Unable to open " << fname << " for writing." << endl;
		exit(1);
	}

	auto for_print = content;
	vector<ullint> test; // for the number of zeros to print ahead each content[i] < base

	if (not for_print.empty())
	{
		for (auto k = 0; k != lbase - 1; k++)
			test.push_back(static_cast<ullint>(pow(10, lbase - 1 - k)));

		if (sign == 1)
			fout << for_print.back();
		else
			fout << "-" << for_print.back();


		for (auto i = for_print.size() - 2; i != -1; i--)
		{
			auto k = 0;

			while (for_print[i] < test[k] && k < test.size())
			{
				fout << 0;
				k++;
			}

			fout << for_print[i];
		}
	}
	else
		fout << 0;

	fout.close();
}

ullint BigInt::length()
{
	if (content.back() == 0)
		return 1;
	else
	{
		auto dig = static_cast<ullint>(log10(content.back())) + 1;
		auto s = lbase * static_cast<ullint>(content.size() - 1) + dig;
		return s;
	}
}
