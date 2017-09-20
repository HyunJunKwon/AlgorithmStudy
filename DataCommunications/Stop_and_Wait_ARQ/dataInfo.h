
#ifndef _DATA_INFO_H
#define _DATA_INFO_H

//Common
#define TRUE 1
#define FALSE 0
#define TOTAL_RUN_TIME 60 * 1000

//transmission error ratio
#define ERROR_RATIO 50

//receiver
#define RECEIVER_INTERVAL 1000

//sender
#define WINDOW_SIZE 5
#define DATA_SIZE 100
#define TIME_OUT 2300
#define SEND_INTERVAL 1000

typedef enum _errorMode{
	normal = 0,
	transmissionError,
	dataError
}ErrorMode;

typedef struct _frame {
	int header; 
	int pData[DATA_SIZE - 1];
}frame;

#endif // _DATA_INFO_H

