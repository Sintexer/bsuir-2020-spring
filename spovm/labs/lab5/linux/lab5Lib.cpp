#include <iostream>
#include <pthread.h>
#include <vector>
#include <dirent.h>
#include <aio.h>
#include <signal.h>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

size_t bsize = 256;

pthread_mutex_t writeMut;
pthread_mutex_t delMut;

extern "C" void nullStr(char* str, int size){
	for(int i=0;i<size && str[i]!='\0';++i){
		str[i]={};
	}
}

extern "C" int getFileSize(string path){
    int size;
    fstream file(path);
    file.seekg(0,ios::end);
    size=file.tellg();
    file.close();
    return size;

}

extern "C" void inThread(void* buffer){
	pthread_mutex_init(&writeMut, NULL);
    pthread_mutex_init(&delMut, NULL);
	pthread_mutex_lock(&writeMut);
    pthread_mutex_lock(&delMut);
	std::vector<string> v;
	v.push_back("input1.txt");
	v.push_back("input2.txt");
	v.push_back("input3.txt");

    aiocb input;
    input.aio_offset=0;
    input.aio_buf=(char*)buffer;
    struct stat stat;                                                          
    int size;       
    while (!v.empty()){

    	cout << v.back().c_str() << endl;
    	int fd = open(v.back().c_str(),O_RDWR, S_IRUSR | S_IWUSR);
    	fstat(fd, &stat);                                                   
    	size = stat.st_size;  
    	cout << fd << "size" << size << endl;
        input.aio_fildes=fd;
        input.aio_nbytes = size;
        aio_read(&input);
        while (aio_error(&input))
	    {
	        puts("Wait for reading from file...");
			if(aio_error(&input)==EINVAL)
			{
				puts("\nFailure");
				getchar();
			}
	    	usleep(500000);
	    }
        close(fd);
        pthread_mutex_unlock(&writeMut);
        usleep(70000);
        pthread_mutex_lock(&writeMut);
        v.pop_back();
        if(!v.size())
        	pthread_mutex_unlock(&delMut);
        nullStr((char*)buffer, bsize);
        usleep(100000);
    }

    pthread_mutex_lock(&delMut);

    pthread_mutex_destroy(&writeMut);
    pthread_mutex_destroy(&delMut);
}

extern "C" void* outThread(void* buffer){
    int fd= open("output.txt", O_RDWR, S_IRUSR | S_IWUSR);
    int size;
    aiocb output;
    output.aio_offset=0;
    output.aio_buf=(char*)buffer;
    output.aio_fildes=fd;
    
    while (pthread_mutex_trylock(&delMut)){
    	pthread_mutex_lock(&writeMut);	
    	std::cout << "Start" << endl;
    	size = strlen((char*)buffer);
    	cout << size << endl;
        output.aio_nbytes= size;
        for(int i =0;i<strlen((char*)buffer);++i){
        	cout << (char*)buffer+i;
        }
        aio_write(&output);
        while (aio_error(&output) == EINPROGRESS)
	    {
	        puts("Wait for writing to the result file...");
	        usleep(500000);
			if(aio_error(&output)==EINVAL)
			{
				puts("nFailure");
				getchar();
			}
	    }
        output.aio_offset+=size;
        pthread_mutex_unlock(&writeMut);
        usleep(70000);
    }
    std::cout << "end" << endl;
    pthread_mutex_unlock(&delMut);
    close(fd);
     
}

