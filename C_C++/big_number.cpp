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
	long long int tempAvRetenue;
	long long int tempApRetenue;
	long long int tempAvReste;
	long long int tempApReste;
	unsigned long long int i = 0; //represents the index of the loop of pMin.
	unsigned long long int j = 0; //represents the index of the loop of pMax.
	bool exist = false;

	//we loop for every "long long int" in pMin.
	while(itMin < pMin->end()){
		tempAvRetenue = 0;
		tempAvReste = 0;
		vector<short int> listeDigits;

		//we split all digits from the "long long int".
		for(unsigned long long int m = 1 ; m < DIGIT_PUISSANCE_10 ; m *= 10 )
			listeDigits.push_back((*itMin % (m * 10)) / m);

		//we loop for every "long long int" in pMax
		while(itMax < pMax->end()){
			tempApReste = 0;
			tempApRetenue = 0;

			//check if res has already a value at the index i+j
			if(res.listeNumbers.size() > (i + j)){
				temp = res.listeNumbers.at(i + j);
				exist = true;
			}
			else
				exist = false;

			temp = temp + tempAvRetenue + tempAvReste;
			//check if temp is greater than DIGIT_PUISSANCE - 1
			if((tempApRetenue = temp / DIGIT_PUISSANCE_10) != 0)
				temp = temp % DIGIT_PUISSANCE_10; //we just need the number before the DIGIT_NUMBER digit

			unsigned long long int k = 1;
			//we loop every digit of listeDigits
			for(unsigned long long int m = 0 ; m < DIGIT_NUMBER ; m++){
				//we check if the multiplication of the digit with the "long long int" from pMax is greater than (DIGIT_PUISSANCE_10/k) - 1
				if((tempApReste += ((*itMax * listeDigits.at(m)) / (DIGIT_PUISSANCE_10 / k))) != 0)
					temp2 += (((*itMax * listeDigits.at(m)) % (DIGIT_PUISSANCE_10 / k)) * k);
				else
					temp2 += (*itMax * listeDigits.at(m) * k);

				//we check if temp2 is greater than DIGIT_PUISSANCE_10 - 1
				if((tempApReste += (temp2 / DIGIT_PUISSANCE_10)) != 0)
					temp2 = temp2 % DIGIT_PUISSANCE_10;

				k *= 10;
			}

			temp += temp2;
			//we check if temp is greater than DIGIT_PUISSANCE_10 - 1
			if((tempApRetenue += temp / DIGIT_PUISSANCE_10) != 0)
				temp = temp % DIGIT_PUISSANCE_10;

			if(exist)
				res.listeNumbers.at(i + j) = temp;
			else
				res.listeNumbers.push_back(temp);

			tempAvRetenue = tempApRetenue;
			tempAvReste = tempApReste;
			temp = 0;
			temp2 = 0;
			j++;
			itMax++;
		}
		if(tempAvReste != 0 || tempAvRetenue != 0){
			// do{
				// if(res.listeNumbers.size() > (i + j)){
				// 	temp = res.listeNumbers.at(i + j);
				// 	exist = true;
				// }
				// else
				// 	exist = false;

				temp = /*temp + */tempAvRetenue + tempAvReste;
				if((tempApRetenue = temp / DIGIT_PUISSANCE_10) != 0)
					temp = temp % DIGIT_PUISSANCE_10;

				// if(exist)
				// 	res.listeNumbers.at(i + j) = temp;
				// else
					res.listeNumbers.push_back(temp);

				// tempAvRetenue = tempApRetenue;
				// j++;
			// }while(tempAvRetenue != 0);
		}
		j = 0;
		itMax = pMax->begin();
		itMin++;
		i++;
	}
	return res;
}

BigNum BigNum::operator - (BigNum& other){
	other.negative = !other.negative;
	return (*this + other);
}

BigNum BigNum::operator + (BigNum& other){
	BigNum res;
	res.negative = false;

	vector<long long int>* pMin = NULL;
	vector<long long int>* pMax = NULL;

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

	short int retenue = 0;
	long long int temp;
		
	if((negative && !other.negative) || (!negative && other.negative)){

		while(itMin < pMin->end()){
			temp = *itMax - *itMin - retenue;
			if(temp < 0)
			{
				temp += DIGIT_PUISSANCE_10;
				retenue = 1;
			}

			res.listeNumbers.push_back(temp);
			
			itMin++;
			itMax++;
		}
		while(itMax < pMax->end())
		{
			if(retenue){
				temp = *itMax - retenue;
				if(temp < 0)
					temp += DIGIT_PUISSANCE_10;
				else
					retenue = 0;
				res.listeNumbers.push_back(temp);
			}
			else
				res.listeNumbers.push_back(*itMax);
			itMax++;
		}

		while(res.listeNumbers.back() == 0 && res.listeNumbers.size() > 1)
			res.listeNumbers.pop_back();
	}
	else{
		if(negative && other.negative)
			res.negative = true;

		while(itMin < pMin->end()){
			temp = (*itMin) + (*itMax) + retenue;
			if((retenue = (temp / DIGIT_PUISSANCE_10)) != 0)
			{
				temp = temp % DIGIT_PUISSANCE_10;
			}
			res.listeNumbers.push_back(temp);
			itMin++;
			itMax++;
		}

		while(itMax < pMax->end()){
			if(retenue != 0){
				if(*itMax != (DIGIT_PUISSANCE_10 - 1)){
					res.listeNumbers.push_back(retenue + *itMax);
					itMax ++;
					retenue = 0;
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
				return res;
			}
		}
		if(retenue != 0)
			res.listeNumbers.push_back(retenue);
		return res;
	}
}

int main(){
	BigNum j("-9999999999999999999999999999999999999999999999999999999999999999999999999999");
	BigNum i("900000000000000000200000000000000");
	j = j * i;
	cout << j <<endl;
	//15 minutes multiplication 745000 numbers (500000 * 280000) ; 19 minutes multiplication 745000 numbers (350000 * 390000)
	//4.2 seconds addition 548000 numbers
	//2.0 seconds soustraction 548000numbers
}