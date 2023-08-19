/*
 * Az3.c 
 __________________________________________________________
 __________________________________________________________
 
    ***MICROPROCESSOR AND COMPUTER ARCHITECTURE LAB***  
    
 * Title:  2 digit 7 segment 00-99 counter (First Odd then Even)
 * Date:   2020.10.21
 * Author: Nasrin Kaimi 97236081      Group:No.22
 * Professor: Dr. Hadi Asharioun
 * Teacher Assiatant: Ms.Solmaz Fattahi 
 * Shahid Beheshti University - Paradise of Shahid Abbaspour


 -chip type: ATmega32
 _Clock frequency of Core: 8.000 MHz
 _Application: Proteus
 _7-SEG-Type: Cathode 4-Digit
 _Delay: 750 ms (0.75 s) 
 __________________________________________________________
 __________________________________________________________
*/
#include <mega32.h>            /*ketab khane atmega 32 ro tariif kardim */
#include <delay.h>             /* ketabkhane delay ra tarif kardim ta be rahati az tabe an estefade konim*/
unsigned char cathode_seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; /*baraye rahati kar code HEX*/ 
                               /* an ra daroone araye ghara dadim ta dar ravande kar az an estefade konim*/
void Show_7_seg(int n)         /*tarz kare kar kardane 7seg ra dar yek tabe tarif kardim ta be rahti dar soorate niaz farakhani konim*/
{                              /*chon tabe faghede khoroji bood az nooe void estefade shode ast*/
    int i, j,r;                /*moarefie motaghar haye i,j,r az noe intiger*/ 
    i = n / 10;                /*adade n taghsim bar 10 mishavad ta meghdar i k haman DAHGAN ast bedast ayad*/
    j = n % 10;                /*meghdare j haman baghimande taghsim n bar 10 ast neshangare YEKAN ast*/
    for(r=0;r<25;r++)          /*chon nmitavan dar ane vahed dar 7seg cheragh ha roshan bashand chon adade chand raghami*/ 
    {                          /*daraye paye haye moshtarake a,b,c,d,e,f,g,dp hastand pas yek haghle tarif kardim ta dar an cheragh ha*/
                               /*cheshmak bazanand va delay ra anghadr kam entekhab mikonikm ta cheshm ensane ghader be tashkhis an nabashad*/
        PORTA.0=0; PORTA.1=1;  /*dahgan khamoosh ast va yekan faal*/
        PORTB=cathode_seg[i];  /*az araye baraye neshan dadane adade yekan estefade mishavad*/
        delay_ms(1);           /*takhir besya kam b andaze 1 ms bara cheshmak zadan*/
        PORTA.0=1; PORTA.1=1;  /*daghan faal shode yekan faal shode*/
        PORTA.0=1; PORTA.1=0;  /*dahgan faal shode yekan gheire faal mishavad*/
        PORTB=cathode_seg[j];  /*az araye baraye neshan dadane adade dahgan estefade mishavad*/
        delay_ms(1);           /*takhir besya kam b andaze 1 ms bara cheshmak zadan*/
        PORTA.0=1; PORTA.1=1;  /*daghan faal shode yekan faal shode*/
    }
}
void main(void)                /*tabe aslie barname c tarif mishavad*/
{
    int n;                     /*motaghayere n az noe intiger tarif mishavad*/
    DDRA = 0xff;               /* ddr ha yek mishavand be neshaneye khorooji boodan*/
    DDRB = 0xff;               /* ddr ha yek mishavand be neshaneye khorooji boodan*/
    while(1)
    {
 for(n=1; n<=99; n+=2)         /*halghe baraye shomaresh az adade 1,3,5,... ta 99*/
 {
 Show_7_seg(n);                /*adade morede nazar tavasote tabe tariif shode va dar 7seg nmayesh dade mishavad*/
 delay_ms(750);                /*takhire morede nazar baraye namayesh adade badi dar soal 0.75 sanie haman 750 mili sanie ast*/
 } 
  for(n=0; n<=99; n+=2)        /*halghe baraye shomaresh az adade 0,2,4,6,... ta 98*/
 {
 Show_7_seg(n);                /*adade morede nazar tavasote tabe tariif shode va dar 7seg nmayesh dade mishavad*/
 delay_ms(750);                /*takhire morede nazar baraye namayesh adade badi dar soal 0.75 sanie haman 750 mili sanie ast*/
 }
   }
   }