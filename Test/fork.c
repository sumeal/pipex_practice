#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	pid = 9;
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("Hello, I am main process (before fork). My PID is %d\n", getpid());

	pid = fork();
	printf("------------------------------------\n");
	printf("Hello, I am main process (after fork). My PID is %d\n", getpid());
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		printf("Hello, I am the child process. My PID is %d, and my child's PID is %d\n", getpid(), pid);
	}
	else
	{
		printf("Hello, I am the parent process. My PID is %d, and my child's PID is %d\n", getpid(), pid);
	}
	return (0);
}