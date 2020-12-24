************* C++ ******************
polymorphism        : send messages to different objects, executed diff method at runtime。
inheritance         : compile time识别class之间的inheritance(public,private,protect...)关系，polymorphism object关系在run time识别(查虚表)。

method   : 只在你call时才take memory。
function : 存当前 call 处的 the address，去 stack

调用a member function时，
method : retreives a pointer to the object receving message。如call method时(&object, int, int) 隐含传的是（A* this, int, int)。
friend : No this pointer, object is passed explicity。

explicit关键字用到时，会取消一切隐含转换, 如函数参数中auto call constructor, (string)"hello"中char[]转成char*
noexcept关键字，说明保证all correct, 让compiler最大去优化
constexpr关键字，说明everything init／calculate／exec at compiler time, NO runtime, type safe compulation, 是const。 

SFINE： applies during overload resolution of function templates: 
When substituting the explicitly specified or deduced type for the template parameter fails, 
the specialization is discarded from the overload set instead of causing a compile error.

Const Type        :  value never changes, must init, 不可assigned。
Volatile Type     : value may change unexpected (prevent variable optimistation), 可改，不许optimise  
eg: volatile const int time{20201201};  

Enumerattion Type : a user-defined set of values 用于代替integer constants。
enumerators exist only at compile time, 不占run time, 所以快，meanful。
eg: enum Choice {No, Yes};   <--- Choice 叫 symbolic name（可以不写）, No: 0, Yes: 1
Choice v = Yes;
while(v){...} or while(Yes){...}

typedef/using: 造alias
typedef unsigned int UI; UI a;
using UI = unsigned int; UI a;    //more readable

左值可以出现在赋值等号的左边，使用时取的是作为对象的身份；
右值不可以出现在赋值等号的左边，使用时取的是对象的值。
lvalue: refer to the address in memory of a variable  eg: += -= /= 5=, &=, ^=, <<=, >>=, ++, --的operand must be lvalue.
rvalue: refer to value stored in a variable.          eg: 3
array name不可用作lvalue， 因其没有memory，只是个reference to a location。

&v[0] : 表示the address of the 1st element of array v
指针p指向v首位，可以用: char *p{v} <==> char *p{&v[0]} <=> char *p = &v[0]
                             |
                       name of array decays to the address of the 1st element of array   
v[i] <=> *(p+i)
v[0], v[4], *v, *(v+4), *p, *(p+4)， *(p += 2)均合法, 但是不存在*(v += 2)。

c++ pass array to functions through pointers.  
eg: call(v), fun(char v[]) 等价于 fun(char *v)
         |
  name of array decays to the address of the 1st element of array

inline functions : compiler replaces decalration of function where you call it.
compile time优化程度：constexpr > inline > 啥也不用，完全不优化

macro substitution : pre-processor可定义macro方便我们做代码置换，macro传的是expression不是value。 
eg:  #define sqr(n) (n)*(n)

const_cast<T> : remove const or volatile
static_cast<T> : convert to target T, apply at compile time. 不能cast struct to int, float to pointer
reinterpret_cast<T> : convert to any other pointer type. 能cast int to pointer, struct to fioat
dynamic_cast<T> : convert to target T, evaluate at run time
  
declaration : tell compiler just func names and arguments types
definition  : compiler 在这才 verify argument types numbers

delegating constructors:    用一个constructor去construct另一个constructor，避免了code repetition
constexpr constructor xx() const noexcept

Astring *p = new Astring("hello");
*p在stack上  pointing to --->   在heap上的hello
在pass by value return value情况下，string copy只copy pointer
String("world")
String在stack上，“world”在heap上，
leak的产生: 因pointer itself都在stack上，stack goes, pointer goes. 如果无reference to／pointing to那块地址，就leak了.
"xxx"  这种形式但叫string constant，C style, 末尾隐含一个'\0'

shallow copy
deep copy

copy 直接拿
assignment sth／object已有，在把别的stuff拿来之前，得先get rid of it first
#ifndef MAX_H
#define MAX_H
   int max(int, int);
#endif
  
