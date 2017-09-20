#include "KWON.h"

int main(void)
{
	// Local variables declare
	int selectmenu;
	int getmenu;
	int clock;
	char c;
	int day = 0;
	int year = 0;
	int mon = 0;
	CUSTOMER * head = NULL;

	// Statements
	head = Load_Info(head); // Store customer's infomation in head
	clock = Show_Time(&day, &year, &mon); // Show present time

	while (1)
	{
		fflush(stdin);
		scanf("%c", &c);
		if (c == '\n')
			break;
	} // If press enter, go to next statement
	while (1)
	{
		selectmenu = Start_Menu();

		if (selectmenu == 1) // Normal mode
		{
			Add_Or_Sub_Product(head, day, year, mon);
		}
		else if (selectmenu == 2) // Supervisor mode
		{
			while (1)
			{
				getmenu = Get_Menu_From_Cursor();
				if (getmenu == 1)
				{
					Add_Customer(head);
					break;
				}
				else if (getmenu == 2)
				{
					Del_Customer(head);
				}
				else if (getmenu == 3)
				{
					Blacklist(head);
					while (1)
					{
						fflush(stdin);
						scanf("%c", &c);
						if (c == '\n')
							break;
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			Print_To_File(head);
			Free_All(head);

			return 0;
		}
	}
}

