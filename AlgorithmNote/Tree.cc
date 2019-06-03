depth: node v to root longest path length. Root's depth is 0.
height: node v to leaf max height, Tree height means root's height.

Traverse VS Divide Conquer
1. Both recursion
2. Result in parameter or Result in return value
3. Top down or Bottom up

*** 前序 = 根—>左—>右；
*** 前序遍历preorder //O(n)
1) Traverse 特点：有个全局变量result, 函数不需要返回参数，返回void即可。改变了原有参数（工程避免这么用）
//把root为根的preorder加入result里面
void Traverse(root，res) {
	if(!root) return;
	res.push_back(root->val);
	Traverse(root->left, res);
	Traverse(root->right, res);
}
2) Divide Conquer 与遍历的区别是有返回，输入参数直接要返回结果。
vector<int> preorder(root) {
	if(!root) return res;
	//Divide 左子树 怎样怎样 右子树 怎样怎样 可以解决问题
	L = preorder(root->left);
	R = preorder(root->right);
	//Conquer 最后把结果merge在一起
	res.push_back(root->val);
	res.push_back(L);
	res.push_back(R);
}
3) Non-recursion/Stack
	stack.push(root);   //根入栈，栈非空时循环 
	while(!stack.empty( )) {      
		TreeNode node = stack.pop();   //每次将栈弹出的元素      
		result.add(node.val); //存入result里      
		if(node.right != null) {     //先右子树是因栈结构是先进后出，先进right，先出left           
			stack.push(node.right);    //先把右节点入栈，后出      
		}      
		if(node.left != null) {      //后进先出           
			stack.push(node.left);     //后入栈左节点，先pop出      
		} 
	} 
	return result；
*** 中序 = 左—>根—>右；
*** 中序遍历inorder
1) Non-recursion/Stack
将根节点p压入栈，和其所有左子结点压入栈
当走空时，逐步弹栈顶t，写入result, 这会满足中序的先左儿子再根
p走向t的右子(无右子则直接继续去栈顶，res入根，p变为根的右子)
vector<int> inorderTraversal(TreeNode* root) {
	vector<int> res;
	stack<TreeNode*> st;
	TreeNode* p = root;
	while(p || !st.empty()) {
		while(p) {          
			st.push(p);
			p = p->left;
		}
		TreeNode* t = st.top(); st.pop();         
		res.push_back(t->val);          
		p = t->right;     
	}       
	return res;
}
173. Binary Search Tree Iterator   
*** 后序 = 左—>右—>根。
*** 后序遍历postorder
1) Non-recursion/Stack
多一个prev变量: 存postorder的上一个处理的节点
(p || !st.empty())循环
先让所选节点p的左儿子全部入栈，当走空时，弹栈顶元素t, 去判断t有没有右儿子
if(t有右儿子&&右儿子不是该节点postorder的上一个节点）
	则把节点p更新为t的右儿子
else 
	栈顶的值入result, 更新prev为t, pop栈顶

vector<int> postorderTraversal(TreeNode* root) {
	vector<int> res;
	stack<TreeNode*> st;
	TreeNode* p = root;
	TreeNode* prev = NULL;
	while(p || !st.empty()) {
		while(p) {
			st.push(p);
			p = p->left;
		}
		TreeNode* t = st.top(); 
		if(t->right && t->right != prev) {
			p = t->right;  
		}
		else {
			res.push_back(t->val);
			prev = t;
			st.pop(); 
		}            
	}
	return res;
}

*** 二叉树 每层遍历
1) BFS法  
 2Queues Q1 Q2一个父层一个子层两个来回倒腾
 1Queue + #，一层结束后删#把#加入队尾
