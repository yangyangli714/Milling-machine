/*
 * Motors.c
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
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <GUI.h>
#include <Drawshapes.h>
extern volatile char c;
// Delay function - creates a delay period
void delay(int delay_ms) {
	word time;
	FC321_Reset();
	do{
		__asm("wfi");
		FC321_GetTimeMS(&time);
	}while(time < delay_ms);
}

// Setting the values of the drive IC
void starterup() {
	reset_SetVal();
	sleep_SetVal();
	mode_0_ClrVal();
	mode_1_ClrVal();
	mode_2_ClrVal();
}

// Stepper motor x function - allows stepper motor to rotate
void x_motor(int x){
	starterup();
	if (x < -5000 || x > 5000) { // need to be checked
		Term1_SetColor(clRed, clWhite);
		Term1_SendStr("Out of range");
		Term1_SetColor(clWhite, clBlack);
	}else {
		Term1_MoveTo(60, 3);
		Term1_EraseLine();
		for (int i = 0; i <= 20; i++) {
			x_step_NegVal();
			delay(1);
			x_step_NegVal();
			delay(1);
		}
	}
}

// Stepper motor y function - allows stepper motor to rotate
void y_motor(int y){
	starterup();
	if (y < -3000 || y > 3000) { // need to be checked
		Term1_SetColor(clRed, clWhite);
		Term1_SendStr("Out of range");
		Term1_SetColor(clWhite, clBlack);
	}else {
		Term1_MoveTo(60, 4);
		Term1_EraseLine();
		for (int i = 0; i <= 20; i++) {
			y_step_NegVal();
			delay(5);
			y_step_NegVal();
			delay(5);
		}
	}
}

// Stepper motor z function - allows stepper motor to rotate
void z_motor(int z){
	starterup();
	if (z < 0 || z > 100){ // need to be checked
		Term1_SetColor(clRed, clWhite);
		Term1_SendStr("Out of range");
		Term1_SetColor(clWhite, clBlack);
	}else {
		Term1_MoveTo(60, 5);
		Term1_EraseLine();
		for (int i = 0; i <= 20; i++) {
			z_step_NegVal();
			delay(5);
			z_step_NegVal();
			delay(5);
		}
	}
}

// Manual control function - allows to control the positions of x,y,z motor also control the speed of the spindle
void manual_control(int x, int y, int z, int p) {
	starterup();
	change_p(p);
	PWM1_SetRatio8(255);
	change_p(255-p);
	do {
		__asm ("wfi");
		// if press d move right
		if (c == 'd') {
			//move x_step +
			x_dir_PutVal(0);
			x_motor(x);
			// New x_step position in relation to set zero point
			x--;
			change_x(x);
			c = 0;
		}
		// if press a move left
		else if (c == 'a') {
			//move x_step -
			x_dir_PutVal(1);
			x_motor(x);
			// New x_step position in relation to set zero point
			x++;
			change_x(x);
			c = 0;
		// if press w move forward
		} else if (c == 'w') {
			// move y_step +
			y_dir_PutVal(1);
			y_motor(y);
			// New y_step position in relation to set zero point
			y++;
			change_y(y);
			c = 0;
		}
		// if press s move backward
		else if (c == 's') {
			//move y_step -
			y_dir_PutVal(0);
			y_motor(y);
			// New y_step position in relation to set zero point
			y--;
			change_y(y);
			c = 0;
		}
		// if press i move up
		else if (c == 'i') {
			//move z_step +
			z_dir_PutVal(0);
			z_motor(z);
			// New x_step position in relation to set zero point
			z--;
			change_z(z);
			c = 0;
		}
		// if press j move down
		else if (c == 'j') {
			//move z_step -
			z_dir_PutVal(1);
			z_motor(z);
			// New x_step position in relation to set zero point
			z++;
			change_z(z);
			c = 0;

		}
		//if press f spindle speed decreases
		else if (c == 'f') {
			clean_prompt();
			if (p < 255) {
				p += 51;
				PWM1_SetRatio8(p);
				change_p(255 - p);
				c = 0;
			} else {
				prompt_increase();

			}
		}
		//if press g spindle speed increases
		else if (c == 'g') {
			clean_prompt();
			if (p > 0) {
				p -= 51;
				PWM1_SetRatio8(p);
				change_p(255 - p);
				c = 0;
			} else {
				prompt_decrease();
			}
		}
	} while (c != 'q'); // press q to to back
}

// x_reset function - Reset the x position move to 0
void x_reset(){
	 x_dir_PutVal(0);
	  int i = 1;
	  while(i <= 9000){
		  x_step_NegVal();
		  delay(1);
		  x_step_NegVal();
		  delay(1);
		  i= i+1;
	  }
}

// y_reset function - Reset the y position move to 0
void y_reset(){
	 y_dir_PutVal(0);
	  int i = 1;
	  while(i <= 8000){
		  y_step_NegVal();
		  delay(1);
		  y_step_NegVal();
		  delay(1);
		  i= i+1;
	  }
}

// z_reset function - Reset the z position move to 0
void z_reset(){
	 z_dir_PutVal(0);
	  int i = 1;
	  while(i <= 1000){
		  z_step_NegVal();
		  delay(1);
		  z_step_NegVal();
		  delay(1);
		  i= i+1;
	  }
}

// reset_position function - reset the motor back to their position
void reset_position(){
	starterup();
	do {
		__asm ("wfi");
		// if press x reset x motor
		if (c == 'x') {
			x_reset();
			change_x(0);
			c = 0;
		// if press y reset y motor
		}else if (c == 'y') {
			y_reset();
			change_y(0);
			c = 0;
		// if press z move forward
		} else if (c == 'z') {
			z_reset();
			change_z(0);
			c = 0;
		}
	}while (c != 'q');	// press q to go back
}
