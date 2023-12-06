/*
#include<iostream>
using namespace std;
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int year = atoi(argv[1]);

	if (year % 4 != 0){
		printf("%s was not a leap year\n", argv[1]);
    } else if (year % 100 != 0) {
		printf("%s was a leap year\n", argv[1]);
    } else if (year % 400 == 0) {
		printf("%s was a leap year\n", argv[1]);
    } else{
		printf("%s was not a leap year\n", argv[1]);
    }

	return 0;
}