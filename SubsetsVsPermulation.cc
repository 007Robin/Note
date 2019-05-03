时间复杂度=方案个数*构造一个方案度时间复杂度 Subsets O(2^n * n), Permulation O(n! *n).
Subsets 1 2 3
[] [1] [1,2] [1,2,3] [1,3] [2] [2,3] [3]
Subsets要所有内部不重复的节点，所以一进入dfs就res.add
							[]
					1		2		3
				12	  13     23
			123
先sort nums，保证子序列后续结果是赠序的，不会有乱序重复现象
有个pos标记，每次添加pos的下一个数，1 -> 1 2 -> 12 3, 回溯到1，添加2的下一个数3， 1	-> 1 3.（无重复）
void dfs(vector<vector<int>>& res, vector<int>& v, int pos, vector<int>& nums) {
	res.push_back(v);
	for(int i = pos; i < nums.size(); ++i) {
		v.push_back(nums[i]);
		dfs(res, v, i+1, nums);
		v.pop_back();
	}
}

Subsets II
对有重复数字case, 在循环及13rd行处，放过i=pos的情况(要正常递归)，其他情况均判断nums[i] == nums[i-1]相等则continue跳过。
		if(i != pos && nums[i] == nums[i - 1])
			continue;

Permulations 1 2 3
[1,2,3],
[1,3,2],
[2,1,3],
[2,3,1],
[3,1,2],
[3,2,1]
Permulations只要叶子节点，所以只有v.size()==nums.size()才res.add



								[]
					1 			2		 	3
				12	 13       21  23       31  32 
-->			 123      132   213    231    312   321

有个visited数组表示数被用过没，记得初始化该数组全0！
1(标记1被visited了) -> 1(1被用过continue，所以加2)2 -> 123(同理，加3) 回溯到1, 不拉下每一个，132也在其中了。

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

Permulation II
对有重复数字case, 
先sort一遍nums，方便之后判断相邻两数相等，
在循环及48行处，加一种情况，放过i=0的情况(要正常递归)，其他情况均判断nums[i] == nums[i-1]相等且visited[i-1]=0, 未被访问过，则continue跳过。
//			if(visited[i] == 1 || (visited[i-1] == 0 && nums[i-1] == nums[i] && i != 0)) {
//			hhh,一个小tips: 上述这种if判断条件的写法，在if里会判断好多遍导致heap越界，所以写if的循环条件要尽量先筛选再判断！
			if(visited[i] == 1 || (i != 0 && nums[i-1] == nums[i] && visited[i-1] == 0)) {
				continue;		
			}
