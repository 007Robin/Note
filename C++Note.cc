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

Const Type        :  value never changes, must init, 不可assigned。
Volatile Type     : value may change unexpected (prevent variable optimistation)  
eg: volatile const int time{20201201};  

Enumerattion Type : a user-defined set of values 用于代替integer constants。
enumerators exist only at compile time, 不占run time, 所以快，meanful。
eg: enum Choice {No, Yes};   <--- Choice 叫 symbolic name（可以不写）, No: 0, Yes: 1
Choice v = Yes;
while(v){...} or while(Yes){...}

typedef/using: 造alias
typedef unsigned int UI; UI a;
using UI = unsigned int; UI a;    //more readable

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
dynamic_cast<T> : onvert to target T, evaluate at run time
  
declaration : tell compiler just func names and arguments types
definition  : compiler 在这才 verify argument types numbers

delegating constructors:    用一个constructor去construct另一个constructor，避免了code repetition
constexpr constructor xx() const noexcept

Astring *p = new Astring("hello");
*p在stack上  pointing to --->   在heap上的hello
leak的产生: 因pointer itself都在stack上，stack goes, pointer goes. 如果无reference to／pointing to那块地址，就leak了.
"xxx"  这种形式但叫string constant，C style, 末尾隐含一个'\0'

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

stactic member function 可access static var/fuc，不可access instance var/fuc

c++中object size的影响因素有：
member data, base case, composed object, virtual function(a pointer to func)

array         int a[2][3];
pointer array int *b[3;     //row 可能diff length, 
eg: int main(int argc, char *argv[])

pointer是有type的，所以type match很重要。
void pointer: 可point to any type of data， must be cast before dereferenced.
不可给const 加pointer
可给const 加const pointer

Function Pointer常用于event-handle, device, event-driven场景
用pointer去invoke function foo()
int (*p) () = foo; //pointer hold address of a function
int (*f) () = nullptr;     //设foo的return是void               
f = reinterpret_cast<int (*) ()> (foo);   //该句不会改foo,但改了what foo look like, 使得可在imcompatiable pointer types间互访问

static object : begin of program, end of program, in data segment, init before main allocate and init once.
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
unique_ptr  : sole custody to pointee, only movable, std::move(unique pointer)
sharded_ptr : 有个referenced counted managed pointer
weak_ptr    : useful when an object needs to be accessed only if it exists
auto_ptr    : 是pre-cursor to unique_ptr  

C++ Templates
init at compile time
declaration and defination must in the same .H file.
                     
lambda function
auto f = [local capture] (optinal_parameters)->optinal_return_type { body };
f();
[]
[=]: all by value
[&]: all by refer
[=, &y]: all by value, y by refer
[&, x]: all by refer, x by value
[&x, y]: x by refer, y by value, only x,y

process : program executed, becomes process. at least one thread executes concurrently.
          provide resources needed to execute a program (address space, security context, environment variables)
          每个进程都有自己的内存地址空间.
thread  : sequence of instructions that execute independency.
          线程没有自己独立的内存资源，它只有自己的执行堆栈和局部变量.
More on: https://blog.csdn.net/honglin_ren/article/details/35839979
                     
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
