//
// Created by Robin on 10/26/17.
//

#pragma once

class Base{
public:
    int pub_mem();
    friend class Pal;       //Pal友元依旧正常访问Base内部成员，不能访问Base的派生类，这种友元关系只对做出声明的类有效
protected:
    int prot_mem;
private:
    char priv_mem;
};
//受保护的成员prot_mem
class Sneaky : public Base {        //class 默认private继承， struct 默认public继承
    friend void clobber(Sneaky &s) { //友元能访问Sneaky::prot_mem
        s.j = s.prot_mem = 0;       //✅ clobber可访问Sneaky对象的private和protected成员
    }
    friend void clobber(Base &b) { //友元不能访问Base::prot_mem
        b.prot_mem = 0;            //❌不可访问Base的protect成员
    }
    int j;                      //j 默认private
    void memfcn(Base &b) { b = *this; }
};
//Public private protected继承Base
struct Pub_Derv : public Base{
    int f() {
        return prot_mem;    //派生类能访问protected成员
    }
    char g() {
        return priv_mem;     //❌派生类不可访问private成员
    }
    void memfcn(Base &b) { b = *this; }
};
struct Priv_Derv : private Base{
    //该private不影响派生类对Base访问权限，它控制派生类用户及其派生类的派生类们对Base成员的访问
    int f1() const {
        return prot_mem;
    }
    void memfcn(Base &b) { b = *this; }
};
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
        return prot_mem;    //❌ Base::prot_mem在Priv_Derv中是private的
    }
    void memfcn(Base &b) { b = *this; }  //不合法❌ Base是private的
};

struct Derived_from_Protected : protected Prot_Derv {
    void memfcn(Base &b) { b = *this; }
};
//友元与继承
class Pal {
public:
    int f(Base b) {
        return b.prot_mem;      //Pal是Base友元，正常访问Protected的成员
    }
    int f2(Sneaky s) {
        return s.j;         //❌ Pal不是Sneaky的友元
    }
    int f3(Sneaky s) {
        return s.prot_mem;      //✅ Pal是Base的友元，可访问Base对象的成员，即使是内嵌在Base的派生类的对象中的对象，也可访问。
    }
};
//把Pal类声明为Base的友元时，这种友元关系只对做出声明的类有效。即D2不能访问Base的protected和private成员
class D2 : public Pal {
public:
    int mem(Base b) {
        return b.prot_mem;      //❌ 友元关系不能继承
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
d2.pub_mem();   // ❌ pub_mem在派生类是private的

Base *p = &d1;//✅
p = &d2;    //❌ Base在Priv_Derv派生类是 private的
p = &d3;    //❌ Base在Priv_Derv派生类是 protected的
p = &dd1;   //✅
p = &dd2;   //❌ Base在Derived_from_ptivate派生类的派生类是 private的
p = &dd3;   //❌ Base在Derived_from_proveted派生类的派生类是 protected的

//提供using声明改变派生类继承的某个名字的访问级别
//using声明语句出现在类的private部分，类的成员和友元可访问该名字
//using声明语句出现在类的public部分，类的所有用户可访问该名字
//using声明语句出现在类的protected部分，类的成员和友元和派生类可访问该名字
