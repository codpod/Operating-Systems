/******************************************************************

Class:     CSCI 480 - 2
Program:   Assignment 4
Author:    Cody McAntire
Z-number:  z1859456
Date Due:  04/23/2021

Purpose:	Simulate a four section intersection and it's traffic
			using semaphores
Execution: ./hw4.exe

*******************************************************************/
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <vector>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define TEN_MILLION 10000000L
#define BUFSIZE 1024
using namespace std;

using namespace std;
#define BUFFER_SIZE 35 
#define ACTION 2 
#define CAR_X 9 
#define T_NUM 1 


pthread_mutex_t mutex; 
int totalPlacements = 0;
int placement = 0;

char sem1[] = "NE";
char sem2[] = "NW";
char sem3[] = "SE";
char sem4[] = "SW";

vector<pair<int, int>> streets;
sem_t semlock; 
sem_t semlockp; 

void worker0(int c)
{

	int ret = pthread_mutex_lock(&mutex); //lock mutex	
	c += 1; //add to car number
	if (ret == 0) 
	{
		ostringstream lhw;
		//Print out car number and what they have lock for
		lhw << "On Lincoln Hwy west, car "<< c << " has obtained lock for " << sem3 << endl
		<< "On Lincoln Hwy west, car "<< c << " has obtained lock for " << sem4 << endl
        << "On Lincoln Hwy west, car "<< c << " now has both locks " << endl
        << "On Lincoln Hwy west, car "<< c << " has crossed " << endl 
        << "On Lincoln Hwy west, car "<< c << " has unlocked " << sem2 << endl
		<< "On Lincoln Hwy west, car "<< c << " has unlocked " << sem4 << endl
		<< "On Lincoln Hwy west, car "<< c << " has released both locks "<< endl;
		cout << lhw.str();
		sleep(1);
		//when an error occurs
		if (ret != 0)
		{
			cerr << "highway way " << c << " Error in Unlock" << endl;
			exit(-1);
		}		
		if (c == 0)
			placement++;
		//insert to vector
		streets.push_back(pair<int, int>(c, placement));
		
	}
	//or there was an error
	else 
	{
		//quit program and display message
		cout << "car " << c << " Error in lock, exit program" << endl;	
		exit(-1);
	}
	//Unlock the mutex
	ret = pthread_mutex_unlock(&mutex);	
}

void worker1(int c) //lincoln highway east worker
{
	int ret = pthread_mutex_lock(&mutex);//mutex is locked
	c += 1;
	if (ret == 0) 
	{
		ostringstream lhe;
		//Print out car number and what they have lock for
		lhe << "On Lincoln Hwy east, car "<< c << " has obtained lock for " << sem1 << endl
		<< "On Lincoln Hwy east, car "<< c << " has obtained lock for " << sem2 << endl
        << "On Lincoln Hwy east, car "<< c << " now has both locks " << endl
        << "On Lincoln Hwy east, car "<< c << " has crossed " << endl 
        << "On Lincoln Hwy east, car "<< c << " has unlocked " << sem1 << endl
		<< "On Lincoln Hwy east, car "<< c << " has unlocked " << sem2 << endl
		<< "On Lincoln Hwy east, car "<< c << " has released both locks "<< endl;
		cout << lhe.str();
		sleep(1);
		//when an error occurs
		if (ret != 0)
		{
			cerr << "highway way " << c << " Error in Unlock" << endl;
			exit(-1);
		}		
		if (c == 0)
			placement++;
		//insert to vector
		streets.push_back(pair<int, int>(c, placement));
		
	}
	else 
	{
		cout << "car " << c << " Error in lock, exit program" << endl;	//tell user
		exit(-1); //exit prog
	}
	ret = pthread_mutex_unlock(&mutex);	//unlock mutex to ret
}

