/*
Resource Acquisition Is Initialization
  In RAII, holding a resource is tied to object lifetime: resource allocation is done during object creation by the constructor, 
  while resource deallocation is done during object destruction by the destructor. 
  Thus the resource is guaranteed to be held between when initialization finishes and finalization starts and to be held only when the object is alive.
*/
//a stack overflow example
void func( int x )
{
    char* pleak = new char[1024]; // might be lost => memory leak
    std::string s( "hello world" ); // will be properly destructed
    if ( x ) throw std::runtime_error( "boom" );
    delete [] pleak; // will only get here if x == 0. if x!=0, throw exception
}
/*
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
//这种做法在大型程序时,一个function有多个exit point，则必须在每个point处，unlock一次，程序难以维护。
  |
  |
  V
//有了lock_guard簡直完美 
void incre(){
    lock_guard<std::mutex> lockGuard(mu); //给一个mutex variable来initialize lock_guard，剩下全它搞定！
    // 此处，实际上lock_guard在constructor里lock你给他的mutex, 在destructor里release同一个mutex. 重点是 他会保证一定call到destructor！
    funA();
}

/*
unique_lock用途同上，并且可以当作function的return type，更加弹性，支持各种不同的lock
  Deferred lock: 先不要acquire 等晚点儿再aquire
  Time-constrained lock: 试着要lock 但一段時間都要不到，就放弃
  Recursive lock: 如果一个function会recursively call自己， 如果你用的是一般的mutex, 那就会deadlock，因为你partner正占用同样的锁。
                  但如果是recursive mutex, 那就可以同一个thread一直acquire同样的lock, 其他thread必須等到這个thread release所有的recursive lock之后才可以acquire
  condition variable都需要搭配unique_lock使用
*/


