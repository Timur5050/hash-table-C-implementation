#include "Header.h"

int main()
{
	char str[] = "cat";
	printf("%d", get_index_of_table(hash_function(str, 151), 53));
	return 0;
}