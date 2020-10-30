/**
*  1. Least Recently Used(LRU)
*  	LRUCache lRUCache = new LRUCache(2);
*  	lRUCache.put(1, 1); // cache is {1=1}
*  	lRUCache.put(2, 2); // cache is {1=1, 2=2}
*  	lRUCache.get(1);    // return 1, 此时cache 尾{2=2, 1=1}头 
*  	lRUCache.put(3, 3); // 挤走在尾部的2，LRU key was 2, evicts key 2, cache is {1=1, 3=3}
*  	lRUCache.get(2);    // returns -1 (not found)
*  	lRUCache.put(4, 4); // 挤走在尾部的1， LRU key was 1, evicts key 1, cache is {4=4, 3=3}
*  	lRUCache.get(1);    // return -1 (not found)
*  	lRUCache.get(3);    // return 3，此时cache仍为尾{4=4, 3=3}头
*  	lRUCache.get(4);    // return 4
*  
*  【1个unordered_map + 1个capacity变量 + 1个cache列表】
*  int capacity
*  list<pair<int,int>> 					     cachelist --> cache的现状
*  unordered_map<int, list<pair<int,int>>::iterator> m --> 哈希表m来保存关键值key和cachelist各项的迭代器之间映射，方便我们以O(1)的时间内找到目标项。
*  Note: get时考虑空，并擅用list的splice，put时考虑把原来的插到list顶，且满则删list尾不常用项，擅用erase, rbegin, push_front, pop_back etc..
**/
clase LRUCache {
	int capacity;
	list<pair<int,int>> l;
	unordered_map<int, list<pair<int,int>>::iterator> m;
public:
	LRUCache(int capacity) capacity{capacity} {}

	//在m中查找给定的key，如果存在就删掉原有项，并在顶部插入新来项，然后判断是否溢出，若溢出则删掉底部项(最不常用项)
	void put(int key, int value) {
		auto iter = m.find(key);
		if(iter != m.end())	{
			l.erase(iter->second);
		}
		l.push_front({key, value});
		m[key] = l.begin();

		//check overflow, remove entry, delete bottom item
		if(m.size() > capacity) {
			int del = l.rbegin()->first;
			m.erase(del);
			l.pop_back();
		}
	}

	//在m中查找给定的key，如果存在则将此项移到顶部，并返回value，若不存在返回-1。
	int get(int key) {
		auto iter = m.find(key);
		if(iter == m.end())	return -1;

		//std::list::splice -> void splice (iterator position, list& x, iterator i);
		//transfers only the element pointed by i from x into the container, inserting them at position.
		l.splice(l.begin, l, iter->second);
		return iter->second->second;
	}
};
/**
*  2. Least Frequently Used(LFU)   --> 需要记录每个entry的频率/出现次数, 每次替换掉用的最少的那个
*  	LFUCache lFUCache = new LFUCache(2);
*  	lFUCache.put(1, 1);
*  	lFUCache.put(2, 2);
*  	lFUCache.get(1);      // return 1, 此时1的频率为2
*  	lFUCache.put(3, 3);   // 挤走频率为1的2，evicts key 2
*  	lFUCache.get(2);      // return -1 (not found)
*  	lFUCache.get(3);      // return 3，此时3的频率为2，cache尾{1=1, 3=3}头
*  	lFUCache.put(4, 4);   // 挤走频率为2但是在cache尾的1，evicts key 1.
*  	lFUCache.get(1);      // return -1 (not found)
*  	lFUCache.get(3);      // return 3, 此时3的频率为3
*  	lFUCache.get(4);      // return 4, 此时4的频率为2 
*  
*  【3个unordered_map + 2个变量capacity, minfreq】
*  unordered_map<int, pair<int,int>>          m    -->  用一个哈希表m来记录当前数据{key, value}和其出现次数之间的映射，
*  unordered_map<int,list<int>>            freq    -->  另一个哈希表freq来建立频率和一个里面所有key都是当前频率的list之间的映射, 这样为了我们把相同频率的key都放到一个list中.
*  unordered_map<int, list<int>::iterator> posmap  -->  用一个哈希表posmap来建立key和freq中key的位置之间的映射, 为了在O(1)的时间内完成操作，快速的定位freq中key的位置
*  最后当然我们还需要两个变量capacity和minfreq，分别来保存cache的大小，和当前最小的频率。
*  Note: get时升了该项的频率，考虑minfreq那一栏key空的情况，put时考虑满则删最小频率项的情况，擅用list rebgin, front, erase, pop_front, push_back etc..
**/
clase LFUCache {
	int capacity;
	int minfreq;
	unordered_map<int, pair<int,int>> 		    m;		//key, {value, freq}
	unordered_map<int, list<int>> 			 freq;		//freq, {keys}
	unordered_map<int, list<int>::iterator> posmap;		//key, pos in freq map
public:
	LFUCache(int capacity) capacity(capacity), minfreq(minfreq) {}
	
	void put(int key, int value) {
		if(capacity <= 0) return;
		
		//已存在，直接更新value
		if(get(key) != -1) {
			m[key].first = value;
			return;
		}
		
		//check overflow，删最小频率那项
		if(m.size() >= capacity) {
			int del = freq[minfreq].front();
			freq[minfreq].pop_front();
			m.erase(del);
			posmap.erase(del);
		}

		//添加新的
		m[key] = {value, 1};
		freq[1].push_back(key);
		posmap[key] = freq[1].rbegin();
		minfreq = 1;
	}

	int get(int key) {
		if(m.find(key) == m.end()) return -1;

		//更新m表，freq表删旧添新，更新posmap表，检查minfreq所在那栏有没有key, 没有则minfreq需增一
		int oldfreq = m[key]->second;
		++m[key]->second;
		freq[oldfreq].erase(key);

		int newfreq = ++oldfreq;
		freq[newfreq].push_back(key);
		posmap[key] = freq[newfreq].rbegin();

		if(freq[minfreq].size() == 0)
			minfreq++;

		return m[key].first;
	}
};
