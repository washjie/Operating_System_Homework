#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/time.h>
#define MAX_THREADS 64
#define MAX_QUEUE 65536

typedef struct threadpool_t threadpool_t;

typedef enum {
    threadpool_invalid        = -1,
    threadpool_lock_failure   = -2,
    threadpool_queue_full     = -3,
    threadpool_shutdown       = -4,
    threadpool_thread_failure = -5
} threadpool_error_t;

typedef enum {
    threadpool_graceful       = 1
} threadpool_destroy_flags_t;

typedef enum {
    immediate_shutdown = 1,
    graceful_shutdown  = 2
} threadpool_shutdown_t;

typedef struct {
    void (*function)(void *);
    void *argument;
} threadpool_task_t;

struct threadpool_t {
  pthread_mutex_t lock;
  pthread_cond_t notify;
  pthread_t *threads;
  threadpool_task_t *queue;
  int thread_count;
  int queue_size;
  int head;
  int tail;
  int count;
  int shutdown;
  int started;
};

threadpool_t *threadpool_create(int thread_count, int queue_size, int flags);
int threadpool_add(threadpool_t *pool, void (*routine)(void *),void *arg, int flags);
int threadpool_destroy(threadpool_t *pool, int flags);
static void *threadpool_thread(void *threadpool);
int threadpool_free(threadpool_t *pool);


void read_file();
void write_file(int a);
void multiple_thread(int);
void bubble_sort(unsigned int *, unsigned int, unsigned int);

unsigned int arr1[1000000];//original arr
unsigned int arr2[1000000];//modified and will be reinitialize using arr1;
unsigned int arr_size;
unsigned int pivot1, pivot2, pivot3, pivot4, pivot5, pivot6, pivot7;
sem_t sem_t2, sem_t3, sem_t4, sem_t5, sem_t6, sem_t7, sem_t8, sem_t9, sem_t10, sem_t11, sem_t12, sem_t13, sem_t14, sem_t15, all_thread_finish;
sem_t sem8to9, sem9to10, sem10to11, sem11to12, sem12to13, sem13to14, sem14to15;

