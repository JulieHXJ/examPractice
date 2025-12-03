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

vect2::~vect2(){
}

int& vect2::operator[](int index){
	if(index == 0){
		return this->x;
	}
	else 
	{
		return this->y;
	}
	
}


int vect2::operator[](int index) const{
	if(index == 0){
		return this->x;
	}
	else
	{
		return this->y;
	}
}

vect2& vect2::operator++(){
	this->x += 1;
	this->y += 1;
	return (*this);

}

vect2 vect2::operator++(int num) {
	(void)num;
	vect2 temp = (*this);
	this->x += 1;
	this->y += 1;
	return (temp);
}

vect2& vect2::operator--(){
	this->x -= 1;
	this->y -= 1;
	return (*this);
}

vect2 vect2::operator--(int num){
	(void)num;
	vect2 temp = (*this);
	this->x -= 1;
	this->y -= 1;
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
	vect2 temp = (*this);
	temp.x += obj.x;
	temp.y += obj.y;
	return (temp);
}

vect2 vect2::operator-(const vect2& obj) const {
	vect2 temp = (*this);
	temp.x -= obj.x;
	temp.y -= obj.y;
	return (temp);
}

vect2 vect2::operator*(int num) const {
	vect2 temp = (*this);
	temp.x *= num;
	temp.y *= num;
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
	if ((this->x == obj.x) && (this->y == obj.y))
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


//不能直接使用x/y，因为是private。需要调用public函数
vect2 operator*(int num, const vect2& obj) {
	vect2 temp(obj);
	temp *= num;
	return (temp);
}



std::ostream& operator<<(std::ostream& os, const vect2& v){
	os << "{" << v.getX() << ", " << v.getY() << "}";
	return os;
}