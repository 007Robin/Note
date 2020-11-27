/*
LinkedList的题多画图
指向的标签名赋值啊交换啊都不会改变链表结构，要改变结构的都是使用.next /.val
不支持index
不能用二分法

有时候需要在最前面建立一个dummy结点的原因是:
  当原来的头结点发生了变换，比如被删除了，或者被交换位置了，就需要记录新的头结点的位置。
  有了dummy结点，那么直接返回dummy->next 就是新链表的头结点了

list里删一个元素，常用：
    head->next = head->next->next;
*/

83. Remove Duplicates from Sorted List
head
  1 --> 1 --> 2 --> 3
prev   cur
1)删到list剩余一个
    ListNode* prev = head;
    ListNode* cur = head->next;
    while(cur) {
        if(cur->val == prev->val) 
            prev->next = cur->next;
        else
            prev=cur;
        cur = cur->next;
    }
    return head;
    
82. Remove Duplicates from Sorted List II
prev    head
-1 -->    1 --> 1 --> 1 --> 2 --> 3
dummy    cur
2)删光list
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *prev = dummy;        
    while(prev->next) {
        ListNode* cur = prev->next;
        //遇到相同的则继续往后走，直到遇到不同项, 此时cur指向第一次产生不同元素的位置
        while(cur->next && cur->next->val == cur->val)
            cur = cur->next;
        if(cur != prev->next)     //证明该位置是从相同元素挪来的，所以该位置要删
            prev->next = cur->next;
        else                      //元素本来就不同，挪prev就行
            prev = prev->next;
    }
    return dummy->next;

 
reverse链表  
206. Reverse Linked List
1）reverse整个链表 共4步:
    
        head
-1 -->    1 --> 2 --> 3 --> 4
dummy   prev   cur  tmp

while(cur)
    ListNode*tmp = cur->next;    //临时tmp来存原来的cur->next
    cur->next = prev;            //cur->next反向指回prev
    prev = cur;                  //prev往后挪一步
    cur = tmp;                   //现在的cur就是存的原来tmp

92. Reverse Linked List II 
2）reverse中间m ～ n 个点: loop一遍从[1,m)确定preM, 接着从[m，n]确定postN点, preM和postN分别指向要翻转的链表的前后的位置 
 A ------->o------->o-------->1--------->2------->3---------->o--------o
 |                  |         |                   |           |
 dummy             preM       m                   n         postN       
本质是reverse（preM,postN) 之间
 A ------->o------->o-------->1--------->2------->3---------->o--------o
 |                  |         |          |        |           |
 dummy             preM    head/cur     cur       t        postN 
模版同上
while(cur != posN)
    ListNode* t = cur->next;
    cur->next = head;
    head = cur;
    cur = t;    
while翻转后链表如下，我们需要1连posN，preM连head   
A ------->o------->o-------->1<---------2<-------3---------->o--------o
 |                 |                             |           |
 dummy             preM                       head      cur/t/postN 

preM->next->next = postN;
preM->next = head;

25. Reverse Nodes in k-Group
一层循环用来分段，一个函数用来翻转(模版同上，只用while(cur != next),最后返回翻转后链尾位置）
pre和next分别指向要翻转的链表的前后的位置，然后翻转后pre的位置更新到如下新的位置
-1 --> 1 --> 2 --> 3 --> 4 -->5
 |                       |
pre  head   cur   tmp   next

-1 --> 3 --> 2 --> 1 --> 4 -->5
                   |     |
                  pre   next
只要next走过k个节点，就可以调用翻转函数来进行局部翻转

Fast Slow Pointers应用
1) 找中点
2) remove Nth from end 
  (删倒数第N）快走N步，开始走慢，然后快慢都一步一步走，当快走到尾时，慢就在倒数第N个了
3) cycle 判链表有没有环: 
  快走2步，慢走1步，相遇了则有，NULL则false；
  while(fast != slow) {
    判fast和fast.next?NULL则false；
    fast2步，
    slow1步
  } 
  return true；
- 找环的入口，则相遇时，找原来头，它和慢都一个一步走，相遇时就是环入口。
  while(head != slow.next) {
    head = head.next; 
    slow = slow.next;
  } 
  return head；
4) rotate
  - NULL->head
  length记录链表长，k = k % length;  
  k = 0 ->head
  快慢指针，快走N步，开始走慢，然后快慢都一步一步走，当快走到尾时即while(fast->next!=NULL)，慢就在倒数第N个了,
  fast->next = head;  //fast的next接上了原来链表头
  head = slow->next;  //head链表头移动到slow下一位
  slow->next = NULL; //slow下一位断开，head链表完成
  返回head