1Queue（best）先进先出
vector<vector<int>> levelOrder(TreeNode* root) {
	vector<vector<int>> res;
	if(!root) return res;
	
	queue<TreeNode*> q;
	q.push(root);
	
	while(!q.empty()) {
		vector<int> level;
		int size = q.size();  //先取队列长度,for循环走每层
		for(int i = 0; i < size; ++i) {
			TreeNode* p = q.front(); q.pop();  //弹出头节点
			level.push_back(p->val);
			if(p->left)
				q.push(p->left);
			if(p->right) 
				q.push(p->right);
		}
		res.push_back(level);
	}
	return res;
}
2) DFS 递归 curlevel从0开始,由于递归的特性，我们会一直深度优先去处理左子结点，势必会穿越不同的层，当要加入某个结点的时候，必须要知道当前的深度，使用一个变量level来标记当前的深度，初始化带入0，表示根结点所在的深度。
由于需要返回的是一个二维数组res，开始时我们又不知道二叉树的深度，不知有多少层，所以无法事先申请好二维数组的大小，只有在遍历的过程中，当level等于数组的长度时，新建一个空层，继续往里面加数字不断的增加。
vector<vector<int>> levelOrder(TreeNode* root) {
	vector<vector<int>> res;
	levelorder(root, 0, res);
	return res;
}
void levelorder(TreeNode* node, int level, vector<vector<int>>& res) {
	if (!node) return;
	if (res.size() == level) res.push_back({});
	res[level].push_back(node->val);
	if (node->left) levelorder(node->left, level + 1, res);
	if (node->right) levelorder(node->right, level + 1, res);
}
*** LCA最近祖先问题
在root为根的二叉树中找A，B的最近祖先LCA
1) 给了父亲parent指针，这种将两个节点p,q的父节点序列找出，然后翻转两序列，找翻转后序列的最后一组相等的父节点即最近。
2) 只给了root，用divide conquer
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if(!root || root == p || root == q) return root;
	//divide 
	TreeNode* left = lowestCommonAncestor(root->left, p, q);
	TreeNode* right = lowestCommonAncestor(root->right, p, q);
	//conquer
	if(left && right)  //找到了返回这个LCA
		return root;
	if(!left) //只碰到A返回A，只碰到B返回B，都没有返回NULL
		return right;
	if(!right)
		return left;
	else
		return NULL;
}
*** Path sum 问题
113. Path Sum II (list all paths, 
437. Path Sum III (how many paths, 
Traverse模版
void helper(root, targetsum, vector<int> path, res) {
1.	if(!root) return;
	//处理当前节点
2.	path.push_back(root->val)
3.	..准备一些算法去更新res..
	//递归处理其左右孩子
4.	helper(root->left, ...)
	helper(root->right, ...)
	//当前子树处理完毕，pop该节点，回溯上一个
5.	path.pop_back();
}
**** Maximum Path Sum root to any 
  		1
	   2  3
	    -1 -2     return 4 (1 + 3)
Divide Conquer
int maxPathSum(root) {
	if(!root) return 0;
	
	int left = maxPathSum(root->left);
	int right = maxPathSum(root->right);
	//与0比较实现了root to any, 若左右的sum比0还小, 那我不加左右儿子的了
	//错误写法root->val + max(left, right); 这种是root to leaves的方法. 
	return root->val + max(max(left, right), 0);  
}

**** Maximum Path Sum any to any 
124. Binary Tree Maximum Path Sum
整棵树的res与左右子树的最长路径有3种联系:
1.res就在left里;  2.在right里;  3.在left跨过根到right里 = 最长(左子树根—Any) + 最长(右子树—Any) + (根)
定义root_anyPath = 根到any节点可以不包含任何点，所以最后要与0比一下; 
any_anyPath = any—any至少包含一点，所以不需要与0比;
ResultType helper(root){
	if(!root) return ResultType(0, INT_MIN);
	//divide
	ResultType left = helper(root->left);   //左子树结果
	ResultType right = helper(root->right);   //右子树结果
	//conquer
	int root_anyPath = max(left.root_anyPath, right.root_anyPath) + root.val;  
	//root_anyPath记录左/右子树MaxPath + 根val
	root_anyPath = max(root_anyPath, 0);   //与0比较
	int any_anyPath = max(left.any_anyPath, right.any_anyPath);   //any_anyPath先记录较大的左/右子树的1.left 2.right的any-any的最大路径
	any_anyPath = max(any_anyPath, left.root_anyPath + right.root_anyPath + root.val);  //再比较其与left跨right的(左根+右根+根值)，选最大那个。
	return ResultType(root_anyPath, any_anyPath);
} 

*** Divide Conquer分置递归法：!root怎样 左子树怎样 右子树怎样 整体怎样
104. Maximum Depth of Binary Tree
111. Minimum Depth of Binary Tree
257. Binary Tree Paths
687. Longest Univalue Path