C++ Linkage
在C++中调用C的代码必须把原来的C语言声明放到extern "C"{...}中, 否则编译无法通过。
原因：C和C++编译和链接方式完全不同。 C 编译函数时，不带函数的类型和作用域信息，只包含函数符号名字;
而c++ 为了实现函数的重载，在编译时会带上函数的类型和作用域信息。
extern "C" {    //stop name mangling 阻止命名修饰
    ...//意思是，这里不用compiler给我命名修饰，别处存在，我在这要用
} 
global变量: visible to everyone in the program. initialized when task is loaded, usually the value is in the executable(可执行文件.cpp)。 
define the global variables in source file, declare them "extern" in a header file. 
.h
int x;  <-- 加static 可避免报重复错误，static意思是只在我这个编译模块使用
int func(){}  <-- 加inline 避免报重复错误，odr原则，
a.cpp #include ""
b.cpp #include ""

stactic member function 可access static var/fuc，不可access instance var/fuc

c++中object size的影响因素有：
member data, base case, composed object, virtual function(a pointer to func)

array         int a[2][3];
pointer array int *b[3;     //row 可能diff length, 
eg: int main(int argc, char *argv[])

pointer是有type的，所以type match很重要。
void pointer: 可point to any type of data， must be cast before dereferenced.
不可给const 加pointer 但可加const pointer

Function Pointer常用于event-handle, device, event-driven场景
用pointer去invoke function foo()
int (*p) () = foo; //pointer hold address of a function
int (*f) () = nullptr;     //设foo的return是void               
f = reinterpret_cast<int (*) ()> (foo);   //该句不会改foo,但改了what foo look like, 使得可在imcompatiable pointer types间互访问

static object : begin of program, end of program, in data segment, init before main allocate and init once. 线程安全的
compiler 1)先allocate, 2) read declaration知道it's a function...
linker 需要definition来check函数arguments match不match 

static void (*lookup[]) (arg1, arg2,...) {...} 语句在data segment和stack中分别是：
data segment:                  
lookup--> zero -->
          one  -->
          two  -->
stack:
lookup[0]() <=> zero() 
     
Smart Pointer : applied to an object and give the implicit this pointer. 
unique_ptr  : exclusive ownership to pointee, only movable, std::move(unique pointer)，
              moving transfer ownership, cant's copy, two can't have same ownership to the same rescourse. 
unique_ptr  : 独占所指向的对象，自动释放所指向内存
sharded_ptr : 有个referenced counted managed pointer
sharded_ptr : 允许多个指针指向同一对象，有个reference count来统计，一旦为0则释放
weak_ptr    : 不控制所指对象生存期，指向由shared_ptr管理的对象
weak_ptr    : useful when an object needs to be accessed only if it exists
auto_ptr    : 是pre-cursor to unique_ptr 

C++ Templates
init at compile time
declaration and defination must in the same .H file.
https://eli.thegreenplace.net/2014/variadic-templates-in-c/
https://www.modernescpp.com/index.php/c-insights-variadic-templates
                     
#include <type_traits>
template <typename T, typename = int>
struct HasX : std::false_type { };
template <typename T>
struct HasX <T, decltype((void) T::x, 0)> : std::true_type { };                     
 https://stackoverflow.com/questions/1005476/how-to-detect-whether-there-is-a-specific-member-variable-in-class

template<int> struct Fibonacci;
template<> struct Fibonacci<0>{ static const int value = 0;};
template<> struct Fibonacci<1>{static const int value = 1;};
template<int i> struct Fibonacci{ static const int value = Fibonacci<i-1>::value + Fibonacci<i-2>::value;};                    
                     
lambda function
auto f = [local capture] (optinal_parameters)->optinal_return_type { body };
f();
for move-only type, can't caputre value [up], if capture reference[&up], would with undesirable custody implications, we use [std::move(up)]                     
[this]: capture class member, pointer, pass by value, copy address
[*this]: 仍pass by value, 但pass address里面的东西
[]
[=]: all by value
[&]: all by refer
[=, &y]: all by value, y by refer
[&, x]: all by refer, x by value
[&x, y]: x by refer, y by value, only x,y

std::function<int (int)> f;     //整体像个type
            return  take      
 f可 = 任何同type的functions，functor，function pointer，method，lambda
std::for each
std::copy_if
std::bind

RAII: Resource Acquisition Is Initialization
1)
std::mutex mymutex; 
mymutex.lock();
//to protect shared data                     
mymutex.unlock();
2)                     
std::lock_guard<std::mutex> guard(mymutex);                     
3)
std::unqiue_lock<std::mutex> l1(mymutex1, std::defer_lock);
std::unqiue_lock<std::mutex> l2(mymutex2, std::defer_lock)
std::lock(l1, l2);      //避免deadlock
 
