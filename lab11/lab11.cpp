#include "Header.h"

int main()
{
	ht_hash_table *map = create_hash_table(20);
	const char date1[] = "03:02:12";
	char date2[] = "13:32:03";
	const char ev1[] = "do home work";
	char ev2[] = "do leetcode";

	ht_insert(map, date1, ev1);
	print_ht(map);
	printf("\n\n\n");
	ht_insert(map, date2, ev2);
	print_ht(map);
	delete_item_from_ht(map, date1);
	printf("\n\n\n");
	print_ht(map);
	//printf("\n\n%d : %d : %d", get_index_of_table(hash_function(date1, 151), 20), get_index_of_table(hash_function(date2, 151), 20), -102 % 10);
	//printf("%d", get_index_of_table(hash_function(str, 151), 53));
	return 0;
}