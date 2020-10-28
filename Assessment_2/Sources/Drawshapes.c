/*
 * Drawshapes.c
 *
 *  Created on: 2020Äê10ÔÂ23ÈÕ
 *      Author: liyangyang
 */
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "x_step.h"
#include "BitIoLdd1.h"
#include "x_dir.h"
#include "BitIoLdd2.h"
#include "y_step.h"
#include "BitIoLdd3.h"
#include "y_dir.h"
#include "BitIoLdd4.h"
#include "z_step.h"
#include "BitIoLdd5.h"
#include "z_dir.h"
#include "BitIoLdd6.h"
#include "reset.h"
#include "BitIoLdd7.h"
#include "sleep.h"
#include "BitIoLdd8.h"
#include "enable.h"
#include "BitIoLdd9.h"
#include "mode_0.h"
#include "BitIoLdd10.h"
#include "mode_1.h"
#include "BitIoLdd11.h"
#include "mode_2.h"
#include "BitIoLdd12.h"
#include "PWM1.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU2.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GUI.h>
#include <Motors.h>

extern volatile char c;

// Draw house function - draw a simple house
void draw_House() {
	PWM1_SetRatio8(0);
	GUI_clear();
	Term1_MoveTo(10, 13);
	Term1_SendStr("Starting to draw house.....q");
	int base = 100;
	// Right roof of the house
	for (int i = 0; i <= (base/2); i++) {
		x_dir_PutVal(1);
		x_motor(1);
		y_dir_PutVal(1);
		y_motor(1);
		change_x(i);
		change_y(i);
	}
	// Left roof of the house
	x_dir_PutVal(1);
	y_dir_PutVal(0);
	for (int i = 0; i <= (base/2); i++) {
		x_motor(1);
		y_motor(1);
		change_x(i);
		change_y(i);
	}
	// Bottom roof of the house, need to be 2 for loops in order to have a enclosed shape
	x_dir_PutVal(0);
	for (int i = 0; i <= base; i++) {
		x_motor(1);
		change_x(i);
	}
	x_dir_PutVal(0);
	for (int i = 0; i <= 5; i++) {
		x_motor(1);
		change_x(i);
	}
	// Right wall of the house
	y_dir_PutVal(0);
	for (int i = 0; i <= base; i++) {
		y_motor(1);
		change_y(i);
	}
	// Bottom wall of the house
	x_dir_PutVal(1);
	for (int i = 0; i <= base; i++) {
		x_motor(1);
		change_x(i);
	}
	// Left wall of the house
	y_dir_PutVal(1);
	for (int i = 0; i <= base; i++) {
		y_motor(1);
		change_y(i);
	}
	Term1_MoveTo(10, 15);
	Term1_SendStr("House has been drawn!");
	Term1_MoveTo(10, 16);
	Term1_SendStr("Press Q to go back");
	PWM1_SetRatio8(255);
}

// Control_circle_dir function - alternates the x and y motor movements
void control_circle_dir(int x, int y, int x_before, int y_before) {
	int i;
	// Increases both x and y axis
	if (x > x_before) {
		for (i = 0; i <= x - x_before; i++) {
			for (int m = 0; m < 10; m++) {
				y_dir_PutVal(1);
				x_step_NegVal();
				delay(1);
				x_step_NegVal();
				delay(1);
			}
		}

	} else if (x < x_before) {
		for (i = 0; i <= x_before - x; i++) {
			for (int m = 0; m < 10; m++) {
				x_dir_PutVal(0);
				x_step_NegVal();
				delay(1);
				x_step_NegVal();
				delay(1);
			}
		}
	}
	// Decreases both x and y axis
	if (y > y_before) {
		for (i = 0; i <= y - y_before; i++) {
			for (int m = 0; m < 10; m++) {
				y_dir_PutVal(1);
				y_step_NegVal();
				delay(1);
				y_step_NegVal();
				delay(1);
			}
		}

	} else if (y < y_before) {
		for (i = 0; i <= y_before - y; i++) {
			for (int m = 0; m < 10; m++) {
				y_dir_PutVal(0);
				y_step_NegVal();
				delay(1);
				y_step_NegVal();
				delay(1);
			}
		}
	}
}

// Draw oval function - draw a simple oval
void draw_oval() {
	PWM1_SetRatio8(0);
	GUI_clear();
	// Initialize parameter
	int radius = 50;
	int x, y, r2, i;
	int x_before = 0, y_before = 0;
	r2 = radius * radius;
	Term1_MoveTo(10, 13);
	Term1_SendStr("Stating to draw oval.....");
	// Draw 1st semicircle
	// Find the relationship between x and y, x^2 + y^2 = 1
	for (x = 0; x <= radius * 2; x++) {
		// Use math library
		y = sqrt(r2 - ((x - radius) * (x - radius)));
		control_circle_dir(x, y, x_before, y_before);
		x_before = x;
		y_before = y;
		Term1_SetColor(clWhite, clBlack);
		change_x(x);
		change_y(y);
	}
	// Draw 1st line
	y_dir_PutVal(0);
	for (i = 0; i <= radius*2; i++) {
		y_motor(1);
		change_y(i);
	}
	// Draw 2nd semicircle
	for (x = radius * 2; x >= 0; x--) {
		y = - sqrt(r2 - ((x - radius) * (x - radius)));
		control_circle_dir(x, y, x_before, y_before);
		x_before = x;
		y_before = y;
		Term1_SetColor(clWhite, clBlack);
		change_x(x);
		change_y(y);
	}
	// Draw 2nd line
	y_dir_PutVal(1);
	for (int i = 0; i <= radius*2; i++) {
		y_motor(1);
		change_y(i);
	}
	Term1_MoveTo(10, 17);
	Term1_SendStr("Oval has been drawn!");
	Term1_MoveTo(10, 19);
	Term1_SendStr("Press Q to Return");
	PWM1_SetRatio8(255);
}

// Select shape to draw
void draw_shapes() {
	do {
		__asm ("wfi");
		// This will draw a simple house
		if (c == 'h') {
			draw_House();
			c = '0';
			PWM1_SetRatio8(0);
		// This will draw an oval
		} else if (c == 'o') {
			draw_oval();
			c = '0';
			PWM1_SetRatio8(0);
		}
	} while (c != 'q');	// press q to go back
}
