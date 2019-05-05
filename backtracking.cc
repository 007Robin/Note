回溯是一种穷举，但与brute force有一些区别，回溯带了两点脑子的，并不多，brute force一点也没带。
第一点脑子是回溯知道回头；相反如果是brute force,发现走不通立刻跳下山摔死，换第二条命从头换一条路走。
第二点脑子是回溯知道剪枝；如果有一条岔路上放了一坨屎，那这条路我们不走，就可以少走很多不必要走的路。

还有一些爱混淆的概念：递归，回溯，DFS。
回溯是一种找路方法，搜索的时候走不通就回头换路接着走，直到走通了或者发现此山根本不通。
DFS是一种开路策略，就是一条道先走到头，再往回走一步换一条路走到头，这也是回溯用到的策略。在树和图上回溯时人们叫它DFS。
递归是一种行为，回溯和递归如出一辙，都是一言不合就回到来时的路，所以一般回溯用递归实现；当然也可以不用，用栈.

一般回溯的问题有三种：
1. Find a path to success 有没有解
2. Find all paths to success 求所有解
	1)求所有解的个数
	2)求所有解的具体信息
3. Find the best path to success 求最优解

关于回溯的三种问题，模板略有不同，
第一种，返回值是true/false。
第二种，求个数，设全局counter，返回值是void；求所有解信息，设result，返回值void。
第三种，设个全局变量best，返回值是void。

第一种：
boolean solve(Node n) {
	if n is a leaf node {
		if the leaf is a goal node, return true
		else return false
	} else {
		for each child c of n {
			if solve(c) succeeds, return true
		}
		return false
	}
}

第二种：
void solve(Node n) {
	if n is a leaf node {
		if the leaf is a goal node, count++, return;
		else return
	} else {
		for each child c of n {
			solve(c)
		}
	}
}

第三种：
void solve(Node n) {
	if n is a leaf node {
		if the leaf is a goal node, update best result, return;
		else return
	} else {
		for each child c of n {
			solve(c)
		}
	}
}
https://www.cis.upenn.edu/~matuszek/cit594-2012/Pages/backtracking.html
