// Include the stdarg.h
// int fixedparam, ...
// Define a va_list variable
// Begin and end the arg list with va_start and va_end

// Add(3, 1, 2, 3) = 6
// Add(6, 20, 20, 20, 10, 10, 20) = 100

#include <stdarg.h>
#include <stdio.h>

int add(int args, ...)
{
	va_list ap;

	va_start(ap, args);

	int i;
	int sum;

	i = 0;
	sum = 0;
	while(i < args)
	{
		sum += va_arg(ap, int); // 2e parametre = le type de variable qu'on veux process
		i++;
	}
	va_end(ap);
	return (sum);
}

int main(void)
{
	printf("Add1 = %d\n", add(3, 1, 2, 3));
	printf("Add2 = %d\n", add(6, 20, 20, 20, 10, 10, 20));
	return (0);
}

