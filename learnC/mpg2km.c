/*
* mpg2km.c / Program in C
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 8, 2023
*
*/

#include <stdio.h>
#include "mpg2km.h"

/*
 * Converts from miles per gallon to kilometers per liter
 *
 * @param mpg: fuel efficiency in miles per gallon
 *
 * @return kml: fuel efficienct in kilometers per liter
 * 
 */

float mpg2kml(float mpg) {
	float kml = mpg / 2.352;
	return kml;
}

/*
 * Converts from miles per gallon to liters per 100 kilometers
 *
 * @param mpg: fuel efficiency in miles per gallon
 *
 * @return lphm: fuel efficiency in liters per 100 kilometers
 * 
 */

float mpg2lphm(float mpg) {
	if (mpg == 0) {
		return 0;
	}
	float lphm = 235.215 / mpg;
	return lphm;
}

/*
 * Converts from liters per 100 kilometers to miles per gallon
 *
 * @param lph: fuel efficiency in liters per 100 kilometers
 *
 * @return mpg: fuel efficiency in miles per gallon
 * 
 */

float lph2mpg(float lph) {
	if (lph == 0) {
		return 0;
	}
	float mpg = 235.215 / lph;
	return mpg;
}

