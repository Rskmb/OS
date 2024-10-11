#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define MAXSIZE 27

void die(char *s)
{
perror(s);
exit(1);
}



int main() {
 char c;
 int shmid;
 
 key_t key;
 
 char *s,*shm;
 key=5678;
 
 if((shmid= shmget(key,MAXSIZE,IPC_CREAT | 0666))< 0)
     die("shmget");
 if((shm=shmat(shmid,NULL,0))== (char *) -1)
     die("shmat");
     
 s=shm;
 
 for(c='a';c<='z';c++)
     putchar(*s);
     putchar("\n");
     
     
*shm = '*';
 
 
   exit(0);
}
