#include "KWON.h"

void Cursor(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int Get_Menu_From_Cursor(void)
{
	// Local variables declare
	char c;
	char choice;
	int menu = 1;
	int x = 8, y = 4;
	FILE * customerfomat;

	// Statements
	system("cls");

	if (!(customerfomat = fopen("customerfomat.txt", "r")))
	{
		printf("Error");
		exit(101);
	}

	while (1) // Select menu
	{
		while ((c = fgetc(customerfomat)) != EOF)
			printf("%c", c);
		fseek(customerfomat, 0L, SEEK_SET);

		Cursor(x, y);
		printf("●");
		if (choice = getch())
		{
			switch (choice)
			{
			case UP:
				y = y - 1;
				menu = menu - 1;
				break;
			case DOWN:
				y = y + 1;
				menu = menu + 1;
				break;
			case ENTER:
				return menu;
			}
			system("cls");
		}
	}
	fclose(customerfomat);

	return menu;
}
void Print_To_File(CUSTOMER * temp)
{
	// Local variables declare
	char phonenum[100 + 4] = { 0, };
	char text[] = ".txt";
	FILE * customerfile;
	FILE * loundryfile;
	int i;

	// Statements
	customerfile = fopen("Customer.txt", "w");
	if (customerfile == NULL)
	{
		printf("\"Customer.txt\"파일 오픈 에러!\n");
		return;
	}
	while (temp != NULL)
	{
		fprintf(customerfile, "%s %s %s, %s %d %d %s\n", temp->name, temp->phone, temp->address, temp->mail, temp->unpaidbalance, temp->gender, temp->idnumber);

		for (i = 0; i < (100 + 4); i++) // Initialize phonenum array
			phonenum[i] = 0;

		strcpy(phonenum, temp->phone);
		strcat(phonenum, text);
		// Using phonenum array, create 
		loundryfile = fopen(phonenum, "w");

		if (loundryfile == NULL)
		{
			printf("\"%s\"파일 오픈 에러\n", phonenum);
			return;
		}

		for (i = 0; i < temp->laundrynumber; i++)
		{
			fprintf(loundryfile, "%s %d %d", temp->mylaundry[i]->type, temp->mylaundry[i]->start_day, temp->mylaundry[i]->end_day);

			if (i == ((temp->laundrynumber) - 1))
			{
				i++;
				break;
			}
			fprintf(loundryfile, "\n");
		}

		fclose(loundryfile);

		temp = temp->next;
	}

	fclose(customerfile);

	return;
}
void Free_All(CUSTOMER * temp)
{
	// Local variables declare
	int i;
	CUSTOMER* temp2 = temp;

	// Statements
	while (temp2 != NULL)
	{
		temp2 = temp->next;

		for (i = 0; i < temp->laundrynumber; i++)
			free(temp->mylaundry[i]);

		free(temp->mylaundry);
		free(temp);

		temp = temp2;
	}
}
void LoadAboutLaundry(CUSTOMER * temp)
{
	// Local variables declare
	char phone[16] = { 0 };
	char arr[100];
	char comp;
	int line = 0;
	int i;
	FILE * load;

	// Statements
	strcpy(phone, temp->phone);
	strcat(phone, ".txt"); // Using phonenumber and strcat function, create ".txt" file

	load = fopen(phone, "r");
	if (load == NULL)
	{
		return;
	}


	while ((comp = fgetc(load)) != EOF)
	{
		if (comp == '\n')
		{
			line++;
		}
	}
	line++;
	temp->laundrynumber = line;
	temp->mylaundry = (LAUNDRY**)malloc(sizeof(LAUNDRY)*line);


	fseek(load, 0, SEEK_SET);

	for (i = 0; i < line; i++)
	{
		temp->mylaundry[i] = (LAUNDRY*)malloc(sizeof(LAUNDRY));
		temp->mylaundry[i]->name = temp;
		fscanf(load, "%s", temp->mylaundry[i]->type);
		fscanf(load, "%d", &temp->mylaundry[i]->start_day);
		fscanf(load, "%d", &temp->mylaundry[i]->end_day);
	}

	// Read line number, and assign array that its size is line number
	// and initialize variables in the array

	fclose(load);
}
int Start_Menu(void)
{
	// Local variables declare
	FILE * file;
	char c;
	char choice;
	int x = 6, y = 3;
	int menu = 1;

	// Statements 
	if (!(file = fopen("startfomat.txt", "r"))) // Starting fomat form
	{
		printf("Error");
		exit(101);
	}

	while (1) // Deciding menu
	{
		system("cls");
		while ((c = fgetc(file)) != EOF) // Getting starting fomat
			printf("%c", c);

		fseek(file, 0L, SEEK_SET);

		Cursor(x, y);
		printf("●");
		if (choice = getch())
		{
			switch (choice)
			{
			case UP:
				y = y - 2;
				menu = menu - 1;
				break;
			case DOWN:
				y = y + 2;
				menu = menu + 1;
				break;
			case ENTER:
				return menu;
			}
		}
	}
	fclose(file);
}
CUSTOMER * Load_Info(CUSTOMER * head)
{
	// Local variables declare
	FILE * cus;
	CUSTOMER * temp;
	CUSTOMER * tail = 0;
	CUSTOMER copy;

	// Statements
	if (!(cus = fopen("Customer.txt", "r")))
	{
		printf("Error");
		return -1;
	}
	while (fscanf(cus, "%s %s %[^,]%*c%s %d %d %s", copy.name, copy.phone, copy.address, copy.mail, &copy.unpaidbalance, &copy.gender, copy.idnumber) != EOF)
	{// Using assignment suppression flag, %[^ ,] to read address until meet ','
		if ((temp = (CUSTOMER*)malloc(sizeof(CUSTOMER))) == NULL)
		{
			printf("Memory allocation error.");
			return -1;
		}

		Insert(temp, &copy); // Insert copy data into temp
		temp->laundrynumber = 0;
		LoadAboutLaundry(temp);

		temp->next = NULL; // Using linked list
		if (head == NULL)
		{
			head = temp;
			head->prev = NULL;
		}
		else
		{
			temp->prev = tail;
			tail->next = temp;
		}
		tail = temp;


	}
	fclose(cus);

	return head;
}
void Insert(CUSTOMER * x, CUSTOMER * y)
{
	// Statements
	strcpy(x->name, y->name);
	strcpy(x->phone, y->phone);
	strcpy(x->address, y->address);
	strcpy(x->mail, y->mail);
	x->unpaidbalance = y->unpaidbalance;
	x->gender = y->gender;
	strcpy(x->idnumber, y->idnumber);
}
int Show_Time(int * day, int * year, int * mon)
{
	// Local variables declare
	int day_gap;
	int starttime;
	int finishtime;
	FILE * file;
	time_t now = 0;
	struct tm * t = 0; // A function that brings present time in sec unit

					   // Statements
	time(&now); // A time function brings time imformation to time data type variable 'now'
	t = localtime(&now); // Store time information using localtime function in variable 't'
	*year = t->tm_year + 1900; // and calculate it year, month, day unit
	*mon = t->tm_mon + 1;
	*day = t->tm_mday;

	printf("Start time : %d Y %d M %d D", *year, *mon, *day);
	starttime = ((*year) * 10000) + ((*mon) * 100) + (*day); // Store time information ex)20160519
	file = fopen("time.txt", "a+");
	fscanf(file, "%d", &finishtime);
	day_gap = starttime - finishtime; // Subract last quit time of program and present program stating time
	return day_gap;
}