#include"transmissionMedia.h"

void sendDataByGoBackN(frame data) {
	receiveData(data);
}

void sendAckByGoBackN(int nAckIndex) {
	receiveACK(nAckIndex);
}