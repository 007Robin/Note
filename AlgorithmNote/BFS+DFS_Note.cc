--------------------- 
搜索问题的解法
	BFS（广度优先搜索）
	DFS（深度优先搜索）
	backtracking（回溯）
--------------------- 
BFS要点 1）用Queue 2）是否需要实现分层
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
DFS模板
void dfs(...) 
{
	// 结束递归的条件
	if (...) {
		..... // 把“当前结果” 加入 “结果集容器” 中
			return;
	}

	// 继续递归，里面可能有回溯，也可能没有
	if (...) {

		... // 在容器中保存当前数据
			dfs() 
			... // 在容器中删除上面保存的数据（注：这种情况下就称为回溯，很明显它是dfs的一个步骤）
	}
}
难点
寻找dfs结束条件
继续dfs的条件
