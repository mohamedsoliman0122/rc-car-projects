#include "Calculator_Project.h"

void Calculator_Project(void)
{
	DIO_Init();
	LCD_Init();
	s8 key, operation_flag = 0,minus_flag =0,plus_flag = 0, times_flag = 0, divded_flag = 0,first_itration = 0, negativ_flag = 0;
	s32 num = 0,  answer = 0  ;
	LCD_GoToWriteString(0,0,"My Name Is :");
	LCD_GoToWriteString(1,0,"Abdel-rahman");
	_delay_ms(2000);
	LCD_Clear();
	LCD_GoToWriteString(0,0,"Welcome To My :");
	LCD_GoToWriteString(1,0,"CalculatorProject");
	_delay_ms(3000);
	LCD_Clear();
	LCD_GoToWriteString(0,0,"Let's Start :)");
	_delay_ms(1500);
	LCD_Clear();
	while(1)
	{
		key = KEYPAD_GetKey();
		if(key != NO_KEY)
		{
			if ((answer > 0 || answer < 0 ) && (operation_flag == 1) && ((key == '/')||(key == '*')||(key == '+')||(key == '-')))
			{
				LCD_Clear();
				LCD_GoToWriteNumber(0,0,answer);
				operation_flag = 0 ;
			}
			else if ((answer > 0 || answer < 0 ) && (operation_flag == 1) && (key >= '0' && key <= '9'))
			{
				LCD_Clear();
				num = 0;
				answer =0 ;
				first_itration = 0 ;
				divded_flag =0 ;
				times_flag = 0;
				minus_flag = 0 ;
				plus_flag = 0 ;
				operation_flag =0 ;
				continue;
			}
			LCD_WriteChar(key);
			if(key >= '0' && key <= '9')
			{
				num = num * 10 + (key -'0');
			}
			else if (key == '/')
			{
				divded_flag = 1 ;
				first_itration = 1;
			}
			else if (key == '*')
			{
				times_flag = 1 ;
				first_itration = 1 ;
			}
			else if (key == '-')
			{
				if((num == 0 ) && (answer == 0))
				{
					negativ_flag = 1 ;
					first_itration = 0  ;
				}
				else
				{
					minus_flag = 1 ;
					first_itration = 1  ;
				}
			}
			else if (key == '+' )
			{
				plus_flag = 1 ;
				first_itration = 1 ;
			}
			else if (key == '=')
			{
				if(divded_flag == 1)
				{
					if(num == 0)
					{
						LCD_Clear();
						LCD_WriteString("Math Error");
						_delay_ms(500);
						LCD_Clear();
						num = 0;
						answer =0 ;
						first_itration = 0 ;
						divded_flag =0 ;
						times_flag = 0;
						minus_flag = 0 ;
						plus_flag = 0 ;
						operation_flag =0 ;
						continue;
					}
					else
					{
						answer = answer / num ;
						divded_flag = 0;
					}
				}
				else if(times_flag  == 1)
				{
					answer = answer * num ;
					times_flag = 0;
				}
				else if(minus_flag == 1 )
				{

					answer = answer - num ;
					minus_flag = 0;
				}
				else if(plus_flag == 1)
				{
					answer = answer + num ;
					plus_flag = 0;
				}
				LCD_GoToWriteNumber(1,0,answer);
				operation_flag = 1 ;
				num = 0;
			}
			else if (key == 'C')
			{
				LCD_Clear();
				num = 0;
				answer =0 ;
				first_itration = 0 ;
				divded_flag =0 ;
				times_flag = 0;
				minus_flag = 0 ;
				plus_flag = 0 ;
				operation_flag = 0 ;
			}
			if((first_itration == 1) && (answer == 0))
			{
				if (negativ_flag == 1)
				{
					num = num * (-1);
					negativ_flag = 0 ;
				}
				answer = num ;
				num = 0;
				first_itration = 2 ;
			}
		}

	}
}
