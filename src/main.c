#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sched.h>

#include "battery.h"
#include "balance.h"
#include "alert.h"
#include "led.h"

pthread_mutex_t mutex;

int main() {
    srand(time(NULL));
    batteries=(Battery*)malloc(sizeof(Battery)*NUM_CELLS);
    if(!batteries){ perror("malloc failed"); return 1; }

    pthread_mutex_init(&mutex,NULL);

    pthread_t threads[NUM_CELLS], balance_t, alert_t;
    int idx[NUM_CELLS];

    for(int i=0;i<NUM_CELLS;i++){
        idx[i]=i;
        pthread_create(&threads[i],NULL,battery_thread,&idx[i]);
    }

    pthread_create(&balance_t,NULL,balance_thread,NULL);
    pthread_create(&alert_t,NULL,alert_thread,NULL);

    // ===== 設定 thread priority 模擬 pre-emptable 任務 =====
    struct sched_param param;
    param.sched_priority = 80; // 高優先
    pthread_setschedparam(balance_t, SCHED_FIFO, &param);

    param.sched_priority = 60; // 警報優先
    pthread_setschedparam(alert_t, SCHED_FIFO, &param);

    // 主 thread join
    for(int i=0;i<NUM_CELLS;i++) pthread_join(threads[i],NULL);
    pthread_join(balance_t,NULL);
    pthread_join(alert_t,NULL);

    pthread_mutex_destroy(&mutex);
    free(batteries);

    return 0;
}
