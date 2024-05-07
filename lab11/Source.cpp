#include <stdlib.h>
#include <string.h>

#include "Header.h"


ht_item* create_hash_item(const char* date, const char* done_work)
{
	ht_item* temp_hash_item = (ht_item*)malloc(sizeof(ht_item));
	temp_hash_item->date = _strdup(date);
	temp_hash_item->done_work = _strdup(done_work);
	return temp_hash_item;
}


ht_hash_table* create_hash_table(int size)
{
	ht_hash_table* temp_hash_table = (ht_hash_table*)malloc(sizeof(ht_hash_table));

	temp_hash_table->size = size;
	temp_hash_table->count = 0;
	temp_hash_table->items = (ht_item**)calloc(size, sizeof(ht_item*));

	return temp_hash_table;
}

void delete_hash_item(ht_item* item)
{
	free(item->date);
	free(item->done_work);
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
