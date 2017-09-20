#ifndef __SENDER_H__
#define __SENDER_H__

#include<time.h>
#include<stdio.h>
#include<Windows.h>
#include "dataInfo.h"
#include"transmissionMedia.h"

void createSender();
void receiveACK(int nACKIndex);

#endif // !__SENDER_H__