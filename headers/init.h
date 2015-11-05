/* 
 * File:   init.h
 * Author: root
 *
 * Created on October 26, 2015, 7:52 PM
 */

#ifndef INIT_H
#define	INIT_H


#define _2PI        6.283185
#define PI_1        3.141592
#define PI_2        1.570779
#define PI_4        0.785398
#define CosPi_4     0.707106
#define SinPi_4     0.707106


int RADxPI_4[600]; // cos == sin;

int sinRADIUSxPI[600][100]; // presision de 0.03°
int cosRADIUSxPI[600][100]; // presision de 0.03°

void init_compute();

#endif	/* INIT_H */

