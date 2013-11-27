#include <cstdlib>

#include "big_number.h"

BigNum::BigNum(const string s){
	string str = s;
	if(str.empty())
		throw "string empty";
	if(str[0] == '-'){
		if(str.size() < 2)
			throw "string not correct";
		else
			negative = true;
			str.erase(0,1);
	}
	else
		negative = false;

	for (int i = str.size() ; i > 0 ; i -= DIGIT_NUMBER){
		if(i - DIGIT_NUMBER <= 0)
			listeNumbers.push_back(strtoll(str.substr(0, i).c_str(), NULL, 10));
		else
			listeNumbers.push_back(strtoll(str.substr(i - DIGIT_NUMBER, DIGIT_NUMBER).c_str(), NULL, 10));
	}
}

BigNum::BigNum(const BigNum& other){
	listeNumbers = other.listeNumbers;
	negative = other.negative;
}

BigNum::BigNum(long long int i){
	if(i < 0)
		negative = true;
	else
		negative = false;

	listeNumbers.push_back(i);
}

BigNum& BigNum::operator = (const BigNum& other){
	listeNumbers = other.listeNumbers;
	negative = other.negative;
	return *this;
}

BigNum& BigNum::operator = (long long int i){
	listeNumbers.clear();
	if(i < 0)
		negative = true;
	else
		negative = false;

	listeNumbers.push_back(i);
}

//not implemented
BigNum BigNum::operator / (BigNum& other){
	return *this;
}

BigNum BigNum::operator * (BigNum& other){
	BigNum res; //result

	//we check what sign the result will be.
	if((negative && !other.negative) || (!negative && other.negative))
		res.negative = true;
	else
		res.negative = false;

	vector<long long int>* pMin;
	vector<long long int>* pMax;

	//pMax has to point to BigNum which has the longest listeNumber. It is the opposite for pMin.
	if(listeNumbers.size() > other.listeNumbers.size()){
		pMin = &(other.listeNumbers);
		pMax = &listeNumbers;
	}
	else{
		pMin = &listeNumbers;
		pMax = &(other.listeNumbers);
	}

	vector<long long int>::iterator itMin = pMin->begin();
	vector<long long int>::iterator itMax = pMax->begin();
	long long int temp = 0;
	long long int temp2 = 0;
	long long int tempBfDeduction;
	long long int tempAfDeduction;
	long long int tempBfRest;
	long long int tempAfRest;
	unsigned long long int i = 0; //represents the index of the loop of pMin.
	unsigned long long int j = 0; //represents the index of the loop of pMax.
	bool exist = false;

	//we loop for every "long long int" in pMin.
	while(itMin < pMin->end()){
		tempBfDeduction = 0;
		tempBfRest = 0;
		vector<short int> listeDigits;

		//we split all digits from the "long long int".
		for(unsigned long long int m = 1 ; m < DIGIT_PUISSANCE_10 ; m *= 10 )
			listeDigits.push_back((*itMin % (m * 10)) / m);

		//we loop for every "long long int" in pMax
		while(itMax < pMax->end()){
			tempAfRest = 0;
			tempAfDeduction = 0;

			//check if res has already a value at the index i+j
			if(res.listeNumbers.size() > (i + j)){
				temp = res.listeNumbers.at(i + j);
				exist = true;
			}
			else
				exist = false;

			temp = temp + tempBfDeduction + tempBfRest;
			//check if temp is greater than DIGIT_PUISSANCE - 1
			if((tempAfDeduction = temp / DIGIT_PUISSANCE_10) != 0)
				temp = temp % DIGIT_PUISSANCE_10; //we just need the number before the DIGIT_NUMBER digit

			unsigned long long int k = 1;
			//we loop every digit of listeDigits
			for(unsigned long long int m = 0 ; m < DIGIT_NUMBER ; m++){
				//we check if the multiplication of the digit with the "long long int" from pMax is greater than (DIGIT_PUISSANCE_10/k) - 1
				if((*itMax * listeDigits.at(m) / (DIGIT_PUISSANCE_10 / k)) != 0){
					tempAfRest += *itMax * listeDigits.at(m) / (DIGIT_PUISSANCE_10 / k);
					temp2 += (((*itMax * listeDigits.at(m)) % (DIGIT_PUISSANCE_10 / k)) * k);
				}
				else
					temp2 += (*itMax * listeDigits.at(m) * k);

				//we check if temp2 is greater than DIGIT_PUISSANCE_10 - 1
				if(temp2 / DIGIT_PUISSANCE_10 != 0){
					tempAfRest += temp2 / DIGIT_PUISSANCE_10;
					temp2 = temp2 % DIGIT_PUISSANCE_10;
				}
				k *= 10;
			}

			temp += temp2;
			//we check if temp is greater than DIGIT_PUISSANCE_10 - 1
			if(temp / DIGIT_PUISSANCE_10 != 0){
				tempAfDeduction += temp / DIGIT_PUISSANCE_10;
				temp = temp % DIGIT_PUISSANCE_10;
			}

			if(exist)
				res.listeNumbers.at(i + j) = temp;
			else
				res.listeNumbers.push_back(temp);

			tempBfDeduction = tempAfDeduction;
			tempBfRest = tempAfRest;
			temp = 0;
			temp2 = 0;
			j++;
			itMax++;
		}
		//there is no more "long long int" in pMax to read but there is maybe a deduction to add.
		if(tempBfRest != 0 || tempBfDeduction != 0){
				temp = /*temp + */tempBfDeduction + tempBfRest;
				if((tempAfDeduction = temp / DIGIT_PUISSANCE_10) != 0)
					temp = temp % DIGIT_PUISSANCE_10;
				
				res.listeNumbers.push_back(temp);
		}
		//we have read all digits of one "long long int" of pMin.
		j = 0;
		itMax = pMax->begin();
		itMin++;
		i++;
	}

	//we get rid of the 0 present et the beginning.
	while(res.listeNumbers.back() == 0 && res.listeNumbers.size() > 1)
		res.listeNumbers.pop_back();

	//we get rid of the sign "-" if the result is 0
	if(res.listeNumbers.size() == 1 && res.listeNumbers.back() == 0)
		res.negative = false;
	return res;
}

