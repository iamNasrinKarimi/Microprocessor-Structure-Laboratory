/*
 * Az6.c 
 __________________________________________________________
 __________________________________________________________
 
    ***MICROPROCESSOR AND COMPUTER ARCHITECTURE LAB***  
    
 * Title:  Timer with LCD
 * Date:   2020.11.18
 * Author: Nasrin Kaimi 97236081      Group:No.22
 * Professor: Dr. Hadi Asharioun
 * Teacher Assiatant: Ms.Solmaz Fattahi 
 * Shahid Beheshti University - Paradise of Shahid Abbaspour


 -chip type: ATmega32
 _Clock frequency of Core: 8.000 MHz
 _Application: Proteus
 _Delay: 1000 ms (1 s) 
 __________________________________________________________
 __________________________________________________________
*/
#include <mega32.h> /*ketab khane atmega 32 ro tariif kardim */
#include <delay.h>  /* ketabkhane delay ra tarif kardim ta be rahati az tabe an estefade konim*/
#include <stdio.h>  /*ketabkhane stdio.h ra baraye print va function variable va,,, farkhani mikonim*/
// Alphanumeric LCD functions
#include <alcd.h>   /*ketab khane LCD ro tariif kardim */

// Declare your global variables here
interrupt [TIM0_OVF] void timer0_ovf_isr(void) /*tavabei az noe void moarefi mikonim*/
{
// Reinitialize Timer 0 value
TCNT0=0x83;
}
void main(void) /*tabe aslie barname c tarif mishavad*/
{
// Declare your local variables here
/*chon timer ma shamele 3 bakhshe second, minute and hour ast va har kodam az in ha shamele 2 ragham hastand*/
int sec0=0;     /*motaghayere sanie aval az rast ra az noe intiger moshakhas mikonad va be an meghdare avalie 0 ra midahad*/
int min0=0;     /*motaghayere minute aval az rast ra az noe intiger moshakhas mikonad va be an meghdare avalie 0 ra midahad*/
int hr0=0;      /*motaghayere hour aval az rast ra az noe intiger moshakhas mikonad va be an meghdare avalie 0 ra midahad*/
int sec1=0;     /*motaghayere sanie dovom az rast ra az noe intiger moshakhas mikonad va be an meghdare avalie 0 ra midahad*/
int min1=0;     /*motaghayere sanie dovom az rast ra az noe intiger moshakhas mikonad va be an meghdare avalie 0 ra midahad*/
int hr1=0;      /*motaghayere sanie dovom az rast ra az noe intiger moshakhas mikonad va be an meghdare avalie 0 ra midahad*/
char time[9];   /*araye time az noe char ra tarii kardim*/
#include <mega32.h>
 /*ba estefade az wizard input va out put hara mortabet ba lcd ghrr dadim va natije ra paste kardim dar code*/
// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
// Declare your local variables here
// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);
// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);
// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);
// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x00;
// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;
// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);
// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
// USART initialization
// USART disabled
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
SFIOR=(0<<ACME);
// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);
// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 3
// RD - PORTD Bit 7
// EN - PORTD Bit 6
// D4 - PORTB Bit 4
// D5 - PORTB Bit 5
// D6 - PORTB Bit 6
// D7 - PORTB Bit 7
// Characters/line: 16
lcd_init(16);

while (1)  /*halghei ke hamishe dorost ast*/
      {
       for(hr1=0; hr1<10; hr1++){    /*baraye por arzeshtarin bite saat halghe tariif kardim k az 0 ta 9 yeki yeki be an ezafe shavad*/
       for(hr0=0; hr0<10; hr0++){    /*baraye kam arzesh tarin bite saat halghe tariif kardim k az 0 ta 9 yeki yeki be an ezafe shavad*/
       for(min1=0; min1<6; min1++){  /*baraye por arzeshtarin bite minute(dahgan) halghe tariif kardim k az 0 ta 6 yeki yeki b an ezafe shavad chon har saat 60 minute ast*/
       for(min0=0; min0<10; min0++){ /*baraye kam arzesh tarin bite minute(yekan) halghe tariif kardim k az 0 ta 9 yeki yeki be an ezafe shavad*/
       for(sec1=0; sec1<6; sec1++){  /*baraye por arzeshtarin bite second(dahgan) halghe tariif kardim k az 0 ta 6 yeki yeki be an ezafe shavad chon har daghighe 60 sanie ast*/
       for(sec0=0; sec0<10;sec0++){  /*baraye kam arzesh tarin bite sanie (yekan) halghe tariif kardim k az 0 ta 9 yeki yeki be an ezafe shavad*/    
       sprintf(time,"%d%d:%d%d:%d%d", hr1, hr0, min1, min0, sec1, sec0); /*time is converted to string va display mikonad ebarat ra*/
       //chon addad ema az noe intiger ast az %d estefade mikonim
       lcd_gotoxy(4,0);             /*be satre aval va sotoon 4om miravad (chon mn mikhastam ke time dar vasat namayesh dde shavad)*/
       lcd_puts(time);              /*zaman ra neshan midahad*/ 
       delay_ms(1000);              /*takhir ra ba estefade az tabe an be asani be meghdare  sanie ya haman 1000m sanie tariif moknim*/
       if (sec0%2==0){              /*agar adad shomareshe yekan zooj shavad yani baghimande an bar 2 sefr shavad*/
       lcd_gotoxy(2,1);             /*be satre dovom rafte va az sotoone dovom*/
       lcd_putsf("Nasrin Karimi");  /*namayesh midahad ebarate morede nazar ra*/
       }
       else                         /*dar gheire in soorat yani zamani k sefr nashavad baghi mande yani adad fard bashad*/
       {
       lcd_gotoxy(2,1);             /*be satre dovom rafte va az sotoone dovom*/
       lcd_putsf("  97236081   ");  /*namayesh midahad ebarate morede nazar ra*/
       }             
       }
       }
       }
       }
       }
       }
       }
       }