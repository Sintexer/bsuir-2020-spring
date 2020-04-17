#include <iostream>
#include <cstring>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>	
#include <pthread.h>
#include <vector>

using namespace std;

pthread_mutex_t mt;

int to_close;
int to_join;
vector<int> indexes;	

void* threadFunc(void* param){
	//int num = 1;
	int num = *(int*)param;
	indexes.push_back(num);
	string info = "Thread " + to_string(num);
	*(int*)param+=1;
	while(true){
		if(num!=indexes[to_join])
			continue;
		pthread_mutex_lock(&mt);
		for(char c: info){
			cout << c;
			usleep(30000);
		}
		cout<<endl;
		++to_join;
		if(to_join>=indexes.size())
			to_join = 0;
		//usleep(90000);
		pthread_mutex_unlock(&mt);
	}
	pthread_exit(0);
}


int main(){
	vector<pthread_t> pt;
	pthread_mutex_init(&mt, NULL);

	cout << "Input +, - or q" << endl;
	to_close = -1;
	int num = 0;
	char c;		
	while(true){
		cin.get(c);
		switch(c){
			case '+':{
				pthread_t temp;
				pthread_create(&temp, NULL, threadFunc, &num);
				pt.push_back(temp);
				sleep(1);
				break;
			}
			case '-':{
				if(!pt.empty()){
					to_close = pt.size()-1;
					pthread_cancel(pt.back());
					pt.pop_back();	
					indexes.pop_back();
				}
				else {
					cout << "No more threads left" << endl;
				}
				break;
			}
			case 'q':{
				while(!pt.empty()){
					to_close = pt.size()-1;
					pthread_cancel(pt.back());
					pt.pop_back();	
					indexes.pop_back();
				}
				exit(0);
			}
			default:{
				cin.ignore(32768, '\n');
				cin.clear();
				cout << "Input +, - or q" << endl;
				continue;
			}

		}

		cin.ignore(32768, '\n');
		cin.clear();
	}


	return 0;
}