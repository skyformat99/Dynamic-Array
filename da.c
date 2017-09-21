#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "da.h"

struct da {
	void (*display)(FILE *, void *);
	void **array;
	int size;
	int used;
};

static void doubleSize(DA *items) {
	items->size *= 2;
	items->array = realloc(items->array, items->size * sizeof(void *));
	assert(items->array != 0);
	return;
} 

/********** public interface **********/

//creates a new dynamic array

DA *newDA(void (*d)(FILE *,void *)) {
	DA *n = malloc(sizeof(DA));
	assert(n != 0);	
	n->array = malloc(sizeof(void *));
	n->size = 1; n->used = 0;	
	n->display = d;
	return n;
}

//inserts a value into the dynamic array

void insertDA(DA *items,void *value) {
	if (items->size <= items->used) {
		doubleSize(items);
	}
	assert(items->array != 0); 
	items->array[items->used] = value;
	items->used++;
	return;
}

//Removes an item from the dynamic array

void *removeDA(DA *items) {	
	assert(items->used > 0);
	items->used--;
	void *temp = items->array[items->used];
	
	//if items used falls below 25% of capacity, divide size in half	
	
	if(((float)items->size / 4.0) > (float)items->used && items->size != 1) {
		items->size /= 2;
		items->array = realloc(items->array, items->size * sizeof(void *));
	}
	return temp;
}

//join the contents of 2 DA's into the recipient DA

void unionDA(DA *recipient,DA *donor) {
	//check for array reaching capacity limit before insertion
	for(int i = 0; i < donor->used; i++) {	
		if(recipient->size <= recipient->used) {
			doubleSize(recipient);
		}
		insertDA(recipient, donor->array[i]);
	}
	//clear contents of donor array
	free(donor->array);
	donor->array = malloc(sizeof(void *));
	assert(donor->array != 0);
	donor->size = 1; donor->used = 0;
	return;
}

//return item at given index

void *getDA(DA *items,int index) {
	assert(index >= 0 && index < items->used);
	return items->array[index];
}

//set item at given index and return replaced item or null pointer

void *setDA(DA *items,int index,void *value) {
	assert(index >= 0 && index <= items->used); 
	if(index == items->used) {
		insertDA(items, value);
		void *i = NULL;
		return i;
	}
	void *temp = items->array[index];
	items->array[index] = value;
	return temp;
}

//extract the underlying C array and clear contents of given DA

void **extractDA(DA *items) {
	void **newArray = malloc(items->used * sizeof(void *));
	assert(newArray != 0);
	for(int i = 0; i < items->used; i++) {
		newArray[i] = items->array[i];
	}
	//clear contents of array
	free(items->array);
	items->array = malloc(sizeof(void *));
	assert(items->array != 0);
	items->size = 1; items->used = 0;
	return newArray;
}

//return number of items in given DA

int sizeDA(DA *items) {
	return items->used;
}

//display contents with given display function
//and number of open slots in given DA

void visualizeDA(FILE *fp,DA *items) {
	displayDA(fp, items);
	fprintf(fp, "[%d]", items->size - items->used);
	return;
}

//display contents with given display function

void displayDA(FILE *fp,DA *items) {
	fprintf(fp, "[");	
	for(int i = 0; i < items->used; i++) {
		if(i > 0) {
			fprintf(fp, ",");
		}
		items->display(fp, items->array[i]);
	}
	fprintf(fp, "]");
	return;
}