#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <utility>
#include <tuple>
#include <exception>

template <typename T, typename Op>
class SegmentTree {
private:
	// �؂̊Ǘ�
	std::vector<T> tree_;
	int size_;
	T identity_;

	// �q�Ɛe�̊֌W
	Op operation_;

	/*-------------------- �R���X�g���N�^ --------------------*/

	// �z���n�����Ƃɂ�菉����
public:
	SegmentTree(const std::vector<T>& vec, Op operation, const T identity)
		: size_(vec.size()), identity_(identity), operation_(operation)
	{
		// �؂̍\�z
		int n = 1;
		while (n < this->size()) n <<= 1;
		int tree_size = 2 * n - 1;
		this->tree_.resize(tree_size, identity);
		for (auto i = 0; i < this->size(); ++i) this->tree_[conv_leaf_idx2tree_idx(i)] = vec[i];
		recalcurate();
	}

	// size�̂ݓn���C��̃Z�O�����g�c���[�����
public:
	SegmentTree(const int size, Op operation, const T identity)
		: size_(size), identity_(identity), operation_(operation)
	{
		// �؂̍\�z
		int n = 1;
		while (n < size) n <<= 1;
		int tree_size = 2 * n - 1;
		this->tree_.resize(tree_size, identity);
	}

	/*-------------------- �m�[�h�ւ̏������� --------------------*/

public:
	void write(T& new_data, const int idx) {
		// @param
		//   new_data: �������܂��f�[�^
		//	 index: �������݈ʒu(leaf_idx)

		// if (0 <= idx && idx < this.size) throw std::out_of_range;

			// �m�[�h�֏�������
		int tree_idx = conv_leaf_idx2tree_idx(idx);
		propagate(new_data, tree_idx);
	}

	/*-------------------- �N�G�� --------------------*/
public:
	inline T query(int left, int right) const {
		// �N�G�������s [left, right)

		T res_left = this->identity_;
		T res_right = this->identity_;
		left = conv_leaf_idx2tree_idx(left);
		right = conv_leaf_idx2tree_idx(right);

		while (left < right) {
			if (!(left & 1)) {
				res_left = this->operation_(res_left, this->tree_[left]);
				left++;
			}
			if (!(right & 1)) {
				right--;
				res_right = this->operation_(this->tree_[right], res_right);
			}
			left = parent_idx(left);
			right = parent_idx(right);
		}
		return this->operation_(res_left, res_right);
	}

	/*-------------------- �؂̍\�z --------------------*/
protected:
	void propagate(const T new_data, const int write_tree_idx) {
		// �t�ɏ�������
		this->tree_[write_tree_idx] = new_data;

		// �����m�[�h���X�V
		int seek_idx = write_tree_idx;
		while (seek_idx != 0) {
			// �e�ֈړ�
			seek_idx = parent_idx(seek_idx);

			// �e���X�V
			T lc = leftchild(seek_idx);
			T rc = rightchild(seek_idx);
			this->tree_[seek_idx] = this->operation_(lc, rc);
		}
	}

protected:
	void recalcurate() {
		for (auto i = conv_leaf_idx2tree_idx(0) - 1; i >= 0; --i) {
			T lc = leftchild(i), rc = rightchild(i);
			this->tree_[i] = this->operation_(lc, rc);
		}
	}

protected:
	/*-------------------- �C���f�b�N�X �v�Z --------------------*/
	inline int leftchild_idx(const int parent_idx) const { return 2 * parent_idx + 1; }				// �eidx���獶�qidx���v�Z
	inline int rightchild_idx(const int parent_idx) const { return 2 * parent_idx + 2; }			// �eidx����E�qidx���v�Z
	inline int parent_idx(const int child_idx) const { return (child_idx - 1) / 2; }				// �qidx����eidx���v�Z

	inline int conv_tree_idx2leaf_idx(const int tree_idx) const { return tree_idx - this->tree_.size() / 2; }		// tree_idx��leaf_idx�ɕϊ�
	inline int conv_leaf_idx2tree_idx(const int leaf_idx) const { return leaf_idx + this->tree_.size() / 2; }		// leaf_idx��tree_idx�ɕϊ�

	/*-------------------- �m�[�h �A�N�Z�X --------------------*/
	inline T leftchild(const int parent_idx) const { return this->tree_[leftchild_idx(parent_idx)]; }				// �E�q�ɃA�N�Z�X
	inline T rightchild(const int parent_idx) const { return this->tree_[rightchild_idx(parent_idx)]; }				// ���q�ɃA�N�Z�X
	inline T parent(const int child_idx) const { return this->tree[parent_idx(parent_idx)]; }						// �e�ɃA�N�Z�X

	/*-------------------- ���� --------------------*/
	inline bool is_leaf(const int idx) const { return conv_leaf_idx2tree_idx(0) <= idx && idx <= conv_leaf_idx2tree_idx(this->size()); }

	/*-------------------- getter --------------------*/
	inline int size() const { return this->size_; }
	inline T identity() const { return this->identity_; }

	/*-------------------- �e�X�g�p --------------------*/
public:
	void show() {
		for (auto ele : this->tree_) {
			std::cout << ele << ",";
		}
		std::cout << std::endl;
	}
};