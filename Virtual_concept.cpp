#include<iostream>
using namespace std;
 
class base
{
public:
    virtual void print () { cout<< "print base class" <<endl; }
    void show (){ cout<< "show base class" <<endl; }
    
    void fun_1() { cout << "base-1\n"; }
    virtual void fun_2() { cout << "base-2\n"; }
    virtual void fun_3() { cout << "base-3\n"; }
    virtual void fun_4() { cout << "base-4\n"; }
};
 
class derived:public base
{
public:
    void print () { cout<< "print derived class" <<endl; } 
    void show () { cout<< "show derived class" <<endl; }
    
    void fun_1() { cout << "derived-1\n"; }
    void fun_2() { cout << "derived-2\n"; }
    void fun_4(int x) { cout << "derived-2\n"; }
};
 
int main()
{
    base *bptr;         //a pointer of base class type
    derived d;
    bptr = &d;          //point to the objects of derived class
     
    bptr->print();      // virtual function, binded at runtime, according to the content of pointer = d's print  
                        // print derived class
    bptr->show();       // Non-virtual function, binded at compile time, according to the type of pointer = b's show
                        // show base class
    base *p;            //a pointer of base class type
    derived obj1;       //create an object of derived class, compiler creates a pointer as a data member of class containing the address of VTABLE of derived class
    p = &obj1;          //initialize it with the address of derived class object
 
    p->fun_1();         // Non-virtual function, Early binding(compile time), according to the type of pointer = b's fun_1()
                        // in base   --> base-1
    
    p->fun_2();         // Late binding (RTP)   --> derived-2     //overried
    p->fun_3();         // Late binding (RTP)   --> base-3        //not overried and is virtual funtion, call b's fun_3()
    p->fun_4();         // Late binding (RTP)   --> base-4        //the same
    
 
    //p->fun_4(5);      // Early binding but this function call is illegal(produces error)
    // becasue pointer is of base type and function is of derived class
    //fun_4(int) in derived class is different from virtual function fun_4() in base class as prototype of both the function is different.
      
}

/*
If object of that class is created then a virtual pointer is inserted as a data member of the class to point to virtual table of that class.
For each new object created, A new virtual Pointer is inserted as a data member of that class.
*/
