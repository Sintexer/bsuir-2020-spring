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
#include <dlfcn.h>

using namespace std;

size_t bsize = 256;

typedef void *(*foo)(void* buffer);

int main() {
    pthread_t reader, writer;
    char* buffer=(char*)calloc(bsize, sizeof(char));
    void *handle = dlopen("/home/maindev/Документы/SPOVM/lab5/lab5Lib.so", RTLD_LAZY);

    if(!handle){	
    	cout << "Error while opening .so file" << endl;
    	return 1;
    }

    foo inThread = (foo)dlsym(handle, "inThread"),
    	outThread = (foo)dlsym(handle, "outThread");

    pthread_create(&reader, NULL, inThread, buffer);
    usleep(300);
    pthread_create(&writer,NULL, outThread, buffer);
    pthread_join(writer, NULL);

    dlclose(handle);
    delete[] buffer;
    return 0;    
}

