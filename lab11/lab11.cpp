#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

#define standart_size 20

int main()
{
	ht_hash_table *map = NULL;

	int num;

	while (1)
	{
		menu();
		scanf_s("%d", &num);
		switch (num)
		{
		case 0:
			map = create_hash_table(standart_size);
			break;
		case 1:
			add_elems_from_file(map);
			break;
		case 2:
			print_ht(map);
			break;
		case 3:
			delete_item_from_ht(map);
			break;
		case 4:
			search_hash_item(map);
			break;
		case 5:
			add_elem_by_keyboard(map);
			break;
		case 6:
			table_load_factor(map);
			break;
		case 9:
			printf("gg\n");
			delete_hash_table(map);
			return 0;
		default:
			printf("only (0 - 5 and 9)\n");
			break;
		}
	}
	


	//map = create_hash_table(standart_size);
	//add_elems_from_file(map);
	//print_ht(map);

	//delete_item_from_ht(map);
	//print_ht(map);

	//char a[] = "as";

	//char* p = _strdup(a);

	//printf("%s", p);

	//free(p);
	//p = NULL;

	//if (p == NULL)
	//{
	//	printf("\nnull");
	//}
	//else
	//{
	//	printf("%d", *p);
	//}

	//add_elems_from_file(map);
	//print_ht(map);
	//printf("size : %d : cellar : %d", map->size, map->cellar);
	////search_hash_item(map);
	//
	//add_elem_by_keyboard(map);
	//print_ht(map);
	//printf("size : %d", map->size);

	//char temp_date[] = "15:10:12";

	//int ht_len = map->size;
	//int hash = hash_function(temp_date, 151);
	//int index_of_hash_table = get_index_of_table(hash, ht_len, map->cellar);

	//printf("%d : size : %d : cellar : %d\n", index_of_hash_table, map->size, map->cellar);

	//search_hash_item(map);
	//printf("%d", )
	//print_ht(map);
	return 0;
}