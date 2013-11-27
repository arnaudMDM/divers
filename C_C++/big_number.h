#ifndef _BIG_NUM_
#define _BIG_NUM_
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdio>

#define DIGIT_NUMBER 17
#define DIGIT_PRINTF "%.17lld"
#define DIGIT_PUISSANCE_10 100000000000000000

using namespace std;

class BigNum{
public:
	BigNum(){};
	BigNum(const string s);
	~BigNum(){};
	BigNum(const BigNum& other);
	BigNum(long long int i);
	vector<long long int>& getListeNumbers(){return listeNumbers;}
	bool getNegatif(){return negatif;}
	BigNum& operator = (const BigNum& other);
	BigNum& operator = (long long int i);
	BigNum operator + (BigNum& other);
	BigNum operator - (BigNum& other);
	BigNum operator * (BigNum& other);
	BigNum operator / (BigNum& other);
protected:
	vector<long long int> listeNumbers;
	bool negatif;
};

ostream& operator << (ostream& os, BigNum& bigNum){
	vector<long long int> liste = bigNum.getListeNumbers();
	char buffer[DIGIT_NUMBER + 2];
	vector<long long int>::reverse_iterator it = liste.rbegin();
	while(it < liste.rend()){
		if(it != liste.rbegin())
			sprintf(buffer, DIGIT_PRINTF,*it);
		else{
			if(bigNum.getNegatif()){
				buffer[0] = '-';
				sprintf(buffer+1,"%lld",*it);
			}
			else
				sprintf(buffer,"%lld",*it);
		}
		os << buffer;
		it++;
	}
	return os;
}

#endif