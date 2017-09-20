/*-------------------------------------------------------------------------------------------------------
Operating Systems Assingnment
2014315327_권현준_Project2
Copyright (c) SungKyunKwan University
Author			      : Kwon Hyun Jun

Initial Creation      : MON, OCTOBER, 3, 2016

Description           : MFQ_Scheduling 기법을 구현한 프로그램입니다.
--------------------------------------------------------------------------------------------------------*/

// Header files inclusion
#include <stdio.h>
#include <stdlib.h>

// Constant declare
#define MAX_SIZE 30 // Array의 최대 크기 지정 (전역 변수 설정위해) [가정: process는 30개 이하로 설정, 그 이상 입력 원할 시, MAX_SIZE 증가]

// Struct definition
typedef struct 
{
	int Burst_Time;
	int Arrival_Time;
	int Process_ID;
	int Turnaround_Time;
	int Waiting_Time;
	int Flag;
	int Execution_Time;
}PROCESS; // Process의 특성들을 구조체로 표현

// Global variables declare 
//(struct variables declare)
PROCESS * RQ_0 = NULL;
/*
구조체 배열을 함수 내에서 선언 시, static scope 문제로 인해 초기화 되는 경우를 보여
간단한 구현을 위해 전역변수로서 선언하였습니다.
*/
PROCESS RQ_1[MAX_SIZE];
PROCESS RQ_2[MAX_SIZE];
PROCESS RQ_3[MAX_SIZE];

// Function declare
void MFQ_Scheduling();
void GanttChartAndResult(int * process_counts, int total_time);
void FindTurnaroundTime(int * process_count, int * TTarr);

void main(void)
{
	MFQ_Scheduling();
	return 0;
}