std::condition_variable : threads wait on cv, notify on cv
std::condition_variable cv;
cv.wait(l1);                            //consuming thread
cv.notify_one(); or cv.notify_all();    //producing thread                   
                     
Constructor cannot be virtual, because when a constructor of a class is executed there is no virtual table in the memory, means no virtual pointer defined yet.
Virtual destructor/Pure virtual destructors are legal, if a class contains a pure virtual destructor, it must provide a function body for the pure virtual destructor.                     

虚表是什么？多态里面，含virtual function的class，会有一张虚表，里面是存virtual pointer，这些virtual pointer指向子类实例。所以虚表是属于class的，不是instance的。                     
怎么找虚表？在instance实例时会有个指向虚表的指针。
B* p = new D();
p->func();
这两句具体发生了什么？
More on: https://tangocc.github.io/2018/03/20/cpp-class-memory-struct/

void task() {cout << "do some work" << endl;}
std::thread t(task);    //create and start a thread to execute the task function
t.join();                //wait for thread to complete
                     
join() : to synchronise calling thread with specified thread, if main thread stops before child threads, it's error.                     
detach() : to create daemon thread, it stops when process terminates                     

Callable 可return, Runnable 无return type

Future, Promise用于asynchronous异步通信
  async lauches a funtion in a new thread returing the value asynchronously.
  promist stores a value for asynchronous retrieval 
  future waits for a value set asynchronously. 
Future: 是一个placeholder代表a value will be available at some time in the future.  is a read-only value
Promise: used to represent write side, one Promise can be watched by many Futures
  Thread1 Promise --> set_value() to -->  common_shared_value -->  get() by -->  Furture Thread2 to retrieval this value

new 是在动态内存(如heap)上给对象开辟内存空间,返回指向该对象的指针。
delete和new配套，用来释放内存，删一个动态分配的元素
new[] 是new分配一个对象数组，返回指向第一个对象的指针
delete[]和new[]配套，是释放一个动态分配的数组
malloc同new, 源自于C语言，不像new失败抛出异常，malloc失败返回NULL
free与malloc配套，作用和delete一样，释放内存。

Move semantics Advantage
  Automatic storage
  Pilfer resources of the source in order to construct the target with minimum expense
  Represent non-copyable resources more efficiently, like sockets
  Treat complex objects as normal values

Pointers Disadvantage
  Allocate on the free store
  Not exception-safety
  Ugly Ownership Issue(for deleting pointer)
  Does not allow for (RAII)Resource acquisition is initialization

printf(%d) 按地址解析成int32位，%lld。

什么是函数重载？ 函数名，参数列表，命名空间／域，const是名字修饰因素，为什么返回类型不是呢？
class A
{
   void func(*this, int a);
   void func(*this, int a) const; //此处const其实暗指 const *this
};

名字隐藏
namespace ns1
{
    int func(){}               // A
}

namespace ns2
{
    void func(){}               // B
    void func(int i){}          // C

    namespace ns3
    {
        void func(double d){}   // D  注释了这句则F处回去调用上层C，但开放这句则会把之前的都名字隐藏
        void run()
        {
            func(1);            // F
            func();             // G
        }
    }
}
                     
引用和指针的区别？
class C {
   int& ri;   
   const int& rri; // reference member
   C(const int& i, int ii) : ri(i), rri(ii) {} 
};

************* OS/Linux ******************    
 
process : program executed, becomes process. at least one thread executes concurrently.
          provide resources needed to execute a program (address space, security context, environment variables)
          每个进程都有自己的内存地址空间.
thread  : sequence of instructions that execute independency.
          线程没有自己独立的内存资源，它只有自己的执行堆栈和局部变量.
More on: https://blog.csdn.net/honglin_ren/article/details/35839979 
http://dreamrunner.org/blog/2014/08/07/C-multithreading-programming/

多process如何互访：IPC 中的 share memory，通过 mmap 映射共享文件
  share memory:内核有专门一块内存区供多个进程之间交换信息
  信号量：一个大于等于0的整型变量，值代表可利用资源的数目，wait()减值，singal()加值，当值为0，阻塞调用它的进程，直到value再次大于0.
  信号：像软件层上对中断机制的模拟，内核利用信号通知user space的进程发生了哪些系统事件

