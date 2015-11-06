#include "kdtree.h"
#include <limits> 

namespace kdTree{

	void kdNode::create( kdNode *left_child, kdNode *right_child,
		kdNode *parent, int spl, _data _vec,  _HyperRectangle rg)
	{
		this->left = left_child;
		this->right = right_child;
		this->parent = parent;
		this->split = spl;
		this->ndata = _vec;
		this->range = rg;
	}

	 kdNode::kdNode( const kdNode &rhs )
	{
		this->left = rhs.left;
		this->right = rhs.right;
		this->parent = rhs.parent;
		this->split = rhs.split;
		this->ndata = rhs.ndata;
		this->range = rhs.range;
	}

	 kdNode& kdNode::operator=( const kdNode &rhs )
	{
		if(this == &rhs) 
			return *this;
		this->left = rhs.left;
		this->right = rhs.right;
		this->parent = rhs.parent;
		this->split = rhs.split;
		this->ndata = rhs.ndata;
		this->range = rhs.range;

		return *this;
	}


	void kdTree::create( const dataset &data_set )
	{
		root = createkdTree(data_set);
	}

	 kdNode* kdTree::createkdTree( const dataset &data_set )
	{
		if(data_set.isempty())
			return NULL;

		dataset data_set_copy(data_set);


		int dims = data_set_copy.getdim();
		int size = data_set_copy.getsize();

		//! 计算每个维的方差，选出方差值最大的维
		double var_max = -0.1; 
		double avg, var;
		int dim_max_var = -1;
		for(int i=0;i<dims;i++)
		{
			avg = 0;
			var = 0;
			//! 求某一维的总和
			for(int j=0;j<size;j++)
			{
				avg += data_set_copy[j][i];
			}
			//! 求平均
			avg /= size;
			//! 求方差
			for(int j=0;j<size;j++)
			{
				var += ( data_set_copy[j][i] - avg ) * 
					( data_set_copy[j][i] - avg );
			}
			var /= size;
			if(var > var_max)
			{
				var_max = var;
				dim_max_var = i;
			}
		}

		//! 确定节点的数据矢量

		_HyperRectangle hr = data_set_copy.calculateRange();
		data_set_copy.sort_k(dim_max_var);
		int mid = size / 2;
		_data exm_split = data_set_copy[mid];
		data_set_copy.remove(mid);

		//! 确定左右节点

		dataset data_set_left(0, data_set_copy.getdim());
		dataset data_set_right(0, data_set_copy.getdim());
		data_set_right.remove(0);

		int size_new = data_set_copy.getsize();
		for(int i=0;i<size_new;i++)
		{
			_data temp = data_set_copy[i];
			if( temp[dim_max_var] < 
				exm_split[dim_max_var] )
				data_set_left.push_back(temp);
			else
				data_set_right.push_back(temp);
		}

		kdNode *pNewNode = new kdNode(0, 0, 0, dim_max_var, exm_split, hr);
		pNewNode->left = createkdTree(data_set_left);
		if(pNewNode->left != NULL)
			pNewNode->left->parent = pNewNode;
		pNewNode->right = createkdTree(data_set_right);
		if(pNewNode->right != NULL)
			pNewNode->right->parent = pNewNode;

		return pNewNode;
	}

void kdTree::destroykdTree( kdNode *root )
{
	if(root != NULL)
	{
		destroykdTree(root->left);
		destroykdTree(root->right);
		delete root;
	}
}

void  kdTree::destroy()
{
	destroykdTree(root);
}

std::pair< _data, double>  kdTree::findNearest_i( kdNode *root, _data target )
{
	//临时搜索指针
	kdNode *pSearch = root;
	//栈用于保存搜索路径
	std::vector<kdNode*> search_path;
	//存放最近点
	_data nearest;
	double max_dist;

	while(pSearch != NULL)
	{
		search_path.push_back(pSearch);
		int s = pSearch->splitDim();
		if(target[s] <= pSearch->getdata()[s])
		{
			pSearch = pSearch->left;
		}
		else
		{
			pSearch = pSearch->right;
		}
	}

	nearest = search_path.back()->getdata();
	max_dist = _distance(nearest, target);

	search_path.pop_back();

	//回溯搜索路径
	while(!search_path.empty())
	{
		kdNode *pBack = search_path.back();
		search_path.pop_back();

		if( pBack->left == NULL && pBack->right == NULL)
		{
			if( _distance(nearest, target) > _distance(pBack->getdata(), target) )
			{
				nearest = pBack->getdata();
				max_dist = _distance(pBack->getdata(), target);
			}
		}
		else
		{
			int s = pBack->splitDim();
			if( abs(pBack->getdata()[s] - target[s]) < max_dist)
			{
				if( _distance(nearest, target) > _distance(pBack->getdata(), target) )
				{
					nearest = pBack->getdata();
					max_dist = _distance(pBack->getdata(), target);
				}
				if(target[s] <= pBack->getdata()[s])
					pSearch = pBack->right;
				else
					pSearch = pBack->left;
				if(pSearch != NULL)
					search_path.push_back(pSearch);
			}
		}
	}

	std::pair<_data, double> res(nearest, max_dist);

	return res;
}

std::pair< _data, double>  kdTree::findNearest( _data target )
{
	std::pair<_data, double> res;
	if(root == NULL)
	{
		res.second = std::numeric_limits<double>::infinity();
		return res;
	}
	return findNearest_i(root, target);
}

int  kdTree::findNearest( _data target, double range, std::vector<std::pair<_data, double>> &res_nearest )
{
	return findNearest_range(root, target, range, res_nearest);
}

int   kdTree::findNearest_range( kdNode *root, _data target, double range, 
	std::vector<std::pair<_data, double>> &res_nearest )
{
	if(root == NULL)
		return 0;
	double dist_sq, dx;
	int ret, added_res = 0;
	dist_sq = 0;
	dist_sq = _distance(root->getdata(), target);

	if(dist_sq <= range) {
		std::pair<_data,double> temp(root->getdata(), dist_sq);
		res_nearest.push_back(temp);
		//! 结果个数+1
		added_res = 1;
	}

	dx = target[root->splitDim()] - root->getdata()[root->splitDim()];
	//! 左子树或右子树递归的查找
	ret = findNearest_range(dx <= 0.0 ? root->left : root->right, target, range, res_nearest);
	if(ret >= 0 && fabs(dx) < range) {
		added_res += ret;
		ret = findNearest_range(dx <= 0.0 ? root->right : root->left, target, range, res_nearest);
	}

	added_res += ret;
	return added_res;
}

};