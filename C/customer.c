#include "KWON.h"

void Add_Customer(CUSTOMER * head)
{
	// Local variables declare
	CUSTOMER * temp;
	CUSTOMER * newcustomer;
	int cmp;

	if ((newcustomer = (CUSTOMER*)malloc(sizeof(CUSTOMER))) == NULL)
	{
		printf("Memory assignment error!");
		exit(101);
	}

	system("cls");
	// Store nwe customer's information temporarily in newcustomer
	printf("�̸��� �Է��ϼ���");
	scanf("%s", newcustomer->name);
	printf("�ڵ��� ��ȣ�� �Է��ϼ���");
	scanf("%s", newcustomer->phone);
	printf("�ּҸ� �Է��ϼ���");
	scanf("%s", newcustomer->address);
	printf("�̸��� �ּҸ� �Է��ϼ���");
	scanf("%s", newcustomer->mail);
	printf("���� �� �Է��ϼ��� (���� 1, ���� 2)");
	scanf("%d", &newcustomer->gender);
	printf("�ֹι�ȣ�� �Է��ϼ���");
	scanf("%s", newcustomer->idnumber);

	temp = head; // As Temp = head, start from head

	while (1)
	{
		cmp = strcmp(temp->name, newcustomer->name);
		if (cmp >= 0) // If temp' name is longer than new's name
		{
			if (temp->prev == NULL) // When temp goes to last order, newcustomer's information is stored
			{
				newcustomer->prev = NULL;
				newcustomer->next = temp;
				head = newcustomer;

				return;
			}
			newcustomer->prev = temp->prev;
			temp->prev->next = newcustomer;
			temp->prev = newcustomer;
			newcustomer->next = temp;

			return;
		}
		else {
			if (temp->next == NULL)	// If there are no data to compare
			{
				temp->next = newcustomer;
				newcustomer->prev = temp;
				newcustomer->next = NULL;
				return;
			}

			temp = temp->next; // Using temp->next pointer, keep moving and searching
		}
	}
}
void Del_Customer(CUSTOMER * head)
{
	// Local variables declare
	CUSTOMER * temp;
	char tempphone[12] = { 0 };

	// Statements
	temp = head;
	system("cls");
	printf("������ ������ ȸ���� �ڵ�����ȣ�� �˷��ּ���\n"); // Because people's phone number is harder to be same than people's name
	scanf("%s", tempphone);

	while (1)
	{
		if ((strcmp(temp->phone, tempphone)) == 0)
		{
			printf("%s ȸ������ ������ �����մϴ�.\n", temp->name);
			if (temp != head)
			{	// Using linked list principle, swap present value of temp->next and temp->prev->next
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				free(temp); // Delete temp node
				temp = NULL;
				printf("ȸ�� ������ ���������� �����Ǿ����ϴ�.\n");
				return;
			}
			else
			{
				head = temp->next;
				head->prev = NULL;
				free(temp);
				return;
			}
		}
		else
		{
			if (temp->next == NULL)
			{
				printf("���Ͻô� ȸ���� ������ �������� �ʽ��ϴ�.");
				return;
			}
			temp = temp->next; // Keep linked list going temp->next
		}
	}
}
void Blacklist(CUSTOMER * head)
{
	// Local variables declare
	int count = 0;
	int tempmoney[5] = { 0, };
	char tempname[5][40] = { 0, }; // To store name temporarily
	CUSTOMER * temp;

	// Statements
	temp = head;
	system("cls");

	while (temp->next != NULL)
	{
		// Search highest unpaidbalance and name who has it storing tempmoney[0], tempname[0]
		if (temp->unpaidbalance >= tempmoney[count])
		{
			strcpy(tempname[count], temp->name);
			tempmoney[count] = temp->unpaidbalance;
		}
		temp = temp->next;
	}
	// And next, store decending order
	for (count = 1; count < 5; count++)
	{
		temp = head;
		while (temp != NULL)
		{
			if (temp->unpaidbalance >= tempmoney[count])
			{
				if (strcmp(tempname[0], temp->name) != 0 && strcmp(tempname[1], temp->name) != 0
					&& strcmp(tempname[2], temp->name) != 0 && strcmp(tempname[3], temp->name) != 0
					&& strcmp(tempname[4], temp->name) != 0)
				{	// Except same name, and decending order and if the unpaidbalance is same amount,
					// store it alphabetic and length order
					strcpy(tempname[count], temp->name);
					tempmoney[count] = temp->unpaidbalance;
				}

			}
			temp = temp->next;
		}
	}
	printf("\n �̳��� TOP 5\n");

	for (count = 0; count < 5; count++)
	{
		printf("[%d] %s�� : %d ��\n", count + 1, tempname[count], tempmoney[count]);
	}
	return;
}