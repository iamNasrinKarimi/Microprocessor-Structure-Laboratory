/*
 * Az5.c 
 __________________________________________________________
 __________________________________________________________
 
    ***MICROPROCESSOR AND COMPUTER ARCHITECTURE LAB***  
    
 * Title:  Key-pad , 7-seg , LED
 * Date:   2020.11.04
 * Author: Nasrin Kaimi 97236081      Group:No.22
 * Professor: Dr. Hadi Asharioun
 * Teacher Assiatant: Ms.Solmaz Fattahi 
 * Shahid Beheshti University - Paradise of Shahid Abbaspour


 -chip type: ATmega32
 _Clock frequency of Core: 8.000 MHz
 _Application: Proteus
 _7-SEG-Type: Cathode 4-Digit
 _KeyPad: 4*4
 __________________________________________________________
 __________________________________________________________
*/
#include <mega32.h> /*ketab khane atmega 32 ro tariif kardim */
#include <delay.h>  /* ketabkhane delay ra tarif kardim ta be rahati az tabe an estefade konim*/

void sevensegment(char);  /*farakhani mikonad tabe namayesh dar 7 segment ra*/
char key_pad(void);       /*az keypad matrisi yek vorudi daryaft mikonad*/
void main(void)           /*tabe aslie barname c tarif mishavad*/
{
char i=0;                 /*moteghayere i az noe char ra tarif mikonad k daraye meghdar avalieye sefr mibashad*/
char n;                   /*moteghayere n az noe char ra tarif mikonad*/
DDRA=0b11110000;          /*dar key pad matrisi ma port ra kamel be keypad ekhtesas midahim va nime aval ra khorooji va nime */
PORTA=0b00001111;         /*dovom ra vorudi dar nazar migirim pas ddrA ra 0 va port a ra 1 dar nazar migirim*/
DDRB=0xff;                /*7 segment ma k adad ra namayesh midahad khorooji mast pas port b ra yek mikonim*/
DDRC=0xf0;                /*port c k marboot be paye haye cathode ast ra be onvane khorooji yek mikonim*/
DDRD=0x0f;                /*paye haye LED k adad ya haman khorooji ra be ma namyesh midahad ra khoroji mikonim*/
while (1)                 /* halghei ke hamishe tekrar mishavad ra tariif mikonim*/
    {                                    
    sevensegment(i);      /*adade morede nazar ra dar 7 segment namayesh midahad*/
    n=key_pad();          /*yek adad be onvane voroodi daryaft mikonad*/
    PORTD = i = n;        /*adad ra dar khorooji LED ha namayesh midahad*/
    }
}
char key_pad(void)        /*tabe keypad ra tariif mikonim*/
{
int i=0;                  /*baraye kar ba keypad k karbar dar har lahze che adadi*/
PORTA.4=0;                /*ra feshorde ast bayad yeki az port haye micro ra be tore kamel*/
if (PINA.0==0)            /*be keypad ekhtesas dahim va nesf an port ra voroodi va nesfash ra khorooji konim*/
 {                        /*be radif aval az tarighe pin marboote sefr midahim dar in zaman baghi radif ha yek hastand*/ 
 delay_ms(5);             /*a sepas in radif ra yek karde badi ra sefr mikonim. dar zamani k har radif sefr ast ba tajoh be*/
  i=1;                    /*inke kodom sotoon sefr ast motavajeh mishavim k kodam button feshordde shode ast*/
 }                        /*dar inja niz be tarib sefro yek mikonim pin ha ra*/
if (PINA.1==0)            /*va har buuton ra be adadi ekhtesas midahim ba sefro yrk shodan*/
{                         /*takhire 5 mili sanie niz baraye an dar nazar migirim*/
 delay_ms(5);             /*delay 5 mili sanie ra besyar kochak baraye cheshmak zadan ba estefade az library tarif mikonim*/
  i=2;                    /*adade 2 ra moshakhas mikonad*/
}
if (PINA.2==0)            /*haman comment haye 46-54*/
 { delay_ms(5);
  i=3;                    /*adade 3 ra moshakhas mikonad*/
 }
PORTA.4=1;
PORTA.5=0;
if (PINA.0==0) 
{ delay_ms(5);            /*delay 5 mili sanie ra besyar kochak baraye cheshmak zadan ba estefade az library tarif mikonim*/
 i=4;                     /*adade 4 ra moshakhas mikonad*/
}                         /*haman comment haye 46-54*/
if (PINA.1==0) 
{ delay_ms(5);           /*delay 5 mili sanie ra besyar kochak baraye cheshmak zadan ba estefade az library tarif mikonim*/
i=5;                     /*adade 5 ra moshakhas mikonad*/
}
if (PINA.2==0) 
{
 delay_ms(5);            /*delay 5 mili sanie ra besyar kochak baraye cheshmak zadan ba estefade az library tarif mikonim*/
 i=6;                    /*adade 6 ra moshakhas mikonad*/
}                        /*haman comment haye 46-54*/
PORTA.5=1;
PORTA.6=0;
if (PINA.0==0) 
{
 delay_ms(5);            /*delay 5 mili sanie ra besyar kochak baraye cheshmak zadan ba estefade az library tarif mikonim*/
 i=7;                    /*adade 7 ra moshakhas mikonad*/
}
if (PINA.1==0) 
{
 delay_ms(5);            /*delay 5 mili sanie ra besyar kochak baraye cheshmak zadan ba estefade az library tarif mikonim*/
  i=8;                  /*adade 8 ra moshakhas mikonad*/
}
if                      /*haman comment haye 46-54*/
(PINA.2==0) 
{
 delay_ms(5);           /*delay 5 mili sanie ra besyar kochak baraye cheshmak zadan ba estefade az library tarif mikonim*/
  i=9;                  /*adade 9 ra moshakhas mikonad*/
}
PORTA.6=1;
PORTA.7=0;                         
if (PINA.1==0)           /*baraye darnazar gereftane adade 0*/
{
delay_ms(5);             /*delay 5 mili sanie ra besyar kochak baraye cheshmak zadan ba estefade az library tarif mikonim*/
i=0;
}
PORTA.7=1;
return i;                  /*dar nahayat khorooji ra return mikonim*/
}
void sevensegment(char n)     /*tabe seven segment ra baraye namyesh adade morede nazar minevisim*/
{
char seg[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};  /*baraye rahati kar code HEX an ra dar araye haii ghara midahim*/
    PORTC.1=1;            /*chon gofte shode ke 2 ragha az chape 7seg adade sefr ra namyesh dahad an ra sefro yek mikonim ba delay */
    PORTB=seg[0];         /*chon hamzaman nemitavanand 4 ta paye faal bashand va in adad besyar kochak ast va baes tashkhis chem ensan nmishavad*/
    delay_ms(5);
    PORTC.1=0;  
    PORTC.2=1;            /*chon gofte shode ke 2 ragha az chape 7seg adade sefr ra namyesh dahad an ra sefro yek mikonim ba delay */
    PORTB=seg[0];         /*chon hamzaman nemitavanand 4 ta paye faal bashand va in adad besyar kochak ast va baes tashkhis chem ensan nmishavad*/
    delay_ms(5);
    PORTC.2=0;
    PORTC.3=1;
    PORTB=seg[n];         /*paye haye 2 ta az rast adade yek raghami ra ba feshorde shodane matris namayesh midahand*/
    delay_ms(5);          /*delay ham baraye in ast ke chon hamzaman nemitavanand 4 ta paye faal bashand va in adad besyar kochak ast va baes tashkhis chem ensan nmishavad*/
    PORTC.3=0;            /*be sorat adade morede nazar cheshmak mizanad 0 va 1 mishad paye ash*/
    PORTC.4=1;
    PORTB=seg[n];        /*paye haye 2 ta az rast adade yek raghami ra ba feshorde shodane matris namayesh midahand*/
    delay_ms(5);          /*delay ham baraye in ast ke chon hamzaman nemitavanand 4 ta paye faal bashand va in adad besyar kochak ast va baes tashkhis chem ensan nmishavad*/
    PORTC.4=0;            /*be sorat adade morede nazar cheshmak mizanad 0 va 1 mishad paye ash*/
 }
     
