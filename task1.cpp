// Task 1: Basic std::thread example (from multi-threading slides, page 22)

#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;
void foo(int a)
{
    sleep(5);
    cout << a << endl;
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
