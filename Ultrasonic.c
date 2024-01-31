#include "Ultrasonic.h"

uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;

void Ultrasonic_edgeProcessing(void)
{	
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = ICU_getInputCaptureValue();
		/* Detect rising edge */
		ICU_setEdgeDetectionType(RISING);

	}
}

void Ultrasonic_Init(void)
{
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, PIN_OUTPUT);
	ICU_ConfigType Config_Ptr={F_CPU_8,RISING};
	ICU_init(&Config_Ptr);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_LOW);
}

void Ultrasonic_trigger(void)
{
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_LOW);

}

uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_trigger();
	while(g_edgeCount!=2);
	g_edgeCount=0;
	return (uint16) (g_timeHigh/58.8)+1; 
}




