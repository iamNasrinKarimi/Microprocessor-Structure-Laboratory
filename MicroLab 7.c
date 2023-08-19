/*
 * Az7.c 
 __________________________________________________________
 __________________________________________________________
 
    ***MICROPROCESSOR AND COMPUTER ARCHITECTURE LAB***  
    
 * Title:  PWM - 7 SEG - LED - KEYPAD
 * Date:   2020.11.25
 * Author: Nasrin Kaimi 97236081      Group:No.22
 * Professor: Dr. Hadi Asharioun
 * Teacher Assiatant: Ms.Solmaz Fattahi 
 * Shahid Beheshti University - Paradise of Shahid Abbaspour


 -chip type: ATmega32
 _Clock frequency of Core: 8.000 MHz
 _Application: Proteus
 _7-SEG-Type: Anode 4-Digit
 _KeyPad: 3*4
 __________________________________________________________
 __________________________________________________________
*/
#include <mega32.h>              /*ketab khane atmega 32 ro tariif kardim */
#include <delay.h>               /* ketabkhane delay ra tarif kardim ta be rahati az tabe an estefade konim*/

//---------------------------------------------------------------------------------------------------------------------------
/* dar neveshtane in barname az bakhshe timer va counter wizard moshakhase haye morede nazar baraye azmayesh ra vared kardim*/
/*az jomle in ke chon dar soal gote shode bood k frequency 50 Hz bashad yani dore tanavobe 20 ms*/
/*A va B dashtim k A az noe not interrupt va B az noe interrupt entkhab kardim, clock value ra 31.250 kHz gharar dadim*/
/*andazeh clock value tasiri dar pasokh nakhahad dasht va ba nesbat ama mikonand*/
//---------------------------------------------------------------------------------------------------------------------------
/*dar ebteda motaghayer hara moarefi va moshakhas mikonim (ebteda 7-seg)*/
char num[20]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; /*baraye rahati kar code HEX an ra dar araye haii ghara midahim*/
char M[20]={0xFE,0xFD,0xFB,0xF7};  /*arayeh haye seven segment ra moshakhas mikonim*/
void main(void)                    /*tabe aslie barname c tarif mishavad*/
{
/*motaghayer haye halghe aslie main void ra moshakhas mikonim*/
int i,j,d=0;                         /*2 moteghayere i , j ra az noe intiger moarefi mikonim*/
int satr=0;                          /*moteghayeri be onvane satr moarefi mikonim az noe intiger*/
int sotoon=-1;                       /*moteghayeri be onvane sotoon moarefi mikonim az noe intiger*/
int T,K;                             /*moteghayeri be onvane T va K moarefi mikonim az noe intiger*/
int place=-1;                        /*moteghayeri be onvane place moarefi mikonim az noe intiger*/
//----------------------------------------------------------------------------------------------------------------------------
/*dar in bakhsh az barname meghdar data haye be dast amade az code wizarde barname paste shode and*/
// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=T Bit6=P Bit5=P Bit4=P Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTA=(0<<PORTA7) | (1<<PORTA6) | (1<<PORTA5) | (1<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

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

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 31.250 kHz
// Mode: Fast PWM top=0x01FF
// OC1A output: Non-Inverted PWM
// OC1B output: Inverted PWM
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 16.384 ms
// Output Pulse(s):
// OC1A Period: 16.384 ms Width: 0 us
// OC1B Period: 16.384 ms Width: 16.384 ms
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (1<<COM1B0) | (1<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);
//---------------------------------------------------------------------------------------------------------------------------
while (1)                       /* halghei ke hamishe tekrar mishavad ra tariif mikonim*/
      {
     for(satr=0;satr<4;satr++)  /*yek halghe i tariif kardim k baraye inke az key pad matrisi tashkhis dahad*/
     /*dar in bakhsh az barname code i neshe shode ast baraye tashkhis adade vared shode az sooye karbar baraye pardazesh haye badi*/
     /*be in goone ke yek port kamele micro ra be tore kamel be key pad ekhtsas dade va be do bakhsh tabdil mikonim*/
     /*va voroodi khorooji mikonim va ba sefro yek kardn satro sotoon va be tartib ba azjam inkar mitavan tashkhis dad k*/
     /*dar kodam satr ya sotoon button feshar dade shode ast*/
     {
     PORTA=M[satr];        /*da inja port a ke takhsis dade shde be Key pad adadi ra daryaft mikonad az ye satri va ma araye an satr ra dar nazar migirim*/
     if(PINA.4==0)         /*inja be bakhshe sefr va yek shodan baraye tashkhis adade var shode ast*/
     {
     sotoon=3;             /*be meghdare sotoon adade 3 midahad*/
     T=satr;               /*meghdar satr ra dar T ghara midahad*/
     while(PINA.4==0){};   /*halghe while k pina.4 dar an barabre sefr ast*/
     K=0;                 /*be k adade sefr midahad*/
     break;               /*az barname kharej mishavad*/
     }
     if(PINA.5==0)        /*inbar agar pina.5 sefr shavad*/
     {
     sotoon=2;            /*be meghdare sotoon adade 2 midahad*/
     T=satr;              /*meghdar satr ra dar T ghara midahad*/
     while(PINA.5==0){};  /*halghe while k pina.5 dar an barabre sefr ast*/
     K=1;                 /*be k adade yek midahad*/
     break;               /*az barname kharej mishavad*/
     }              
     if(PINA.6==0)        /*inbar agar pina.6 sefr shavad*/
     {
     sotoon=1;            /*be meghdare sotoon adade 1 midahad*/
     T=satr;              /*meghdar satr ra dar T ghara midahad*/
     while(PINA.6==0){};  /*halghe while k pina.6 dar an barabre sefr ast*/
     K=2;                 /*be k adade do midahad*/
     break;               /*az barname kharej mishavad*/
     }
     }
     /*dar inja be bakhsi miresim ke bayad motanaseb be adadii ke daryaft kardim az keypad led hara roshan konim*/  
      j=0b10000000;          /*j ra be shekle bionary tariif mikonim k betavan dar marahele bad ba shift dadn led hara roshan konim*/   
      place=3*T+(sotoon);    /*sotoon ra bar 3 barabare t jamkarde va dar place gharar midahim*/
      d=place;               /*makan ra dar d gharar midahim*/
      if(place > 10)         /*agar bishtar az 10 bashad place*/
      {
      place=0;               /*meghdarash sefr shavad*/
      }
      for(i=0;i<4;i++)       /*halghe  ke dar an i=0 ta i=4 i ra yeki yeki ziad konad*/
      {
      PORTD=j;               /*meghdar j ra be port d midahad va addad dar led namayesh dade mishavad*/
      PORTB=num[place];      /*adad ra be seven segment mifrstad va dar anja namayesh midahad*/
      delay_ms(5);           /*takhir bataye cheshmak zadan chon hamzaman nmitavd roshan bashad*/ 
      j=j>>1;                /*shift midahahd ta cheragh badi dar marhale badi roshan shavad*/
      place=0;               /* b place meghdare sefr midahad*/
      }
      OCR1A=((d)*(512))/10;  /*khorooji ha baraye bedast avardane duty cycle darsad dar 512 zarb shode va taghsim be 10 mishavad ta duty cycle bedast ayad*/
      OCR1B=512-(d*512)/10;  /*mokamele ghabli yani az kol kam shavad. mesal;a=90 b=10 */
//--------------------------------------------------------------------------------------------------------------------------
/*ba tavajoh be tozihi ke ghablan dadim : dar in bakhsh az barname code i neshe shode ast baraye tashkhis adade vared shode az sooye karbar baraye pardazesh haye badi*/
     /*be in goone ke yek port kamele micro ra be tore kamel be key pad ekhtsas dade va be do bakhsh tabdil mikonim*/
     /*va voroodi khorooji mikonim va ba sefro yek kardn satro sotoon va be tartib ba azjam inkar mitavan tashkhis dad k*/
     /*dar kodam satr ya sotoon button feshar dade shode ast
     dar inja an adad ha be led ha nesbat dade mishavand cho bara ye baraye mesal yek led baraye do 2 led va be tartib
     be tedad dahgane 7 segment led ha az rast be chap roshan mishavand */
//--------------------------------------------------------------------------------------------------------------------------    
    PORTA.0=0;    /*be tartib sotoon hara sefr mikonad va ba sefr shodan satr adade morede nazar ra be dast avarde va led hara roshan mikonad*/   
    if(PINA.6==0){PORTC.0=1;}
    if(PINA.5==0){PORTC.0=PORTC.1=1;}
    if(PINA.4==0){PORTC.0=PORTC.1=PORTC.2=1;}
    PORTA.0=1;
    
    PORTA.1=0;    /*be tartib sotoon hara sefr mikonad va ba sefr shodan satr adade morede nazar ra be dast avarde va led hara roshan mikonad*/
    if(PINA.6==0){PORTC.0=PORTC.1=PORTC.2=PORTC.3=1;}
    if(PINA.5==0){PORTC.0=PORTC.1=PORTC.2=PORTC.3=PORTC.4=1;}
    if(PINA.4==0){PORTC.0=PORTC.1=PORTC.2=PORTC.3=PORTC.4=PORTC.5=1;}
    PORTA.1=1;
    
    PORTA.2=0;   /*be tartib sotoon hara sefr mikonad va ba sefr shodan satr adade morede nazar ra be dast avarde va led hara roshan mikonad*/
    if(PINA.6==0){PORTC.0=PORTC.1=PORTC.2=PORTC.3=PORTC.4=PORTC.5=PORTC.6=1;}
    if(PINA.5==0){PORTC.0=PORTC.1=PORTC.2=PORTC.3=PORTC.4=PORTC.5=PORTC.6=PORTC.7=1;}
    if(PINA.4==0){PORTC.0=PORTC.1=PORTC.2=PORTC.3=PORTC.4=PORTC.5=PORTC.6=PORTC.7=1;PORTD.0=1;}
    PORTA.2=1; 
    
    PORTA.3=0;   /*in halete sefr shodan hameghi ra barresi ikonad va tamami led hara khamoosh mikonad*/
    if(PINA.5==0){PORTC.0=PORTC.1=PORTC.2=PORTC.3=PORTC.4=PORTC.5=PORTC.6=PORTC.7=PORTD.0=0;}
    PORTA.3=1;
   
}
}