void task_1(){//
//	printf("job1\n");
	unsigned int i, j;

	pivot1 = 0;
	i = 0;
	j = arr_size;
	do{
		do i++;while(arr2[i]<arr2[pivot1]);
		do j--;while(arr2[j]>arr2[pivot1]);
		if(i<j){ 
			unsigned int temp = arr2[i];
			arr2[i] = arr2[j];
			arr2[j] = temp;
		}
	}while(i<j);
	unsigned int temp = arr2[pivot1];
	arr2[pivot1] = arr2[j];
	arr2[j] = temp;
	pivot1 = j;
	//	printf("pivot1 = %u\n", pivot1);
	sem_post(&sem_t2);
	sem_post(&sem_t3);
}
void task_2(){
	sem_wait(&sem_t2);
//	printf("job2\n");
	unsigned int i, j;
	pivot2 = 0;
	i = pivot2;
	j = pivot1;
	do{
		do i++;while(arr2[i]<arr2[pivot2]);
		do j--;while(arr2[j]>arr2[pivot2]);
		if(i<j){ 
			unsigned int temp = arr2[i];
			arr2[i] = arr2[j];
			arr2[j] = temp;
		}
	}while(i<j);
	unsigned int temp = arr2[pivot2];
	arr2[pivot2] = arr2[j];
	arr2[j] = temp;
	pivot2 = j;
	//job done
	sem_post(&sem_t2);
	//	printf("pivot2 = %u\n", pivot2);
	sem_post(&sem_t4);
	sem_post(&sem_t5);
}
void task_3(){
	sem_wait(&sem_t3);
//	printf("job3\n");
	unsigned int i, j;
	pivot3 = pivot1+1;
	i = pivot3;
	j = arr_size;
	do{
		do i++;while(arr2[i]<arr2[pivot3]);
		do j--;while(arr2[j]>arr2[pivot3]);
		if(i<j){ 
			unsigned int temp = arr2[i];
			arr2[i] = arr2[j];
			arr2[j] = temp;
		}
	}while(i<j);
	unsigned int temp = arr2[pivot3];
	arr2[pivot3] = arr2[j];
	arr2[j] = temp;
	pivot3 = j;
	//job done
	sem_post(&sem_t3);
	//	printf("pivot3 = %u\n", pivot3);
	sem_post(&sem_t6);
	sem_post(&sem_t7);
}
void task_4(){
	sem_wait(&sem_t4);
//	printf("job4\n");
	unsigned int i, j;
	pivot4 = 0;
	i = pivot4;
	j = pivot2;
	do{
		do i++;while(arr2[i]<arr2[pivot4]);
		do j--;while(arr2[j]>arr2[pivot4]);
		if(i<j){ 
			unsigned int temp = arr2[i];
			arr2[i] = arr2[j];
			arr2[j] = temp;
		}
	}while(i<j);
	unsigned int temp = arr2[pivot4];
	arr2[pivot4] = arr2[j];
	arr2[j] = temp;
	pivot4 = j;	
	//job done
	sem_post(&sem_t4);
	//	printf("pivot4 = %u\n", pivot4);
	sem_post(&sem_t8);
	sem_post(&sem_t9);
}
void task_5(){
	sem_wait(&sem_t5);
//	printf("job5\n");
	unsigned int i, j;
	pivot5 = pivot2+1;
	i = pivot5;
	j = pivot1;
	do{
		do i++;while(arr2[i]<arr2[pivot5]);
		do j--;while(arr2[j]>arr2[pivot5]);
		if(i<j){ 
			unsigned int temp = arr2[i];
			arr2[i] = arr2[j];
			arr2[j] = temp;
		}
	}while(i<j);
	unsigned int temp = arr2[pivot5];
	arr2[pivot5] = arr2[j];
	arr2[j] = temp;
	pivot5 = j;
	//job done
	sem_post(&sem_t5);
	//	printf("pivot5 = %u\n", pivot5);
	sem_post(&sem_t10);
	sem_post(&sem_t11);
}
void task_6(){
	sem_wait(&sem_t6);
//	printf("job6\n");
	unsigned int i, j;
	pivot6 = pivot1+1;
	i = pivot6;
	j = pivot3;
	do{
		do i++;while(arr2[i]<arr2[pivot6]);
		do j--;while(arr2[j]>arr2[pivot6]);
		if(i<j){ 
			unsigned int temp = arr2[i];
			arr2[i] = arr2[j];
			arr2[j] = temp;
		}
	}while(i<j);
	unsigned int temp = arr2[pivot6];
	arr2[pivot6] = arr2[j];
	arr2[j] = temp;
	pivot6 = j;
	//job done
	sem_post(&sem_t6);
	//	printf("pivot6 = %u\n", pivot6);
	sem_post(&sem_t12);
	sem_post(&sem_t13);
}
void task_7(){
	sem_wait(&sem_t7);
//	printf("job7\n");
	unsigned int i, j;
	pivot7 = pivot3+1;
	i = pivot7;
	j = arr_size;
	do{
		do i++;while(arr2[i]<arr2[pivot7]);
		do j--;while(arr2[j]>arr2[pivot7]);
		if(i<j){ 
			unsigned int temp = arr2[i];
			arr2[i] = arr2[j];
			arr2[j] = temp;
		}
	}while(i<j);
	unsigned int temp = arr2[pivot7];
	arr2[pivot7] = arr2[j];
	arr2[j] = temp;
	pivot7 = j;
	//job done
	sem_post(&sem_t7);
	//	printf("pivot7 = %u\n", pivot7);
	sem_post(&sem_t14);
	sem_post(&sem_t15);
}
void task_8(){
	sem_wait(&sem_t8);
	bubble_sort(arr2, 0, pivot4);
	//job done
	sem_post(&sem_t8);
	//sem_post to other 4 level thread
	sem_post(&sem8to9);
}
void task_9(){
	sem_wait(&sem_t9);
	bubble_sort(arr2, pivot4, pivot2);
	//job done
	sem_post(&sem_t9);
//
	sem_wait(&sem8to9);
	sem_post(&sem8to9);//for destroy purpose
	sem_post(&sem9to10);
}
void task_10(){
	sem_wait(&sem_t10);
	bubble_sort(arr2, pivot2, pivot5);
	//job done
	sem_post(&sem_t10);
//
	sem_wait(&sem9to10);
	sem_post(&sem9to10);
	sem_post(&sem10to11);
}
void task_11(){
	sem_wait(&sem_t11);
	bubble_sort(arr2, pivot5, pivot1);
	//job done
	sem_post(&sem_t11);
//
	sem_wait(&sem10to11);
	sem_post(&sem10to11);
	sem_post(&sem11to12);
}
void task_12(){
	sem_wait(&sem_t12);
	bubble_sort(arr2, pivot1, pivot6);
	//job done
	sem_post(&sem_t12);
//
	sem_wait(&sem11to12);
	sem_post(&sem11to12);
	sem_post(&sem12to13);
}
void task_13(){
	sem_wait(&sem_t13);
	bubble_sort(arr2, pivot6, pivot3);
	//job done
	sem_post(&sem_t13);
//
	sem_wait(&sem12to13);
	sem_post(&sem12to13);
	sem_post(&sem13to14);
}
void task_14(){
	sem_wait(&sem_t14);
	bubble_sort(arr2, pivot3, pivot7);
	//job done
	sem_post(&sem_t14);
//
	sem_wait(&sem13to14);
	sem_post(&sem13to14);
	sem_post(&sem14to15);
}
void task_15(){
	sem_wait(&sem_t15);	
	bubble_sort(arr2, pivot7, arr_size);
	//job done
	sem_post(&sem_t15);
//
	sem_wait(&sem14to15);
	sem_post(&sem14to15);
	sem_post(&all_thread_finish);
}

