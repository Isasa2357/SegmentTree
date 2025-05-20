#pragma once

#include "SegmentTree.h"

template <typename T, typename Op>
class DequeSegmentTree: public SegmentTree<T, Op> {

	int real_size_;			// �i�[����Ă���l�̐�
	int write_idx_;			// ���ɏ������ޒl�̈ʒu

	DequeSegmentTree(const int size, Op op, T identity)
		:SegmentTree(size, op, identity), real_size_(0), write_idx_(0)
	{
		/*
		*	@param
		*		capacity: �i�[�\�ȍő��
		*		op: �e�Ǝq�̊֌W
		*		identity: ���������Ă��Ȃ��Ƃ��̒l
		*/
	}

	DequeSegmentTree(const std::vector<T>& vec, const int size, Op op, T identity) 
		:DequeSegmentTree(size, op, identity)
	{
		for (auto& ele : vec) {
			this->write(vec, this->write_idx_);
		}
	}

	/*-------------------- write_idx�Ǘ� --------------------*/
	void step_write_idx() { 
		this->write_idx_ = (this->write_idx_ + 1) % this->size();
	}




	/*-------------------- gettter ---------------------*/

	inline int real_size() const { return this->real_size_; }
	inline int write_idx() const { return this->write_idx_; }
};

