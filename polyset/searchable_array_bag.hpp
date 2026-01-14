#pragma once

#include "array_bag.hpp"
#include "searchable_bag.hpp"


// 实现 bool has(int) const
// 提供 OCF（可以简单调用父类）
class searchable_array_bag : public array_bag, public searchable_bag
{
public:
	searchable_array_bag();
	searchable_array_bag(const searchable_array_bag& other);
	searchable_array_bag& operator=(const searchable_array_bag& other);
	~searchable_array_bag();
	bool has(int) const;
};

