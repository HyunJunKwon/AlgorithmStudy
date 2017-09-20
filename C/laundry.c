#include "KWON.h"

void Add_Or_Sub_Product(CUSTOMER * head, int day, int year, int mon)
{
	// Local variables declare
	char phonenumber[100 + 4] = { 0 };
	char txt[] = ".txt";
	int find = 0;
	CUSTOMER * temp = head;
	char c = "";
	int i = 0;
	char laundryaddordel = "";
	char k = "";

	// Statements
	system("cls");

	printf("휴대폰 번호를 입력하세요 ex) 00011112222\n");
	Cursor(0, 4);
	while (temp != NULL)
	{
		printf("%s\t", temp->name);
		printf("%s\t", temp->phone);
		printf("%s\t", temp->address);
		printf("%s\t", temp->mail);
		printf("%s\n", temp->idnumber);
		temp = temp->next;
	}

	Cursor(0, 2);
	scanf("%s", phonenumber);

	temp = head;


	while (temp != NULL) // Searching customer
	{
		if (strcmp(phonenumber, temp->phone) == 0)
		{
			find = 1;
			break;
		}
		temp = temp->next;
	}

	if (find == 0)
	{
		system("cls");
		printf("손님정보를 찾을수 없습니다 \n");

		while (1)
		{
			fflush(stdin);
			scanf("%c", &c);
			if (c == '\n')
				break;
		}
		return;
	}
	else
	{
		system("cls");

		printf("-------------맡긴 세탁물-------------\n\n");
		printf("종류\t맡긴 날짜\t찾아갈 날짜 \n\n");

		for (i = 0; i < temp->laundrynumber; i++)
		{
			printf("%s\t%d\t%d", temp->mylaundry[i]->type, temp->mylaundry[i]->start_day, temp->mylaundry[i]->end_day);

			if (i == (temp->laundrynumber) - 1)
			{
				i++;
				break;
			}
			printf("\n");
		}

		printf("\n\n--------------------------------------\n");

		printf("추가하시려면 1을 삭제하시려면 2를 눌러주세요.");
		laundryaddordel = getch();

		if (laundryaddordel == '1')
		{
			free(temp->mylaundry);
			Add_Laundry(temp, day, year, mon);
		}
		else
			Del_Laundry(head);

		system("cls");
		getchar();
		printf("금액을 지불하셨습니까? Y/N   ");
		scanf_s("%c", &k);
		if (k == 'Y')
			temp->unpaidbalance = 0;
	}
	return;
}
void Add_Laundry(CUSTOMER * temp, int day, int year, int mon)
{
	// Local variables declare
	char phone[16] = { 0 };
	char arr[100];
	char li;
	FILE * load;
	int line = 0;
	int i;
	char type[100];

	// Statements
	strcpy(phone, temp->phone);
	strcat(phone, ".txt");

	load = fopen(phone, "a");
	if (load == NULL)
	{
		return;
	}
	system("cls");
	printf("추가할 옷의 종류를 입력해주세요\n\n");
	printf("와이셔츠, 러닝셔츠, 청바지, 면바지, 패딩, 코트\n\n [          ]\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%s", type);
	fprintf(load, "\n%s\t%d%0.2d%0.2d\t%d%0.2d%0.2d", type, year, mon, day, year, mon, day + 3);
	temp->unpaidbalance = temp->unpaidbalance + 3000; // Recalulate unpaidbalance

	fclose(load);
	load = fopen(phone, "r");

	while ((li = fgetc(load)) != EOF)
	{
		if (li == '\n')
		{
			line++;
		}
	}
	line = line + 2;
	temp->laundrynumber = line - 1;
	temp->mylaundry = (LAUNDRY**)malloc(sizeof(LAUNDRY)*(line));


	fseek(load, 0, SEEK_SET);
	for (i = 0; i<line; i++) // Renew information
	{
		temp->mylaundry[i] = (LAUNDRY*)malloc(sizeof(LAUNDRY));
		temp->mylaundry[i]->name = temp;
		fscanf(load, "%s", temp->mylaundry[i]->type);
		fscanf(load, "%d", &temp->mylaundry[i]->start_day);
		fscanf(load, "%d", &temp->mylaundry[i]->end_day);
	}

	fclose(load);
}
void Del_Laundry(CUSTOMER * temp)
{
	// Local variables declare
	int i;
	int c;
	int a = 0;
	LAUNDRY ** laundry;
	int line = 0;

	// Statements
	system("cls");

	printf("삭제할 세탁물의 번호를 입력해주세요.\n");
	for (i = 0; i < temp->laundrynumber; i++)
	{
		printf("[%d] ", i);
		printf("%s\t\n", temp->mylaundry[i]->type);
	} // Print all laundry 
	Cursor(45, 0);
	printf("[ ]\b\b");
	scanf("%d", &c);

	temp->mylaundry[i] = NULL;
	temp->laundrynumber = temp->laundrynumber - 1;
	laundry = (LAUNDRY**)malloc(sizeof(LAUNDRY)*(temp->laundrynumber)); // Allocate laundry

	for (i = 0; i< temp->laundrynumber; i++)
	{
		if (temp->mylaundry[i] != NULL)
		{
			laundry[i] = (LAUNDRY*)malloc(sizeof(LAUNDRY));

		}
	}

	for (i = 0; i< temp->laundrynumber + 1; i++)
	{
		if (i != c)
		{
			strcpy(laundry[a]->type, temp->mylaundry[i]->type);
			laundry[a]->start_day = temp->mylaundry[i]->start_day;
			laundry[a]->end_day = temp->mylaundry[i]->end_day;
			a++;
		}
	}

	free(temp->mylaundry);
	temp->mylaundry = laundry;
	return;
}