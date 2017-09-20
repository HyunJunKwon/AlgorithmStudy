#ifndef __TRANSMISSION_MEDIA_H__
#define __TRANSMISSION_MEDIA_H__

#include"sender.h"
#include"receiver.h"
#include"dataInfo.h"

void sendDataStopAndWait(frame data);
void sendAckStopAndWait(int nAckIndex);

#endif // !__TRANSMISSION_MEDIA_H__