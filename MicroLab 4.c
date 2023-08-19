/*
 * Az4.c 
 __________________________________________________________
 __________________________________________________________
 
    ***MICROPROCESSOR AND COMPUTER ARCHITECTURE LAB***  
    
 * Title:  Interrupt and 7-segment counter
 * Date:   2020.10.28
 * Author: Nasrin Kaimi 97236081      Group:No.22
 * Professor: Dr. Hadi Asharioun
 * Teacher Assiatant: Ms.Solmaz Fattahi 
 * Shahid Beheshti University - Paradise of Shahid Abbaspour


 -chip type: ATmega32
 _Clock frequency of Core: 8.000 MHz
 _Application: Proteus
 _7-SEG-Type: Cathode 4-Digit
 _Delay: 1000 ms (1 s) 
 __________________________________________________________
 __________________________________________________________
*/
#include <mega32.h> /*ketab khane atmega 32 ro tariif kardim */

#include <delay.h>  /* ketabkhane delay ra tarif kardim ta be rahati az tabe an estefade konim*/

unsigned char num[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90} ;   /*baraye rahati kar code HEX*/
                          /* an ra daroone araye ghara dadim ta dar ravande kar az an estefade konim*/
    int i =0;             /* tarif moteghayer haye barname */
    int flag=2;           /* tarif flag baraye barname */


int getDigit(int i, int n)  /*tabei tarif kardim ta mogheiite n ome intiger i ra be ma bargardanad va az sefr shoroo mishavad*/
{
   int z;                /* tarif moteghayer haye barname */
   for(z=0; z<n; z+=1)   /* halghe i tariif kardim k az 0 ta n yeki yeki be an ezafe shavad*/
        i /= 10;         /*adade i taghsim bar 10 mishavad ta meghdar i k haman DAHGAN ast bedast ayad*/
   return (i%10);        /*meghdare baghimande taghsim i bar 10 ast neshangare YEKAN ast ra bazmigardanad*/

}    // in tabe addade n ra be digit haye mokhtalef paksh mikonad. ma inja az 4 digit estefade mikonim chon//
      //mikhahim k 2 raghe counter zoj dar chap va 2 raghame counter fard dar rast 7-seg 4 digit ma bashad//
      //harkodam az digit ha be haryek az 4 khane a,b,c,d k dar zir tariif kardeim miravad.//

  void display(int i) //yek tabei tarif kardim k chon faghede oroodi ast az void estfade kardim baraye namayesh adad dar 7-seg
  { /*tarz kare kar kardane 7seg ra dar yek tabe tarif kardim ta be rahti dar soorate niaz farakhani konim*/
  int a = getDigit(i,0) ; //mogheiat 0 motalegh be digit a (7-seg)
  int b = getDigit(i,1) ; //mogheiat 1 motalegh be digit b (7-seg)
  int c = getDigit(i,2) ; //mogheiat 2 motalegh be digit c (7-seg)
  int d = getDigit(i,3) ; //mogheiat 3 motalegh be digit d (7-seg)
    PORTC = 0x70;         //b port c meghdare 0x70 ra midahad
    PORTB = num[a];       //addi k a khahad bud ra be port b midahad
    delay_ms(1) ;          //ba estefade az tabe delay k tariif kardim takhir 1 sanie ijad mikonad
    PORTC = 0xb0;         //b port c meghdare 0xb0 ra midahad
    PORTB= num[b];        //addi k b khahad bud ra be port b midahad
    delay_ms(1);           //ba estefade az tabe delay k tariif kardim takhir 1 sanie ijad mikonad

    PORTC = 0xd0;         //b port c meghdare 0xd0 ra midahad
    PORTB = num[c];       //addi k c khahad bud ra be port b midahad
    delay_ms(1);           //ba estefade az tabe delay k tariif kardim takhir 1 sanie ijad mikonad

    PORTC = 0xe0;          //b port c meghdare 0xe0 ra midahad
    PORTB = num[d];        //addi k d khahad bud ra be port b midahad
    delay_ms(1);           //ba estefade az tabe delay k tariif kardim takhir 1 sanie ijad mikonad




    }

void main(void)           /*tabe aslie barname c tarif mishavad*/
{
 int z;                   /*motaghayere z az noe intiger tarif mishavad*/
 DDRB=0xff;               /* ddr ha yek mishavand be neshaneye khorooji boodan*/
 DDRC=0xff;               /* ddr ha yek mishavand be neshaneye khorooji boodan*/

 MCUCR= 0x0f;                     /*bala ravande va afzayesh labe :rising edge*/
 GICR|=(1<<INT1) | (1<<INT0) ;    /*int0 va int1 ra faal sazi mikonad*/

 #asm("sei");                     /* faal sazi interrupt haye khareji*/ 

while (1)                         /* halghei ke hamishe tekrar mishavad ra tariif mikonim*/
 {
      if(flag ==1)                /*yek halghe sharti tariif kardim k agar flag yek shavad int0 k marboot be button sefr ast faal mishavad*/
      {               
       i+=1;                      /*be 2 joft adade samte rast 1 meghdar ezafe mikonad*/
         for(z=0; z<250; z++)     /*dar in halghe addade 1 ra neshan midahad be modate 1 sanie*/
              display(2*i+1);     /*ba ezafe kardane 1 baes mishavad adade far ra be tartib dar 2 digit raste 7-seg namayesh dahad*/
      }
      if(flag ==0)                /*yek halghe sharti tariif kardim k agar flag sefr shavad int1 k marboot be button yek ast faal mishavad*/
      {   
       i+=100;                    /*be 2 joft adade samte chap 1 meghdar ezafe mikonad tavajoh darim k */
         for(z=0; z<250; z++)     /*dar in halghe addade 1 ra neshan midahad be modate 1 sanie*/
              display(2*i);       /*adade zoj ra namayesh midahad*/
      }
      }
}
interrupt [EXT_INT0] void ext_int0_isr(void)   /*tabe interrupt0 dar micro darsoorati ke interrupt 0 faal shavad in tabe ejra khahad shod*/
{
   flag=0;                                     /*be flag meghdare sefr midahad (button 0 faal shavad)*/

}
interrupt [EXT_INT1] void ext_int1_isr(void)   /*tabe interrupt1 dar micro darsoorati ke interrupt 1 faal shavad in tabe ejra khahad shod*/
{
   flag=1;                                     /*be flag meghdare yek midahad (button 1 faal shavad)*/
}