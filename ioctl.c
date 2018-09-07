#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include"ioctl.h"
#include<sys/ioctl.h>
int main()
{
	int choice;
	int fd;
	fd = open("/home/anmolzehra/Projects/drivers/Testdriver_ioctl/Mydev",O_WRONLY);
	if(!fd)
	{
		perror("File descriptor couldn't be assigned\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("fd = %d\n",fd);
	printf("1 -> DEVRESET\n");
	printf("0 -> EXIT \n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: 
			printf("Choosing IOCTL\n");
			ioctl(fd,DEVRESET,1);
			break;
		case 0: 
			exit(EXIT_SUCCESS);
			
	}
}
