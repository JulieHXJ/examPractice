#ifndef BIGINT_VEC_HPP
#define BIGINT_HPP

#include <iostream>
#include <vector>

class bigint
{
private:
	std::vector<int> digits; // store each digit separately in right order

public:
	bigint() { digits.push_back(0); }; //default 0
	~bigint() {};
	bigint(unsigned int num);
	bigint(const bigint &other): digits(other.digits) {};


	//print helper
	std::string getNumbers() const;

	// addition +, +=
	bigint& operator+=(const bigint& num);//overwrite current object, may have leading 0
	bigint operator+(const bigint& num) const;//return new object
	// increment ++
	bigint& operator++(); // prefix ++i 
	bigint operator++(int); // postfix i++ 


	// shift operators <<, >>, <<=, >>=
	bigint& operator<<=(unsigned int n);
	bigint operator<<(unsigned int n)const;
	bigint& operator>>=(unsigned int n);
	
	bigint operator>>(unsigned int n)const;
	// unsigned int to_uint(const bigint& obj) const;
	bigint& operator>>=(const bigint& n);


	// comparison for >, >=, <, <=, ==, !=
	bool operator<(const bigint& other) const;
	bool operator==(const bigint& other) const;
	bool operator>(const bigint& other) const;
	bool operator<=(const bigint& other) const;
	bool operator>=(const bigint& other) const;
	bool operator!=(const bigint& other) const;

	// normalize leading 0
	void normalize();
};

std::ostream& operator<<(std::ostream& os, const bigint& obj);

#endif // BIGINT_HPP