#pragma once


typedef struct
{
	char* date;
	char* done_work;
}ht_item;

typedef struct
{
	int size;
	int count;
	ht_item** items;
}ht_hash_table;


ht_item* create_hash_item(char* date, char* done_work);

ht_hash_table* create_hash_table(int size);

void delete_hash_item(ht_item* item);

void delete_hash_table(ht_hash_table* table);


