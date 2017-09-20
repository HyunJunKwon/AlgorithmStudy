/*-------------------------------------------------------------------------------------------------------
Operating Systems Assingnment
2014315327_������_Project2
Copyright (c) SungKyunKwan University
Author			      : Kwon Hyun Jun

Initial Creation      : MON, OCTOBER, 3, 2016

Description           : MFQ_Scheduling ����� ������ ���α׷��Դϴ�.
--------------------------------------------------------------------------------------------------------*/

// Header files inclusion
#include <stdio.h>
#include <stdlib.h>

// Constant declare
#define MAX_SIZE 30 // Array�� �ִ� ũ�� ���� (���� ���� ��������) [����: process�� 30�� ���Ϸ� ����, �� �̻� �Է� ���� ��, MAX_SIZE ����]

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
}PROCESS; // Process�� Ư������ ����ü�� ǥ��

// Global variables declare 
//(struct variables declare)
PROCESS * RQ_0 = NULL;
/*
����ü �迭�� �Լ� ������ ���� ��, static scope ������ ���� �ʱ�ȭ �Ǵ� ��츦 ����
������ ������ ���� ���������μ� �����Ͽ����ϴ�.
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
	} // Process������ Process �迭�� �����Ҵ��� �̿��Ͽ� ����
	for (i = 0; i < process_counts; i++)
		total_time += RQ_0[i].Burst_Time; // �� ���� �ð��� RQ_0�� ������ �̸� ���� 
		
	for (k = 0; k < process_counts; k++)
	{
		for (i = 0; i < process_counts; i++)
		{
			if (RQ_0[i].Burst_Time > 0 && RQ_0[i].Flag == 0)	//  ó�� process���� q0���°� ����
			{
				if ((RQ_0[i].Burst_Time - 2) > 0) // Queue 0�� time quntum�� 2���ε�, burst time�� �װͺ��� ���� ���.
				{
					RQ_1[i].Burst_Time = (RQ_0[i].Burst_Time - 2); // ROUND ROBIN Time Quntum = 2
					RQ_1[i].Flag = 1; // Queue 1�� �ű�� ���� flag
					RQ_1[i].Execution_Time = 2; // ���� �ð�
					RQ_1[i].Process_ID = RQ_0[i].Process_ID; // Queue 1�� preemption. RQ_1�ȿ� �ִ� �������� preemption �� ����̴�
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
			// ���� ������ RQ_1�� ����
			
			else if (RQ_1[i].Burst_Time > 0 && RQ_1[i].Flag == 1) // Queue 1������ ���
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
			// ���� ������ RQ_2�� ����

			else if (RQ_2[i].Burst_Time >= 0 && RQ_2[i].Flag == 2) // Queue 2 FCFS
			{
				RQ_3[i].Process_ID = RQ_2[i].Process_ID;
				RQ_3[i].Execution_Time = RQ_2[i].Burst_Time; // Time Quntum�� ������ �̹Ƿ�
				RQ_3[i].Burst_Time = 0;
				RQ_3[i].Flag = 3;
				RQ_2[i].Flag = 3;
				
			}
			// ���� ������ RQ_3�� ����
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
	int arr[3000] = { 0, }; // ��� Queue ���� ���� �ð��� ���� process_ID�� ������ �迭
	int TTarr1[100] = { 0, };
	int TTarr2[100] = { 0, };
	int TTarr3[1000] = { 0, };
	int flag = 0;

	// Statements
	for (i; i < *(process_counts); i++)
		*(TTarr + i) = 0; // Initializing �ȱ׷��� �����Ⱚ�� ����ǹǷ�

	// TTarr1, TTarr2, TTarr3�� ������ �����ٸ� ����� ������̶� ���� 
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
	} // arr �迭�� gantt chart�� process_ID�� ������� ����

	i = 0;
	for (j = 0; j < *(process_counts); j++)
	{
		while (arr[i] != 0)
		{
			if (arr[i] == (j + 1))
			{
				*(TTarr + j) = i + 1; // turnaround time ���� �� ����
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
	double total_wt = 0; // �� turnaround time �� waiting time�� ���ϱ� ���� ����
	int * TTarr; // �� process�� turnaround time�� �����ϱ� ���� �迭 ������
	int * TTarr1;
	int * TTarr2;

	// Statements
	printf("====================================The Result===========================================\n\n");
	printf("1. GANTT CHART\n\n");
	printf("| | <- �� ���� �� ĭ�� 1�ʸ� �ǹ��մϴ�!\n");

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
	
	printf("\n\n2. �� ���� �ð�: %d ��\n\n\n", total_time);
	TTarr = (int *)malloc(sizeof(int) * *(process_counts)); // Turnaround time�� ������ �迭, 100�� �̸����� ��� �����ٸ��� ����ȴٰ� ����
	
	printf("3. �� ���μ��� �м�\n\n");
	FindTurnaroundTime(process_counts, TTarr, RQ_0); // turnaround time �м�
	
	for (i = 0; i < *(process_counts); i++) // ���
	{
		RQ_0[i].Waiting_Time = *(TTarr + i) - RQ_0[i].Burst_Time;
		total_tt += *(TTarr + i);
		total_wt += RQ_0[i].Waiting_Time;
		printf("|PID|	|AT|	|BT|	|TT|	|WT|\n");
		printf("%d	%d	%d	%d	%d\n", RQ_0[i].Process_ID, RQ_0[i].Arrival_Time, RQ_0[i].Burst_Time, *(TTarr + i), RQ_0[i].Waiting_Time);
	}
	printf("\n\n4. ��ü ���μ����� ��� TT: %.2f\n\n", (total_tt / *(process_counts)));
	printf("5. ��ü ���μ����� ��� WT: %.2f\n\n", (total_wt / *(process_counts)));

	free(TTarr);
}




