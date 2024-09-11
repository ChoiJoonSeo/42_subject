
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>

// int mails = 0;

// void* routine(){
// 	for (int i=0;i<1000000;i++){
// 		mails++;
// 	}
// }

// int main(){
// 	pthread_t p1, p2;
// 	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
// 		return 1;
// 	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
// 		return 2;

// 	if (pthread_join(p1, NULL) != 0)
// 		return 3;
// 	if (pthread_join(p2, NULL) != 0)
// 		return 4;
// 	printf("Number of mails : %d\n", mails); 
// 	return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <pthread.h>


// void* routine(){
// 	printf("test from threads\n");
// }

// int main(){
// 	pthread_t t1, t2;
// 	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
// 		return 1;
// 	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
// 		return 2;

// 	// if (pthread_join(t1, NULL) != 0)
// 	// 	return 3;
// 	if (pthread_join(t2, NULL) != 0)
// 		return 4;
// 	// printf("Number of mails : %d\n", mails); 
// 	return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
int cnt = 0;

void* routine(void	*arg){
	
	char *name = (char *)arg;
	cnt = 0;

	for (int i = 0; i < 10; i++)
	{
		printf("%s cnt : %d\n", name, cnt);
		usleep(1000);
		cnt++;
	}
}

int main(){
	pthread_t t1, t2;
	pthread_create(&t1, NULL, &routine, (void *)"thread1");
	pthread_create(&t2, NULL, &routine, (void *)"thread2");

	// if (pthread_join(t1, NULL) != 0)
	// 	return 3;
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	// printf("Number of mails : %d\n", mails); 
	return 0;
}



// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>

// int mails = 0;
// pthread_mutex_t mutex;

// void* routine(){
// 	for (int i=0;i<1000000;i++){
// 		pthread_mutex_lock(&mutex);
// 		mails++;
// 		pthread_mutex_unlock(&mutex);
// 	}
// }

// int main(){
// 	pthread_t p1, p2;
// 	pthread_mutex_init(&mutex, NULL);
// 	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
// 		return 1;
// 	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
// 		return 2;

// 	if (pthread_join(p1, NULL) != 0)
// 		return 3;
// 	if (pthread_join(p2, NULL) != 0)
// 		return 4;


// 	pthread_mutex_destroy(&mutex);
// 	printf("Number of mails : %d\n", mails);
// 	return 0;
// }
