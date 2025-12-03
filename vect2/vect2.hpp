
#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
private:
	int x;
	int y;
public:
	vect2();
	vect2(int x, int y);
	vect2(const vect2 &other);// copy constructor
	vect2& operator=(const vect2 &other);
	~vect2();



	int getX() const {return x;}
	int getY() const {return y;}

	int& operator[](int index);
	int operator[](int index) const;

	// ++, --, non-const
	vect2& operator++();//change itself
	vect2 operator++(int num);//change value and return old
	vect2& operator--();
	vect2 operator--(int num);


	// calculations (return itself)
	vect2& operator+=(const vect2& obj);
	vect2& operator-=(const vect2& obj);
	vect2& operator*=(int num);

	// return new object
	vect2 operator+(const vect2& obj) const;
	vect2 operator-(const vect2& obj) const;
	vect2 operator*(int num) const; // v3 * 2


	// minus -v2
	vect2 operator-() const;


	// comparison
	bool operator== (const vect2& obj) const;
	bool operator!= (const vect2& obj) const;
	
};

//3 * v2
vect2 operator*(int num, const vect2& obj);


std::ostream& operator<<(std::ostream& os, const vect2& v);







#endif