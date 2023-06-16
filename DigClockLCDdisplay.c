#define F_CPU 8000000
#define RS PA0
#define RW PA1
#define EN PA2

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

/*int main(void)
{
	DDRA=0x07;
	DDRB=0xff;
    
    while (1) 
    {
	   PORTB= 0x38;        //commands are sent to data pins
	   PORTA &=~ (1<<RS);  //RS is low
	   PORTA &=~ (1<<RW);  //RW is low
	   PORTA |= (1<<EN);   //En is high
	   _delay_ms(10);
	   PORTA &=~ (1<<EN);  //En is low
	   
	   PORTB= 0x06;        //command for print cursor
	   PORTA &=~ (1<<RS);  //RS is low
	   PORTA &=~ (1<<RW);  //RW is low
	   PORTA |= (1<<EN);   //En is high
	   _delay_ms(10);
	   PORTA &=~ (1<<EN);  //En is low
	   
	   PORTB= 0x0e;        //command for blinking cursor
	   PORTA &=~ (1<<RS);  //RS is low
	   PORTA &=~ (1<<RW);  //RW is low
	   PORTA |= (1<<EN);   //En is high
	   _delay_ms(10);
	   PORTA &=~ (1<<EN);  //En is low
	   
	   PORTB= 0x80;        //command for selecting row
	   PORTA &=~ (1<<RS);  //RS is low
	   PORTA &=~ (1<<RW);  //RW is low
	   PORTA |= (1<<EN);   //En is high
	   _delay_ms(10);
	   PORTA &=~ (1<<EN);  //En is low
	   
	   PORTB= 'H' ;        //data
	   PORTA |= (1<<RS);   //RS is high for sending data
	   PORTA &=~ (1<<RW);  //RW is low
	   PORTA |= (1<<EN);   //En is high
	   _delay_ms(10);
	   PORTA &=~ (1<<EN);  //En is low
	   
	   PORTB= ':' ;        //data
	   PORTA |= (1<<RS);   //RS is high for sending data
	   PORTA &=~ (1<<RW);  //RW is low
	   PORTA |= (1<<EN);   //En is high
	   _delay_ms(10);
	   PORTA &=~ (1<<EN);  //En is low
	   
	   PORTB= 'M' ;        //data
	   PORTA |= (1<<RS);   //RS is high for sending data
	   PORTA &=~ (1<<RW);  //RW is low
	   PORTA |= (1<<EN);   //En is high
	   _delay_ms(10);
	   PORTA &=~ (1<<EN);  //En is low
	   
	   PORTB= ':' ;        //data
	   PORTA |= (1<<RS);   //RS is high for sending data
	   PORTA &=~ (1<<RW);  //RW is low
	   PORTA |= (1<<EN);   //En is high
	   _delay_ms(10);
	   PORTA &=~ (1<<EN);  //En is low
	   
	   PORTB= 'S' ;        //data
	   PORTA |= (1<<RS);   //RS is high for sending data
	   PORTA &=~ (1<<RW);  //RW is low
	   PORTA |= (1<<EN);   //En is high
	   _delay_ms(10);
	   PORTA &=~ (1<<EN);  //En is low
	   	   
    }
}
*/
//functions 
void lcd_cmd(char cmd);
void lcd_data(char data);
void lcd_init(void);
void lcd_string(char *str);
void lcd_linebr(char row);
void lcd_clear(void);
void min(int n);
void min1(int m);
void hr(int p);
void hr1(int q);
void hr2(int r);


void lcd_cmd(char cmd)
{
	PORTB= cmd;
	PORTA &=~ (1<<RS);  //RS is low
	PORTA &=~ (1<<RW);  //RW is low
	PORTA |= (1<<EN);   //En is high
	_delay_ms(10);
	PORTA &=~ (1<<EN);  //En is low
}
void lcd_data(char data)
{
	PORTB= data;
	PORTA |= (1<<RS);   //RS is high for sending data
	PORTA &=~ (1<<RW);  //RW is low
	PORTA |= (1<<EN);   //En is high
	_delay_ms(10);
	PORTA &=~ (1<<EN);  //En is low
}
void lcd_init(void)
{
	lcd_cmd(0x38);  //8bit mode
	lcd_cmd(0x06);  //printing cursor
	lcd_cmd(0x0e);  //blinking cursor
	lcd_cmd(0x80);  //selecting row
}
void lcd_string(char *str)
{
	while (*str != '\0')      //Null value 
	{
		lcd_data(*str);
		str++;
	}
}
void lcd_linebr(char row)
{    
	char address=0x40+row;
	char faddress =(0x80|address);
	lcd_cmd(faddress);
}
void lcd_clear()

{

	lcd_cmd(0x01);                   // send hex 01 to Clear display
                                  // send hex 80 to Cursor at home position
}


