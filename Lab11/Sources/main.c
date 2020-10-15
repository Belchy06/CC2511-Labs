/* ###################################################################
**     Filename    : main.c
**     Project     : Lab11
**     Processor   : MK22FN512VDC12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-10-10, 08:07, # CodeGen: 0
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
#include "FC.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
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
#include <stdio.h>
#include "dotproduct.h"

// Input data
// Fixed point numbers using Q20 format, i.e. there is an implied denominator of 2^20
const int Q = 20;
unsigned int vecA [200] =
	{864183U,228833U,104483U,649599U,108858U,837877U,946786U,327693U,295268U,7111U,
	519959U,1036499U,773787U,325813U,629573U,819651U,116951U,607471U,912650U,723283U,
	254773U,359370U,571935U,70855U,430386U,249049U,512726U,845222U,396202U,543139U,
	99193U,953255U,217716U,400624U,692354U,795212U,181476U,542512U,1043688U,741982U,
	84481U,45412U,515014U,468290U,510445U,173949U,378176U,923504U,780510U,437016U,
	951430U,98888U,190134U,992569U,105748U,406887U,303274U,76637U,204061U,437765U,
	307156U,736246U,251357U,1006090U,320300U,162441U,582493U,828945U,465434U,1044192U,
	457794U,319230U,258485U,1007498U,233708U,414826U,235431U,283141U,438768U,1046202U,
	955285U,577164U,625303U,82990U,604647U,941802U,485816U,417749U,109535U,683919U,
	1039873U,711011U,449291U,686609U,617344U,781247U,672001U,528143U,983608U,634749U,
	669960U,736790U,902771U,398105U,746715U,548951U,381146U,455791U,720998U,237871U,
	1026560U,1023065U,303577U,354873U,1044848U,827296U,833536U,663087U,850868U,469860U,
	870961U,132816U,538201U,750708U,260200U,557738U,400776U,840708U,703449U,1030603U,
	982328U,604265U,84081U,433927U,189630U,1043995U,545664U,928286U,679741U,488902U,
	99909U,1014834U,650234U,163581U,417718U,925374U,565197U,570086U,463945U,192671U,
	261337U,298961U,555231U,587032U,435312U,949675U,319966U,681333U,302810U,267651U,
	375582U,845066U,565105U,618727U,242370U,106898U,675959U,1027750U,106664U,196992U,
	9841U,879025U,504724U,491290U,952683U,437411U,570570U,732964U,82890U,534161U,
	510550U,897456U,644250U,123119U,636352U,172155U,418409U,558217U,917725U,691052U,
	825886U,132147U,550475U,943173U,114383U,665396U,84773U,431208U,747251U,105301U};

unsigned int vecB [200] =
	{849291U,668792U,941694U,652027U,434747U,679014U,513036U,98310U,668282U,996421U,
	499517U,632087U,620215U,236204U,700903U,164156U,811861U,223402U,177339U,761007U,
	268634U,170673U,656175U,262928U,275753U,884923U,416726U,109659U,203271U,380707U,
	917016U,628905U,270651U,375839U,930653U,944275U,469712U,281911U,580718U,187535U,
	901463U,243245U,176271U,28021U,338093U,582132U,864581U,843315U,25594U,389552U,
	515763U,488691U,43740U,646973U,606111U,313324U,456829U,143270U,314280U,798359U,
	37017U,282591U,1044663U,468657U,160207U,929278U,32905U,121671U,263041U,796577U,
	941946U,234273U,706005U,858559U,995025U,916786U,412862U,982476U,458118U,170417U,
	324871U,714195U,979428U,993410U,628184U,994967U,423644U,43026U,308098U,33491U,
	906508U,453558U,97317U,144485U,253725U,233842U,909891U,801297U,361459U,403471U,
	623761U,561115U,349759U,896200U,278548U,979307U,408771U,716246U,288369U,29316U,
	986304U,559908U,703776U,637047U,787348U,1028991U,763017U,898966U,1040023U,796352U,
	153135U,342156U,30184U,728289U,1005329U,764461U,772543U,183093U,372674U,602564U,
	482288U,874224U,855055U,339688U,484111U,706697U,624140U,140915U,20439U,131186U,
	234122U,470955U,560497U,1038499U,752193U,1027665U,56348U,667811U,1007033U,283035U,
	995526U,946061U,204104U,769604U,183355U,110248U,329371U,365707U,418342U,297709U,
	329160U,753171U,990534U,92053U,293113U,625118U,868677U,820146U,584307U,38039U,
	701887U,890229U,68645U,378290U,270586U,453610U,320939U,1013542U,136245U,227998U,
	936791U,651906U,417504U,373387U,677981U,768702U,767244U,1004720U,48187U,444975U,
	9455U,737993U,818825U,592278U,24427U,7931U,1037009U,211442U,863333U,378484U};

// Correct answers
const int answer_fixed_point = 53446101;
const float answer_floating_point = 50.970173;

// Buffer for string formatting
#define OUTPUT_BUF_SIZE 100
char output_buf [OUTPUT_BUF_SIZE];

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  Term1_SendStr("-----------\r\n");
  snprintf(output_buf, OUTPUT_BUF_SIZE, "correct answer:        %i (= %f)\r\n", answer_fixed_point, answer_floating_point);
  Term1_SendStr(output_buf);

  // Test the C implementation

  // Repeat it 5000 times for more accurate timing
  int i;
  volatile unsigned int answer;
  word timeMS;
  FC_Reset();
  for (i = 0; i < 5000; i++) {
	  answer = c_dotproduct(Q, 200, vecA, vecB);
  }
  FC_GetTimeMS(&timeMS);
  snprintf(output_buf, OUTPUT_BUF_SIZE, "c_dotproduct answer:   %i (= %f)\r\n", answer, (float)answer/(1 << Q));
  Term1_SendStr(output_buf);
  snprintf(output_buf, OUTPUT_BUF_SIZE, "c_dotproduct error:    %i (= %f)\r\n", answer-answer_fixed_point, (float)(answer-answer_fixed_point)/(1 << Q));
  Term1_SendStr(output_buf);
  snprintf(output_buf, OUTPUT_BUF_SIZE, "c_dotproduct time:     %i ms\r\n", timeMS);
  Term1_SendStr(output_buf);

  // Test the ASM implementation

  // Repeat it 5000 times for more accurate timing
  FC_Reset();
  for (i = 0; i < 5000; i++) {
	  answer = asm_dotproduct(Q, 200, vecA, vecB);
  }
  FC_GetTimeMS(&timeMS);
  snprintf(output_buf, OUTPUT_BUF_SIZE, "asm_dotproduct answer: %i (= %f)\r\n", answer, (float)answer/(1 << Q));
  Term1_SendStr(output_buf);
  snprintf(output_buf, OUTPUT_BUF_SIZE, "asm_dotproduct error:  %i (= %f)\r\n", answer-answer_fixed_point, (float)(answer-answer_fixed_point)/(1 << Q));
  Term1_SendStr(output_buf);
  snprintf(output_buf, OUTPUT_BUF_SIZE, "asm_dotproduct time:   %i ms\r\n", timeMS);
  Term1_SendStr(output_buf);
  Term1_SendStr("\r\n");

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
