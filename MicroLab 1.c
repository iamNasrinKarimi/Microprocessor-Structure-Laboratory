/*
 * Az1.c 
 __________________________________________________________
 __________________________________________________________
 
    ***MICROPROCESSOR AND COMPUTER ARCHITECTURE LAB***  
    
 * Title:  8 Bit Binary Counter with LED (odd)
 * Date:   2020.10.07
 * Author: Nasrin Kaimi 97236081      Group:No.22
 * Professor: Dr. Hadi Asharioun
 * Teacher Assiatant: Ms.Solmaz Fattahi 
 * Shahid Beheshti University - Paradise of Shahid Abbaspour


 -chip type: ATmega32
 _Clock frequency of Core: 8.000 MHz
 _Application: Proteus
 __________________________________________________________
 __________________________________________________________
*/

#include <io.h>
#include <mega32.h>
#include <delay.h>

void main(void)
{
int i;
while (1)
    {

      for(i=1;i<256;i+=2)   //chon 8 bit ast yani 2^8=256 .ba tavajoh b fard
                            //budane shomare daneshjooii pas az adade 1 shoroo
                           //karde va 2ta 2ta jelo miravad.
                          //shomarande mitavanad az 0 ta 255 ra beshmarad.
      {
      PORTD=i;           // adad i ra be port D midahad
      delay_ms(1000);   //baraye sade sazi dar neveshtane barname dar ebteda 
                        //ketabkhane delay.h ra tarif kardim. 
                        //chon gofteshode k takhir 1 sanie bashad yani 1000 mili sanie.
      }                 
    }
}
