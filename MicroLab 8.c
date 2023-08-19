/*
 * Az8.c 
 __________________________________________________________
 __________________________________________________________
 
    ***MICROPROCESSOR AND COMPUTER ARCHITECTURE LAB***  
    
 * Title:  Tempreture Sensor (lm35)-7segment-DC motor
 * Date:   2020.12.06
 * Author: Nasrin Kaimi 97236081      Group:No.22
 * Professor: Dr. Hadi Asharioun
 * Teacher Assiatant: Ms.Solmaz Fattahi 
 * Shahid Beheshti University - Paradise of Shahid Abbaspour


 -chip type: ATmega32
 _Clock frequency of Core: 8.000 MHz
 _Application: Proteus
 _7-SEG-Type: Cathode 4-Digit
 _LM35 
 __________________________________________________________
 __________________________________________________________
*/
#include <mega32.h>                  /*ketab khane atmega 32 ro tariif kardim */
#include <delay.h>                   /* ketabkhane delay ra tarif kardim ta be rahati az tabe an estefade konim*/
// Declare your global variables here
//========================================================================================================================
/*dar neveshtane in barname az code wizard estefade shode ast, be in tartib k ebteda az pooshe wizard ba entekhabe
gozine Analog to Digital Converter ba faal kardane ADC be taiine moshakhasat pardakhtim,
clock 500MHz entkhab shod,ADC enabled,Int.,cap.on AREF, Use 8 bits, ADC stopped; pas az an dar ghesmate port ha
be Input va Output budan hara moshakhas kardim, dar nahat barname ra program karde va mohtava ra copy va paste kardim dar
fazaye barname*/
//========================================================================================================================
// Voltage Reference: Int., cap. on AREF
#define ADC_VREF_TYPE ((1<<REFS1) | (1<<REFS0) | (1<<ADLAR))

// Read the 8 most significant bits
// of the AD conversion result
void sevensegment(int n);            /*tabe 7segment ra farakhani kardim*/
unsigned char read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCH;
}

void main(void)                      /*tabe aslie barname c tarif mishavad*/
{
// Declare your local variables here
       int a=0;                      /*moteghayeri az noe integer tarif kardim ke meghdar ADC dar an gharar khahad gereft*/
// Input/Output Ports initialization
                                    /*port A input va baghie port ha output hastand*/
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
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

// ADC initialization
// ADC Clock frequency: 500.000 kHz
// ADC Voltage Reference: Int., cap. on AREF
// ADC Auto Trigger Source: ADC Stopped
// Only the 8 most significant bits of
// the AD conversion result are used
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

while (1)                      /*tabe i ke hamishe dorost ast*/
      {
      a=read_adc(0);           /*meghdar adad dar adc khane aval ke hama porta.0 ast dar integer a ghrr migird*/
      sevensegment(a);         /*adad dar tabe 7 segment baraye namayesh ghrr migirad*/
      if(a>=30)                /*agar dama az 30 bishtar shavad*/
      {
      PORTD.0=1;               /*portd.0=1 mishavad yani motor DC shoroo be harekat mikonad*/
      }
      if(a==25)                /*agar dama be 25 beresad*/
      {PORTD.0=0;              /*Motor DC motafaghef mishavad*/
      }
      }
}
unsigned char ca_seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; /*baraye rahati kar code HEX*/
                              
void sevensegment(int n)       /*tarz kare kar kardane 7seg ra dar yek tabe tarif kardim ta be rahti dar soorate niaz farakhani konim*/
{      
    int i, j,r;                /*moarefie motaghar haye i,j,r az noe intiger*/
    j = n / 10;                /*adade n taghsim bar 10 mishavad ta meghdar j k haman DAHGAN ast bedast ayad*/       
    i = n % 10;                /*meghdare i haman baghimande taghsim n bar 10 ast neshangare YEKAN ast*/      
    PORTC.6=PORTC.7=1;         /*ba 2 namayeshgare samte chap kari nadarim pas an hara khamoosh mikonim ba yek kardane port ha 
                                chon az noe cathode hastand( dar anode port sefr mishavad baraye khamoosh kardan)*/                      
               
    for(r=0;r<25;r++)          /*chon nmitavan dar ane vahed dar 7seg cheragh ha roshan bashand chon adade chand raghami*/    
    {                          /*daraye paye haye moshtarake a,b,c,d,e,f,g,dp hastand pas yek haghle tarif kardim ta dar an cheragh ha*/   
                               /*cheshmak bazanand va delay ra anghadr kam entekhab mikonikm ta cheshm ensane ghader be tashkhis an nabashad*/
        PORTC.4=0; PORTC.5=1;  /*dahgan khamoosh ast va yekan faal*/ 
        PORTB=ca_seg[i];       /*az araye baraye neshan dadane adade yekan estefade mishavad*/
        delay_ms(1);           /*takhir besya kam b andaze 1 ms bara cheshmak zadan*/ 
        PORTC.4=1; PORTC.5=1;  /*daghan faal shode yekan faal shode*/
        PORTC.4=1; PORTC.5=0;  /*dahgan faal shode yekan gheire faal mishavad*/
        PORTB=ca_seg[j];       /*az araye baraye neshan dadane adade dahgan estefade mishavad*/
        delay_ms(1);           /*takhir besya kam b andaze 1 ms bara cheshmak zadan*/
        PORTC.4=1; PORTC.5=1;  /*daghan faal shode yekan faal shode*/
        
    }
}