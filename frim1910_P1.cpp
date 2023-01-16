//#pragma warning(disable : 4996)
//Farago Richard 512 frim1910
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class NullavalValoOsztas{
public:
	string err = "Error: Nullaval valo osztas!\n";
};

class MyInt{
private:
	int sign;	//szam elojele
	int n;		//szamjegyek szama
	char* s;	//szamjegyek
	int compare(MyInt& myInt); //osszehasonlit 2 szamot
	MyInt& shift();
	MyInt add(MyInt& myInt);
	MyInt sub(MyInt& myInt);
	MyInt mul(MyInt& myInt);
	MyInt div(MyInt& myInt);
public:
	MyInt();
	MyInt(int sign, int n, const char* s);
	MyInt(const MyInt& myInt);
	MyInt(const string& s);
	MyInt(int x);
	MyInt(long int x);
	~MyInt();
	ostream& print(ostream& out);
	MyInt& operator =(MyInt myInt);
	MyInt operator +(MyInt& myInt);
	MyInt& operator +=(MyInt& myInt);
	MyInt operator -(MyInt& myInt);
	MyInt& operator -=(MyInt& myInt);
	MyInt operator *(MyInt& myInt);
	MyInt& operator *=(MyInt& myInt);
	MyInt operator /(MyInt& myInt);
	MyInt& operator /=(MyInt& myInt);
	MyInt& operator ++();
	MyInt operator ++(int);
	MyInt& operator --();
	MyInt operator --(int);
};

MyInt::MyInt() {
	this->sign = 0;
	this->n = 1;
	this->s = new char[n + 1];
	strcpy(this->s,"0");
}

MyInt::MyInt(int sign, int n, const char* s) {
	int i;
	for(i=0; s[i] == '0'; i++);
	this->sign = sign;
	this->n = n - i;
	this->s = new char[n + 1];
	strcpy(this->s, s+i);
}

MyInt::MyInt(const MyInt& myInt) {
	this->sign = myInt.sign;
	this->n = myInt.n;
	this->s = new char[this->n + 1];
	strcpy(this->s,myInt.s);
}

MyInt::MyInt(const string& s){
	this->n = s.length();
	this->s = new char [n+1];
	for(int i=0; i<=this->n; i++){
		this->s[i] = s[i];
	}
	if(this->s[0] == '-'){
		strcpy(this->s,this->s + 1);
		this->n--;
		this->sign = -1;
	}
	else if(this->s[0] != '0'){
		this->sign = 1;
	}
	else{
		this->sign = 0;
		delete[] this->s;
		this->n = 1;
		this->s = new char [this->n+1];
		strcpy(this->s,"0");
	}
}

MyInt::MyInt(int x) {
	if (!x) {
		this->sign = 0;
	}
	else if (x > 0) {
		this->sign = 1;
	}
	else {
		this->sign = -1;
		x *= -1;
	}
	int y = x;
	this->n = 0;
	while (y) {
		y /= 10;
		(this->n)++;
	}
	this->s = new char[this->n + 1];
	sprintf(this->s,"%d",x);
}

MyInt::MyInt(long int x) {
	if (!x) {
		this->sign = 0;
	}
	else if (x > 0) {
		this->sign = 1;
	}
	else {
		this->sign = -1;
		x *= -1;
	}
	long int y = x;
	this->n = 0;
	while (y) {
		y /= 10;
		(this->n)++;
	}
	this->s = new char[this->n + 1];
	sprintf(this->s, "%ld", x);
}

MyInt::~MyInt() {
	delete this->s;
}

ostream& MyInt::print(ostream& out) {
	if (sign == -1) {
		out << "-";
	}
	return out<<s;
}

ostream& operator <<(ostream &out, MyInt myInt) {
	return myInt.print(out);
}

int MyInt::compare(MyInt& myInt) {
	int i = 0, j = 0, nn = this->n, mm = myInt.n;
	if (nn < mm) {
		return -1;
	}
	else if (nn > mm) {
		return 1;
	}
	else {
		char* s1 = this->s, * s2 = myInt.s;
		while (s1[i] == s2[j] && (i < nn && j < mm)) {
			i++;
			j++;
		}
		if (s1[i] == s2[j]) {
			return 0;
		}
		else if (s1[i] < s2[j]) {
			return -1;
		}
		else {
			return 1;
		}
	}
}

MyInt& MyInt::shift() {
	char* tmp = new char[this->n + 1];
	strcpy(tmp, this->s);
	delete[] this->s;
	this->s = new char[this->n + 2];
	strcpy(this->s, tmp);
	this->s[this->n] = '0';
	this->s[++this->n] = '\0';
	return *this;
}

