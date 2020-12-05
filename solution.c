#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <string.h> 
#include <stdlib.h> 
#include <sys/wait.h> 



int fibo(int n){
 if(n<0) {return 0;}
 if(n==0){return 0;}
 if(n==1){return 1;}
 if(n==2){return 1;}
 if(n>2) {return fibo(n-2)+fibo(n-1);}
 
}


int main(int argc, char *argv[]){
 
 int n;
 int pid; // process Id(it can be type int or pid_t)
 int childpid;//child process Id
 int fd[2];
 int fn,sumfn;
 
 pipe(fd); //create pipe for fd

 if((childpid=fork())== -1) {
     perror("Error: Fork");
     exit(1);               }// if finished for fork() error

 else if(childpid==0) {
     childpid=getpid();
     int sizen =sizeof(n);
     read(fd[0],&n,sizen);
     close(fd[0]); 

     int finalnumber=0;
     int fsum=0;
     int i=0;
     while (i <= n) {
          fsum+=fibo(i);
          i++; 
                     } //while finished
	 
    finalnumber=fibo(n);
    wait(&childpid); ///<sys/wait.h> 
     int sizefinalnum =sizeof(finalnumber);
     int sizefsum =sizeof(fsum);
     write(fd[1],&finalnumber,sizefinalnum);
     write(fd[1],&fsum,sizefsum);
     close(fd[1]);  
   
     } //else if finished

 else {
     
      
      childpid = getpid();
      scanf("%d",&n);
      int sizen =sizeof(n);
      int sizefn =sizeof(fn);
      int sizesumfn =sizeof(sumfn);
      write(fd[1],&n,sizen); 
      close(fd[1]); 

      wait(&childpid); //<sys/wait.h> 

      read(fd[0], &fn, sizefn);
      read(fd[0], &sumfn, sizesumfn);
      close(fd[0]);
      
      printf("_________________\n");
      printf("|n:\t   %d\t|\n",n);			
      printf("|fn(%d):    %d\t|\n",n,fn);
      printf("|SumFn(%d): %d\t|\n",n,sumfn);
      printf("|_______________|\n");
                                    
      }// else finished    



return 0;
}// main funtion finished






