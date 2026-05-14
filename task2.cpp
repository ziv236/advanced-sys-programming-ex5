// Task 2

#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex>

using namespace std;
mutex mtx;
void foo(int a)
{
    sleep(5);
    mtx.lock();
    cout << a << endl;
    mtx.unlock();
}
int main()
{
    thread threads[20];
    for (int i = 0; i < 20; i++){
        threads[i] = thread(foo, i);
    }
    for (int i = 0; i < 20; i++){
        threads[i].join();
    }
}
