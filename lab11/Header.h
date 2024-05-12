#pragma once
#include <stdlib.h>
#include <string.h>
#include "stdio.h"

//struct ht_item;

typedef struct ht_item
{
	char* date;
	char* done_work;
	ht_item* next = NULL;
}ht_item;

typedef struct 
{
	int size;
	int count;
	int cellar;
	ht_item** items;
}ht_hash_table;


ht_item* create_hash_item(char* date, char* done_work);

ht_hash_table* create_hash_table(int size);

int pow(int a, int b);

int hash_function(const char* string, const int a);

int get_index_of_table(int hash, int len_of_table, int cellar);

void resize_hash_table(ht_hash_table* hash_table, int new_size);

void resize_ht(ht_hash_table* hash_table);

int ht_insert(ht_hash_table* hash_table, const char* date, const char* done_work);

void add_elem_by_keyboard(ht_hash_table* hash_table);

void add_elems_from_file(ht_hash_table* hash_table);

void delete_item_from_ht(ht_hash_table* hash_table);

void search_hash_item(ht_hash_table* hash_table);

void table_load_factor(ht_hash_table* hash_table);

void print_ht(ht_hash_table* hash_table);

void menu();

void delete_hash_item(ht_item* item);

void delete_hash_table(ht_hash_table* table);


