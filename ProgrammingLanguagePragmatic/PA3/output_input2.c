#include <stdio.h>
int main ( ) {
	int g;
	void A(int a) {
		g = 1;
		g = g + a;
	}
	int B(int b) {
		int g;
		g = 3.0;
		g = g + b;
		A(g);
	}
	B(3);
	printf("Value of g will be printed.\n", g);
	return 0;
}