int main(){//this is the main function;
	
	read_file();

	printf("multi-thread with thread pools size = 1.\n");
	multiple_thread(1);
	write_file(1);
	int i; for(i=0; i<arr_size; i++){arr2[i] = arr1[i];}//reinitialize the arr2 using arr1

	printf("multi-thread with thread pools size = 2.\n");
	multiple_thread(2);
	write_file(2);
	for(i=0; i<arr_size; i++){arr2[i] = arr1[i];}

	printf("multi-thread with thread pools size = 3.\n");
	multiple_thread(3);
	write_file(3);
	for(i=0; i<arr_size; i++){arr2[i] = arr1[i];}

	printf("multi-thread with thread pools size = 4.\n");
	multiple_thread(4);
	write_file(4);
	for(i=0; i<arr_size; i++){arr2[i] = arr1[i];}

	printf("multi-thread with thread pools size = 5.\n");
	multiple_thread(5);
	write_file(5);
	for(i=0; i<arr_size; i++){arr2[i] = arr1[i];}

	printf("multi-thread with thread pools size = 6.\n");
	multiple_thread(6);
	write_file(6);
	for(i=0; i<arr_size; i++){arr2[i] = arr1[i];}

	printf("multi-thread with thread pools size = 7.\n");
	multiple_thread(7);
	write_file(7);
	for(i=0; i<arr_size; i++){arr2[i] = arr1[i];}

	printf("multi-thread with thread pools size = 8.\n");
	multiple_thread(8);
	write_file(8);

/*	printf("multi-thread with 2 thread\n");
	gettimeofday(&start,0);
	multiple_thread(2);
	gettimeofday(&end,0);
	sec = end.tv_sec-start.tv_sec;
	usec = end.tv_usec=start.tv_usec;
	printf("elapsed %f ms\n", sec*1000+(usec/1000.0));
*/

	return 0;
}


