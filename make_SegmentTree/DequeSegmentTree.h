#pragma once

#include "SegmentTree.h"

template <typename T, typename Op>
class DequeSegmentTree: public SegmentTree<T, Op> {
protected:
	int real_size_;			// 格納されている値の数
	int write_idx_;			// 次に書き込む値の位置

public:
	DequeSegmentTree(const int size, Op op, T identity)
		:SegmentTree<T, Op>(size, op, identity), real_size_(0), write_idx_(0)
	{
		/*
		*	@param
		*		capacity: 格納可能な最大量
		*		op: 親と子の関係
		*		identity: 何も入っていないときの値
		*/
	}

public:
	DequeSegmentTree(const std::vector<T>& vec, const int size, Op op, T identity) 
		:DequeSegmentTree(size, op, identity)
	{
		for (auto& ele : vec) {
			this->add(ele);
		}
	}

	/*-------------------- 書き込み ---------------------*/
public:
	inline void add(T new_data) {
		this->write(new_data, this->write_idx_);
		this->step_write_idx();
	}

	/*-------------------- write_idx管理--------------------*/
protected:
	inline void step_write_idx() { this->write_idx_ = (this->write_idx_ + 1) % this->size(); }


	/*-------------------- gettter ---------------------*/
public:
	inline int real_size() const { return this->real_size_; }
	inline int write_idx() const { return this->write_idx_; }
};