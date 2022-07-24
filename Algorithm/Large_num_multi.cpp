#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> LargeInteger;
const int threshold = 2;

int cnt = 0;

void roundup_carry(LargeInteger& v) {
	int carry = 0;
	for (int i = 0; i < v.size(); i++) {
		v[i] += carry;
		carry = v[i] / 10;
		v[i] = v[i] % 10;
	}
	if (carry != 0)
		v.push_back(carry);
}

void rounddown_carry(LargeInteger &v){
	for(int i=0;i<v.size()-1;i++){
		if(v[i]<0){
			v[i]+=10;
			v[i+1]-=1;
		}
	}
}

void ladd(LargeInteger a, LargeInteger b, LargeInteger& c) {
	c.resize(max(a.size(), b.size()));
	fill(c.begin(), c.end(), 0);
	for (int i = 0; i < c.size(); i++) {
		if (i < a.size()) c[i] += a[i];
		if (i < b.size()) c[i] += b[i];
	}
	roundup_carry(c);
}

void lsub(LargeInteger a, LargeInteger b, LargeInteger& c) {
	c.resize(max(a.size(), b.size()));
	fill(c.begin(), c.end(), 0);
	for (int i = 0; i < c.size(); i++) {
		if(a.size()>b.size()){
			c[i] = a[i];
			if(i<b.size()){
				c[i] -= b[i];
			}
		}
		else{
			c[i] = b[i];
			if(i<a.size()){
				c[i] -= a[i];
			}
		}
	}
	rounddown_carry(c);
}
void lmult(LargeInteger a, LargeInteger b, LargeInteger& c) {
	c.resize(a.size() + b.size() - 1);
	fill(c.begin(), c.end(), 0);
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < b.size(); j++)
			c[i + j] += a[i] * b[j];
	roundup_carry(c);
}

void pow_by_exp(LargeInteger u, int m, LargeInteger& v) {
	if (u.size() == 0)
		v.resize(0);
	else {
		v.resize(u.size() + m);
		fill(v.begin(), v.end(), 0);
		copy(u.begin(), u.end(), v.begin() + m);
	}
}
void remove_leading_zeros(LargeInteger& v) {
	while (!v.empty() && v.back() == 0)
		v.pop_back();
}
void rem_by_exp(LargeInteger u, int m, LargeInteger& v) {
	if (u.size() == 0)
		v.resize(0);
	else {
		// Note that u.size() can be smaller than m.
		int k = m < u.size() ? m : u.size();
		v.resize(k);
		copy(u.begin(), u.begin() + k, v.begin());
		remove_leading_zeros(v);
	}
}
void div_by_exp(LargeInteger u, int m, LargeInteger& v) {
	if (u.size() == 0)
		v.resize(0);
	else {
		int k = m;
		v.resize(u.size() - k + 1);
		copy(u.begin() + k, u.end(), v.begin());
		remove_leading_zeros(v);

	}
}
void prod(LargeInteger u, LargeInteger v, LargeInteger& r) {
	LargeInteger x, y, w, z;
	LargeInteger t1, t2, t3, t4, t5, t6, t7, t8;
	int n = max(u.size(), v.size());
	if (u.size() == 0 || v.size() == 0)
		r.resize(0);
	else if (n <= threshold)
		lmult(u, v, r);
	else {
		int m = n / 2;
		div_by_exp(u, m, x); rem_by_exp(u, m, y);
		div_by_exp(v, m, w); rem_by_exp(v, m, z);
		// t2 <- prod(x,w) * 10^(2*m)
		prod(x, w, t1); pow_by_exp(t1, 2 * m, t2);
		// t6 <- (prod(x,z)+prod(w,y)) * 10^m
		prod(x, z, t3); prod(w, y, t4); ladd(t3, t4, t5); pow_by_exp(t5, m, t6);
		// r <- t2 + t6 + prod(y, z)
		prod(y, z, t7);
		ladd(t2, t6, t8); ladd(t8, t7, r);
	}
	cnt++;
}

void prod2(LargeInteger u, LargeInteger v, LargeInteger& r) {
	
	cnt++;
	LargeInteger x, y, w, z, r2, p, q;
	LargeInteger t1, t2, t3, t4, t5, t6, t7, t8;
	int n = max(u.size(), v.size());
	if (u.size() == 0 || v.size() == 0)
		r.resize(0);
	else if (n <= threshold)
		lmult(u, v, r);
	else {
		int m = n / 2;
		div_by_exp(u, m, x); rem_by_exp(u, m, y);
		div_by_exp(v, m, w); rem_by_exp(v, m, z);
		// t2 <- prod(x,w) * 10^(2*m)
		ladd(x, y, t1);	ladd(w, z, t2);
		prod(t1, t2, r2);
		prod(x, w, p);
		prod(y, z, q);

		pow_by_exp(p,2*m,t1);

		lsub(r, q, t2);
		lsub(t2, q, t3);
		pow_by_exp(t3, m, t4);

		ladd(t1, t4, t5);
		ladd(t5, q, r);
	}
}
int main() {
	string str1, str2;
	cin >> str1 >> str2;
	LargeInteger x(str1.size());
	LargeInteger y(str2.size());
	LargeInteger res(max(str2.size(), str1.size()));
	int j = 0;
	for (int i = str1.size() - 1; i >= 0; i--) {
		x[j++] = (str1[i] - 48);
	}
	j = 0;
	for (int i = str2.size() - 1; i >= 0; i--) {
		y[j++]=(str2[i] - 48);
	}

	prod2(x, y, res);

	cout << cnt << endl;
	remove_leading_zeros(res);

	for (int i = res.size() - 1; i >= 0; i--) {
		cout << res[i];
	}
}