BigNum BigNum::operator - (BigNum& other){
	//soustract A from B is the same as add -A and B.
	other.negative = !other.negative;
	return (*this + other);
}

BigNum BigNum::operator + (BigNum& other){
	BigNum res;
	res.negative = false;

	vector<long long int>* pMin = NULL;
	vector<long long int>* pMax = NULL;

	//decide who is pMin and pMax. decide also if the result is negative or positive
	if(listeNumbers.size() > other.listeNumbers.size()){
		pMin = &(other.listeNumbers);
		pMax = &listeNumbers;
		if(negative)
			res.negative = true;
	}
	else if(listeNumbers.size() < other.listeNumbers.size()){
		pMin = &listeNumbers;
		pMax = &(other.listeNumbers);
		if(other.negative)
			res.negative = true;
	}
	else{
		vector<long long int>::reverse_iterator it1 = listeNumbers.rbegin();
		vector<long long int>::reverse_iterator it2 = other.listeNumbers.rbegin();
		while(it1 < listeNumbers.rend() && pMin == NULL){
			if(*it1 > *it2){
				pMin = &(other.listeNumbers);
				pMax = &listeNumbers;
				if(negative)
					res.negative = true;
			}
			else if(*it1 < *it2){
				pMin = &listeNumbers;
				pMax = &(other.listeNumbers);
				if(other.negative)
					res.negative = true;
			}
			it1++;
			it2++;
		}
		if(pMin == NULL){
			pMin = &listeNumbers;
			pMax = &(other.listeNumbers);
		}
	}

	vector<long long int>::iterator itMin = pMin->begin();
	vector<long long int>::iterator itMax = pMax->begin();

	short int deduction = 0;
	long long int temp;
		
	//algorithm of two number having the same sign is diffrent of two numbers having opposite signs.
	if((negative && !other.negative) || (!negative && other.negative)){

		//we are soustracting *itMin from *itMax because they have opposite sign.
		while(itMin < pMin->end()){
			temp = *itMax - *itMin - deduction;
			if(temp < 0)
			{
				temp += DIGIT_PUISSANCE_10; //to understand this, see 15 - 6 when the number of digit is 1.
				deduction = 1;
			}

			res.listeNumbers.push_back(temp);
			
			itMin++;
			itMax++;
		}
		//itMin is fully read. Now we just have to add the rest in itMax considering the deduction.
		while(itMax < pMax->end())
		{
			if(deduction){
				temp = *itMax - deduction;
				if(temp < 0)
					temp += DIGIT_PUISSANCE_10;
				else
					deduction = 0;
				res.listeNumbers.push_back(temp);
			}
			else
				res.listeNumbers.push_back(*itMax);
			itMax++;
		}
	}
	else{
		//if the two nulbers are negative
		if(negative && other.negative)
			res.negative = true;

		//we doing the addition itMin and itMax and the deduction.
		while(itMin < pMin->end()){
			temp = (*itMin) + (*itMax) + deduction;
			if((deduction = (temp / DIGIT_PUISSANCE_10)) != 0)
			{
				temp = temp % DIGIT_PUISSANCE_10;
			}
			res.listeNumbers.push_back(temp);
			itMin++;
			itMax++;
		}

		//add the rest of itMax considering the deduction
		while(itMax < pMax->end()){
			if(deduction != 0){
				if(*itMax != (DIGIT_PUISSANCE_10 - 1)){
					res.listeNumbers.push_back(deduction + *itMax);
					itMax ++;
					deduction = 0;
				}
				else{
					res.listeNumbers.push_back(0);
					itMax++;
				}
			}
			else{
				while(itMax < pMax->end()){
					res.listeNumbers.push_back(*itMax);
					itMax ++;
				}
				break;
			}
		}
		if(deduction != 0)
			res.listeNumbers.push_back(deduction);
	}

	//we get rid of the 0 present et the beginning.
	while(res.listeNumbers.back() == 0 && res.listeNumbers.size() > 1)
		res.listeNumbers.pop_back();

	//we get rid of the sign "-" if the result is 0
	if(res.listeNumbers.size() == 1 && res.listeNumbers.back() == 0)
		res.negative = false;

	return res;
}

int main(){
	BigNum j("1");
	BigNum i("555555555555555555555555555555555555555555555555555");
	j = j + i;
	cout << j <<endl;
	//15 minutes multiplication 745000 numbers (500000 * 280000) ; 19 minutes multiplication 745000 numbers (350000 * 390000)
	//4.2 seconds addition 548000 numbers
	//2.0 seconds soustraction 548000numbers
}