int main(void)
{
	int r=0;
	DDRA = 0x07;
	DDRB = 0xff;
	lcd_init();  
	lcd_string("Hr:Min:Sec");
	lcd_linebr(0x02);  
	lcd_cmd(0xc0);     //creating second row
	lcd_string("00:00:00");
	lcd_cmd(0xc7);
	lcd_string(" ");
	while(1)
	{
		 int r=0;
		 hr1(r);
		 r++;  
	} 
}
void min(int n)
{
	while(n<6)
	{
		
		lcd_cmd(0xc7);
		lcd_string(" ");
		
		lcd_cmd(0xc7);
		lcd_string("1");
		_delay_ms(1000);
		
		lcd_cmd(0xc7);
		lcd_string(" ");
		
		lcd_cmd(0xc7);
		lcd_string("2");
		_delay_ms(1000);
		
		lcd_cmd(0xc7);
		lcd_string(" ");
		
		lcd_cmd(0xc7);
		lcd_string("3");
		_delay_ms(1000);
		
		lcd_cmd(0xc7);
		lcd_string(" ");
		
		lcd_cmd(0xc7);
		lcd_string("4");
		_delay_ms(1000);
		
		lcd_cmd(0xc7);
		lcd_string(" ");
		
		lcd_cmd(0xc7);
		lcd_string("5");
		_delay_ms(1000);
		
		lcd_cmd(0xc7);
		lcd_string(" ");
		
		lcd_cmd(0xc7);
		lcd_string("6");
		_delay_ms(1000);
		
		lcd_cmd(0xc7);
		lcd_string(" ");
		
		lcd_cmd(0xc7);
		lcd_string("7");
		_delay_ms(1000);
		
		lcd_cmd(0xc7);
		lcd_string(" ");
		
		lcd_cmd(0xc7);
		lcd_string("8");
		_delay_ms(1000);
		
		lcd_cmd(0xc7);
		lcd_string(" ");
		
		lcd_cmd(0xc7);
		lcd_string("9");
		_delay_ms(1000);
		
		lcd_cmd(0xc7);
		lcd_string(" ");
		
		lcd_cmd(0xc7);
		lcd_string("0");
		_delay_ms(1000);
		
		lcd_cmd(0xc6);
		lcd_string(" ");
		switch(n+1)
		{
			
			case 1:
			lcd_cmd(0xc6);
			lcd_string("1");
			_delay_ms(1000);
			break;
			
			case 2:
			lcd_cmd(0xc6);
			lcd_string("2");
			_delay_ms(1000);
			break;
			
			case 3:
			lcd_cmd(0xc6);
			lcd_string("3");
			_delay_ms(1000);
			break;
			
			case 4:
			lcd_cmd(0xc6);
			lcd_string("4");
			_delay_ms(1000);
			break;
			
			case 5:
			lcd_cmd(0xc6);
			lcd_string("5");
			_delay_ms(1000);
			break;
			
			case 6:
			lcd_cmd(0xc6);
			lcd_string("0");
			_delay_ms(1000);
			break;
			
			
			
		}
		
		
		
		n++;
		
		
	}
}
void min1(int m)
{
	while(m<10)
	{
		 int n=0;
		 min(n);
		 lcd_cmd(0xc4);
		 lcd_string(" ");
		 switch (m+1)
		 {
			 case 1:
			     lcd_cmd(0xc4);
			     lcd_string("1");
			     _delay_ms(1000);
			     break;
		     case 2:
		         lcd_cmd(0xc4);
		         lcd_string("2");
		         _delay_ms(1000);
		         break;
			 case 3:
			     lcd_cmd(0xc4);
			     lcd_string("3");
			     _delay_ms(1000);
			     break;
			 case 4:
			     lcd_cmd(0xc4);
			     lcd_string("4");
			     _delay_ms(1000);
			     break;
			 case 5:
			     lcd_cmd(0xc4);
		     	 lcd_string("5");
		     	 _delay_ms(1000);
			     break;
			 case 6:
			     lcd_cmd(0xc4);
			     lcd_string("6");
			     _delay_ms(1000);
			     break;
		     case 7:
			     lcd_cmd(0xc4);
			     lcd_string("7");
			     _delay_ms(1000);
			     break;
			 case 8:
			     lcd_cmd(0xc4);
			     lcd_string("8");
			     _delay_ms(1000);
			     break;
			 case 9:
			     lcd_cmd(0xc4);
			     lcd_string("9");
			     _delay_ms(1000);
			     break;
			 case 10:
			     lcd_cmd(0xc4);
			     lcd_string("0");
			     _delay_ms(1000);
			     break;
			 
			 
               
		 }
		 
		 
		 m++;  
	}
	
}

