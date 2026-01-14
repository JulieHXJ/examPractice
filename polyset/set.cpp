#include "set.hpp"

set::set(searchable_bag& b) : bag(b) {};

bool set::has(int value) const{
	return (bag.has(value));
}

//no duplication allowed
void set::insert(int value){
	if (!(this->has(value)))
	{
		bag.insert(value);
	}
	
}

//利用上一个函数，检查后插入
void set::insert(int* data, int size){
	for (int i = 0; i < size; i++)
	{
		this->insert(data[i]);
	}
	
}
	
void set::clear(){
	bag.clear();
}

void set::print() const{
	bag.print();
}


const searchable_bag& set::get_bag() const{
	return bag;
}