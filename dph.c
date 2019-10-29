#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct Philosopher {
	int id;
	//0 for sleep and 1 for eat
	int state;
	//0 for not use and 1 for in use
	int left_chop;
	int right_chop;
	pthread_t behaviour;
	struct Philosopher* left_pher;
	struct Philosopher* right_pher;
} Pher;

pthread_mutex_t lock;
pthread_cond_t wait;

Pher* head = NULL;

void pickup_forks(Pher* pher) {
	//printf("%d\n", pher->id);
	//printf("1\n");
	pthread_mutex_lock(&lock);
	if(pher->left_chop==0 && pher->right_chop==0) {
		pher -> left_chop = 1;
		pher -> right_chop = 1;
		pher -> state = 1;
		pher -> left_pher -> right_chop = 1;
		pher -> right_pher -> left_chop = 1;
		printf("[Philosopher%d] Eating...\n", pher->id);
		sleep(1);
	}
	else {
		printf("[Philosopher%d] Waiting...\n", pher->id);
		pthread_cond_wait(&wait, &lock);
		pickup_forks(pher);
	}
	pthread_mutex_unlock(&lock);
}

void return_forks(Pher* pher) {
	pthread_mutex_lock(&lock);
	pher -> left_chop = 0;
	pher -> right_chop = 0;
	pher -> state = 0;
	pher -> left_pher -> right_chop = 0;
	pher -> right_pher -> left_chop = 0;

	printf("[Philosopher%d] Sleeping...\n", pher->id);
	pthread_cond_signal(&wait);
	pthread_mutex_unlock(&lock);

	int sleep_time = 0;
	sleep_time = rand() % 5 + 1;
	sleep(sleep_time);
}

void* behave(void *arg) {
	Pher* pher = (Pher*) arg;
	//printf("1\n");
	while(1) {
		printf("[Philosopher%d] Asking...\n", pher->id);
		pickup_forks(pher);
		return_forks(pher);
	}
}

void philosopher_init(void) {
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&wait, NULL);

	head = (Pher*) malloc(sizeof(Pher));
	head -> id = 0;
	head -> state = 0;
	head -> left_chop = 0;
	head -> right_chop = 0;
	head -> left_pher = NULL;
	head -> right_pher = NULL;

	Pher* pher = NULL;
	Pher* tail = head;
	for(int i=0; i<4; i++) {
		pher = (Pher*) malloc(sizeof(Pher));
		pher -> id = i+1;
		pher -> state = 0;
		pher -> left_chop = 0;
		pher -> right_chop = 0;
		pher -> left_pher = NULL;
		pher -> right_pher = NULL;

		tail ->	right_pher = pher;
		tail = tail -> right_pher;
		tail -> left_pher = pher;
	}
	tail -> right_pher = head;
	head -> left_pher = tail;

	//printf("1\n");
	pher = head;
	for(int k=0; k<5; k++) {
		pthread_create(&(pher->behaviour), NULL, behave, (void*)pher);
		pher = pher -> right_pher;
	}
}

int main(void) {
	philosopher_init();

	Pher* pher = head;
	for(int i=0; i<5; i++) {
		pthread_join(pher->behaviour, NULL);
		pher = pher -> right_pher;
	}
	return 0;
}