void hr(int p)
{
	while(p<6)
	{
		int m=0;
		min1(m);
		lcd_cmd(0xc3);
		lcd_string(" ");
		switch (p+1)
		{
			case 1:
			lcd_cmd(0xc3);
			lcd_string("1");
			_delay_ms(1000);
			break;
			case 2:
			lcd_cmd(0xc3);
			lcd_string("2");
			_delay_ms(1000);
			break;
			case 3:
			lcd_cmd(0xc3);
			lcd_string("3");
			_delay_ms(1000);
			break;
			case 4:
			lcd_cmd(0xc3);
			lcd_string("4");
			_delay_ms(1000);
			break;
			case 5:
			lcd_cmd(0xc3);
			lcd_string("5");
			_delay_ms(1000);
			break;
			case 6:
			lcd_cmd(0xc3);
			lcd_string("0");
			_delay_ms(1000);
			break;
			
			
			
			
		}
		
		
		p++;
	}
}
void hr1(int q)
{  
   int c=0;
   switch (c)
   {
	case 0:
	while(q<10)
	{
		int p=0;
		hr(p);
		lcd_cmd(0xc1);
		lcd_string(" ");
		switch (q+1)
		{
			case 1:
			lcd_cmd(0xc1);
			lcd_string("1");
			_delay_ms(1000);
			break;
			case 2:
			lcd_cmd(0xc1);
			lcd_string("2");
			_delay_ms(1000);
			break;
			case 3:
			lcd_cmd(0xc1);
			lcd_string("3");
			_delay_ms(1000);
			break;
			case 4:
			lcd_cmd(0xc1);
			lcd_string("4");
			_delay_ms(1000);
			break;
			case 5:
			lcd_cmd(0xc1);
			lcd_string("5");
			_delay_ms(1000);
			break;
			case 6:
			lcd_cmd(0xc1);
			lcd_string("6");
			_delay_ms(1000);
			break;
			case 7:
			lcd_cmd(0xc1);
			lcd_string("7");
			_delay_ms(1000);
			break;
			case 8:
			lcd_cmd(0xc1);
			lcd_string("8");
			_delay_ms(1000);
			break;
			case 9:
			lcd_cmd(0xc1);
			lcd_string("9");
			_delay_ms(1000);
			break;
			case 10:
			lcd_cmd(0xc1);
			lcd_string("0");
			_delay_ms(1000);
			break;
			
			
		}
		
		
		q++;
	}
	case 1:
		while(q<10)
		{
			int p=0;
			hr(p);
			lcd_cmd(0xc1);
			lcd_string(" ");
			switch (q+1)
			{
				case 1:
				lcd_cmd(0xc1);
				lcd_string("1");
				_delay_ms(1000);
				break;
				case 2:
				lcd_cmd(0xc1);
				lcd_string("2");
				_delay_ms(1000);
				break;
				case 3:
				lcd_cmd(0xc1);
				lcd_string("3");
				_delay_ms(1000);
				break;
				case 4:
				lcd_cmd(0xc1);
				lcd_string("4");
				_delay_ms(1000);
				break;
				case 5:
				lcd_cmd(0xc1);
				lcd_string("5");
				_delay_ms(1000);
				break;
				case 6:
				lcd_cmd(0xc1);
				lcd_string("6");
				_delay_ms(1000);
				break;
				case 7:
				lcd_cmd(0xc1);
				lcd_string("7");
				_delay_ms(1000);
				break;
				case 8:
				lcd_cmd(0xc1);
				lcd_string("8");
				_delay_ms(1000);
				break;
				case 9:
				lcd_cmd(0xc1);
				lcd_string("9");
				_delay_ms(1000);
				break;
				case 10:
				lcd_cmd(0xc1);
				lcd_string("0");
				_delay_ms(1000);
				break;
				
				
			}
			q++;
	}
	
	case 2:
	while(q<4)
	{
		int p=0;
		hr(p);
		lcd_cmd(0xc1);
		lcd_string(" ");
		switch (q+1)
		{
			case 1:
			lcd_cmd(0xc1);
			lcd_string("1");
			_delay_ms(1000);
			break;
			case 2:
			lcd_cmd(0xc1);
			lcd_string("2");
			_delay_ms(1000);
			break;
			case 3:
			lcd_cmd(0xc1);
			lcd_string("3");
			_delay_ms(1000);
			break;
			case 4:
			lcd_cmd(0xc1);
			lcd_string("0");
			_delay_ms(1000);
			break;
			
			
			
		}
		q++;
	}
   }
   c++;
}
void hr2(int r)
{
	while(r<2)
	{
		int q=0;
		hr1(q);
		lcd_cmd(0xc0);
		lcd_string(" ");
		switch (q+1)
		{
			case 1:
			lcd_cmd(0xc0);
			lcd_string("1");
			_delay_ms(1000);
			break;
			case 2:
			lcd_cmd(0xc0);
			lcd_string("2");
			_delay_ms(1000);
			break;
			case 3:
			lcd_cmd(0xc0);
			lcd_string("0");
			_delay_ms(1000);
			break;
			
			
		}
		
		
		r++;
	}
}