#include <stdio.h>

int main()
{
	int a = 10; /*00001010*/
	int b = 5;  /*00000101*/

	int bitwise_and = a & b; /*00001010
							   00000101
							   00000000 = 0*/

	int bitwise_or = a | b; /*00001010
							  00000101
							  00001111 = 15*/

	int bitwise_xor = a ^ b; /*00001010
							   00000101
							   00001111 = 15*/

	int left_shift = a << 1; /*00101000 = 40*/

	int right_shift = a >> 1; /*00000010* = 2*/

	int bitwise_not = ~a; /*00001010
							11110101 = ?*/

	printf("%i\n", bitwise_and);
	printf("%i\n", bitwise_or); //their values after operation are displayed when hovering into each variable, except (and, or, xor -and- not).
	printf("%i\n", bitwise_xor);               
	printf("%i\n", left_shift);
	printf("%i\n", right_shift);
	printf("%i\n", bitwise_not);

}