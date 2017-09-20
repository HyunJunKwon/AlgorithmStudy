#include"transmissionMedia.h"

void sendDataStopAndWait(frame data) {
	receiveData(data);
}

void sendAckStopAndWait(int nAckIndex) {
	receiveACK(nAckIndex);
}