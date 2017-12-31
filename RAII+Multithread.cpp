/*
Resource Acquisition Is Initialization
  In RAII, holding a resource is tied to object lifetime: resource allocation is done during object creation by the constructor, 
  while resource deallocation is done during object destruction by the destructor. 
  Thus the resource is guaranteed to be held between when initialization finishes and finalization starts and to be held only when the object is alive.
*／
//a stack overflow example
void func( int x )
{
    char* pleak = new char[1024]; // might be lost => memory leak
    std::string s( "hello world" ); // will be properly destructed
    if ( x ) throw std::runtime_error( "boom" );
    delete [] pleak; // will only get here if x == 0. if x!=0, throw exception
}
／*
C++的compiler會在一個scope要結束的時候(about to go out of scope or exception thrown)去执行所有变量的destructor in reverse order。
reverse order顺序是因为，后面destruct的变量可能用到前面要destruct变量的参数，保险起见，先destruct后面的。
*/

/*
multi-thread里c++有lock_guard & unique_lock
*/

void incre(){
    mu.lock();
    funA();//if funA throw unexpected exception, the lock will never release
    mu.unlock();
} 
  |
  |
  V
void incre(){
    mu.lock()
    try{
        funA();
    } catch(std::exception &cException){
        mu.unlock();
        throw cException;
    }
    mu.unlock(); 
} 
//这种做法在大型程序时
