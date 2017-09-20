#include"sender.h"

frame senderQueue[WINDOW_SIZE];
int nStartDataIndex;
clock_t start, finish;

void runSender();
void createData(int count);
ErrorMode checkACK();

void createSender() {
	clock_t initStart = clock();
	createData(WINDOW_SIZE);
	while (TRUE) {
		
		start = clock();
		runSender();
		finish = clock();

		while (finish - start < TIME_OUT) {
			Sleep(SEND_INTERVAL);
			finish = clock();
		}

		if (finish - initStart > TOTAL_RUN_TIME)
			break;

		if (start == 0)
			continue;

		printf("-------------------TIME OUT---------------\n");
	}
}

void receiveACK(int nACKIndex) {
	switch (checkACK()) {
	case normal:
		printf("ACK : %d\n", nACKIndex);
		nStartDataIndex = nACKIndex;
		start = 0;
		break;
	case transmissionError:
		printf("ACK : %d is loss\n", nACKIndex);
		break;
	case dataError:
		printf("ACK : %d is corrupted\n", nACKIndex);
		break;
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
	printf("%-10s %d data \n", "SENDER : ", nStartDataIndex);
	sendDataStopAndWait(senderQueue[nStartDataIndex]);
	Sleep(SEND_INTERVAL);
}

ErrorMode checkACK() {
	int num = rand() % 100;
	if (num < ERROR_RATIO) {
		num = rand() % 100;
		return (num > 50) ? transmissionError : dataError;
	}

	return normal;
}