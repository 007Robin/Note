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
374. Guess Number Higher or Lower（mid直接表示这个数）
162. Find Peak Element (mid表index,分情况讨论遇到峰，谷，递增，递减)

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
300. Longest Increasing Subsequence （用新的数去替换first>=x的数，维护一个递增序列这样子。返回size）
315. Count of Smaller Numbers After Self (求x右边比x小的数有几个，倒叙遍历数并插入新数组，找first >= n的数的位置插入该数，且该位置就是右边比我小的数的个数)
354. Russian Doll Envelopes （小信封嵌套大的里，(w增,h减)排序, 再求h的LIS，用新H去替换掉first>=h的数，维护递增，返回size）
475. Heaters (去找每个house距离heater的min左右distance)

2.upper_bound(v.begin(), v.end(), k), 返回v里>k的第一个数的位置


* 有些题用二分搜索找k smallest的xxx, 即求第k个xxx, 基本方法是:
先确定一个xxx的范围从[L,R], 再用cnt变量去统计有多少个xxx<mid，如果cnt不够k, 涨L=mid+1
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
668.kth-smallest-number-in-multiplication-table
719.Find K-th Smallest Pair Distance
