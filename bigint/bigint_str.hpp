#ifndef BIGINT_STR_HPP
#define BIGINT_STR_HPP

#include <iostream>
#include <algorithm>

class bigint
{
private:
	std::string digits; 

public:
	bigint(): digits("0") {}; //default 0
	~bigint() {};
	bigint(unsigned int num): digits(std::to_string(num)) {};
	bigint(const bigint &other): digits(other.digits) {};

	//print helper
	std::string getNumbers() const {return digits;};

	// addition +, +=
	bigint& operator+=(const bigint& num);//overwrite current object, may have leading 0
	bigint operator+(const bigint& num) const;//return new object
	// increment
	bigint& operator++(); // prefix ++i 
	bigint operator++(int); // postfix i++ 

	// shift operators <<, >>, <<=, >>=
	bigint& operator<<=(unsigned int n);
	bigint operator<<(unsigned int n)const;
	bigint& operator>>=(unsigned int n);
	bigint operator>>(unsigned int n)const;
	
	// unsigned int to_uint(const bigint& obj) const;
	bigint operator<<(const bigint& other)const;
		bigint operator>>(const bigint& other)const;
		bigint& operator<<=(const bigint& other);
	bigint& operator>>=(const bigint& n);

	// comparison for >, >=, <, <=, ==, !=
	bool operator==(const bigint& other) const;
	bool operator!=(const bigint& other) const;
	bool operator<(const bigint& other) const;
	bool operator>(const bigint& other) const;
	bool operator<=(const bigint& other) const;
	bool operator>=(const bigint& other) const;
};

std::ostream& operator<<(std::ostream& os, const bigint& obj){
	os << obj.getNumbers();
	return (os);
}

#endif // BIGINT_STR_HPP