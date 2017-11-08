#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_THREADS 16

void read_file();
void write_file();
void single_thread();
void multiple_thread();
void bubble_sort(unsigned int *, unsigned int, unsigned int);

unsigned int arr1[1000000];
unsigned int arr2[1000000];
unsigned int arr_size;
pthread_t threads[NUM_THREADS];
unsigned int pivot1, pivot2, pivot3, pivot4, pivot5, pivot6, pivot7;
sem_t all_thread_create, sem_t1, sem_t2, sem_t3, sem_t4, sem_t5, sem_t6, sem_t7, sem_t8, sem_t9, sem_t10, sem_t11, sem_t12, sem_t13, sem_t14, sem_t15, all_thread_finish;
sem_t sem8to9, sem9to10, sem10to11, sem11to12, sem12to13, sem13to14, sem14to15;

void *thread_function(void *param){
	pthread_t id = pthread_self();
	
	if(pthread_equal(id, threads[1])){//t1
		sem_wait(&all_thread_create);
	//	printf("I am thread 1\n");
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
	else if (pthread_equal(id, threads[2])){
		sem_wait(&sem_t2);
	//	printf("I am thread 2\n");
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
	//	printf("pivot2 = %u\n", pivot2);
		sem_post(&sem_t4);
		sem_post(&sem_t5);
	}
	else if (pthread_equal(id, threads[3])){
		sem_wait(&sem_t3);
	//	printf("I am thread 3\n");
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
	//	printf("pivot3 = %u\n", pivot3);
		sem_post(&sem_t6);
		sem_post(&sem_t7);
	}
	else if (pthread_equal(id, threads[4])){
		sem_wait(&sem_t4);
	//	printf("I am thread 4\n");
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
	//	printf("pivot4 = %u\n", pivot4);
		sem_post(&sem_t8);
		sem_post(&sem_t9);
	}
	else if (pthread_equal(id, threads[5])){
		sem_wait(&sem_t5);
	//	printf("I am thread 5\n");
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
	//	printf("pivot5 = %u\n", pivot5);
		sem_post(&sem_t10);
		sem_post(&sem_t11);
	}
	else if (pthread_equal(id, threads[6])){
		sem_wait(&sem_t6);
	//	printf("I am thread 6\n");
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
	//	printf("pivot6 = %u\n", pivot6);
		sem_post(&sem_t12);
		sem_post(&sem_t13);
	}
	else if (pthread_equal(id, threads[7])){
		sem_wait(&sem_t7);
	//	printf("I am thread 7\n");
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
	//	printf("pivot7 = %u\n", pivot7);
		sem_post(&sem_t14);
		sem_post(&sem_t15);
	}
	else if (pthread_equal(id, threads[8])){//below is level 4
		sem_wait(&sem_t8);
	//	printf("I am thread 8\n");
		bubble_sort(arr2, 0, pivot4);
		//sem_post to other 4 level thread
		sem_post(&sem8to9);
	}
	else if (pthread_equal(id, threads[9])){
		sem_wait(&sem_t9);
	//	printf("I am thread 9\n");
		bubble_sort(arr2, pivot4, pivot2);
		sem_wait(&sem8to9);
		sem_post(&sem9to10);
	}
	else if (pthread_equal(id, threads[10])){
		sem_wait(&sem_t10);
	//	printf("I am thread 10\n");
		bubble_sort(arr2, pivot2, pivot5);
		sem_wait(&sem9to10);
		sem_post(&sem10to11);
	}
	else if (pthread_equal(id, threads[11])){
		sem_wait(&sem_t11);
	//	printf("I am thread 11\n");
		bubble_sort(arr2, pivot5, pivot1);
		sem_wait(&sem10to11);
		sem_post(&sem11to12);
	}
	else if (pthread_equal(id, threads[12])){
		sem_wait(&sem_t12);
	//	printf("I am thread 12\n");
		bubble_sort(arr2, pivot1, pivot6);
		sem_wait(&sem11to12);
		sem_post(&sem12to13);
	}
	else if (pthread_equal(id, threads[13])){
		sem_wait(&sem_t13);
	//	printf("I am thread 13\n");
		bubble_sort(arr2, pivot6, pivot3);
		sem_wait(&sem12to13);
		sem_post(&sem13to14);
	}
	else if (pthread_equal(id, threads[14])){
		sem_wait(&sem_t14);
	//	printf("I am thread 14\n");
		bubble_sort(arr2, pivot3, pivot7);
		sem_wait(&sem13to14);
		sem_post(&sem14to15);
	}
	else if (pthread_equal(id, threads[15])){
		sem_post(&all_thread_create);
		sem_wait(&sem_t15);
	//	printf("I am thread 15\n");		
		bubble_sort(arr2, pivot7, arr_size);
		sem_wait(&sem14to15);
		sem_post(&all_thread_finish);
	}
	else{
	//	printf("just a test.\n");
	}

	pthread_exit(NULL);
}

int main(){//this is the main function;
	struct timeval start, end;
	read_file();

	printf("multi-thread.\n");
	gettimeofday(&start,0);
	multiple_thread();
	gettimeofday(&end,0);
	int sec = end.tv_sec-start.tv_sec;
	int usec = end.tv_usec=start.tv_usec;
	printf("elapsed %f ms\n", sec*1000+(usec/1000.0));

	printf("single thread\n");
	gettimeofday(&start,0);
	single_thread();
	gettimeofday(&end,0);
	sec = end.tv_sec-start.tv_sec;
	usec = end.tv_usec=start.tv_usec;
	printf("elapsed %f ms\n", sec*1000+(usec/1000.0));

	write_file();

	return 0;
}

void single_thread(){//use arr1
	bubble_sort(arr1, 0, arr_size);
}

void multiple_thread(){//use arr2
	int rc, i;
	int ret;
	ret = sem_init(&all_thread_create, 0, 0);
	sem_init(&sem_t1, 0, 0);
	sem_init(&sem_t2, 0, 0);
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
	sem_init(&all_thread_finish, 0, 0);
	sem_init(&sem8to9, 0, 0);
	sem_init(&sem9to10, 0, 0);
	sem_init(&sem10to11, 0, 0);
	sem_init(&sem11to12, 0, 0);
	sem_init(&sem12to13, 0, 0);
	sem_init(&sem13to14, 0, 0);
	sem_init(&sem14to15, 0, 0);
	
	for(i=0; i<NUM_THREADS; i++){//no usage of threads[0]
		rc = pthread_create(&threads[i], NULL, thread_function, NULL);
		if(rc){
			printf("ERROR; return code from pthread_create() #%d", i);
			exit(-1);
		}
	}

	ret = sem_wait(&all_thread_finish);

	printf("this is the mother task.\n");

}

void read_file(){
	FILE *fp;
	char *input_file=NULL;
	ssize_t buffer_size=0;
	unsigned int i=0;
	
	getline( &input_file, &buffer_size, stdin);
	
	for(i=0; i<buffer_size; i++){
		if(input_file[i]=='\n'){input_file[i]='\0';}
	}

	fp=fopen( input_file, "rt");
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

void write_file(){
	FILE *fp;
	int i;
	fp=fopen("output1.txt", "w");
	for(i=0; i<arr_size; i++){
		fprintf(fp, "%u ", arr2[i]);//multithread use arr2
	}
	fclose(fp);
	
	fp=fopen("output2.txt", "w");
	for(i=0; i<arr_size; i++){
		fprintf(fp, "%u ", arr1[i]);//singlethread use arr1
	}
	fclose(fp);
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
