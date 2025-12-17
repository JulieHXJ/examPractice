#include "bigint.hpp"

bigint::bigint()
{
	digits.push_back(0);
}
bigint::~bigint()
{}

bigint:: bigint(unsigned int num)
{
	if(num == 0)
	{
		digits.push_back(0);
		return;
	}
	std::vector<int> temp;//reversed digits
	while(num > 0)
	{
		temp.push_back(num % 10);
		num /= 10;
	}
	for(int i = temp.size() - 1; i >= 0; i--)
	{
		digits.push_back(temp[i]);
	}
}

bigint::bigint(const bigint &other)
{	
	digits = other.digits;
}

bigint& bigint::operator=(const bigint &other){
	if(this != &other){
		digits = other.digits;
	}
	return(*this);
}

std::string bigint::getNumbers() const {
	std::string output;
	for (size_t i = 0; i < digits.size(); i++)
	{
		output += '0' + digits[i];
	}
	return(output);
}

void bigint::normalize(){
	while(digits.size() > 1 && digits[0] == 0){
		digits.erase(digits.begin());
	}
	if(digits.empty()){
		digits.push_back(0);
	}
}

bigint& bigint::operator+=(const bigint& num) {

	int digitA;
	int digitB;
	int carry = 0;
	int indexA = digits.size() - 1;
	int indexB = num.digits.size() - 1;
	std::vector<int> result;

	while(indexA >= 0 || indexB >= 0 || carry != 0) {
		digitA = (indexA >= 0? digits[indexA] : 0);
		digitB = (indexB >= 0? num.digits[indexB] : 0);
		int res = digitA + digitB + carry;
		if (res >= 10)
		{
			carry = 1;
		}
		else
			carry = 0;
		result.push_back(res % 10);
		indexA--;
		indexB--;
	}
	//reverse result and write back to digits
	digits.clear();
	for (size_t i = 0; i < result.size(); i++)
	{
		digits.push_back(result[result.size() - 1 - i]);
	}
	normalize();	
	return(*this);
}

bigint bigint::operator+(const bigint& num) const {
	bigint res = (*this);
	res += num;
	return(res);
}

// 前置 ++a 
bigint& bigint::operator++(){
	(*this) += bigint(1);
	return(*this);
}

// 后置 a++
bigint bigint::operator++(int) {
	bigint temp = (*this);
	++(*this);
	return(temp);
}

//在 _digits 末尾 push_back(0) n 次
bigint& bigint::operator<<=(unsigned int n)
{
	if (digits.size() == 1 && digits[0] == 0)
	{
		return(*this);
	}
	for (unsigned int i = 0; i < n; i++)
	{
		digits.push_back(0);
	}
	normalize();//ex: 1099 << 1
	return(*this);
}

// 左移operator<<（返回新对象)逻辑：
// 复制一个临时对象 tmp（拷贝构造）
// 对 tmp 做 <<= n
// 返回 tmp
bigint bigint::operator<<(unsigned int n) const {
	bigint temp = (*this);
	temp <<= n;
	return(temp);
}


bigint& bigint::operator>>=(const bigint& num){
	//put digits in to unsigned int
	unsigned int n = 0;
	for (unsigned int i = 0; i < num.digits.size(); i++){
		n = n * 10 + num.digits[i];
	}

	//if int >= size return 0;
	if (n >= digits.size())
	{
		digits.clear();
		digits.push_back(0);
		return(*this);
	}
	for(unsigned int i = 0; i < n; i++){
		digits.pop_back();
	}
	normalize();
	return (*this);
}

bool bigint::operator<(const bigint& other) const {
	int len1 = digits.size();
	int len2 = other.digits.size();
	if(len1 != len2)
		return(len1 < len2);
	for (int i = 0; i < len1; i++) {
		if (digits[i] != other.digits[i])
		{
			return (digits[i] < other.digits[i]);
		}
	}
	return false;
}

bool bigint::operator>(const bigint& other) const {
	return(other < (*this));
}

bool bigint::operator==(const bigint& other) const {
	if(digits.size() != other.digits.size())
		return(false);
	for (size_t i = 0; i < digits.size(); i++)
	{
		if(digits[i] != other.digits[i])
			return(false);
	}
	return(true);
}


bool bigint::operator<=(const bigint& other) const{
	return ((*this) < other || (*this) == other);
}

bool bigint::operator>=(const bigint& other) const{
	return((*this) > other || (*this) == other);
}

bool bigint::operator!=(const bigint& other) const{
	return (!((*this) == other));
}


std::ostream& operator<<(std::ostream& os, const bigint& obj){
	os << obj.getNumbers();
	return(os);
}