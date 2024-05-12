#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"


ht_item* create_hash_item(const char* date, const char* done_work)
{
	ht_item* temp_hash_item = (ht_item*)malloc(sizeof(ht_item));
	if (!temp_hash_item)
	{
		return NULL;
	}
	temp_hash_item->date = _strdup(date);
	temp_hash_item->done_work = _strdup(done_work);
	temp_hash_item->next = NULL;
	return temp_hash_item;
}


ht_hash_table* create_hash_table(int size)
{
	ht_hash_table* temp_hash_table = (ht_hash_table*)malloc(sizeof(ht_hash_table));
	if (!temp_hash_table)
	{
		return NULL;
	}
	temp_hash_table->size = size;
	temp_hash_table->count = 0;
	temp_hash_table->cellar = temp_hash_table->size / 4;
	temp_hash_table->items = (ht_item**)calloc(size, sizeof(ht_item*));

	for (int i = 0; i < size; i++)
	{
		temp_hash_table->items[i] = NULL;
	}

	return temp_hash_table;
}

int pow(int a, int b)
{
	if (b == 0) return 1;
	else if ((b % 2) == 0)
		return pow(a, b / 2) * pow(a, b / 2);
	else
		return a * pow(a, b / 2) * pow(a, b / 2);
}


// a is always > 128 and a is prime
int hash_function(const char* string, const int a)
{
	long hash = 0;
	const int string_len = strlen(string);
	const char* ptr = string;
	int i = 0;
	while (*ptr != '\0')
	{
		hash += (long)(pow(a, (string_len - (i + 1))) * int(*ptr));
		i++;
		ptr++;
	}
	if ((int)hash < 0) return (int)hash * -1;
	return (int)hash;
}

int get_index_of_table(int hash, int len_of_table, int cellar)
{
	return hash % (len_of_table - cellar);
}

void resize_hash_table(ht_hash_table* hash_table, int new_size)
{
	ht_hash_table* new_ht = create_hash_table(new_size);
	int i;
	for (i = 0; i < hash_table->size; i++)
	{
		ht_item* item = hash_table->items[i];
		while (item != NULL)
		{
			ht_insert(new_ht, item->date, item->done_work);
			item = item->next;
		}
	}
	
	hash_table->size = new_size;
	hash_table->cellar = new_size / 4;
	free(hash_table->items);
	hash_table->items = new_ht->items;


	free(new_ht);
}

void resize_ht(ht_hash_table* hash_table)
{
	int new_size = hash_table->size * 2;
	resize_hash_table(hash_table, new_size);
}

int ht_insert(ht_hash_table* hash_table, const char* date, const char* done_work)
{
	if (!hash_table)
	{
		printf("create hash table firstly bro\n");
		return 0;
	}

	int ht_len = hash_table->size;
	int hash = hash_function(date, 151);
	int index_of_hash_table = get_index_of_table(hash, ht_len, hash_table->cellar);


	if (!hash_table->items[index_of_hash_table] || !hash_table->items[index_of_hash_table]->date)
	{
		ht_item* temp = create_hash_item(date, done_work);
		if (temp)
		{
			hash_table->items[index_of_hash_table] = temp;
			hash_table->count++;
			return 0;
		}
	}
	else if (strcmp(hash_table->items[index_of_hash_table]->date, date) == 0) return 0;
	else
	{
		int cursor = ht_len - 1;
		ht_item* it = hash_table->items[index_of_hash_table];

		while (cursor > hash_table->cellar && hash_table->items[cursor] != NULL && hash_table->items[cursor]->date)
		{
			if ((hash_table->items[cursor]->date) && strcmp(hash_table->items[cursor]->date, date) == 0) return 0;
			--cursor;
		}

		if (cursor == hash_table->cellar)// cellar is fulll
		{
			resize_ht(hash_table);
			ht_insert(hash_table, date, done_work);
			return 0; 
		}
		hash_table->items[cursor] = create_hash_item(date, done_work);
		hash_table->count++;

		while (it->next != NULL)
		{
			it = it->next;
		}
		it->next = hash_table->items[cursor];
	}
	return 0;
}

void add_elem_by_keyboard(ht_hash_table* hash_table)
{
	while (getchar() != '\n');
	if (!hash_table)
	{
		printf("create hash table firstly");
		return;
	}

	char temp_date[200], temp_work[200];
	printf("data (dd.mm.yy): ");
	gets_s(temp_date);

	printf("word : ");
	gets_s(temp_work);

	ht_insert(hash_table, temp_date, temp_work);
}

void add_elems_from_file(ht_hash_table* hash_table)
{
	FILE* fl;
	fl = fopen("file.txt", "r");
	if (!fl)
	{
		printf("no file\n\n");
		return;
	}

	if (hash_table == NULL)
	{
		printf("create hash table first\n");
		return;
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

		//printf("date : %s, task : %s\n", temp_date, temp_task);
		ht_insert(hash_table, temp_date, temp_task);
		ptr = fgetc(fl);
	}
}

