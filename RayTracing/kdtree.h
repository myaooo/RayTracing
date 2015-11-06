//kdTree.h
//programed by M.Y.

#ifndef KDTREE
#define KDTREE

namespace kdTree
{
	///////////////////
	//kdNode declaration
	///////////////////
	template <class T>
	class kdNode
	{
	private:
		int split;
		T ndata;
		_HyperRectangle range;
	public:
		kdNode *left, *right, *parent;
	public:
		kdNode():left(0), right(0), parent(0), split(0){}
		kdNode(kdNode *l, kdNode *r, kdNode *p, int spl, T vec, _HyperRectangle rg):
		left(l), right(r), parent(p), split(spl), ndata(vec), range(rg){}

		kdNode(const kdNode &rhs);
		kdNode& operator=(const kdNode &rhs);
		_data& getdata() { return ndata; }
		_HyperRectangle& getHyperRectangle(){ return range; }
		int& splitDim(){ return split; }
		void create(kdNode *l, kdNode *r, kdNode *p, int spl, _data _vec, _HyperRectangle rg);
	};

	///////////////////
	//kdTree declaration
	///////////////////
	class kdTree
	{
	public:
		kdNode *root;
	public:
		kdTree():root(NULL){}
		//调用private函数createtree建树
		void create(const dataset &data_set);
		//调用private函数destroykdTree销毁树
		void destroy();
		~kdTree(){ destroykdTree(root); }
		//最邻近搜索
		std::pair<_data, double> findNearest(_data target);	
		//范围搜索
		int findNearest(_data target, double range,	std::vector<std::pair<_data, double>> &res_nearest);
	private:
		kdNode* createkdTree(const dataset &data_set);
		void destroykdTree(kdNode *root);
		std::pair<_data, double> findNearest_i(kdNode *root, _data target);
		int findNearest_range(kdNode *root, _data target, double range, 
			std::vector<std::pair<_data, double>> &res_nearest);
	};
}

#endif