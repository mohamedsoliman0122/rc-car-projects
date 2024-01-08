

#include "StdTypes.h"
#include "ADC.h"
#include "Sensors.h"

/*******************Sensors (LM 35) ***********************/


u16 TEMP_Read(void)
{
	u16 volt=ADC_ReadVolt(LM53_CH);
	u16 temp=volt;
	return temp;
}