void delete_item_from_ht(ht_hash_table* hash_table)
{
	while (getchar() != '\n');
	if (!hash_table)
	{
		printf("no elemens\n");
		return;
	}
	char temp_date[200];
	printf("enter date to delete : ");
	gets_s(temp_date);

	if (hash_table == NULL)
	{
		printf("create hash table first\n");
		return;
	}

	int ht_len = hash_table->size;
	int hash = hash_function(temp_date, 151);
	int index_of_hash_table = get_index_of_table(hash, ht_len, hash_table->cellar);

	if (!hash_table->items[index_of_hash_table]) return;

	if (strcmp(hash_table->items[index_of_hash_table]->date, temp_date) == 0)
	{
		if (hash_table->items[index_of_hash_table]->next == NULL)
		{
			delete_hash_item(hash_table->items[index_of_hash_table]);
			//ht_item* temp = hash_table->items[index_of_hash_table];
			hash_table->items[index_of_hash_table] = NULL;
			return;
		}
		else
		{
			//strcpy_s(hash_table->items[index_of_hash_table]->date, strlen(hash_table->items[index_of_hash_table]->date), hash_table->items[index_of_hash_table]->next->date);
			//strcpy_s(hash_table->items[index_of_hash_table]->done_work, strlen(hash_table->items[index_of_hash_table]->done_work), hash_table->items[index_of_hash_table]->next->done_work);
			char* t = hash_table->items[index_of_hash_table]->date;
			hash_table->items[index_of_hash_table]->date = hash_table->items[index_of_hash_table]->next->date;
			hash_table->items[index_of_hash_table]->next->date = t;

			char* t1 = hash_table->items[index_of_hash_table]->done_work;
			hash_table->items[index_of_hash_table]->done_work = hash_table->items[index_of_hash_table]->next->done_work;
			hash_table->items[index_of_hash_table]->next->done_work = t1;


			ht_item* temp = hash_table->items[index_of_hash_table]->next->next;
			delete_hash_item(hash_table->items[index_of_hash_table]->next);
			//hash_table->items[index_of_hash_table]->next = NULL;
			if (temp) hash_table->items[index_of_hash_table]->next = temp;


			//ht_item* temp = hash_table->items[index_of_hash_table]->next;
			//hash_table->items[index_of_hash_table]->next = hash_table->items[index_of_hash_table]->next->next;
			//delete_hash_item(temp);
			//temp = NULL;
		}
		return;
	}
	ht_item* temp = hash_table->items[index_of_hash_table];
	while (temp)
	{
		if (temp->date && strcmp(temp->date, temp_date) == 0)
		{
			break;
		}
		temp = temp->next;
	}

	if (temp && temp->date && strcmp(temp->date, temp_date) == 0)
	{
		delete_hash_item(temp);
	}
}

void search_hash_item(ht_hash_table* hash_table)
{
	while (getchar() != '\n');
	if (hash_table == NULL)
	{
		printf("create hash table first\n");
		return;
	}
	char temp_date[200];
	printf("enter date to search : ");
	gets_s(temp_date);

	int ht_len = hash_table->size;
	int hash = hash_function(temp_date, 151);
	int index_of_hash_table = get_index_of_table(hash, ht_len, hash_table->cellar);

	if (hash_table->items[index_of_hash_table] == NULL)
	{
		printf("value is not found\n");
		return;
	}
	if (strcmp(hash_table->items[index_of_hash_table]->date, temp_date) == 0)
	{
		printf("value is found : %s\n", hash_table->items[index_of_hash_table]->done_work);
		return;
	}

	ht_item* temp = hash_table->items[index_of_hash_table];
	while (strcmp(temp->date, temp_date) != 0 && temp != NULL)
	{
		temp = temp->next;
	}

	if (temp == NULL)
	{
		printf("value is not found\n");
		return;
	}

	printf("value is found : %s\n", temp->done_work);

}

void table_load_factor(ht_hash_table* hash_table)
{
	if (!hash_table)
	{
		printf("create hash table firstly\n");
		return;
	}
	printf("table load factor : %d\n", hash_table->count);
}


void print_ht(ht_hash_table* hash_table)
{
	if (!hash_table)
	{
		printf("no elements\n");
		return;
	}
	int i = 0;
	while (i < hash_table->size)
	{
		if (hash_table->items[i] && hash_table->items[i]->date)
		{
			printf("date : %s, event : %s, index in hash table : %d\n", hash_table->items[i]->date, hash_table->items[i]->done_work, get_index_of_table(hash_function(hash_table->items[i]->date, 151), hash_table->size, hash_table->cellar));
		}
		i++;
	}
}

void menu()
{
	printf("0 - create hash table\n");
	printf("1 - add elements from file to ht\n");
	printf("2 - print hash table\n");
	printf("3 - delete elem in hash table\n");
	printf("4 - search in hash table\n");
	printf("5 - add new elem by keyboard\n");
	printf("6 - table load factor\n");
	printf("9 - quit\n : ");
}

void delete_hash_item(ht_item* item)
{
	free(item->date);
	free(item->done_work);
	item->next = NULL;
	//free(item);
	item->date = NULL;
	item->done_work = NULL;
}


void delete_hash_table(ht_hash_table* hash_table)
{
	if (hash_table == NULL)
	{
		return;
	}
	int len = hash_table->size;
	for (int i = 0; i < len; i++)
	{
		if (hash_table->items[i])
		{
			delete_hash_item(hash_table->items[i]);
			free(hash_table->items[i]);
		}
	}
	free(hash_table->items);
	free(hash_table);
}
