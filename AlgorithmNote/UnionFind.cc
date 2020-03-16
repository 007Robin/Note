** union-find 一般题模版naive
0)Initialize的root数组表示自个儿是自个儿的老大
 for(int i = 0; i < n; ++i) 
	root[i] = i;
1)union -- union目的一定要找到老大，合并老大
 void union(int x, int y) {
	int fa_x = find(root, x);
	int fa_y = find(root, y);
	if(fa_x != fa_y)
		root[x] = y;
 }
2) find是每次找root=自身的点，是个子函数，来查找祖宗结点
int find(root, i) {
	while(i != root[i])
		i = root[i];
	return i;
}
实际里这两种写法都是可行的：
int find(vector<int>& root, int i) {
	while (i != root[i]) 
		i = root[i];
	return i;
}
int find(vector<int>& root, int i) {
	return i == root[i] ? i : getRoot(root, root[i]);
}
//The above union() and find() are naive and the worst case time complexity is linear. 
785. Is Graph Bipartite?(两端点染不同颜色方法，归并到不同集合里）

** Union-Find with rank 实现  
//optimized to O(Log n) in worst case
class UnionFind{
	private:
		int* parent, *rank;
		int n;
	public:
		UnionFind(int n) : n(n), parent(new int[n]), rank(new int[n]) {
			for(int i = 0; i < n; i++) {
				parent[i] = i;
				rank[i] = 0;
			} 
		}
		~UnionFind() {
			delete [] parent;
			delete [] rank;
		}
		int find(int i) {
			if(i != parent[i])
				parent[i] = find(parent[i]);
			return parent[i];
		}
		//基本想法是path compress, 每当find x时沿路上去找到它的root，把x的等级提到root之下，并在root的直接分支下 
		void merge(int x, int y) {
			x = find(x), y = find(y);
			// Attach smaller rank tree under root of high rank tree 
			if(rank[x] > rank[y])   
				parent[y] = x;
			else 
				parent[x] = y;
			// If ranks are same, then make one as root and increment its rank by one
			if(rank[x] == rank[y]) {
				rank[y]++;
				n--;		//mark for Disjoin set number
			}
		}
		bool isAset(int x, int y) {
			return find(x) == find(y);
		}
		int getDisjointSetNumber() {
			return n;
		
};
union by rank 图解理念：
		       9
		  /    |    \  
		 4     5      6
		/      \     /  \
		0      3     7    8
		      /  \
		     1    2 

find(3) 返回9，同时merge(3,9)使得，3变为9的直接儿子，在下次find(3)时可以很快返回9

		9
	  /    /  \    \
	4    5    6     3 
	/        /  \   /  \
	0       7    8  1   2           

Redundant Connection I (无向图union-find，遍历边集，union端点，==则找到)
Redundant Connection II (有向图union-find，3种情况要考虑,1）入度为2的边 2）环 3）二者both)

heap用二叉树实现
stack用数组实现 (树的层序遍历，维护一个递增数列用到栈)
union-find用数组实现（常用hashMap存A与A.father)