void worker2(int c) //Annie Glidden North
{
	int ret = pthread_mutex_lock(&mutex); //lock mutex	
	c += 1; //add to car number
	if (ret == 0) 
	{
		ostringstream agn;
		//Print out car number and what they have lock for
		agn << "On Annie Glidden north, car "<< c << " has obtained lock for " << sem2 << endl
		<< "On Annie Glidden north, car "<< c << " has obtained lock for " << sem4 << endl
        << "On Annie Glidden north, car "<< c << " now has both locks " << endl
        << "On Annie Glidden north, car "<< c << " has crossed " << endl 
        << "On Annie Glidden north, car "<< c << " has unlocked " << sem2 << endl
		<< "On Annie Glidden north, car "<< c << " has unlocked " << sem4 << endl
		<< "On Annie Glidden north, car "<< c << " has released both locks "<< endl;
		cout << agn.str();
		sleep(1);

		//when an error occurs
		if (ret != 0)
		{
			cerr << "highway way " << c << " Error in Unlock" << endl;
			exit(-1);
		}		
		if (c == 0)
			placement++;
		//insert to vector
		streets.push_back(pair<int, int>(c, placement));
		
	}
	//when an error occurs
	else 
	{
		//quit program and display message
		cout << "car " << c << " Error in lock, exit program" << endl;	
		exit(-1);
	}
	//Unlock the mutex
	ret = pthread_mutex_unlock(&mutex);	
}

void worker3(int c) //Annie Glidden south
{
	int ret = pthread_mutex_lock(&mutex); //lock mutex	
	c += 1; //add to car number
	if (ret == 0) 
	{
		ostringstream ags;
		//Print out car number and what they have lock for
		ags << "On Annie Glidden south, car "<< c << " has obtained lock for " << sem1 << endl
		<< "On Annie Glidden south, car "<< c << " has obtained lock for " << sem3 << endl
        << "On Annie Glidden south, car "<< c << " now has both locks " << endl
        << "On Annie Glidden south, car "<< c << " has crossed " << endl 
        << "On Annie Glidden south, car "<< c << " has unlocked " << sem2 << endl
		<< "On Annie Glidden south, car "<< c << " has unlocked " << sem4 << endl
		<< "On Annie Glidden south, car "<< c << " has released both locks "<< endl;
		cout << ags.str();
		sleep(1);
		//when an error occurs
		if (ret != 0)
		{
			cerr << "highway way " << c << " Error in Unlock" << endl;
			exit(-1);
		}		
		if (c == 0)
			placement++;
		//insert to vector
		streets.push_back(pair<int, int>(c, placement));
		
	}
	//when an error occurs
	else 
	{
		//quit program and display message
		cout << "car " << c << " Error in lock, exit program" << endl;	
		exit(-1);
	}
	//Unlock the mutex
	ret = pthread_mutex_unlock(&mutex);	
}

//function for when car releases locks
void del(int c) 
{

	int ret = pthread_mutex_lock(&mutex);	
	//If statement to quit program if error occurs
	if (ret == 0) 
	{	
		totalPlacements--; //decrement to del from buf
		streets.erase(streets.begin());
	}
	else //lock didnt work
	{
		cerr << "Car lock " << c << ": lock failure" << endl;
		exit(-1);
	}
	ret = pthread_mutex_unlock(&mutex);	

	//If lockMutex not = 0, display message and exit -1
	if (ret != 0)
	{
		cerr << "car " << c << ":could not unlock" << endl;
		exit(-1);
	}
}

//void function use thread to insert placemnt buffers
void* process(void * c) 
{
	//store c as a long like simple example posted 
	long temp = (long)c;	
	for (int i = 0; i < 1; i++) 
	{
		sem_wait(&semlock);	 //semaphore waits while not full
		worker0(temp); //lincoln hwy east
		sem_post(&semlockp);
		sleep(1);
	}
	for (int i = 0; i < 1; i++) 
	{
		sem_wait(&semlock);	
		worker1(temp); //lincoln hwy west
		sem_post(&semlockp); //sem posts when not empty
		sleep(1);
	}
	for (int i = 0; i < 1; i++) 
	{
		sem_wait(&semlock);	
		worker2(temp); //annie glidden north
		sem_post(&semlockp); //sem posts when not empty
		sleep(1);
	}
	for (int i = 0; i < 1; i++) 
	{
		sem_wait(&semlock);	 //semaphore waits while not full
		worker3(temp); //annie glidden south
		sem_post(&semlockp); //sem posts when not empty
		sleep(1);
	}

	pthread_exit(NULL); //exit process
}