void multiple_thread(int num_thread){//use arr2
	struct timeval start, end;
	gettimeofday(&start,0);

	int ret;

	ret = sem_init(&sem_t2, 0, 0);
	sem_init(&sem_t3, 0, 0);
	sem_init(&sem_t4, 0, 0);
	sem_init(&sem_t5, 0, 0);
	sem_init(&sem_t6, 0, 0);
	sem_init(&sem_t7, 0, 0);
	sem_init(&sem_t8, 0, 0);
	sem_init(&sem_t9, 0, 0);
	sem_init(&sem_t10, 0, 0);
	sem_init(&sem_t11, 0, 0);
	sem_init(&sem_t12, 0, 0);
	sem_init(&sem_t13, 0, 0);
	sem_init(&sem_t14, 0, 0);
	sem_init(&sem_t15, 0, 0);
	
	sem_init(&sem8to9, 0, 0);
	sem_init(&sem9to10, 0, 0);
	sem_init(&sem10to11, 0, 0);
	sem_init(&sem11to12, 0, 0);
	sem_init(&sem12to13, 0, 0);
	sem_init(&sem13to14, 0, 0);
	sem_init(&sem14to15, 0, 0);

	ret = sem_init(&all_thread_finish, 0, 0);
	threadpool_t *tp;
	tp = threadpool_create(num_thread, 16, 0);
	
	ret = threadpool_add(tp, &task_1, 0, 0);
	ret = threadpool_add(tp, &task_2, 0, 0);
	ret = threadpool_add(tp, &task_3, 0, 0);
	ret = threadpool_add(tp, &task_4, 0, 0);
	ret = threadpool_add(tp, &task_5, 0, 0);	
	ret = threadpool_add(tp, &task_6, 0, 0);
	ret = threadpool_add(tp, &task_7, 0, 0);
	ret = threadpool_add(tp, &task_8, 0, 0);
	ret = threadpool_add(tp, &task_9, 0, 0);
	ret = threadpool_add(tp, &task_10, 0, 0);
	ret = threadpool_add(tp, &task_11, 0, 0);
	ret = threadpool_add(tp, &task_12, 0, 0);
	ret = threadpool_add(tp, &task_13, 0, 0);
	ret = threadpool_add(tp, &task_14, 0, 0);
	ret = threadpool_add(tp, &task_15, 0, 0);

	ret = sem_wait(&all_thread_finish);
	sem_post(&all_thread_finish);
	sem_destroy(&all_thread_finish);

	threadpool_destroy(tp, 0);

	sem_destroy(&sem_t2);
	sem_destroy(&sem_t3);
	sem_destroy(&sem_t4);
	sem_destroy(&sem_t5);
	sem_destroy(&sem_t6);
	sem_destroy(&sem_t7);
	sem_destroy(&sem_t8);
	sem_destroy(&sem_t9);
	sem_destroy(&sem_t10);
	sem_destroy(&sem_t11);
	sem_destroy(&sem_t12);
	sem_destroy(&sem_t13);
	sem_destroy(&sem_t14);
	sem_destroy(&sem_t15);
	
	sem_destroy(&sem8to9);
	sem_destroy(&sem9to10);
	sem_destroy(&sem10to11);
	sem_destroy(&sem11to12);
	sem_destroy(&sem12to13);
	sem_destroy(&sem13to14);
	sem_destroy(&sem14to15);

	//printf("this is the mother task.\n");
	gettimeofday(&end,0);
//	int sec = end.tv_sec-start.tv_sec;
//	int usec = end.tv_usec-start.tv_usec;
	printf("elapsed %f ms\n", (end.tv_sec-start.tv_sec)*1000+((end.tv_usec-start.tv_usec)/1000.0));
}

void read_file(){
	FILE *fp;
	char *input_file=NULL;
	ssize_t buffer_size=0;
	unsigned int i=0;

	fp=fopen( "input.txt", "r");
	if(fp){printf("read success.\n");}
	else{printf("read failed.\n"); exit(EXIT_FAILURE);}
	fprintf(fp, "Testing...\n");

	fscanf(fp, "%u ", &arr_size);

	for(i=0; i<arr_size; i++){
		fscanf(fp, "%u", &arr1[i]);
		arr2[i] = arr1[i];
	}
	fclose(fp);
}

void write_file(int a){
	FILE *fp;
	int i;
	switch(a){
	case 1:
		fp = fopen("output1.txt", "w");
		break;
	case 2:
		fp = fopen("output2.txt", "w");
		break;
	case 3:
		fp = fopen("output3.txt", "w");
		break;
	case 4:
		fp = fopen("output4.txt", "w");
		break;
	case 5:
		fp = fopen("output5.txt", "w");
		break;
	case 6:
		fp = fopen("output6.txt", "w");
		break;
	case 7:
		fp = fopen("output7.txt", "w");
		break;
	case 8:
		fp = fopen("output8.txt", "w");
		break;
	
	}
	for(i=0; i<arr_size; i++){
		fprintf(fp, "%u ", arr2[i]);//multithread use arr2
	}
	fclose(fp);
/*
	fp=fopen("output2.txt", "w");
	for(i=0; i<arr_size; i++){
		fprintf(fp, "%u ", arr1[i]);//singlethread use arr1
	}
	fclose(fp);
*/
}

