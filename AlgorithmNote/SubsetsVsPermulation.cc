Subsets 1 2 3
[] [1] [1,2] [1,2,3] [1,3] [2] [2,3] [3]
Subsets要所有内部不重复的节点，所以一进入dfs就res.add
							[]
					1		2		3
				12	  13     23
			123
先sort nums，
pos标记很重要，每次添加pos的下一个数，
1 -> 1 2 -> 12 3, 回溯到1，添加2的下一个数3， 1 -> 1 3.（无重复）

void dfs(vector<vector<int>>& res, vector<int>& v, int pos, vector<int>& nums) {
	res.push_back(v);
	for(int i = pos; i < nums.size(); ++i) {
		v.push_back(nums[i]);
		dfs(res, v, i+1, nums);
		v.pop_back();
	}
}

去重复问题要选代表处理。调用函数前sort()排序nums，
并在for循环第一步进行判断，加上
	if( i != pos && nums[i] == nums[i - 1]) { continue; } 这段即可
同理对于permulatoin:
	if (i != 0 && nums[i] == nums[i - 1] && visited[i - 1] == false) { continue; }

Permulations 1 2 3
[1,2,3],
[1,3,2],
[2,1,3],
[2,3,1],
[3,1,2],
[3,2,1]
Permulations只要叶子节点，所以只有v.size()==nums.size()才res.add

						     []
					1 	     2		  3
				12	 13       21   23       31  32 
	------output-----> 123        132      213    231    312   321

有个visited数组表示数被用过，
1(标记1被visited了) -> 1(1被用过continue，所以加2)2 -> 123(同理，加3) 回溯到1 -> 13 -> 132。

void dfs(vector<vector<int>>& res, vector<int>& v, vector<int>& nums, vector<int>& visited){
	if(v.size() == nums.size()) {
		res.push_back(v);
		return;
	}
	for(int i = 0; i < nums.size(); ++i) {
		if(visited[i] == 1)
			continue;

		visited[i] = 1;
		v.push_back(nums[i]);
		dfs(res, v, nums, visited);
		visited[i] = 0;
		v.pop_back();
	}
}


同模版可以应用于 => DFS的4种应用情况之三
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
Combination Sum
Combination Sum II
Combination Sum III

2) 切分划分问题 Partition 等同于组合问题
	长度为n的string,有n-1个位置可以切，每个位置2种可能性切与不切，一共切法有2^(n-1)种。
	// i表示切在[startIndex, string.size()]之间的某个位置
	if (...) ...
	for i = startIndex -> size 
		push_back([startIndex, i]之间的子串)
		helper(i + 1, ...)
		pop_back()...

Palindrome Partitioning
注意其中用到 string的substr函数， 其参数为(size_t pos, size_t len);
132. Palindrome Partitioning II (DP动态规划题了，不属于该范畴，https://leetcode.com/problems/palindrome-partitioning-ii/)

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
