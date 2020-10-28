/*
 * GUI.c
 *
 *  Created on: 2020Äê10ÔÂ23ÈÕ
 *      Author: liyangyang
 */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <Motors.h>
#include <Drawshapes.h>

extern volatile char c;

// main GUI - give the information
void GUI_main(int x, int y, int z, int p) {
	// Clear GUI
	Term1_Cls();
	// Display main GUI
	Term1_MoveTo(15, 2);
	Term1_SetColor(clBlack, clWhite);
	Term1_SendStr("CC2511 A2 Group12 ");
	Term1_SetColor(clWhite, clBlack);
	Term1_MoveTo(12, 4);
	Term1_SendStr("Milling Machine GUI");
	Term1_MoveTo(12, 5);
	Term1_SendStr("Alvin, YangYang, Kevin, Eugen");

	// Shows the current position
	Term1_MoveTo(50, 2);
	Term1_SendStr("Current position:");
	Term1_MoveTo(50, 3);
	Term1_SendStr("X: ");
	Term1_MoveTo(55, 3);
	Term1_SendNum(x);
	Term1_MoveTo(50, 4);
	Term1_SendStr("Y: ");
	Term1_MoveTo(55, 4);
	Term1_SendNum(y);
	Term1_MoveTo(50, 5);
	Term1_SendStr("Z: ");
	Term1_MoveTo(55, 5);
	Term1_SendNum(z);

	// Shows the current speed for spindle
	Term1_MoveTo(50, 6);
	Term1_SendStr("PWM: ");
	Term1_MoveTo(55, 6);
	Term1_SendNum(p);
}

// Option Menu - choose different keys to do different options
void GUI_Menu() {
	Term1_MoveTo(5, 10);
	Term1_SetColor(clWhite, clBlack);
	Term1_SendStr("Select the following options:");
	Term1_MoveTo(7, 12);
	Term1_SendStr("Manual Control   =====>>   press 1");
	Term1_MoveTo(7, 14);
	Term1_SendStr("Drawing shapes   =====>>   press 2");
	Term1_MoveTo(7, 16);
	Term1_SendStr("Reset positions  =====>>   press 3");
	Term1_MoveTo(7, 20);
	Term1_SendStr(">>>");
}

// GUI for manual control - display the GUI for manual control option
void GUI_manual() {
	// Display manual movement instructions
	Term1_MoveTo(5, 11);
	Term1_SendStr("Use the following key to control the milling machine");
	// Control the x axis
	Term1_MoveTo(5, 12);
	Term1_SendStr("D =====>> Move to left  ( + X axis )");
	Term1_MoveTo(5, 13);
	Term1_SendStr("A =====>> Move to right ( - X axis )");
	// Control the y axis
	Term1_MoveTo(5, 14);
	Term1_SendStr("W =====>> Move forward  ( + Y axis )");
	Term1_MoveTo(5, 15);
	Term1_SendStr("S =====>> Move backward ( - Y axis )");
	// Control the z axis
	Term1_MoveTo(5, 16);
	Term1_SendStr("I =====>> Move upward   ( + Z axis )");
	Term1_MoveTo(5, 17);
	Term1_SendStr("J =====>> Move downward ( - Z axis )");
	// Control the spindle speed
	Term1_MoveTo(5, 18);
	Term1_SendStr("F =====>>    - Spindle Speed");
	Term1_MoveTo(5, 19);
	Term1_SendStr("G =====>>    + Spindle Speed");
	// Back to menu
	Term1_MoveTo(5, 20);
	Term1_SendStr("Q =====>>    Return to menu");
}

// Clear GUI
void GUI_clear() {
	for (int i = 10; i <= 28; i++) {
		Term1_MoveTo(5, i);
		Term1_EraseLine();
	}
}

// Option Menu - choose different keys to draw different shapes
void GUI_shapes() {
	Term1_MoveTo(5, 10);
	Term1_SendStr("Choose the following key to draw different shapes ");
	Term1_MoveTo(5, 12);
	Term1_SendStr("H =====>>    House");
	Term1_MoveTo(5, 13);
	Term1_SendStr("O =====>>    Oval");
	Term1_MoveTo(5, 14);
	Term1_SendStr("Q =====>>    Return to menu");
}

// Clean the promotion line
void clean_prompt() {
	Term1_MoveTo(50, 7);
	Term1_EraseLine();
	Term1_MoveTo(50, 8);
	Term1_EraseLine();
}

// Promotion for requiring to deduct steps
void prompt_decrease() {
	Term1_MoveTo(50, 7);
	Term1_SendStr("Maximum spindle speed");
	Term1_MoveTo(50, 8);
	Term1_SendStr("Please decrease it! =====>> G");
	Term1_SetColor(clWhite, clBlack);
}

// Promotion for requiring to add steps
void prompt_increase() {
	Term1_MoveTo(50, 7);
	Term1_SendStr("Minimum spindle speed");
	Term1_MoveTo(50, 8);
	Term1_SendStr("Please increase it! =====>> H");
	Term1_SetColor(clWhite, clBlack);
}

// Change the current position for x,y,z,p
void change_x(int x) {
	Term1_MoveTo(55, 3);
	Term1_SendStr("     ");
	Term1_MoveTo(55, 3);
	Term1_SendNum(x);
}
void change_y(int y) {
	Term1_MoveTo(55, 4);
	Term1_SendStr("     ");
	Term1_MoveTo(55, 4);
	Term1_SendNum(y);
}
void change_z(int z) {
	Term1_MoveTo(55, 5);
	Term1_SendStr("     ");
	Term1_MoveTo(55, 5);
	Term1_SendNum(z);
}
void change_p(int p) {
	Term1_MoveTo(55, 6);
	Term1_SendStr("    ");
	Term1_MoveTo(55, 6);
	Term1_SendNum(p);
}

void reset_position_GUI(){
	Term1_MoveTo(5, 10);
	Term1_SendStr("Choose the following key to draw different shapes ");
	Term1_MoveTo(5, 12);
	Term1_SendStr("X =====>>    Reset x motor");
	Term1_MoveTo(5, 13);
	Term1_SendStr("Y =====>>    Reset y motor");
	Term1_MoveTo(5, 14);
	Term1_SendStr("Z =====>>    Reset z motor");
	Term1_MoveTo(5, 15);
	Term1_SendStr("Q =====>>    Return to menu");
}