多thread如何互访：全局变量，信号量，mutex,condition_variable
  信号量补充：semaphore是一个在单核和多核之间都有效的同步手段。多核系统在很多场合 spin lock/自旋锁 比semaphore效率更高。因semaphore在同步时需要对进程进行休眠和唤醒的操作，耗资源。
spin lock 只有在多核系统上才有效，在单核上是没有用。当获取锁失败时,spinlock 不会让线程进入睡眠,而是不断 poll 去获取这个锁直到获取成功.
  信号补充：unix 系统通过 signal 通知进程相关的系统事件。信号分为2类，异步信号（e.g. SIGINT）和同步信号（e.g. SIGSEGV）。

main函数执行前会有哪些事情发生？
1. pre-processor: 通过 include 找所有.h，看declaration，来保证没有重复，会进行所有对静态变量、全局变量和全局对象的构造以及初始化工作， 
2. compile .C 去生成.O object files. it contain func definition with external linkage(visible to linker)
3. 最后 linker link all .o to build executable program

虚拟内存具有许多的优势和好处：
  可以支持多进程运行
  可以支持需求比物理内存更大空间的进程执行
  不必把程序的所有代码都加载到内存中就可以执行
  每个进程只能访问属于自己的那部分内存，可以有效地隔离进程
  进程之间可以共享程序代码
  程序可以被方便地进行重定向，可以在物理内存的任意地方被加载执行
  程序编写的时候，可以不用关系物理机器的物理内存结构                     

内存池：
https://zhuanlan.zhihu.com/p/64719710
MessageQueue:
//single producer(writer) multiple consumer(reader) queue                     
https://github.com/007Robin/spmcqstudy/tree/main/SPMC_Queue_bak
https://github.com/007Robin/PubSubQueue
epoll,select,poll区别
select,poll都需要最后轮询一遍fd,找到ready的那个，epoll是有个callback机制，直接对应到ready的fd.
epoll_create(),epoll_ctl_ADD,epoll_ctl_DEL, epoll_wait()...

栈溢出攻击？
当某个数据超过了处理程序回传堆栈地址限制的范围时，程序出现的异常操作
当把data的数据拷贝到buffer内时，超过缓冲区区域的高地址部分数据会“淹没”原本的其他栈帧数据
 
************* OO design ******************
objects hold values/are instance of a class
objects can't change type during run-time
  
Object间的关系有：
Association： 互相无ownership
eg: stock&exhange, factory(含对接外界的logic)&DBconnectionTool, car&station, studend&professor， 各自掌握自己life
Aggregation： 互相有part relationship
eg: student (attend) courses, but student 能自己掌握自己life
Composition： 互相有强ownership，strong relationship
eg: table&cell, windows create/own power to create/delete pane etc. 有种propagation

************* DB ******************
select Student，avg(Score) 
from A 
group by Student

reduncdency, inconsistency, security, integrity, concurrent access
DDL: define
DML: manipulate
More info: https://docs.google.com/document/d/1DY_TtIY8ThXA0nGp82bwR931Y2WCaYEJzqI6ElHoJvQ/edit

Transaction：
数据库中当data changes，可lock 1)单个cell 2)一整行row 3)整个table
但isolation level有以下4种：
Repeatable read (RR)  -- locks all the rows, no other application can update, delete, or insert a row, the same result is returned each time 
Read stability (RS)  -- locks only those rows, any change to a row made by another application process cannot be read until the change is committed by that process
Cursor stability (CS) -- locks any row being accessed during a transaction while the cursor is positioned on that row
Uncommitted read (UR) -- allows an application to access the uncommitted changes of other transactions, allows accessing a row that is being read

Isolation level	     | Access to uncommitted | data	Non-repeatable reads | Phantom reads
---------------------------------------------------------------------------------------
Repeatable read (RR) |	  Not possible	     |         Not possible	     |   Not possible
Read stability (RS)	 |    Not possible	     |         Not possible	     |   Possible
Cursor stability (CS)|	  Not possible	     |         Possible	         |   Possible
Uncommitted read (UR)|	  Possible	         |         Possible	         |   Possible

More info: https://www.ibm.com/support/knowledgecenter/SSEPGG_11.1.0/com.ibm.db2.luw.admin.perf.doc/doc/c0004121.html