//function removes buffer
void * rmbuf(void * c) 
{
	long temp = (long)c;	//conver to int

	//calls del  for each action
	for (int i = 0; i < ACTION; i++) 
	{
		sem_wait(&semlockp);
		del(temp);	
		sem_post(&semlock);
		sleep(1);
	}
	pthread_exit(NULL);	
}


int main(int argc, char *argv[])
{

 	//semphore max size
	sem_init(&semlock, 0, BUFFER_SIZE);
	sem_init(&semlockp, 0, 0);

	//array for producer and consumer threads
	pthread_t Producer[CAR_X];
	pthread_t Consumer[ACTION];	

	int shared_memory_id;
	struct sem_struct *shared_memory_ptr;
	int total_count;
	if (argc != 2)
	total_count = 0;
	else 
	{
		total_count = atoi(argv[1]);
		if (total_count < 9)
		total_count += 1;
	}

	shared_memory_id =  shmget(IPC_PRIVATE, sizeof(sem_t), (S_IRUSR|S_IWUSR));//shmget(SHM_KEY, sizeof(struct sem_struct), 0644|IPC_CREAT);
	if (shared_memory_id == -1) 
	{
		perror("failed to create shared memory segment");
		return 1;
	}

   // Attach to the segment to get a pointer to it.
   shared_memory_ptr = (sem_struct *)shmat(shared_memory_id, NULL, 0);
   if (shared_memory_ptr == (void *) -1) 
	{
		perror("failed to attach memory segment");
		return 1;
	}

	ostringstream mem;
	mem << endl << "Got shared memory with id " << shared_memory_id << endl
		<<  "Attached to shared memory at "   << (void *)shared_memory_ptr << endl
		<<  "Initialized semaphore # 0: (NE) to 1" << endl
		<<  "Initialized semaphore # 1: (NW) to 1" << endl
		<<  "Initialized semaphore # 2: (SE) to 1" << endl
		<<  "Initialized semaphore # 3: (SW) to 1" << endl
		<<  "Initialized semaphore # 4: for cout\n"  << endl;
	mem << mem.str();

    pthread_mutex_init(&mutex, NULL);	
	int returned; 
	ostringstream st;
		st << "Starting process for street 0: Lincoln Hwy west\n"
			<< "Starting process for street 1: Lincoln Hwy east\n"
			<< "Starting process for street 2: Annie Glidden north\n"
			<< "Starting process for street 3: Annie Glidden south\n";
	cout << st.str();

    //child process
	for (long i = 0; i < T_NUM; i++) 
	{
		//create consumer thread
		returned = pthread_create(&Consumer[i], NULL, rmbuf, (void *)i);

		//if error, exit program 
		if (returned) 
		{
			cerr << "Error in the consumer create. " << endl;
			exit(-1);
		}
	}

    //parent process
	for (long i = 0; i < CAR_X; i++) 
	{
    //cout << "hi hi hi \n\n";
		returned = pthread_create(&Producer[i], NULL, process, (void *)i); 	//If there is an error exit

		if (returned) 
		{	
			cout << "Error in the producer create." << endl;
			exit(-1);
		}
	}
    //at the end join delete the threads
	for (int i = 0; i < 1; i++) 
	{
		pthread_join(Consumer[i], NULL);
	}
	//delete the threads
	for (int i = 0; i < CAR_X; i++) 
	{	
		pthread_join(Producer[i], NULL);
	}

	sem_destroy(&semlock); 
	sem_destroy(&semlockp); 
	pthread_mutex_destroy(&mutex); //get rid of mutex
	pthread_exit(NULL); //exit program
	return 0;
}