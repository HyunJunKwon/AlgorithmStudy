#pragma once
/*-------------------------------------------------------------------------------------------------------
gleentopia
Copyright (c) SungKyunKwan University
Author			      : Kwon Hyun Jun

Initial Creation      : Wed, MAY, 18, 2016

Description           : ��Ź�ҿ��� �մ��� �����ϴ� ���α׷��Դϴ�. ����ڴ� �մ��� ���� (�̸�, �޴���ȭ
��ȣ, �ּ�, ����, �������)�� �޾� �����ϸ� �մ��� ���� �Ǵ� �߰� �� �� �ֽ��ϴ�. ���� �մ� ��������
��Ź�� ������ �� �� ������ �׿� ���� û�������� ������ �� �ֽ��ϴ�.
--------------------------------------------------------------------------------------------------------*/
// Header files inclusion
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>

// Define constants
#define UP      72
#define DOWN    80
#define LEFT    75
#define RIGHT   77
#define ENTER   13
#define ESC		27

// Define structure
typedef struct _LAUNDRY
{
	char type[100];
	int start_day;
	int end_day;
	struct _CUSTOMER * name;
}LAUNDRY;
typedef struct _CUSTOMER
{
	char name[100];
	char phone[100];
	char address[100];
	char mail[100];
	int unpaidbalance; // �̳���
	int gender;
	char idnumber[100];
	int laundrynumber;
	struct _CUSTOMER * prev;
	struct _CUSTOMER * next;
	LAUNDRY ** mylaundry; // Array that store LUNDRY address value
}CUSTOMER;

// Functions declare
int Start_Menu(void); // Deciding menu
CUSTOMER * Load_Info(CUSTOMER * head); // Read customer information
void Insert(CUSTOMER * x, CUSTOMER * y); // Copy structures
int Get_Menu_From_Cursor(void); // Select menu from cursor
void Add_Customer(CUSTOMER * head);
void Del_Customer(CUSTOMER* head);
void LoadAboutLaundry(CUSTOMER * temp);
void Add_Or_Sub_Product(CUSTOMER * temp, int day, int year, int mon);
void Blacklist(CUSTOMER * head); // Search top 5 about unpaidbalance
void Print_To_File(CUSTOMER * temp);
void Free_All(CUSTOMER * temp);
void Add_Laundry(CUSTOMER * temp, int day, int year, int mon);
void Del_Laundry(CUSTOMER * temp);
void Cursor(int x, int y); // Cursor
int Show_Time(int * day, int * year, int * mon); // Show present time