MyInt MyInt::add(MyInt& myInt) {
	if (!this->sign || !myInt.sign) {
		if (!this->sign && !myInt.sign) {
			return MyInt();
		}
		else if (!this->sign) { 
			return MyInt(myInt);
		}
		else {
			return MyInt(*this);
		}
	}
	else if (this->sign == myInt.sign) {
		int i = this->n - 1, j = myInt.n - 1, sum = 0;
		MyInt tmp1(*this), tmp2(myInt), newInt(this->sign, ((i>j)?(i+1):(j+1)), "");
		char* s1 = tmp1.s, * s2 = tmp2.s, * s3 = newInt.s;
		newInt.n = 0;
		while (i >= 0 && j >= 0) {
			sum += ((s1[i--] - '0') + (s2[j--] - '0'));
			s3[newInt.n++] = (sum % 10) + '0';
			sum /= 10;
		}
		while (i >= 0) {
			sum += (s1[i--] - '0');
			s3[newInt.n++] = (sum % 10) + '0';
			sum /= 10;
		}
		while (j >= 0) {
			sum += (s2[j--] - '0');
			s3[newInt.n++] = (sum % 10) + '0';
			sum /= 10;
		}
		if (sum) {
			s3[newInt.n++] = sum + '0';
		}
		s3[newInt.n] = 0;
		for (int l = 0; l <= (newInt.n - 1) / 2; l++) {
			char aux = s3[l];
			s3[l] = s3[newInt.n - l - 1];
			s3[newInt.n - l - 1] = aux;
		}
		return newInt;
	}
	else {
		if(this->sign == -1){
			MyInt tmp(1,this->n,this->s);
			return myInt.sub(tmp);
		}
		else if(myInt.sign == -1){
			MyInt tmp(1,myInt.n,myInt.s);
			return this->sub(tmp);
		}
	}
}

MyInt MyInt::sub(MyInt& myInt) {
	if (!this->sign || !myInt.sign) {
		if (!this->sign && !myInt.sign) {
			return MyInt();
		}
		else if (!this->sign) {
			myInt.sign *= (-1);
			return MyInt(myInt);
		}
		else {
			return MyInt(*this);
		}
	}
	else if (this->sign == myInt.sign) {
		int e = this->compare(myInt);
		if (!e) {
			return MyInt();
		}
		else {
			int i = this->n - 1, j = myInt.n - 1;
			MyInt tmp1(*this), tmp2(myInt), newInt(0, ((i > j) ? (i+1) : (j+1)), "");
			char* s1 = tmp1.s, * s2 = tmp2.s, * s3 = newInt.s;
			newInt.n = 0;

			if (e == 1) {
				while (i >= 0 && j >= 0) {
					if (s1[i] - '0' >= s2[j] - '0') {
						s3[newInt.n++] = (s1[i--] - '0') - (s2[j--] - '0') + '0';
					}
					else {
						int l = i - 1;
						while (s1[l] == '0') {
							l--;
						}
						s1[l++]--;
						while (l < i) {
							s1[l++] = '9';
						}
						s3[newInt.n++] = (s1[i--] - '0') + (10 - (s2[j--] - '0')) + '0';
					}
				}
			}
			else {
				while (i >= 0 && j >= 0) {
					if (s2[j] - '0' >= s1[i] - '0') {
						s3[newInt.n++] = (s2[j--] - '0') - (s1[i--] - '0') + '0';
					}
					else {
						int l = j - 1;
						while (s2[l] == '0') {
							l--;
						}
						s2[l++]--;
						while (l < j) {
							s2[l++] = '9';
						}
						s3[newInt.n++] = (s2[j--] - '0') + (10 - (s1[i--] - '0')) + '0';
					}
				}
			}
			if (e == 1) {
				while (i >= 0) {
					s3[newInt.n++] = s1[i--];
				}
				while (s3[newInt.n - 1] == '0') {
					newInt.n--;
				}
				newInt.sign = this->sign;
			}
			else {
				while (j >= 0) {
					s3[newInt.n++] = s2[j--];
				}
				while (s3[newInt.n - 1] == '0') {
					newInt.n--;
				}
				newInt.sign = myInt.sign * (-1);
			}
			s3[newInt.n] = 0;
			for (int l = 0; l <= (newInt.n - 1) / 2; l++) {
				char aux = s3[l];
				s3[l] = s3[newInt.n - l - 1];
				s3[newInt.n - l - 1] = aux;
			}
			return newInt;
		}
	}
	else {
		MyInt tmp(myInt.sign*(-1),myInt.n,myInt.s);
		return this->add(tmp);
	}
}

MyInt MyInt::mul(MyInt& myInt) {
	if (!this->sign || !myInt.sign) {
		return MyInt();
	}
	else {
		int newSign = this->sign * myInt.sign;
		MyInt tmp(*this), tmp2(myInt);
		if(tmp.sign == -1){
			tmp.sign = 1;
		}
		if(tmp2.sign == -1){
			tmp2.sign = 1;
		}
		int mm = myInt.n - 1;
		MyInt newInt;
		char* s2 = tmp2.s;
		int i = mm, e = 0;
		while (s2[i] == '0') {
			e++;
			i--;
		}
		int f = 0;
		while (i >= 0) {
			MyInt sum;
			for (int j = 1; j <= s2[i] - '0'; j++) {
				sum += tmp;
			}
			if (i != mm - e) {
				f++;
				int k = f;
				while (k > 0) {
					sum.shift();
					k--;
				}
			}
			i--;
			newInt += sum;
		}
		while (e) {
			e--;
			newInt.shift();
		}
		newInt.sign = newSign;
		newInt.s[newInt.n] = 0;
		return newInt;
	}
}

