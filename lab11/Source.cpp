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

int get_index_of_table(int hash, int len_of_table)
{
	return hash % len_of_table;
}

int ht_insert(ht_hash_table* hash_table, const char* date, const char* done_work)
{
	if (!hash_table) return 2;

	int ht_len = hash_table->size;
	int hash = hash_function(date, 151);
	int index_of_hash_table = get_index_of_table(hash, ht_len);


	if (!hash_table->items[index_of_hash_table])
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

		while (cursor > hash_table->cellar && hash_table->items[cursor] != NULL)
		{
			if (strcmp(hash_table->items[cursor]->date, date) == 0) return 0;
			--cursor;
		}

		if (cursor == hash_table->cellar) return -1; // cellar is fulll

		hash_table->items[cursor] = create_hash_item(date, done_work);

		while (it->next != NULL)
		{
			it = it->next;
		}
		it->next = hash_table->items[cursor];
	}
	return 0;
}


void delete_item_from_ht(ht_hash_table* hash_table, const char* date)
{
	int ht_len = hash_table->size;
	int hash = hash_function(date, 151);
	int index_of_hash_table = get_index_of_table(hash, ht_len);

	if (!hash_table->items[index_of_hash_table]) return;

	if (strcmp(hash_table->items[index_of_hash_table]->date, date) == 0)
	{
		if (hash_table->items[index_of_hash_table]->next == NULL)
		{
			delete_hash_item(hash_table->items[index_of_hash_table]);
			hash_table->items[index_of_hash_table] = NULL;
		}
		else
		{
			strcpy_s(hash_table->items[index_of_hash_table]->date, strlen(hash_table->items[index_of_hash_table]->date), hash_table->items[index_of_hash_table]->next->date);
			strcpy_s(hash_table->items[index_of_hash_table]->done_work, strlen(hash_table->items[index_of_hash_table]->done_work), hash_table->items[index_of_hash_table]->next->done_work);
			hash_table->items[index_of_hash_table]->next = hash_table->items[index_of_hash_table]->next->next;
			delete_hash_item(hash_table->items[index_of_hash_table]->next);
			hash_table->items[index_of_hash_table]->next = NULL;
		}
		return;
	}
	ht_item* temp = hash_table->items[index_of_hash_table];
	while (temp->next->date != date)
	{
		temp = temp->next;
	}
	if (temp->next->next == NULL)
	{
		delete_hash_item(temp->next->next);
		temp->next->next = NULL;
	}
	else
	{
		temp->next = temp->next->next;
		delete_hash_item(temp->next);
		temp->next = NULL;
	}
}


void search_hash_item(ht_hash_table* hash_table, const char* date)
{
	int ht_len = hash_table->size;
	int hash = hash_function(date, 151);
	int index_of_hash_table = get_index_of_table(hash, ht_len);

	if (hash_table->items[index_of_hash_table] == NULL)
	{
		printf("value is not found\n");
		return;
	}
	if (strcmp(hash_table->items[index_of_hash_table]->date, date) == 0)
	{
		printf("value is found : %s\n", hash_table->items[index_of_hash_table]->done_work);
		return;
	}

	ht_item* temp = hash_table->items[index_of_hash_table];
	while (strcmp(temp->date, date) != 0 && temp != NULL)
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


void print_ht(ht_hash_table* hash_table)
{
	if (!hash_table) return;
	int i = 0;
	while (i < hash_table->size)
	{
		if (hash_table->items[i])
		{
			printf("date : %s, event : %s\n", hash_table->items[i]->date, hash_table->items[i]->done_work);
		}
		i++;
	}
}


void delete_hash_item(ht_item* item)
{
	free(item->date);
	free(item->done_work);
	item->next = NULL;
	free(item);
}


void delete_hash_table(ht_hash_table* table)
{
	int len = table->size;
	for (int i = 0; i < len; i++)
	{
		if(table->items[i]) delete_hash_item(table->items[i]);
	}
	free(table->items);
	free(table);
}
