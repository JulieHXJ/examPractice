#include "bigint_str.hpp"

bigint& bigint::operator+=(const bigint& num){
	int carry = 0;
	int indexA = digits.size() - 1;
	int indexB = num.digits.size() - 1;
	std::string result;

	while(indexA >= 0 || indexB >= 0 || carry != 0) {
		int digitA = (indexA >= 0? digits[indexA] - '0' : 0);
		int digitB = (indexB >= 0? num.digits[indexB] - '0' : 0);
		int sum = digitA + digitB + carry;
		carry = sum / 10;
		result.push_back((sum % 10) + '0');
		indexA--;
		indexB--;
	}

	std::reverse(result.begin(), result.end());//!!
	digits = result;
	return(*this);
}

bigint bigint::operator+(const bigint& num) const{
	bigint temp(*this);
	temp += num;
	return(temp);
}
	
// increment
bigint& bigint::operator++(){
	(*this) += (bigint)1;
	return (*this);
}
	
bigint bigint::operator++(int){
	bigint temp(*this);
	++(*this);
	return temp;
}

// shift operators <<, >>, <<=, >>=
bigint& bigint::operator<<=(unsigned int n){
	if (digits != "0")
	{
		digits.append(n, '0');
	}
	//if digits is "0", do nothing, avoid leading zeros like "0000"
	return (*this);
}
	
bigint bigint::operator<<(unsigned int n) const{
	bigint temp(*this);
	temp <<= n;
	return (temp);
}
	
bigint& bigint::operator>>=(unsigned int n) {
	const unsigned int size = digits.size();
	if(n >= size)
	{
		digits = "0";
	} else {
		digits.erase(size - n, n);
	}
	return(*this);
}

bigint& bigint::operator>>=(const bigint& n){
	//convert bigint to unsigned long
	const unsigned long num = std::atol(n.digits.c_str());
	(*this) >>= num;
	return (*this);
}

// comparison for >, >=, <, <=, ==, !=
bool bigint::operator==(const bigint& other) const{
	return (digits == other.digits);
}

bool bigint::operator!=(const bigint& other) const{
	return !((*this) == other);
}

bool bigint::operator<(const bigint& other) const{
	if (digits.size() != other.digits.size())
	{
		return (digits.size() < other.digits.size());
	}
	return (digits < other.digits);
	
}
	
bool bigint::operator>(const bigint& other) const{
	return (other < (*this));
}
	
bool bigint::operator<=(const bigint& other) const{
	return !((*this) > other);
}
	
bool bigint::operator>=(const bigint& other) const{
	return !((*this) < other);
}