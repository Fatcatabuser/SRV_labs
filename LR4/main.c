#include <stdio.h>
#include <time.h>
#include <sync.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include <process.h>
#include <pthread.h>

barrier_t barrier;

struct thread_info
{
    int thread_id;
    int thread_delay;
};

void *thread_func(void *not_used)
{
    struct thread_info *tinfo = not_used;
    time_t now;
    char buf[27];
    time(&now);
    printf("Potok %d , vremia starta %s \n", tinfo->thread_id, ctime_r(&now, buf));
    sleep(tinfo->thread_delay);
    barrier_wait(&barrier);
    time(&now);
    printf("barier v potoke %d, vremia srabativania %s \n", tinfo->thread_id, ctime_r(&now, buf));
}
int main()
{
    time_t now;
    struct thread_info *tinfo = (struct thread_info *)calloc(2, sizeof(tinfo));

    char buf[27];

    tinfo[0].thread_id = 1;
    tinfo[1].thread_id = 2;
    
    tinfo[0].thread_delay = 3;
    tinfo[1].thread_delay = 2;

    barrier_init(&barrier, NULL, 3);

    printf("Start \n");

    pthread_create(NULL, NULL, thread_func, &tinfo[0]);
    pthread_create(NULL, NULL, thread_func, &tinfo[1]);

    time(&now);
    printf("Main(Sergei Sisoev) : oshidanie y bariera, vrimia %s \n", ctime_r(&now, buf));
    barrier_wait(&barrier);
    time(&now);
    printf("barier v main(I993) , vremia srabativania %s \n", ctime_r(&now, buf));
    free(tinfo);
    sleep(5);
}
