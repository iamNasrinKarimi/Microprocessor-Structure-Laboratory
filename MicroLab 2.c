/*
 * Az2.c 
 __________________________________________________________
 __________________________________________________________
 
    ***MICROPROCESSOR AND COMPUTER ARCHITECTURE LAB***  
    
 * Title:  8 Bit Binary Counter with LED (odd-Assembly)
 * Date:   2020.10.14
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
void main(void) 
{
#asm                  
;barname b zabane assembly neveshte shode
.equ ddrd=$11         ;voroodi haye address ro az ghabl taiin mikonim
.equ portd=$12        ;arddress port ha
      ldi R16,0       ;meghdar 0 ra dar r16 gharar midahad
      inc R16         ;yek vahed b r16 ezafe mikonad. bayad az adade 1 shoroo konim chon shomarande fard ast
      ldi R17,0xff    ;baraye khorooji kardane port d meghdar 1 ra be r17 midahim
      out ddrd,R17    ;chon nmitavan mostaghim b meghdar port i/o adad dad an ra daroon yek
      out portd,R16   ;register gharar dade va ba estefade az out meghdar r17 ra b port d enteghal midahim
delay3:               ;chon adade yek ra sari rad mikard yek halghe baraye an neveshtam
      ldi R20,10      ;ta modat zaman kafi namayesh dade shavad adade yek
DELAY4:               ;adade 10 ba azmoono khata entekhab shod k besyar monaseb ast
      dec R20         ;yek vahed az r20 kam mikonad 
      brne DELAY      ;vagti flag z=0 nashavad in kar edame peida mikonad va b delay3 barmigardad 
counter:              ;shomarande i tariif shode ta dar khorooji dar marhale led ra 0 , 1 kond
      out portd,R16   ;meghdar daroone r16 ra dar portd gharar midahad
      inc R16         ;chon shomarande fard ast yani 2 vahed bayad ezafe shavad yani az 2 inc estefade mikoim
      inc R16         ;yek vahed b meghdar r16 ezafe mikonad 
delay1:               ;baraye takhir 0.5 mili sanie khaste shode az halghe haye
      ldi R30,255     ;too dar too estefade mishavad
delay2:               ;chon har halghe k ba estefade az brne nvshte mishavad 256 bar 
      ldi R31,30      ;mitavanad anjam dahad baraye ezafe tar kardan an bayad az
DELAY:                ;halghe haye too dar too estedafe kard.
      dec R31         ;yek vahed az r31 kam mikonad 
      brne DELAY      ;vagti flag z=0 nashavad in kar edame peida mikonad
      dec R30         ;flag z zamani sefr mishavad k hase amaliar 0 shavad
      brne delay2     ;halghe haye too dar too
      dec R29         ;yek vahed az r29 kahesh midahad
      brne delay1 
rjmp counter         ;rjmp yek dastoor 2 biti ast k be halghe mored nazar barmigardad
;dastoor assembly payan miyabad
#endasm               
while(1)
{
}
}
