#include <iostream>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <vector>

#define MAXDIGITS 100
#define PLUS 1
#define MINUS -1
using namespace std;

ifstream in("bignum.inp");
ofstream out("bignum.out");

typedef struct {
	char digits[MAXDIGITS];
	int signbit;
	int lastdigit;
}bignum;

void Initialize_bignum(bignum* c) {
	for (int i = 0; i < MAXDIGITS; i++) c->digits[i] = 0;
	c->lastdigit = 0;
	c->signbit = PLUS;
}

void add_bignum(bignum* a, bignum* b, bignum* c);

void digit_shift(bignum* n, int d) {
	int i;

	if ((n->lastdigit == 0) && (n->digits[0] == 0)) return;

	for (i = n->lastdigit; i >= 0; i--)
		n->digits[i + d] = n->digits[i];

	for (i = 0; i < d; i++) n->digits[i] = 0;

	n->lastdigit = n->lastdigit + d;
}


int compare_bignum(bignum* a, bignum* b) {

	int i;

	if ((a->signbit == MINUS) && (b->signbit == PLUS)) return PLUS;
	if ((a->signbit == PLUS) && (b->signbit == MINUS)) return MINUS;

	if (b->lastdigit > a->lastdigit) return (PLUS * a->signbit);
	if (a->lastdigit > b->lastdigit) return (MINUS * a->signbit);

	for (int i = a->lastdigit; i >= 0; i--) {
		if (a->digits[i] > b->digits[i]) return (MINUS * a->signbit);
		if (b->digits[i] > a->digits[i]) return (PLUS * a->signbit);
	}

	return 0;
}



void zero_justify(bignum* n) {

	while ((n->lastdigit > 0) && (n->digits[n->lastdigit] == 0))
		n->lastdigit--;

	if ((n->lastdigit == 0) && (n->digits[0] == 0))
		n->signbit = PLUS;
}


void gogo(string k, bignum* n) {

	if (k[0] == '-') {
		k.erase(k.begin(), k.begin() + 1);
	}

	int l = k.size() - 1;

	reverse(k.begin(), k.end());

	for (int i = 0; i < k.size(); i++) {
		n->digits[i] = k[i] - '0';
	}

	for (int i = l; i >= 0; i--) {

		if (n->digits[i] == 0)l--;
		else break;
	}
	n->lastdigit = l;
}


void subtract_bignum(bignum* a, bignum* b, bignum* c) {

	int borrow;
	int v;
	int i;

	Initialize_bignum(c);

	if ((a->signbit == MINUS) || (b->signbit == MINUS)) {
		b->signbit = -1 * b->signbit;
		add_bignum(a, b, c);
		b->signbit = -1 * b->signbit;
		return;
	}

	if (compare_bignum(a, b) == PLUS) {
		subtract_bignum(b, a, c);
		c->signbit = MINUS;
		return;
	}

	c->lastdigit = max(a->lastdigit, b->lastdigit);
	borrow = 0;

	for (int i = 0; i <= (c->lastdigit); i++) {
		v = (a->digits[i] - borrow - b->digits[i]);

		if (a->digits[i] > 0)
			borrow = 0;
		if (v < 0) {
			v = v + 10;
			borrow = 1;
		}

		c->digits[i] = (char)v % 10;
	}

	zero_justify(c);

}

void add_bignum(bignum* a, bignum* b, bignum* c) {

	int carry;
	int i;

	Initialize_bignum(c);

	if (a->signbit == b->signbit) {
		c->signbit = a->signbit;
	}
	else {
		if (a->signbit == MINUS) {
			a->signbit = PLUS;
			subtract_bignum(b, a, c);
			a->signbit = MINUS;
		}
		else {
			b->signbit = PLUS;
			subtract_bignum(a, b, c);
			b->signbit = MINUS;
		}
		return;
	}


	c->lastdigit = max(a->lastdigit, b->lastdigit) + 1;
	carry = 0;

	for (int i = 0; i <= (c->lastdigit); i++) {
		c->digits[i] = (char)(carry + a->digits[i] + b->digits[i]) % 10;
		carry = (carry + a->digits[i] + b->digits[i]) / 10;
	}

	zero_justify(c);
}


