#include <thread> 
#include <iostream>
#include <vector>
#include <mutex>
#include <deque>
using namespace std;
struct QueueBuffer {
    deque<int> deq;   //use to store value
    int capacity;
    mutex lock;     //the lock all thread share
    condition_variable not_full;    //condition_variable is where the producer thread sleep at.
    condition_variable not_empty;    //condition_variable is where the consumer thread sleep at. 
    
    QueueBuffer(int capacity) : capacity(capacity){}
    void deposit(int data){     //deposit -> the producer thread get lock first
        unique_lock<mutex> lk(lock);
        while(deq.size() == capacity){   //wait condition, check CV to see sleep or push.
            not_full.wait(lk);    //if pool size is full, the producer thread then must sleep
        }
        deq.push_back(data);      //otherwise, push the producer thread's data into the thread queue
        lk.unlock();              //release the lock  
        //if we don't call lk.unlock(), as RAII say, destructor will call unlock. The 2 method difference is just only about the performance.
        //when we wake up/notify a condition_variable, we do not need keep that lock, better to relase it and give it to others.
        not_empty.notify_one();   //call one thread in consumer thread queue(not empty) wake up to consume one
                                  
    }
    int fetch(){
        unique_lock<mutex> lk(lock);
        while(deq.size() == 0){
            not_empty.wait(lk);
        }
        int ret = deq.front();
        deq.pop_front();
        lk.unlock();
        not_full.notify_one();
        return ret;
    }
};
void consumer(int id, QueueBuffer& buffer){
    for(int i = 0; i < 20; ++i){
        int value = buffer.fetch();
        cout << "Consumer " << id << " fetched " << value << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void producer(int id, QueueBuffer& buffer){
    for(int i = 0; i < 30; ++i){
        buffer.deposit(i);
        cout << "Produced " << id << " produced " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main(){
    QueueBuffer buffer(4);

    thread c1(consumer, 0, ref(buffer));
    thread c2(consumer, 1, ref(buffer));
    thread c3(consumer, 2, ref(buffer));
    thread p1(producer, 0, ref(buffer));
    thread p2(producer, 1, ref(buffer));

    c1.join();
    c2.join();
    c3.join();
    p1.join();
    p2.join();

    return 0;
}

/*
Conditional variable is amazing. 
thread它并不是一直在while里面确认condition。它是一直在CV里面睡觉，直到有人叫它起床，做几件事。
step:
1.acquire lock (就是前面的unique_lock， 每次我们sleep之前都release它了
2.check condition
3.是个可以做到的condition的话，跳出while loop做事
4.condition还是不对的话，一样release刚刚拿的lock，进CV里睡觉。

deposit 过程是：拿锁，确认条件pool满了没有，不满则有位置可以放的话就放一个，放完后release lock, 叫consumer thread queue的人起床，该consumer一个啦。
fetch 过程是：拿锁，确认条件pool是空的吗，不空则有东西可以拿的话就拿，拿完后release lock, 叫producer thread queue的人起床，你去produce去吧。
*/

