#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
   pid_t pid2,pid3,pid4,pid5,pid6,pid7,pid8;
   pid2=fork();
   if(pid2==0)
   {
      printf("\nPID2:%d\nParent2:%d\n\n",getpid(),getppid());
      pid4=fork();
      if(pid4==0)
      {
	 printf("\nPID4:%d\nParent(4):%d\n\n",getpid(),getppid());
	 pid8=fork();
	 if(pid8==0)
	 {
	    wait(NULL);
	    printf("\nPID8:%d\nParent8:%d\n\n",getpid(),getppid());
	 }
	 else if(pid8>0)
	 {
	    wait(NULL);
	 }
      }
      else if(pid4>0)
      {
	 wait(NULL);
	 pid5=fork();
	 if(pid5==0)
	 {
	    printf("\nPID5:%d\nPPID5:%d\n\n",getpid(),getppid());
	 }
	 else if (pid5>0)
	 {
	    wait(NULL);
	 }

      }
   }
   else if(pid2>0)
   {
      pid3=fork();
      if (pid3==0)
      {
	 printf("\nPID3:%d\nPPID3:%d\n\n",getpid(),getppid());
	 pid7=fork();
	 if (pid7==0)
	 {
	    printf("\nPID7:%d\nPPID(7):%d\n\n",getpid(),getppid());
	 }
	 else if(pid7>0)
	 {
	    wait(NULL);
	    pid6=fork();
	    if (pid6==0)
	    {
	       printf("\nPID6:%d\nPPID6:%d\n\n",getpid(),getppid());
	    }
	    else if(pid6>0)
	    {
	       wait(NULL);
	    }
	 }
      }
      else if(pid3>0)
      {
	 wait(NULL);
	 printf("\nPID1:%d\n\n",getpid());
      }
   }
   return 0;
}
