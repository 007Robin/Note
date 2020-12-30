* 二分九章通用模版
sort array是前提，在sort的东西里search才可。
	L = 0, R = n
	while L + 1 < R 
		mid = L + (R - L) / 2;
		? mid = target
			got it!
		? mid < target
			 = mid
		? mid > target
			 = mid
	L ? target
	R ? target

##该法多加了几次判断避免了死循环情况，mid可以是数组的索引，也可以直接表示一个数
33. Search in Rotated Sorted Array
	(利用旋转数组的规律：若中间的数 < 最右边的数，则右半段是有序的，若中间数 > 最右边数，则左半段是有序的, mid表示数组的索引)
81. Search in Rotated Sorted Array II (允许数字重复）
	(对于重复的会有[3 1 1] 和 [1 1 3 1]这中间值==最右值两种情况，处理非常简单，只要把最右值向左移，直到移到值不同为止)
374. Guess Number Higher or Lower
	（mid直接表示这个数）
162. Find Peak Element 
	(题目找任意一个峰值，常规二分，看mid是不是, mid直接表示这个数)

* c++的lower/upper_bound函数本质是二分

1.lower_bound(v.begin(), v.end(), k), 返回v里>=k的第一个数的位置	
	L = 0， R = v.size();
	while L < R
		mid = L + (R - L) / 2;
		if v[mid] >= k
			R = mid;
		else				//数v[mid]小于k，要找first>=k的，则新L要从mid+1开始
			L = mid + 1
	end at L == R 
	return R

##许多题用到lower_bound(), 去找第一个first >= target的数, or, 该数的位置
300. Longest Increasing Subsequence 
	(遍历数组，维护一个递增子序列res, 数x > 当前res队尾则入队，数x < res队尾时，去res里找 first >= x的那个数所在位置，替换掉，循环遍历至结束。返回res的size）
315. Count of Smaller Numbers After Self 
	(求x右边比x小的数有几个。设一个新数组t，起始为空，我们倒叙遍历旧数组，把数插入排序到新数组，每次将数x插入新数组的first >= x的位置，显然，该位置号便是旧数组中右边比x小的数的个数)
354. Russian Doll Envelopes 
	(求最多有多少小信封(width,height)嵌套在大信封里。(w增,h减)排序, 再求h的LIS，同上先维护一个递增res, x<res队尾时，用新H去替换掉res里first>=h的数，维护递增，返回size）
475. Heaters 
	(去找每个house距离heater的min左右distance。先排序方便用二分法，对每个house,去heater中找first >= house的heater，相当于把house插入heater[r-1], heater[r]之间，
那么右边距离便是hearter[r]-house, 左边便是heater[r-1]-house了，对每个house选minDistance，注意当r==0的case即可。)

2.upper_bound(v.begin(), v.end(), k), 返回v里>k的第一个数的位置

* 有些题用二分搜索找k smallest的xxx, 即求第k个xxx, 基本方法是:
先确定一个xxx所属的最小最大值范围，对应模版中[L,R], mid直接表示一个数，再用cnt变量去统计有多少个xxx<mid，如果cnt不够k, 涨L=mid+1
	while L < R
		mid = L + (R - L) / 2;
		cnt = 0
		Do loop to 统计有多少个xxx < mid
			cnt += 一次循环的结果
		if cnt < k			//还不够k证明L太小，涨L到mid+1
			L = mid + 1
		else
			R = mid

378.Kth Smallest Element in a Sorted Matrix
	(sorted matrix中找<=x的cnt, 方法是从matrix最左下角[row-1][0]开始找, 如果这个元素>x，则它后面的肯定都比x大，我们可以直接看上一行即i--，
如果<=x，则这个元素所在这一例的上方且含它自己的共i+1个数都满足<=x, 我们简单的将cnt+=i+1，然后j++，从该行向右继续遍历)
668.kth-smallest-number-in-multiplication-table
	(解题完全同上，因multiplication table就是一个sorted matrix)
719.Find K-th Smallest Pair Distance
	(需要先排序数组，得到的距离范围是[0, nums.back()-nums[0]]，对应模版[L,R]，用法同上，只是这次要在数组中找pair distance < mid的cnt数，
我们借助辅助变量start，表示较小数字的索引号，遍历数组，将nums[i]于nums[start]做差，如果差值>mid, 则说明距离太大，我们需要缩短距离，所以start++，
这样到nums[i]，nums[start]间数的距离<mid，退出循环，则统计 < mid的pair distance数便是cnt += i - start)

215. Kth Largest Element in an Array	 
* 快排 + 二分思想：
确定个l,r 然后选个pivot, 
while (l <= r) {
	//把大于中枢点的数字放到左半边，小于中枢点的放在右半边,中枢点是整个数组中第几大的数字就确定了
	if (nums[l] < pivot && nums[r] > pivot) {
	//pivot在num[l],num[r]之间，交换num[l],num[r]， l,r各往中间凑一凑
	swap(nums[l++], nums[r--]);
	}
	//左边维护比pivot大的，右边维护比pivot小的
	if (nums[l] >= pivot) ++l;
	if (nums[r] <= pivot) --r;
}
swap(nums[left], nums[r]);	//最后放pivot
	
* QuickSort O(nlogn)
核心思想： 
随意选中一个pivot调换到数组末尾，
用start表示从左开始，都是比pivot小的数的索引下标, p则表示常规index,我们不断移动p，
当有比pivot更小的则swap(v[p],v[start]), start++; 实现把小数安插到p左边
没有，则不断p++，继续check。我们不关心每个半边是否有序，只先移成[左边小][pivot][右边大]的这种形式。
最后swap(v[p],v[start])。这样经过一次Sort可以得到，以start为界限，左边是比pivot小的一些数，右边是比pivot大的数
	 
//get a pivot, sort once
void SortOnce(vector<int>&v, int beg, int end) {
	// get a pivot
	if(beg >= end) return ;
	int pos	= rand() % (end - beg) + beg;
	swap(v[pos], v[end]);
	int pivot = v[end];
	
	int start = beg;
	int p = beg;
	while(p < end) {
		if(v[p] < pivot) {
			swap(v[start], v[p]);
			start++;
		}
		p++;
	}
	swap(v[start], v[p]);
	
	SortOnce(v, beg, start - 1);
	SortOnce(v, start + 1, end);
}
void QuickSort(vector<int>& v) {
	// number of elements
	int n = v[0];
	v.erase(v.begin());
	SortOnce(v, 0, v.size() - 1);	
}
	 
//****** Binary seach ****** O(logn)
int binarysearch(int a[], int n, int target) {
	int L = 0, R = n – 1;
	while( L < R)  {
		int mid = L + (R - L )/2;
		if( a[mid] < target) 
			L = mid - 1;
		else if (a[mid] > target) 
			R = mid - 1;
		else 
			return mid;
	}
	return -1;
}
int binarysearch2(int a[], int n, int target) {
	int L = 0, R = n – 1;
	while( L +1 < R ) {
		int mid = L + (R – L ) /2;
		if( a[mid] < target) 
			L = mid;
		else if ( a[mid] > target) 
			R = mid;
		else 
			return mid;
	}
	if(a[L] == target) return L;
	if(a[R] == target) return R;
	return -1;
}

Sliding Window相关：	 
239. Sliding Window Maximum 求滑动窗户内最大值
维护一个长度为k的双头队列deque, 每个deque内放数字下标，其实是维护（i - q.front==k）
当添加的新的数更大了，则从队列尾巴开始不断往前删元素，把比该值小的都删光，最后把该值插入队尾
当每走k步即i >= k -1时，往结果集里加入此时，队头下标所指向的元素。

3. Longest Substring Without Repeating Characters 最长无重复子串
256位大小的整型数组，存字母和下标映射关系， res用来记录最长无重复子串的长度，left指向该无重复子串左边的起始位置， 计算最长无重复子串，i - left

76. Minimum Window Substring 找S中最小子串，包含t中所有字母
先扫描一遍T，把对应的字符及其出现的次数存到 256位大小的整型数组 中 ++letterCnt[c]，
遍历S，不断把map中次数--，--letterCnt[s[i]]， 如果减1后仍大于等于0，计数器 cnt 自增1, 说明当前遍历到的字母是T串中的字母，
当 cnt 和T串字母个数相等时，说明此时的窗口已经包含了T串中的所有字母，此时更新一个 minLen 和结果 res。
然后收缩左边界，++letterCnt[s[left]]， 由于遍历的时候，对映射值减了1，所以此时去除字母的时候，就要把减去的1加回来，
此时如果加1后的值大于0了，说明此时少了一个T中的字母，那么 cnt 值就要减1了，然后移动左边界 left。
