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
	std::vector<T> tree;
	int size;
	T identity;

	// �q�Ɛe�̊֌W
	Op operation;

	/*-------------------- �R���X�g���N�^ --------------------*/

	// �z���n�����Ƃɂ�菉����
public:
	SegmentTree(const std::vector<T>& vec, Op operation, const T identity) 
		: size(vec.size()), identity(identity), operation(operation)
	{
		// �؂̍\�z
		int n = 1;
		while (n < size) n <<= 1;
		int tree_size = 2 * n - 1;
		std::cout << tree_size << std::endl;
		this->tree.resize(tree_size, identity);
		std::cout << this->tree.size() << std::endl;
		for (auto i = 0; i < this->size; ++i) this->tree[conv_leaf_idx2tree_idx(i)] = vec[i];
		recalcurate();
	}

	// size�̂ݓn���C��̃Z�O�����g�c���[�����
public:
	SegmentTree(const int size, Op operation, const T identity) 
		: size(size), identity(identity), operation(operation)
	{
		// �؂̍\�z
		int n = 1;
		while (n < size) n <<= 1;
		int tree_size = 2 * n - 1;
		this->tree.resize(tree_size, identity);
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
		
		T res_left = this->identity;
		T res_right = this->identity;
		left = conv_leaf_idx2tree_idx(left);
		right = conv_leaf_idx2tree_idx(right);

		while (left < right) {
			if (!(left & 1)) {
				res_left = this->operation(res_left, this->tree[left]);
				left++;
			}
			if (!(right & 1)) {
				right--;
				res_right = this->operation(this->tree[right], res_right);
			}
			left = parent_idx(left);
			right = parent_idx(right);
		}
		return this->operation(res_left, res_right);
	}

	/*-------------------- �؂̍\�z --------------------*/
protected:
	void propagate(const T new_data, const int write_tree_idx) {
		// �t�ɏ�������
		this->tree[write_tree_idx] = new_data;

		// �����m�[�h���X�V
		int seek_idx = write_tree_idx;
		while (seek_idx != 0) {
			// �e�ֈړ�
			seek_idx = parent_idx(seek_idx);

			// �e���X�V
			T lc = leftchild(seek_idx);
			T rc = rightchild(seek_idx);
			this->tree[seek_idx] = this->operation(lc, rc);
		}
	}

protected:
	void recalcurate() {
		for (auto i = conv_leaf_idx2tree_idx(0) - 1; i >= 0; --i) {
			T lc = leftchild(i), rc = rightchild(i);
			this->tree[i] = this->operation(lc, rc);
		}
	}

protected:
	/*-------------------- �C���f�b�N�X �v�Z --------------------*/
	inline int leftchild_idx(const int parent_idx) const { return 2 * parent_idx + 1; }				// �eidx���獶�qidx���v�Z
	inline int rightchild_idx(const int parent_idx) const { return 2 * parent_idx + 2; }			// �eidx����E�qidx���v�Z
	inline int parent_idx(const int child_idx) const { return (child_idx - 1) / 2; }				// �qidx����eidx���v�Z

	inline int conv_tree_idx2leaf_idx(const int tree_idx) const { return tree_idx - this->tree.size() / 2; }		// tree_idx��leaf_idx�ɕϊ�
	inline int conv_leaf_idx2tree_idx(const int leaf_idx) const { return leaf_idx + this->tree.size() / 2; }		// leaf_idx��tree_idx�ɕϊ�

	/*-------------------- �m�[�h �A�N�Z�X --------------------*/
	inline T leftchild(const int parent_idx) const { return this->tree[leftchild_idx(parent_idx)]; }				// �E�q�ɃA�N�Z�X
	inline T rightchild(const int parent_idx) const { return this->tree[rightchild_idx(parent_idx)]; }				// ���q�ɃA�N�Z�X
	inline T parent(const int child_idx) const { return this->tree[parent_idx(parent_idx)]; }						// �e�ɃA�N�Z�X

	/*-------------------- ���� --------------------*/
	inline bool is_leaf(const int idx) const { return conv_leaf_idx2tree_idx(0) <= idx && idx <= conv_leaf_idx2tree_idx(this->size); }

	/*-------------------- �e�X�g�p --------------------*/
public:
	void show() {
		for (auto ele : this->tree) {
			std::cout << ele << ",";
		}
		std::cout << std::endl;
	}
};

