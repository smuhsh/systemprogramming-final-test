/*msg1-receiver3.c*/
/* use program parameter to indicate the msg type*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define BUFF_SIZE 1024

typedef struct {
	long data_type;
	int data_num;
	char data_buff[BUFF_SIZE];
}msg_t;

int main(int argc, char *argv[]){
	int msqid;
	int i;
	msg_t data;
	struct msqid_ds msqstat;

	if(argc < 2){
		perror("parameter is required");
		exit(1);
	}

	if(-1 == (msqid == msgget((key_t)1223334444, IPC_CREAT | 0666))){
		perror("msgget() error");
		exit(1);
	}
	if(-1 == msgctl(msqid , IPC_STAT, &msqstat)){
		perror("msgctl() eror");
		exit(1);
	}
	printf("# of msg in the queue: %ld\n", msqstat.msg_qnum);

	for(i = 0; i < msqstat.msg_qnum; i++){
		// get the messages according to argv[1]
		if (-1 == msgrcv(msqid, &data, sizeof(msg_t) - sizeof(long),atoi(argv[1]), 0)){
			perror("msgrcv() error");
			exit(1);
		}
		printf("%d - %s\n", data.data_num, data.data_buff);
	}
	return(0);
}