void bubble_sort(unsigned int *arr, unsigned begin, unsigned int end){
	unsigned int i, j;
	for(i=begin; i<end-1; i++){
		for(j=i+1; j<end; j++){
			if(arr[i] > arr[j]){
				unsigned int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

threadpool_t *threadpool_create(int thread_count, int queue_size, int flags)
{
    threadpool_t *pool;
    int i;
    (void) flags;

    if(thread_count <= 0 || thread_count > MAX_THREADS || queue_size <= 0 || queue_size > MAX_QUEUE) {
        return NULL;
    }

    if((pool = (threadpool_t *)malloc(sizeof(threadpool_t))) == NULL) {
    	return NULL;
    }

    /* Initialize */
    pool->thread_count = 0;
    pool->queue_size = queue_size;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = pool->started = 0;

    /* Allocate thread and task queue */
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_count);
    pool->queue = (threadpool_task_t *)malloc
        (sizeof(threadpool_task_t) * queue_size);

    /* Initialize mutex and conditional variable first */
    if((pthread_mutex_init(&(pool->lock), NULL) != 0) ||
       (pthread_cond_init(&(pool->notify), NULL) != 0) ||
       (pool->threads == NULL) ||
       (pool->queue == NULL)) {
        return NULL;
    }

    /* Start worker threads */
    for(i = 0; i < thread_count; i++) {
        if(pthread_create(&(pool->threads[i]), NULL,
                          threadpool_thread, (void*)pool) != 0) {
            threadpool_destroy(pool, 0);
            return NULL;
        }
        pool->thread_count++;
        pool->started++;
    }

    return pool;

}

int threadpool_add(threadpool_t *pool, void (*function)(void *),
                   void *argument, int flags)
{
    int err = 0;
    int next;
    (void) flags;

    if(pool == NULL || function == NULL) {
        return threadpool_invalid;
    }

    if(pthread_mutex_lock(&(pool->lock)) != 0) {
        return threadpool_lock_failure;
    }

    next = (pool->tail + 1) % pool->queue_size;

    do {
        /* Are we full ? */
        if(pool->count == pool->queue_size) {
            err = threadpool_queue_full;
            break;
        }

        /* Are we shutting down ? */
        if(pool->shutdown) {
            err = threadpool_shutdown;
            break;
        }

        /* Add task to queue */
        pool->queue[pool->tail].function = function;
        pool->queue[pool->tail].argument = argument;
        pool->tail = next;
        pool->count += 1;

        /* pthread_cond_broadcast */
        if(pthread_cond_signal(&(pool->notify)) != 0) {
            err = threadpool_lock_failure;
            break;
        }
    } while(0);

    if(pthread_mutex_unlock(&pool->lock) != 0) {
        err = threadpool_lock_failure;
    }

    return err;
}

int threadpool_destroy(threadpool_t *pool, int flags)
{
    int i, err = 0;

    if(pool == NULL) {
        return threadpool_invalid;
    }

    if(pthread_mutex_lock(&(pool->lock)) != 0) {
        return threadpool_lock_failure;
    }

    do {
        /* Already shutting down */
        if(pool->shutdown) {
            err = threadpool_shutdown;
            break;
        }

        pool->shutdown = (flags & threadpool_graceful) ?
            graceful_shutdown : immediate_shutdown;

        /* Wake up all worker threads */
        if((pthread_cond_broadcast(&(pool->notify)) != 0) ||
           (pthread_mutex_unlock(&(pool->lock)) != 0)) {
            err = threadpool_lock_failure;
            break;
        }

        /* Join all worker thread */
        for(i = 0; i < pool->thread_count; i++) {
            if(pthread_join(pool->threads[i], NULL) != 0) {
                err = threadpool_thread_failure;
            }
        }
    } while(0);

    /* Only if everything went well do we deallocate the pool */
    if(!err) {
        threadpool_free(pool);
    }
    return err;
}

int threadpool_free(threadpool_t *pool)
{
    if(pool == NULL || pool->started > 0) {
        return -1;
    }

    /* Did we manage to allocate ? */
    if(pool->threads) {
        free(pool->threads);
        free(pool->queue);
 
        /* Because we allocate pool->threads after initializing the
           mutex and condition variable, we're sure they're
           initialized. Let's lock the mutex just in case. */
        pthread_mutex_lock(&(pool->lock));
        pthread_mutex_destroy(&(pool->lock));
        pthread_cond_destroy(&(pool->notify));
    }
    free(pool);    
    return 0;
}


static void *threadpool_thread(void *threadpool)
{
    threadpool_t *pool = (threadpool_t *)threadpool;
    threadpool_task_t task;

    for(;;) {
        /* Lock must be taken to wait on conditional variable */
        pthread_mutex_lock(&(pool->lock));

        /* Wait on condition variable, check for spurious wakeups.
           When returning from pthread_cond_wait(), we own the lock. */
        while((pool->count == 0) && (!pool->shutdown)) {
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }

        if((pool->shutdown == immediate_shutdown) ||
           ((pool->shutdown == graceful_shutdown) &&
            (pool->count == 0))) {
            break;
        }

        /* Grab our task */
        task.function = pool->queue[pool->head].function;
        task.argument = pool->queue[pool->head].argument;
        pool->head = (pool->head + 1) % pool->queue_size;
        pool->count -= 1;

        /* Unlock */
        pthread_mutex_unlock(&(pool->lock));

        /* Get to work */
        (*(task.function))(task.argument);
    }

    pool->started--;

    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);
    return(NULL);
}
