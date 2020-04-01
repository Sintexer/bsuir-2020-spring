#include <iostream>
#include <cstring>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>	

using namespace std;	

void child(sem_t* sem, int fpipe){
	char buffer[256], q[2];
	strcpy(q, "q");
	do{
		sem_wait(sem);
		read(fpipe, buffer, 256);
		if(strcmp(q, buffer)==0)
			break;
		cout << "Recieved message:\n" << buffer << endl;
		sem_post(sem);
		usleep(100);
	}while(true);
	sem_post(sem);
	return;
}

void parent(sem_t* sem, int fpipe){
	string message;
	bool con{true};
	cout << "Input message or \"q\" for exit:" << endl;
	while(con){
		getline(cin, message);
		if(!message.compare("q")){
			con = false;
			cout << "quit" << endl;
		}
		write(fpipe, message.c_str(), message.length()+1);
		sem_post(sem);
		usleep(100);
		sem_wait(sem);
	}
}

int main(){
	sem_t *sem;
	int c, flags;
	int filepipes[2];
	char message[256];

	if(pipe(filepipes)!=0){
		cerr << "Error while pipe()" << endl;
		exit(1);
	}

	sem_unlink("sem");
	flags = O_RDWR | O_CREAT | O_EXCL;
	sem = sem_open("/sem", flags, 0644, 1);
	cout << sem << endl;
	sem_wait(sem);

	pid_t pid;
	pid = fork();
	switch(pid){
		case -1:{
			cerr << "Error while fork" << endl;
			sem_close(sem);
			break;
		}
		case 0:{
			child(sem, filepipes[0]);
			exit(0);
		}
		default:{
			parent(sem, filepipes[1]);
		}
	}

	sem_unlink("/sem");
	return 0;
}