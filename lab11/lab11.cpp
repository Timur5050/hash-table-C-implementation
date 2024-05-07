#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

int main()
{
	ht_hash_table *map = create_hash_table(20);
	//const char date1[] = "03:02:12";
	//char date2[] = "13:32:03";
	//const char ev1[] = "do home work";
	//char ev2[] = "do leetcode";

	//ht_insert(map, date1, ev1);
	//print_ht(map);
	//printf("\n\n\n");
	//ht_insert(map, date2, ev2);
	//print_ht(map);
	//delete_item_from_ht(map, date1);
	//printf("\n\n\n");
	//print_ht(map);
	 
	FILE* fl;
	fl = fopen("file.txt", "r");
	if (!fl)
	{
		printf("no file\n\n");
		return 1;
	}

	char ptr = fgetc(fl);
	while (!feof(fl))
	{
		char temp_date[9], temp_task[200];
		int temp_counter = 0;	
		while (ptr != ' ')
		{
			temp_date[temp_counter++] = ptr;
			ptr = fgetc(fl);
		}
		temp_date[temp_counter] = '\0';
		temp_counter = 0;
		ptr = fgetc(fl);

		while (ptr != '\n' && !feof(fl))
		{		
			temp_task[temp_counter++] = ptr;
			ptr = fgetc(fl);
		}
		temp_task[temp_counter] = '\0';

		printf("date : %s, task : %s\n", temp_date, temp_task);
		ht_insert(map, temp_date, temp_task);
		ptr = fgetc(fl);
	}
	printf("\n\n\n");
	print_ht(map);

	char temp[10] = "22:10:11";

	search_hash_item(map, temp);
	//search_hash_item(map, date1);

	//printf("\n\n%d : %d : %d", get_index_of_table(hash_function(date1, 151), 20), get_index_of_table(hash_function(date2, 151), 20), -102 % 10);
	//printf("%d", get_index_of_table(hash_function(str, 151), 53));
	return 0;
}