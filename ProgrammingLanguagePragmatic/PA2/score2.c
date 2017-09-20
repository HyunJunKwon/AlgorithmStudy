#include <stdio.h>
#include <stdlib.h>

int main()
{
	char name[20];
	int score[3];
	int i, total;
	int num;
	printf("The number of students: ");
	scanf("%d", &num);
	if(num > 0)
	{
		int j;
		j = 0;
		do{
			total = 0;
			printf("name: ");
			scanf("%s", name);

			for(i=0; i<3; i=i+1)
			{
				printf("Score #%d: ",i+1);
				scanf("%d", &score[i]);
				total = total + score[i];
			}
			printf("%s's total score is %d, average is %.2f \n",name,total,total/3.0);
			j = j + 1;
		}while(j < num);
	}
	else if(num < 0)
	{
		exit(1);
	}
	else
	{
		return ;
	}

	switch(num)
	{
	case 1:
		printf("hi");
		break;
	case 2:
		printf("hi");
		break;
	default:
		printf("");
	}

 
	return 0;
}
