#include"sender.h"

frame senderQueue[WINDOW_SIZE];
int nStartDataIndex;

void runSender();
void createData(int count);
int checkACK();
int bInitTimer;
clock_t initStart, start, finish;
CRITICAL_SECTION g_cs;

void createSender() {
	InitializeCriticalSection(&g_cs);
	initStart = clock();
	createData(WINDOW_SIZE);
	while (TRUE) {
		start = clock();
		runSender();
		finish = clock();

		while (finish - start < TIME_OUT) {
			Sleep(SEND_INTERVAL);
			finish = clock();
		}

		
		printf("-------------------TIME OUT---------------\n");
	}
}

void receiveACK(int nACKIndex) {
	if (!checkACK()) {
		printf("ACK : %d is loss\n", nACKIndex);
	}
	else {
		printf("ACK : %d\n", nACKIndex);
		EnterCriticalSection(&g_cs);
		nStartDataIndex = nACKIndex;
		bInitTimer = TRUE;
		LeaveCriticalSection(&g_cs);
	}
}

void createData(int count) {
	for (int i = 0; i < count; i++) {
		frame newData;
		newData.header = i;
		senderQueue[i] = newData;
	}
}

void runSender() {
	EnterCriticalSection(&g_cs);
	int nStartIndex = nStartDataIndex;
	LeaveCriticalSection(&g_cs);
	for (int i = 0; i < WINDOW_SIZE; i++) {
		printf("%-10s %d data \n", "SENDER : ", nStartIndex);
		sendDataByGoBackN(senderQueue[nStartIndex]);
		nStartIndex = ++nStartIndex % WINDOW_SIZE;
		Sleep(SEND_INTERVAL);

		if (finish - initStart > TOTAL_RUN_TIME) {
			DeleteCriticalSection(&g_cs);
			exit(0);
		}

		EnterCriticalSection(&g_cs);
		if (bInitTimer) {
			bInitTimer = FALSE;
			i = 0;
			start = finish = clock();
		}
		LeaveCriticalSection(&g_cs);
	}
}

int checkACK() {
	int num = rand() % 100;
	if (num < ERROR_RATIO)
		return FALSE;

	return TRUE;
}