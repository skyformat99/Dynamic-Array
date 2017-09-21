#include <stdio.h>
#include <stdlib.h>
#include "da.h"
#include "integer.h"

void printMe(DA *d);
void printMeV(DA *d);

int main(void) {
	
	//---------------DA TESTING--------------//
	
	printf("test-da version 1:\n");
	//start insert, remove, display tests	
	printf("d:\n");
	INTEGER *i1 = newINTEGER(1);
	INTEGER *i2 = newINTEGER(2);
	INTEGER *i3 = newINTEGER(3);
	INTEGER *i4 = newINTEGER(4);
	INTEGER *i5 = newINTEGER(5);
	DA *d = newDA(displayINTEGER);
	insertDA(d, i1);
	printMe(d);
	insertDA(d, i2);
	printMe(d);
	insertDA(d, i3);
	printMe(d);
	insertDA(d, i4);
	printMe(d);
	removeDA(d);
	printMe(d);
	removeDA(d);
	printMe(d);
	removeDA(d);
	printMe(d);
	removeDA(d);
	printMe(d);
	insertDA(d, i4);
	printMe(d);
	printf("\nvisualizeDA function:\n");
	printMeV(d);
	removeDA(d);
	printMeV(d);
	insertDA(d, i1);
	printMeV(d);
	insertDA(d, i2);
	printMeV(d);
	insertDA(d, i3);
	printMeV(d);
	insertDA(d, i4);
/*	
	//----SHOULD CREATE ERROR----//
	removeDA(d);
	visualizeDA(stdout, d);

	//----EXCTRACT TEST----//
	void **temp = extractDA(d);
	printf("%d\n", *(int *)temp[0]);
*/	
	//----UNION TEST----//
	printf("\nunionDA function\n");
	DA *d1 = newDA(displayINTEGER);
	insertDA(d1, i3);
	insertDA(d1, i1);
	insertDA(d1, i2);
	printf("d1: ");
	printMeV(d1);
	printf("d : ");
	printMeV(d);
	unionDA(d, d1);
	printf("d1: ");
	printMeV(d1);
	printf("d: ");
	printMeV(d);
	
	//----TEST SET & GET----//
	
	for(int i = 0; i < 3; i++) displayINTEGER(stdout, getDA(d, i));
	//displayINTEGER(stdout, getDA(d, 4)); // should create an error
	printf("\n");
	setDA(d, 0, i2);
	printMe(d);
	setDA(d, 3, i5);
	setDA(d, 4, i2);
	setDA(d, 6, i3);
	printMe(d);
	return 0;
}

void printMe(DA *d){
	displayDA(stdout, d);
	printf("\n");
	return;
}
void printMeV(DA *d){
	visualizeDA(stdout, d);
	printf("\n");
	return;
}