void multiply_bignum(bignum* a, bignum* b, bignum* c) {

	bignum row;
	bignum tmp;
	int i, j;

	Initialize_bignum(c);

	row = *a;

	for (i = 0; i <= b->lastdigit; i++) {
		for (j = 1; j <= b->digits[i]; j++) {
			add_bignum(c, &row, &tmp);
			*c = tmp;
		}
		digit_shift(&row, 1);
	}

	c->signbit = a->signbit * b->signbit;
	zero_justify(c);
}

int zero_check(bignum* n) {

	int check = 1;

	for (int i = n->lastdigit; i >= 0; i--) {

		if (n->digits[i] != 0) {
			check = 0;
			break;
		}
	}
	return check;
}

void divide_bignum(bignum* a, bignum* b, bignum* c) {

	bignum row;
	bignum tmp;

	int asign, bsign;
	int i, j;

	Initialize_bignum(c);
	c->signbit = a->signbit * b->signbit;

	asign = a->signbit;
	bsign = b->signbit;

	a->signbit = PLUS;
	b->signbit = PLUS;

	Initialize_bignum(&row);
	Initialize_bignum(&tmp);

	c->lastdigit = a->lastdigit;

	for (i = a->lastdigit; i >= 0; i--) {
		digit_shift(&row, 1);
		row.digits[0] = a->digits[i];
		c->digits[i] = 0;

		while (compare_bignum(&row, b) != PLUS) {
			c->digits[i]++;
			subtract_bignum(&row, b, &tmp);
			row = tmp;
		}
	}

	bignum tmp2;
	Initialize_bignum(&tmp2);
	gogo("1", &tmp2);

	bignum tmp3;

	if (c->signbit == -1 && zero_check(&row) == 0) {
		subtract_bignum(c, &tmp2, &tmp3);
		*c = tmp3;
	}

	zero_justify(c);

	a->signbit = asign;
	b->signbit = bsign;
}

void mode_bignum(bignum* a, bignum* b, bignum* c) {

	bignum row;
	bignum tmp;

	int asign, bsign;
	int i, j;

	Initialize_bignum(c);
	c->signbit = a->signbit * b->signbit;

	asign = a->signbit;
	bsign = b->signbit;

	a->signbit = PLUS;
	b->signbit = PLUS;

	Initialize_bignum(&row);
	Initialize_bignum(&tmp);

	c->lastdigit = a->lastdigit;

	for (i = a->lastdigit; i >= 0; i--) {
		digit_shift(&row, 1);
		row.digits[0] = a->digits[i];
		c->digits[i] = 0;

		while (compare_bignum(&row, b) != PLUS) {
			c->digits[i]++;
			subtract_bignum(&row, b, &tmp);
			row = tmp;
		}
	}

	bignum tmp3;
	bignum tmp2;
	Initialize_bignum(&tmp2);

	tmp3 = *b;
	tmp3.signbit = 1;

	if (c->signbit == -1 && zero_check(&row) == 0) {
		subtract_bignum(&tmp3, &row, &tmp2);
		*c = tmp2;
	}
	else
		*c = row;

	zero_justify(c);

	a->signbit = asign;
	b->signbit = bsign;
}

int main() {
	while (1) {
		bignum a, b, c;

		Initialize_bignum(&a);
		Initialize_bignum(&b);
		Initialize_bignum(&c);

		string a1, b1;

		char c1;

		in >> a1 >> c1 >> b1;

		if ((a1[0] == '0' && a1.size() == 1) && (b1[0] == '0' && b1.size() == 1))break;

		if (a1[0] == '-') {
			a.signbit = -1;
		}
		else a.signbit = 1;

		if (b1[0] == '-') {
			b.signbit = -1;
		}
		else b.signbit = 1;

		gogo(a1, &a);
		gogo(b1, &b);

		if (c1 == '+') {
			add_bignum(&a, &b, &c);
		}
		else if (c1 == '-') {
			subtract_bignum(&a, &b, &c);
		}
		else if (c1 == '*') {
			multiply_bignum(&a, &b, &c);
		}
		else if (c1 == '/') {
			divide_bignum(&a, &b, &c);
		}
		else {
			mode_bignum(&a, &b, &c);
		}

		string ret = "";

		if (c.signbit == -1) out << "-";

		for (int i = c.lastdigit; i >= 0; i--) {
			ret += c.digits[i] + '0';
		}
		out << ret << "\n";
	}
}