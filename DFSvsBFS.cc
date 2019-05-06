原文：https://blog.csdn.net/renwotao2009/article/details/52993277 
--------------------- 

搜索问题的解法
	DFS（深度优先搜索）
	BFS（广度优先搜索）
	backtracking（回溯）

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

--------------------- 
BFS模板
	模板1
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
	模板2
void bfs(...)
{
	queue q;
	q.push(startRoot);
	while (!q.empty()) {
		// 按照层次处理
		size = q.size();
		for (i = 0; i < size; i++) {
			curNode = q.front();
			q.pop();

			if (... ) {
				// 处理curNode,并把curNode的相邻Nodes加入队列
			}
		}
	}

}
