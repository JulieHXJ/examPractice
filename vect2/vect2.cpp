#include "vect2.hpp"

vect2::vect2(){
	this->x = 0;
	this->y = 0;
}

vect2::vect2(int x, int y) {
	this->x = x;
	this->y = y;
}


vect2::vect2(const vect2& other){
	this->x = other.x;
	this->y = other.y;
}

vect2& vect2::operator=(const vect2& other){
	if (this != &other)
	{
		this->x = other.x;
		this->y = other.y;
	}
	return (*this);
}

vect2::~vect2(){}

//for printing and assign v1[1] = 12;
int& vect2::operator[](int index){
	if(index == 0)
		return this->x;
	else
		return this->y;
}

//for printing v1[0] and v1[1], only readable
int vect2::operator[](int index) const{
	if(index == 0)
		return this->x;
	else
		return this->y;
}

//++v
vect2& vect2::operator++(){
	this->x++;
	this->y++;
	return (*this);

}

//v++
vect2 vect2::operator++(int) {
	vect2 temp = (*this);
	++(*this);
	return (temp);
}

vect2& vect2::operator--(){
	this->x -= 1;
	this->y -= 1;
	return (*this);
}

vect2 vect2::operator--(int){
	vect2 temp = (*this);
	--(*this);
	return (temp);
}

vect2& vect2::operator+=(const vect2& obj){
	this->x += obj.x;
	this->y += obj.y;
	return(*this);
}

vect2& vect2::operator-=(const vect2& obj) {
	this->x -= obj.x;
	this->y -= obj.y;
	return(*this);
}

vect2& vect2::operator*=(int num) {
	this->x *= num;
	this->y *= num;
	return (*this);
}

vect2 vect2::operator+(const vect2& obj) const {
	vect2 temp(*this);
	temp += obj;
	return (temp);
}

vect2 vect2::operator-(const vect2& obj) const {
	vect2 temp(*this);
	temp -= obj;
	return (temp);
}

vect2 vect2::operator*(int num) const {
	vect2 temp(*this);
	temp *= num;
	return (temp);
}

//-v2
vect2 vect2::operator-() const {
	vect2 temp = (*this);
	temp.x = -temp.x;
	temp.y = -temp.y;
	return(temp);
}

//comparison
bool vect2::operator==(const vect2& obj) const {
	if (x == obj.x && y == obj.y)
	{
		return true;
	}
	return false;
}

bool vect2::operator!=(const vect2& obj) const {
	if (*this == obj)
	{
		return false;
	}
	return true;
}

//for 3 * v2; 
vect2 operator*(int num, const vect2& obj) {
	vect2 temp(obj);
	temp *= num;
	return (temp);
}

std::ostream& operator<<(std::ostream& os, const vect2& v){
	os << "{" << v[0] << ", " << v[1] << "}";
	return os;
}