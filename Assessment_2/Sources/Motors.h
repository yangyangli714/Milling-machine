/*
 * Motors.h
 *
 *  Created on: 2020Äê10ÔÂ23ÈÕ
 *      Author: liyangyang
 */

#ifndef SOURCES_MOTORS_H_
#define SOURCES_MOTORS_H_

void delay(int delay_ms);
void starterup();
void x_motor(int x);
void y_motor(int y);
void z_motor(int z);
void spindle(int dir, int depth, int z);
void manual_control(int x, int y, int z, int p);
void x_reset();
void y_reset();
void z_reset();
void reset_position();

#endif /* SOURCES_MOTORS_H_ */