// Functions definition
void MFQ_Scheduling()
{
	// Local variables declare
	int temp = 0;
	int k = 0;
	int count = 0;
	int process_counts = 0;;
	int total_time = 0;
	int i = 0;
	FILE * file = NULL;

	// Statement
	file  = fopen("input.txt", "r");
	fscanf(file, "%d", &process_counts);

	RQ_0 = (PROCESS *)malloc(sizeof(PROCESS) * process_counts);
	temp = process_counts;
	while (temp-- > 0)
	{

		fscanf(file, "%d %d %d", &RQ_0[i].Process_ID, &RQ_0[i].Arrival_Time, &RQ_0[i].Burst_Time);
		RQ_0[i].Flag = 0;
		RQ_0[i].Execution_Time = 0;
		i++;
	} // Process정보를 Process 배열에 동적할당을 이용하여 저장
	for (i = 0; i < process_counts; i++)
		total_time += RQ_0[i].Burst_Time; // 총 실행 시간등 RQ_0의 정보를 미리 저장 
		
	for (k = 0; k < process_counts; k++)
	{
		for (i = 0; i < process_counts; i++)
		{
			if (RQ_0[i].Burst_Time > 0 && RQ_0[i].Flag == 0)	//  처음 process들이 q0오는걸 가정
			{
				if ((RQ_0[i].Burst_Time - 2) > 0) // Queue 0의 time quntum이 2초인데, burst time이 그것보다 작을 경우.
				{
					RQ_1[i].Burst_Time = (RQ_0[i].Burst_Time - 2); // ROUND ROBIN Time Quntum = 2
					RQ_1[i].Flag = 1; // Queue 1로 옮기기 위한 flag
					RQ_1[i].Execution_Time = 2; // 실행 시간
					RQ_1[i].Process_ID = RQ_0[i].Process_ID; // Queue 1로 preemption. RQ_1안에 있는 정보들은 preemption 후 모습이다
					RQ_0[i].Flag = 1;
				}
				else
				{
					RQ_1[i].Execution_Time = RQ_0[i].Burst_Time;
					RQ_1[i].Burst_Time = 0;
					RQ_1[i].Flag = 1;
					RQ_1[i].Process_ID = RQ_0[i].Process_ID;
					RQ_0[i].Flag = 1;
				}

			}
			// 이후 정보는 RQ_1에 저장
			
			else if (RQ_1[i].Burst_Time > 0 && RQ_1[i].Flag == 1) // Queue 1에서의 모습
			{
				if ((RQ_1[i].Burst_Time - 4) > 0) // Round Robin Time Quntum = 4
				{
					RQ_2[i].Burst_Time = RQ_1[i].Burst_Time - 4;
					RQ_2[i].Flag = 2;
					RQ_2[i].Execution_Time = 4;
					RQ_2[i].Process_ID = RQ_1[i].Process_ID;
					RQ_1[i].Flag = 2;
				}
				else
				{
					RQ_2[i].Execution_Time = RQ_1[i].Burst_Time;
					RQ_2[i].Burst_Time = 0;
					RQ_2[i].Flag = 2;
					RQ_2[i].Process_ID = RQ_1[i].Process_ID;
					RQ_1[i].Flag = 2;
				}
			}
			// 이후 정보는 RQ_2에 저장

			else if (RQ_2[i].Burst_Time >= 0 && RQ_2[i].Flag == 2) // Queue 2 FCFS
			{
				RQ_3[i].Process_ID = RQ_2[i].Process_ID;
				RQ_3[i].Execution_Time = RQ_2[i].Burst_Time; // Time Quntum이 무제한 이므로
				RQ_3[i].Burst_Time = 0;
				RQ_3[i].Flag = 3;
				RQ_2[i].Flag = 3;
				
			}
			// 이후 정보는 RQ_3에 저장
		}
	}

	GanttChartAndResult(&process_counts, total_time);

}
void FindTurnaroundTime(int * process_counts, int * TTarr)
{
	// Local variables declare
	int i = 0;
	int j = 0;
	int k = 0;
	int arr[3000] = { 0, }; // 모든 Queue 에서 실행 시간에 따른 process_ID를 저장할 배열
	int TTarr1[100] = { 0, };
	int TTarr2[100] = { 0, };
	int TTarr3[1000] = { 0, };
	int flag = 0;

	// Statements
	for (i; i < *(process_counts); i++)
		*(TTarr + i) = 0; // Initializing 안그러면 쓰레기값이 저장되므로

	// TTarr1, TTarr2, TTarr3을 각각의 스케줄링 기법의 결과물이라 가정 
	for (i = 0; i < *(process_counts); i++)
	{
		for (j = 0; j < RQ_1[i].Execution_Time; j++)
			TTarr1[k++] = RQ_1[i].Process_ID;
	}
	k = 0;
	for (i = 0; i < *(process_counts); i++)
	{
		for (j = 0; j < RQ_2[i].Execution_Time; j++)
			TTarr2[k++] = RQ_2[i].Process_ID;
	}
	k = 0;
	for (i = 0; i < *(process_counts); i++)
	{
		for (j = 0; j < RQ_3[i].Execution_Time; j++)
			TTarr3[k++] = RQ_2[i].Process_ID;
	}

	// 
	i = 0;
	while (TTarr1[i] != 0)
	{
		arr[i] = TTarr1[i];
		i++;
	}
	j = 0;
	while (TTarr2[j] != 0)
	{
		arr[i] = TTarr2[j];
		i++;
		j++;
	}
	k = 0;
	while (TTarr3[k] != 0)
	{
		arr[i] = TTarr3[k];
		i++;
		k++;
	} // arr 배열에 gantt chart의 process_ID를 순서대로 저장

	i = 0;
	for (j = 0; j < *(process_counts); j++)
	{
		while (arr[i] != 0)
		{
			if (arr[i] == (j + 1))
			{
				*(TTarr + j) = i + 1; // turnaround time 저장 밑 갱신
				RQ_0[j].Turnaround_Time = *(TTarr + j);
				i++;
			}
			else
				i++;
		}
		i = 0;
	}
}
void GanttChartAndResult(int * process_counts, int total_time)
{
	// Local variables declare
	int i = 0;
	int j = 0;
	double total_tt = 0; 
	double total_wt = 0; // 총 turnaround time 과 waiting time을 구하기 위한 변수
	int * TTarr; // 각 process의 turnaround time을 저장하기 위한 배열 포인터
	int * TTarr1;
	int * TTarr2;

	// Statements
	printf("====================================The Result===========================================\n\n");
	printf("1. GANTT CHART\n\n");
	printf("| | <- 왼 쪽의 한 칸은 1초를 의미합니다!\n");

	for (i = 0; i < *(process_counts); i++)
	{
		for (j = 0; j < RQ_1[i].Execution_Time; j++)
			printf("|P%d|", (RQ_1[i].Process_ID));
	}
	for (i = 0; i < *(process_counts); i++)
	{
		for (j = 0; j < RQ_2[i].Execution_Time; j++)
			printf("|P%d|", (RQ_2[i].Process_ID ));
	}
	for (i = 0; i < *(process_counts); i++)
	{
		for (j = 0; j < RQ_3[i].Execution_Time; j++)
			printf("|P%d|", (RQ_3[i].Process_ID));
	}
	
	printf("\n\n2. 총 실행 시간: %d 초\n\n\n", total_time);
	TTarr = (int *)malloc(sizeof(int) * *(process_counts)); // Turnaround time을 저장할 배열, 100초 미만으로 모든 스케줄링이 종료된다고 가정
	
	printf("3. 각 프로세스 분석\n\n");
	FindTurnaroundTime(process_counts, TTarr, RQ_0); // turnaround time 분석
	
	for (i = 0; i < *(process_counts); i++) // 출력
	{
		RQ_0[i].Waiting_Time = *(TTarr + i) - RQ_0[i].Burst_Time;
		total_tt += *(TTarr + i);
		total_wt += RQ_0[i].Waiting_Time;
		printf("|PID|	|AT|	|BT|	|TT|	|WT|\n");
		printf("%d	%d	%d	%d	%d\n", RQ_0[i].Process_ID, RQ_0[i].Arrival_Time, RQ_0[i].Burst_Time, *(TTarr + i), RQ_0[i].Waiting_Time);
	}
	printf("\n\n4. 전체 프로세스의 평균 TT: %.2f\n\n", (total_tt / *(process_counts)));
	printf("5. 전체 프로세스의 평균 WT: %.2f\n\n", (total_wt / *(process_counts)));

	free(TTarr);
}




