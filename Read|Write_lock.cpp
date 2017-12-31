#include <iostream> 
#include <cstdlib>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;
class RWLock {
    private:
        std::mutex              shared;   //RWlock 有一个共用的mutex
        std::condition_variable readerQ;  //两个condition variable
        std::condition_variable writerQ;
        int                     active_readers; //  三个记录当前状态的变量
        int                     waiting_writers;
        int                     active_writers;
        
    public:
        RWLock()
            : shared()
              , readerQ(), writerQ()
              , active_readers(0), waiting_writers(0), active_writers(0){}

        bool no_one_writing(){
            return active_readers > 0 || active_writers == 0;
        }
        bool no_one_read_and_no_one_write(){
            return active_readers == 0 && active_writers == 0;
        }
        
        //RWlock的4个method：
        void ReadLock() {     //need read
            std::unique_lock<std::mutex> lk(shared);    //acquire lock
            readerQ.wait(lk, bind(&RWLock::no_one_writing, this));  //chech condition
                    // no one writhing or some one is reading, readlock thread can read, reader++ then unlock, 
                    //otherwise, the readlock thread sleep at readerQ wait for wake up.
            ++active_readers;
            lk.unlock();
        }

        void ReadUnlock() {     //is reading
            std::unique_lock<std::mutex> lk(shared);    //acquire lock
            --active_readers;     //reader minus 1
            lk.unlock();          //optional
            writerQ.notify_one();   //go to wake up a witer thread in writer thread queue
        }

        void WriteLock() {    //need write in
            std::unique_lock<std::mutex> lk(shared);
            ++waiting_writers;    //first goto wait, make wait_wirter++
            writerQ.wait(lk, bind(&RWLock::no_one_read_and_no_one_write, this)); //check condition
                        //if no one read and no one wirte, writelock thread can do write and wait_wirters--, active_writers++, then unlock
                        //otherwise, go to writerQ to wait/sleep, until other wake it up
            --waiting_writers;
            ++active_writers;
            lk.unlock();
        }

        void WriteUnlock() {    //is writing
            std::unique_lock<std::mutex> lk(shared);
            --active_writers;     //active writer minus 1
            if(waiting_writers > 0)     //check state, if writers are still exist, go to wake up one in WriteQ
                writerQ.notify_one();
            else                        //otherwise, no writers is waiting, go to wake up all read threads in readerQ
                readerQ.notify_all();
            lk.unlock();
        }
};
int result = 0;
void func(RWLock &rw, int i){
    if(i % 2 == 0){
        rw.WriteLock();
        result += 1;
        rw.WriteUnlock();
        rw.ReadLock();
        rw.ReadUnlock();
    }else{
        rw.ReadLock();
        rw.ReadUnlock();
        rw.WriteLock();
        result += 2;
        rw.WriteUnlock();

    }
}
void not_safe(int i){
    if(i%2 == 0){
        result += 1;
    }else{
        result += 2;
    }
}
int main(){
    RWLock rw;
    std::vector<std::thread> threads;
    for(int i = 0; i < 1000; i++){
        threads.push_back(std::thread(func, ref(rw), i));
        //threads.push_back(std::thread(not_safe, i));
    }
    for(int i = 0; i < threads.size() ; i++)
    {
        threads[i].join();
    }
    cout << result << endl;
    return 0;
}
/*
main里面初始化一个RWlock rw，用reference把它丢给所有的threads, reference ref(rw)保证了所有线程共用同一个rw。
func就是要改动result前call WriteLock, 改完result后call WriteUnlock。

RWlock详解4个method：
ReadLock:
1.acquire lock
2.确认condition,以下两种写法都等价，wait(lk,f)把判断要不要做事的逻辑写在另一个function里。
  while (!f()) { wait(lk);}   <==>   wait(lk,f);
  这里bind this可以先看成readerQ.wait(lk, no_one_writing);
  用readerQ.wait(lk, bind(&RWLock::no_one_writing, this)); 一句搞定
3.Readlock只有在没人写或者有人在读的情况下放心去读。
4.active_reader++
5.解锁（optional）

ReadUnLock:
1.acquire lock
2.改变shared data，当前reader里面减一
3.unlock(optional)
4.去叫writer thread queue的一个writer thread起床, 用WriteQ.notify_one()

WriteLock:
1.acquire lock
2.先去wait_writer里，wait_writer++
3.确认condition，如果没人读且没人写，我可以放心去写do this，(4.则wait_writer--，active_writer++)
                否则，去WriteQ里wait
                用writerQ.wait(lk, bind(&RWLock::no_one_read_and_no_one_write, this));一句搞定
4.wait_writer--，active_writer++
5.unlock(optional)

WriteUnlock:
1.acquire lock
2.改变shared data，当前writer里面减一
3.确认现在state，如果还有writer在等，则wake one thread in wirterQ, 如果没人等了，去reader thread queue里把all read thread叫起，因为多个reader可以同时read
4.unlock(optional)
*/
