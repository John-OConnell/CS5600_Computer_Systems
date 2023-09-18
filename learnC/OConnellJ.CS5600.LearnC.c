/*
* OConnellJ.CS5600.LearnC.c / Program in C
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 8, 2023
*
*/

#include <stdio.h>
#include "mpg2km.h"

int main(){
	
	float num1 = 0;
	float num2 = 5;
	float num3 = 100;
	float num4 = 123456;
	float num5 = -5;
	float num6 = -1000;

	float test1;
	float test2;
	float test3;
	float test4;
	float test5;
	float test6;

	printf("--------Test Cases for mpg2kml--------\n");
	test1 = mpg2kml(num1);
	test2 = mpg2kml(num2);
	test3 = mpg2kml(num3);
	test4 = mpg2kml(num4);
	test5 = mpg2kml(num5);
	test6 = mpg2kml(num6);
	printf("Test 1: %.3f mpg = %.3f kml\n", num1, test1);
	printf("Test 2: %.3f mpg = %.3f kml\n", num2, test2);
	printf("Test 3: %.3f mpg = %.3f kml\n", num3, test3);
	printf("Test 4: %.3f mpg = %.3f kml\n", num4, test4);
	printf("Test 5: %.3f mpg = %.3f kml\n", num5, test5);
	printf("Test 6: %.3f mpg = %.3f kml\n", num6, test6);

	printf("\n--------Test Cases for mpg2lphm--------\n");
	test1 = mpg2lphm(num1);
	test2 = mpg2lphm(num2);
	test3 = mpg2lphm(num3);
	test4 = mpg2lphm(num4);
	test5 = mpg2lphm(num5);
	test6 = mpg2lphm(num6);
	printf("Test 1: %.3f mpg = %.3f lphm\n", num1, test1);
	printf("Test 2: %.3f mpg = %.3f lphm\n", num2, test2);
	printf("Test 3: %.3f mpg = %.3f lphm\n", num3, test3);
	printf("Test 4: %.3f mpg = %.3f lphm\n", num4, test4);
	printf("Test 5: %.3f mpg = %.3f lphm\n", num5, test5);
	printf("Test 6: %.3f mpg = %.3f lphm\n", num6, test6);

	printf("\n--------Test Cases for lph2mpg--------\n");
	test1 = lph2mpg(num1);
	test2 = lph2mpg(num2);
	test3 = lph2mpg(num3);
	test4 = lph2mpg(num4);
	test5 = lph2mpg(num5);
	test6 = lph2mpg(num6);
	printf("Test 1: %.3f lph = %.3f mpg\n", num1, test1);
	printf("Test 2: %.3f lph = %.3f mpg\n", num2, test2);
	printf("Test 3: %.3f lph = %.3f mpg\n", num3, test3);
	printf("Test 4: %.3f lph = %.3f mpg\n", num4, test4);
	printf("Test 5: %.3f lph = %.3f mpg\n", num5, test5);
	printf("Test 6: %.3f lph = %.3f mpg\n", num6, test6);
	
	return 0;
}
