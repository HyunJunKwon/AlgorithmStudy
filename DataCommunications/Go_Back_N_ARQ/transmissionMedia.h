#ifndef __TRANSMISSION_MEDIA_H__
#define __TRANSMISSION_MEDIA_H__

#include"sender.h"
#include"receiver.h"
#include"dataInfo.h"

void sendDataByGoBackN(frame data);
void sendAckByGoBackN(int nAckIndex);

#endif // !__TRANSMISSION_MEDIA_H__