MyInt MyInt::div(MyInt& myInt) {
	if(!this->sign || this->compare(myInt) == -1){
		return MyInt();
	}
	else if(!myInt.sign){
		throw NullavalValoOsztas();
	}
	else{
		MyInt newInt(1), tmp(*this), tmp2(myInt);
		if(tmp.sign == -1){
			tmp.sign = 1;
		}
		if(tmp2.sign == -1){
			tmp2.sign = 1;
		}
		int newSign = this->sign * myInt.sign;
		int nn = this->n - 1, mm = myInt.n - 1;
		MyInt x(10);
		for(int i=1; i<=nn-mm; i++){
			newInt *= x;
		}
		MyInt sum(newInt);
		sum *= tmp2;
		int i=0, j = sum.n;
		while(tmp.compare(tmp2) == 1){
			int db = 0;
			while(tmp.compare(sum) >= 0){
				tmp -= sum;
				db++;
			}
			newInt.s[i++] = db + '0';
			if(sum.compare(tmp2) == 1){
				sum.n--;
				sum.s[--j] = 0;
			}
		}
		for(i=0; newInt.s[i] == '0'; i++);
		strcpy(newInt.s,newInt.s+i);
		newInt.n -= i;
		newInt.sign = newSign;
		return newInt;
	}
}

MyInt& MyInt::operator =(MyInt myInt) {
	this->sign = myInt.sign;
	this->n = myInt.n;
	delete[] this->s;
	this->s = new char[myInt.n + 1];
	strcpy(this->s, myInt.s);
	return *this;
}

MyInt MyInt::operator +(MyInt& myInt) {
	return this->add(myInt);
}

MyInt MyInt::operator -(MyInt& myInt) {
	return this->sub(myInt);
}

MyInt& MyInt::operator +=(MyInt& myInt) {
	return (*this = (*this + myInt));
}

MyInt& MyInt::operator -=(MyInt& myInt) {
	return (*this = (*this - myInt));
}

MyInt MyInt::operator *(MyInt& myInt) {
	return this->mul(myInt);
}

MyInt MyInt::operator /(MyInt& myInt) {
	return this->div(myInt);
}

MyInt& MyInt::operator *=(MyInt& myInt) {
	return (*this = (*this * myInt));
}

MyInt& MyInt::operator /=(MyInt& myInt) {
	return (*this = (*this / myInt));
}

MyInt& MyInt::operator ++() {
	MyInt tmp(1);
	return (*this += tmp);
}

MyInt MyInt::operator ++(int) {
	MyInt cpy(*this), tmp(1);
	*this += tmp;
	return cpy;
}

MyInt& MyInt::operator --() {
	MyInt tmp(1);
	return (*this -= tmp);
}

MyInt MyInt::operator --(int) {
	MyInt cpy(*this), tmp(1);
	*this -= tmp;
	return cpy;
}

int main() {
	string x1, x2;
	char muv;
	
	/*fstream in("input.dat",ios::in);
	
	while(in>>x1>>x2>>muv){
		MyInt a(x1), b(x2);
		switch(muv){
			case '+':{
				cout << a + b << endl;
				break;
			}
			case '-':{
				cout << a - b << endl;
				break;
			}
			case '*':{
				cout << a * b << endl;
				break;
			}
			case '/':{
				try{
					cout << a / b << endl;
				}
				catch(NullavalValoOsztas e){
					cout << e.err;
				}
				break;
			}
		}
	}
	
	in.close();*/
	
	MyInt a(-1, 20, "23762187362187362187");
	MyInt b(1, 30, "376487316487326483274687648732");
	MyInt c(1, 34, "4223762187323432432432462187362187");
	MyInt d(-1, 39, "832749832376487316487326483274687648732");
	MyInt e(1, 51, "234768194687463827649831768321764982764821374741872");
	MyInt f(1, 8, "12123213");
	MyInt g(-1, 59, "52253452234768194687463827649831768321764982764821374741872");
	MyInt h(0, 1, "0");
	
	cout << a << " * " << b << " = " << a * b << endl;
	cout << c << " * " << d << " = " << c * d << endl;
	try{
		cout << e << " / " << f << " = " << e / f << endl;
	}
	catch(NullavalValoOsztas e){
		cout << e.err;
	}
	try{
		cout << g << " / " << h << " = " << g / h << endl;
	}
	catch(NullavalValoOsztas e){
		cout << e.err;
	}
	return 0;
}