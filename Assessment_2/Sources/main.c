/* ###################################################################
**     Filename    : main.c
**     Project     : Assessment_2_YangYang_Li
**     Processor   : MK22FN512VDC12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-10-23, 21:23, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


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
#include <Motors.h>
#include <Drawshapes.h>

volatile char c;
//volatile char buffer[100];
//volatile uint8 index = 0;
//volatile bool command_complete = false;

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
// Initialize the position and speed of the spindle
	int x = 0;
	int y = 0;
	int z = 0;
	int p = 0;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  GUI_main(x, y, z, p);
  GUI_Menu();
  PWM1_SetRatio8(255);
  /* Write your code here */
  /* For example: for(;;) { } */
  for (;;) {

  		__asm ("wfi");
  		// Manual Control
  		if (c == '1') {
  			GUI_clear();
  			GUI_manual(x, y, z, p);
  			manual_control(x, y, z, p);
  			GUI_clear();
  			GUI_main(x, y, z, p);
  			GUI_Menu();
  			c = 0;
  		// Draw shapes
  		} else if (c == '2') {
  			GUI_clear();
  			Term1_MoveTo(5, 9);
  			GUI_shapes();
  			draw_shapes();
  			GUI_clear();
  			GUI_main(x, y, z, p);
  			GUI_Menu();
  			PWM1_SetRatio8(255);
  			c = 0;
  		// Reset the position for all motors
  		} else if(c == '3'){
  			GUI_clear();
  			reset_position_GUI();
  			reset_position();
  			GUI_clear();
  			GUI_main(x, y, z, p);
  			GUI_Menu();
  			change_x(0);
  			change_y(0);
  			change_z(0);
  			c = 0;
  		}
  		// if 1 or 2 is not press shows a error messesage
//  		else {
//  			GUI_clear();
//  			Term1_SendStr("Error, try again!\n\r");
//  		}
}

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
