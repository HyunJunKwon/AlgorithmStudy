#include"receiver.h"

HANDLE hPushThread;
unsigned pushThreadID;
FrameQueue *queueFrontPtr;
FrameQueue *queueTailPtr;
int nACKIndex;
int nCount;

void runReceiver();
unsigned WINAPI threadReceiveData(void *para);
void receiveNormalData(frame *data);
int checkData();
void inQueue(frame data);
frame *deQueue();


void createReceiver() {
	srand(time(NULL));
	runReceiver();
}

void receiveData(frame data) {
	if (!checkData()) {
		printf("%d data is error\n", data.header);
	}
	else {
		inQueue(data);
	}
}

void runReceiver() {
	hPushThread = (HANDLE)_beginthreadex(NULL, 0, threadReceiveData, 0, 0, &pushThreadID);
	if (hPushThread == NULL) {
		puts("fail creating sender\n");
		exit(1);
	}
}

unsigned WINAPI threadReceiveData(void *para) {
	while (TRUE) {
		Sleep(RECEIVER_INTERVAL);
		frame *data = deQueue();
		if (data == NULL) {
			
			continue;
		}

		receiveNormalData(data);

		free(data);
	}
}

void receiveNormalData(frame *data) {
	printf("%-10s %d\n", "Receive : ", data->header);
	if (data->header != nACKIndex){
		printf("%-10s %d data isn't accepted, we are waiting %d data\n", "Receive : ", data->header, nACKIndex);
		return;
	}

	nCount++;
	
	printf("%-10s %lld Byte\n","Receive : ", (long long)nCount * sizeof(frame));
	nACKIndex = ++nACKIndex % WINDOW_SIZE;
	sendAckByGoBackN(nACKIndex);
}

int checkData() {
	int num = rand() % 100;
	if (num < ERROR_RATIO)
		return FALSE;
	
	return TRUE;
}


void inQueue(frame data) {
	
	FrameQueue *temp = (FrameQueue *)malloc(sizeof(FrameQueue));
	memset(temp, 0, sizeof(FrameQueue));
	temp->data = (frame *)malloc(sizeof(frame));
	memset(temp->data, 0, sizeof(frame));
	memcpy(temp->data, &data, sizeof(frame));

	if (queueFrontPtr == NULL) {
		queueFrontPtr = temp;
		queueTailPtr = temp;
	}
	else {
		temp->next = queueTailPtr;
		queueTailPtr->pre = temp;
		queueTailPtr = temp;
	}
}

frame *deQueue() {
	if (queueFrontPtr == NULL)
		return NULL;

	FrameQueue *temp = queueFrontPtr;
	queueFrontPtr = queueFrontPtr->pre;

	frame *data = (frame *)malloc(sizeof(frame));
	memset(data, 0, sizeof(frame));
	memcpy(data, temp->data, sizeof(frame));
	free(temp);

	return data;
}