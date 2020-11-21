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
