#pragma once

#include "searchable_bag.hpp"

class set
{
private:
	searchable_bag& bag;
public:
	set() = delete;
	set(searchable_bag& b);
	set(const set& other) = delete;
	set& operator=(const set& other) = delete;
	// ~set();

	bool has(int value) const;
	void insert(int);
	void insert(int*, int);
	void clear();
	void print() const;

	const searchable_bag& get_bag() const;
};



