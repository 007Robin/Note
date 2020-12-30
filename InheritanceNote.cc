#pragma once
/*****  Base friend, public, private, protected Derive, Derive of Derive ***/
class Base {
    public:
        int pub_mem();
        friend class Pal;       //Pal友元依旧正常访问Base内部成员，不能访问Base的派生类，这种friend 关系只对做出声明的类有效
    protected:
        int prot_mem;           //visible by mem_func, friend, subclass's mem_func, objects
    private:
        char priv_mem;          //visible by mem_func, friend
};

//class 默认private继承， struct 默认public继承

class Sneaky : public Base {  
    int j;                      //j is private by default
    
    //my friend 能访问 Sneaky::prot_mem
    friend void clobber(Sneaky &s) { 
        s.j = s.prot_mem = 0;       //✅ clobber可访问 Sneaky对象的private 和 protected成员
    }
    //my friend 不能访问 Base::prot_mem
    friend void clobber(Base &b) { 
        //b.prot_mem = 0;            //❌不可访问Base的protect成员
    }
    void memfcn(Base &b) { b = *this; }
};

//public 继承Base
struct Pub_Derv : public Base{
    int f() {
        return prot_mem;    //Derive类能访问 Base::protected成员
    }
    char g() {
        //return priv_mem;     //❌派生类不可访问 Base::private成员
    }
    void memfcn(Base &b) { b = *this; }
};

//private 继承Base
struct Priv_Derv : private Base{
    //该private不影响派生类对Base访问权限，Derive类照旧可访问 Base::protected成员
    //但它的作用是，控制了派生类用户及其派生类的派生类们对Base成员的访问， eg: here, base's prot_mem, pub_mem seen as private
    int f1() const {
        return prot_mem;
    }
    void memfcn(Base &b) { b = *this; }
};

//protected 继承Base
struct Prot_Derv : protected Base {
    void memfcn(Base &b) { b = *this; }
};

//派生类的派生类
struct Derived_from_Public : public Pub_Derv {
    int use_base() {
        return prot_mem;    //✅ Base::prot_mem在Pub_Derv中依然是protected的
    }
    void memfcn(Base &b) { b = *this; }
};

struct Derived_from_Private : public Priv_Derv {
    int use_base() {
        //return prot_mem;    //❌ Base::prot_mem在Priv_Derv中是private的
    }
    //void memfcn(Base &b) { b = *this; }  //不合法❌ Base是private的
};

struct Derived_from_Protected : protected Prot_Derv {
    void memfcn(Base &b) { b = *this; }
};

//友元与继承
friend class Pal {
public:
    int f(Base b) {
        return b.prot_mem;      //Pal是Base友元，正常访问Protected的成员
    }
    int f2(Sneaky s) {
        //return s.j;         //❌ Pal不是Sneaky的友元
    }
    int f3(Sneaky s) {
        return s.prot_mem;      //✅ Pal是Base的友元，可访问Base对象的成员，即使是内嵌在Base的派生类的对象中的对象，也可访问。
    }
};

//把Pal类声明为Base的友元时，这种友元关系只对做出声明的类有效。即D2不能访问Base的protected和private成员
class D2 : public Pal {
public:
    int mem(Base b) {
        //return b.prot_mem;      //❌ 友元关系不能继承
    }
};

//用户
Pub_Derv d1;
Priv_Derv d2;
Prot_Derv d3;
Derived_from_Public dd1;
Derived_from_Private dd2;
Derived_from_Protected dd3;

d1.pub_mem();   // ✅ pub_mem在派生类是public的
//d2.pub_mem();   // ❌ pub_mem在派生类是private的

Base *p = &d1;//✅
//p = &d2;    //❌ Base在Priv_Derv派生类是 private的
//p = &d3;    //❌ Base在Priv_Derv派生类是 protected的
p = &dd1;   //✅
//p = &dd2;   //❌ Base在Derived_from_ptivate派生类的派生类是 private的
//p = &dd3;   //❌ Base在Derived_from_proveted派生类的派生类是 protected的

/******** using声明 可改变派生类继承的某个名字的访问级别 **********/
1) using声明语句出现在类的private部分，  类的成员和友元可访问该名字
2) using声明语句出现在类的public部分，   类的所有用户可访问该名字
3) using声明语句出现在类的protected部分，类的成员和友元和派生类可访问该名字

class B {
    foo();
    foo(int);
};
class D: B {  
    using B::foo;   //bring B's foo name into this region of the code //if no this line, B's foo would be hiddend.
    foo(float);

    using B::B;     //可把B的constructor拉到当前，复用B的constructor
}

D d;
d.foo();
d.foo(2);
d.foo(3.14);

/*********** polymorphism  **********/
Person  *ptr = new Person(p);
Student *stu = new Student(s);

1) default static binding:
    ptr = stu;
    ptr->display();     //compiler只认ptr是个Person *, compiler can only choose baed on its type  
    p = s;              //copy assignment: member copy, 去match p的all members，s多余的不管
    ptr = stu;          //passing address

2) dynamic binding:     //compiler choose base run time object time.
    virtual, virtual    //一个virtual pointer指向virtual function，存在一个virtual table里，
    ptr = stu;
    ptr->display();     //compiler查虚表，发现有Student的virtual display, 则call Student的display 
Person  *ptr = new Student{"Paul", "c++"};
    ptr->display();     //compiler查虚表，call Student的display，但ptr仍是个person, 它只可访问Person的 members

//compiler call 哪个？
有virtual, call virtual table里most instanced的。 
无virtual, call 基于它自己指针的 its type

Pure Virtual Functions
class Base {
    virtual func() = 0;           //这个class不可被instantiated，是个abstract类，有virtual table.
};
Base::func() {...}

func() 必须在subclass中implement，但也可用default implementation， 格式Base::func

Reference Polymophism用法：
Derived d;
Base&   br = d;
br.func();                      //call Derived里的func, 因为Base里func=0。

multiple inheritance:
class A {
   // price 0
};
class A1 : virtual public A {
   // price 5
};
class A2 : virtual public A{
   // price 10
};
class B : A1, A2;    which price??? -->  is price 10 from A2. if swap A1,A2, then is price 5 from A1.
所以需要具体去解决constructor conflicts
 

/********* static_cast vs. dynamic_cast *******/
Animal *p;
//把Animal转换成一个Bird
Bird *b = static_case<Brid*>{p};            //p不含一个Bird，则会crash
b->fly();

Bird *b = dynamic_case<Brid*>{p};           //p不含一个Bird, 会返回0，nullptr, 更safe, 但至少要有一个virtual function
b->fly();

/********  Exception **********/
//throw value
throw {<object>}  eg: throw(DividebyZero());
//catch reference
try{
    ...
} catch ( <object> or type ) {   //eg: catch(DividebyZero&)
    ...
    //release sth    
    throw;  //不是function，是operator
} catch (superClass&) {            //catch 是有顺序的
    ...
    throw subclassError；
}

std::terminate()

