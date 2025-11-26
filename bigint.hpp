#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class bigint
{
private:
	// std::string digits;
	std::vector<int> digits; // store each digit separately in right order

public:
	bigint(); // 默认值 = 0
	~bigint();
	// constructor takes number
	bigint(unsigned int num);// 用普通 int 初始化 
	// copy constructor for bigint e(d);
	bigint(const bigint &other);
	// assign
	bigint& operator=(const bigint &other);

	//print helper
	std::string getNumbers() const;

	// addition +, +=, ++i, i++
	bigint& operator+=(const bigint& num);//修改原对象（先写）
	bigint operator+(const bigint& num) const;//返回新对象
	bigint& operator++(); // prefix ++i 返回本身
	bigint operator++(int); // postfix i++ 返回修改前旧值


	// shift operators <<, >>, <<=, >>=
	bigint operator<<(unsigned int n)const;//返回新对象
	bigint operator>>(unsigned int n)const;
	bigint& operator<<=(unsigned int n);//修改当前对象乘以10（push_back/append）
	bigint& operator>>=(unsigned int n);//删掉当前（pop_back)

	unsigned int to_uint(const bigint& obj) const;
	bigint& operator>>=(const bigint& n);


	// comparison for >, >=, <, <=, ==, !=
	// 	长度不同 → 长度长的更大
	// 长度相同 → 从高位开始逐位比较
	// 相等 → 所有 digit 一样
	bool operator<(const bigint& other) const;
	bool operator==(const bigint& other) const;
	bool operator>(const bigint& other) const;
	bool operator<=(const bigint& other) const;
	bool operator>=(const bigint& other) const;
	bool operator!=(const bigint& other) const;
};

std::ostream& operator<<(std::ostream& os, const bigint& obj);




#endif // BIGINT_HPP