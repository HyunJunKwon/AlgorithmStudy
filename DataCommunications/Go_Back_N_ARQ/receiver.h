#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include<process.h>
#include<Windows.h>
#include<time.h>
#include<stdio.h>
#include"dataInfo.h"
#include"transmissionMedia.h"

void createReceiver();
void receiveData(frame data);

#endif // !__RECEIVER_H__
