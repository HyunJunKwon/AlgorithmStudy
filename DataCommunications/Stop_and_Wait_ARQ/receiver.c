#include"receiver.h"

int nACKIndex;
int nCount;

void receiveData(frame data);
void receiveNormalData(frame *data);
ErrorMode checkData();

void createReceiver() {
	srand(time(NULL));
}

void receiveData(frame data) {

	switch (checkData()) {
	case normal:
		receiveNormalData(&data);
		break;
	case transmissionError:
		printf("%d data is loss\n", data.header);
		break;
	case dataError:
		printf("%d data is corrupted\n", data.header);
		Sleep(RECEIVER_INTERVAL);
		sendAckStopAndWait(nACKIndex);
		break;
	}
}

void receiveNormalData(frame *data) {
	printf("%-10s %d\n", "Receive : ", data->header);
	if (data->header != nACKIndex) {
		printf("%-10s %d data isn't accepted, we are waiting %d data\n", "Receive : ", data->header, nACKIndex);
	}
	else {
		nCount++;
		printf("%-10s %lld Byte\n", "Receive : ", (long long)nCount * sizeof(frame));
		nACKIndex = ++nACKIndex % WINDOW_SIZE;
	}
	Sleep(RECEIVER_INTERVAL);
	sendAckStopAndWait(nACKIndex);
}

ErrorMode checkData() {
	int num = rand() % 100;
	if (num < ERROR_RATIO) {
		num = rand() % 100;
		return (num > 50) ? transmissionError : dataError;
	}

	return normal;
}
