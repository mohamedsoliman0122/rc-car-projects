#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"

#define F_CPU  8000000
#include <util/delay.h>

/*************************** CONFIG 7 SEG **********************/
#define SEGMENT_PORT    PORTA

	void segment_dis(char n)
	{
		char arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
		PORTD=arr[n/10];
		PORTC=arr[n%10];
		//PORTA=arr[n]>>1;
	}
	void segment_dis_BCD(char n)//decoder
	{
		//PORTD=n;
		//PORTC=n;
		
		char d0=n%10;
		char d1=n/10;
		SEGMENT_PORT=d0|d1<<4;
	}
	void segment_dis_BCD_hex(char n)
	{
		SEGMENT_PORT=n;
	}
	void segment_dis_MLX(char n)//decoder
	{
		char arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
		char d0=n%10;
		char d1=n/10;
		
		SET_BIT(PORTC,6);
		SEGMENT_PORT=arr[d0]<<1;
		CLR_BIT(PORTC,7);
		_delay_ms(10);
		SET_BIT(PORTC,7);
		SEGMENT_PORT=arr[d1]<<1;
		CLR_BIT(PORTC,0);
		_delay_ms(10);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*************************************************project watch **********************************************/
	
	
/*#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"

#define F_CPU  8000000
#include <util/delay.h>


#define Repet 5
volatile long i=0;

int main(void)
	{
		
	    int min=59,sec=0,hour=1;
		int seg1,seg2,seg3,seg4,seg5,seg6;
		int delay;
	    char arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
			DDRC=0xff;
			DDRD=0xff;
			
		while(1)
		{

			for(sec=0;sec<60;sec++)
			{
				seg6=sec%10;
				seg5=sec/10;
				
				seg4=min%10;
				seg3=min/10;
				
				seg2=hour%10;
				seg1=hour/10;
			
			    for(delay=0;delay<25;delay++)  //5+10+5+5+5+10=40   1000/40=25
			    {
			    	PORTD=0xDF; //1101 1111
			    	PORTC=arr[seg6];
			    	_delay_ms(10);
				
			    	PORTD=0xEF; //1110 1111
			    	PORTC=arr[seg5];
			    	_delay_ms(5);
				
			    	PORTD=0xF7; //1111 0111
			    	PORTC=arr[seg4];
			    	_delay_ms(5);
				
			    	PORTD=0xFB; //1111 1011
			    	PORTC=arr[seg3];
			    	_delay_ms(5);
				
			    	PORTD=0xFD; //1111 1101
			    	PORTC=arr[seg2];
			    	_delay_ms(10);
				
			    	PORTD=0xFE; //1111 1110
				    PORTC=arr[seg1];
				    _delay_ms(5);
		    	 }
				 
				 if(sec==59)
				 {
					 min=min+1;
				 }
				 if (min==60)
				 {
					 hour=hour+1;
					 min=0;
				 }
				 if(hour==12)
				 {
					 hour=1;
				 }
	   
         	}
			
	   }	
	}		
			
*/