#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "thread.h"
#include "lock.h"

using namespace multi;

class myThread : public thread
{
public:
    void *run() {
        for (int i = 0; i < N; i++) {
            printf("thread %u running, i = %d\n", self(), i);
            sleep(1);
        }
        printf("thread %u done\n", self());
        return NULL;
    }
private:
    const int N = 5;
};

int main()
{
    myThread* t1 = new myThread();
    myThread* t2 = new myThread();
    t1->start();
    t2->start();
    t1->join();
    t2->join();
    printf("main done\n");
    exit(0);
}
