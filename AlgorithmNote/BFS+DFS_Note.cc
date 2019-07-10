--------------------- 
搜索问题的解法
	
	BFS（广度优先搜索）走到一个节点，遍历完该点的下一层的所有节点，然后处理下一层的第一个点
	使用情况：图由点及面的搜索(DFS会很深)，简单图最短路径(没必要DFS找所有路径)
	
	DFS（深度优先搜索）走到一个节点，往下再走一层，能走则继续往深处走，走不通则回到上一层，继续遍历adjacent点
	使用情况：找所以方案的题目，排列组合问题
	
	backtracking（回溯）变过去又变回来
--------------------- 
BFS
2个要点 1）用Queue 2）是否需要实现分层
- 模板1 不分层，常用模版
void bfs(...)
{
	queue q;
	q.push(startRoot);
	while (!q.empty()) {
		// 按照节点处理
		curNode = q.front();
		q.pop();

		if (...) {
			// 处理curNode,并把curNode的相邻Nodes加入队列
		}
	}

}
- 模板2 要分层，多加一个for循环
void bfs(...)
{
	queue q;
	q.push(startRoot);
	while (!q.empty()) {
		// 按照层次处理
		size = q.size();
		for (i = 0; i < size; i++) {
			//同上		
			curNode = q.front();
			q.pop();

			if (... ) {
				// 处理curNode,并把curNode的相邻Nodes加入队列
			}
		}
	}
}

BFS有3种应用情况
1) 二叉树 BFS in Binary Tree
102.Binary Tree Level Order Traversal I/107.II
297.Binary Tree Serialization
103.Binary Tree Zigzag Order Traversal
Convert Binary Tree to Linked Lists by Depth

2) 图 BFS in Graph 
N个点，M条边, M最大是 O(N^2) 的级,图上BFS时间复杂度 = O(N + M)
	• 层级遍历 Level Order Traversal
	• 由点及面 Connected Component
	• 拓扑排序 Topological Sorting  
		分3步：N个vertexes （有时候是Node形式，有时候是数字形式） 
		1.统计所有点的入度indegree (数组/map都行，只要存 点-入度 映射关系)
			若边node-->neighbor形式，in[neighbor]++，是neighbor的入度++
		2.入度为0的点先放入queue
		3.BFS 
			while循环，
			取队头顶点t
				走t的neighbor同时减其入度，
				入度为0继续入queue
		判断有无环的问题只需加一句判断res.size() == graph.size() 相等则无环，不等则有环。
		或者判断有没有顶点的入度还不等于0，有非0入度则证明有环false，否则true
  最短路径 Shortest Path in Simple Graph 
	• 仅限简单图求最短路径
	• 即，图中每条边长度都是1，且没有方向
Build Post Office	
Graph Valid Tree
Clone Graph
Search Graph Nodes
Topological Sorting
Course Schedule I && II
Sequence Reconstruction
Word Ladder I 
Word Ladder II (BFS + DFS结合） 

3) 棋盘/矩阵 BFS
R行C列,R*C个点，R*C*2 条边,矩阵中BFS时间复杂度 = O(R * C)
小知识：
 利用坐标变换数组
	int[] deltaX = {1,0,0,-1};
	int[] deltaY = {0,1,-1,0};
	int[] deltaX = {1,1,2,2,-1,-1,-2,-2};
	int[] deltaY = {2,-2,1,-1,2,-2,1,-1};
 写一个判断是否越界的函数isBorder() {
	x<0, x>=r  false
	y<0, y>=c  false
	return ...
 }
BFS 3层循环
	while(!q.empty())
		int size = q.size();
		for(int i = 0; i < size; ++i) {
			
			for(int direction = 0; direction < 4; direction++) {
				if(!isBorder()) {
					continue;
				}
			}
		}
Number of Islands
Zombie in Matrix
Knight Shortest Path

--------------------- 
DFS
实现方式有2种，1) 递归recursion 2) 非递归non-recursion/用stack方式
复杂度为 O(答案个数 * 构造每个答案的时间复杂度)
DFS recursion 模板
void dfs(...) 
{
	// 结束递归的条件
	if (...) {
		..... // 把“当前结果” 加入 “结果集容器” 中
			return;
	}

	// 继续递归，里面可能有回溯，也可能没有
	if (...) {

		...push_back // 在容器中保存当前数据
		dfs(...) 
		...pop_back() // 在容器中删除上面保存的数据（注：这种情况下就称为回溯，很明显它是dfs的一个步骤）
	}
}
难点
该dfs要干什么事／recursion定义
寻找dfs结束条件／recursion出口
继续dfs的条件／recursion拆解

DFS的4种应用情况
1) 组合搜索问题 Combination
	1.是指从给定n个数的元素中仅仅挑出指定r个数的元素，不考虑排序，求所有满足条件的“组合”／问有几种
	2.时间复杂度与 2^n 相关。
    //i表示挑到的当前元素的索引号
	if (...) ...
	for i = startIndex -> size
		push_back(nums[i])
		helper(i, ...)可重复挑 or helper(i + 1, ...)不可重复挑 
		pop_back()...
Subset I
Subset II
Combination I
Combination II

2) 切分划分问题 Partition 等同于组合问题
	长度为n的string,有n-1个位置可以切，每个位置2种可能性切与不切，一共切法有2^(n-1)种。
	// i表示切在[startIndex, string.size()]之间的某个位置
	if (...) ...
	for i = startIndex -> size 
		push_back([startIndex, i]之间的子串)
		helper(i + 1, ...)
		pop_back()...
Palindrome Partitioning

3) 排列搜索问题 Permutation
	1.求出所有满足条件的“排列”
	2.时间复杂度与 n! 相关
	3.类似于组合问题，但少了startIndex变量，多了visited数组用于表示数有没有被用过
	for i = 0 -> size
		visited[i] = true;
		push_back(nums[i])
		helper(...)
		pop_back()...
		visited[i] = false;

Permutation
N queen
Shudu

4) 树/图／隐式图的深度搜索
Word Ladder II (BFS + DFS结合） 

2) 非递归non-recursion/用stack方式 DFS
Tree Traversal
http://www.jiuzhang.com/solutions/binary-tree-preorder-traversal/
http://www.jiuzhang.com/solutions/binary-tree-inorder-traversal/ 
http://www.jiuzhang.com/solutions/binary-tree-postorder-traversal/ 
http://www.jiuzhang.com/solutions/binary-search-tree-iterator/ 
Combination
http://www.jiuzhang.com/solutions/subsets/
Permutation
http://www.jiuzhang.com/solutions/permutations/
