/*
 * Az9.c 
 __________________________________________________________
 __________________________________________________________
 
    ***MICROPROCESSOR AND COMPUTER ARCHITECTURE LAB***  
    
 * Title:  Calculator
 * Date:   2020.12.17
 * Author: Nasrin Kaimi 97236081      Group:No.22
 * Professor: Dr. Hadi Asharioun
 * Teacher Assiatant: Ms.Solmaz Fattahi 
 * Shahid Beheshti University - Paradise of Shahid Abbaspour


 -chip type: ATmega32
 _Clock frequency of Core: 8.000 MHz
 _Application: Proteus
 _KeyPad: 4*4
 __________________________________________________________
 __________________________________________________________
*/
#include <io.h>             /*ketab khane AVR ra tariif kardim*/
#include <mega32.h>        /*ketab khane atmega 32 ro tariif kardim */
#include <delay.h>         /* ketabkhane delay ra tarif kardim ta be rahati az tabe an estefade konim*/    
#include <stdio.h>         /*tariif in ketabkhane baraye tabdile int be char va estefade az dastoore sprintf*/
#include <stdlib.h>         /*tariif in library baraye tarif motaghaye ha va tavabe mokhtalef*/
#include <lcd.h>           /*ketab khane haye marboot be lcd ra tarif kardim*/

#asm                     
   .equ __lcd_port=0x1b ;PORTA      /*baraye taiine in ke kodam port be lcd motasel ast,dar inja porta*/ 
#endasm
int n=0;                  /*moteghayere n ra ba meghdar avalie 0 az noe intiger moarefi mikonim*/
int m=0;                  /*moteghayere m ra ba meghdar avalie 0 az noe intiger moarefi mikonim*/
int k=0;                  /*moteghayere k ra ba meghdar avalie 0 az noe intiger moarefi mikonim*/
int f=0;                  /*moteghayere f ra ba meghdar avalie 0 az noe intiger moarefi mikonim*/
int num=-1;               /*moteghayere num ra ba meghdar avalie -1 az noe intiger moarefi mikonim*/
//--------------------------------------------------------------------------------------------------------------------------
/*dar in bakhsh az barname code i neshe shode ast baraye tashkhis adade vared shode az sooye karbar baraye pardazesh haye badi
be in goone ke yek port kamele micro ra be tore kamel be key pad ekhtsas dade va be do bakhsh tabdil mikonim
va voroodi khorooji mikonim va ba sefro yek kardn satro sotoon va be tartib ba azjam inkar mitavan tashkhis dad k
dar kodam satr ya sotoon button feshar dade shode ast
dar inja an adad ha be led ha nesbat dade mishavand cho bara ye baraye mesal yek led baraye do 2 led va be tartib
be tedad dahgane 7 segment led ha az rast be chap roshan mishavand */
//--------------------------------------------------------------------------------------------------------------------------  
int key_pad(void)
{  
PORTB.0=0;PORTB.1=1;PORTB.2=1;PORTB.3=1;  /*dar inja satre aval ra sefr va ba sefro yek kardane sotoon ha*/
if(!PINB.4){return num=7;k++;}            /*be tartib har adadi be keypad ekhtesas midahim*/
if(!PINB.5){return num=8;k++;}            /*va baraye inke tedad adade vared shode ra dashte bashim k ra dar har*/
if(!PINB.6){return num=9;k++;}            /*marhaleye vared shodane adad yek vahed be an ezafe mishavad*/
if(!PINB.7){return num=15;k++;}
PORTB.0=1;PORTB.1=0;PORTB.2=1;PORTB.3=1;  /*dar inja satre dovom ra sefr va ba sefro yek kardane sotoon ha*/
if(!PINB.4){return num=4;k++;}            /*be tartib har adadi be keypad ekhtesas midahim*/
if(!PINB.5){return num=5;k++;}            /*va baraye inke tedad adade vared shode ra dashte bashim k ra dar har*/
if(!PINB.6){return num=6;k++;}            /*marhaleye vared shodane adad yek vahed be an ezafe mishavad*/
if(!PINB.7){return num=14;k++;}
PORTB.0=1;PORTB.1=1;PORTB.2=0;PORTB.3=1;  /*dar inja satre sevom ra sefr va ba sefro yek kardane sotoon ha*/
if(!PINB.4){return num=1;k++;}            /*be tartib har adadi be keypad ekhtesas midahim*/
if(!PINB.5){return num=2;k++;}            /*va baraye inke tedad adade vared shode ra dashte bashim k ra dar har*/
if(!PINB.6){return num=3;k++;}            /*marhaleye vared shodane adad yek vahed be an ezafe mishavad*/
if(!PINB.7){return num=13;k++;}
PORTB.0=1;PORTB.1=1;PORTB.2=1;PORTB.3=0;   /*dar inja satre chaharom ra sefr va ba sefro yek kardane sotoon ha*/
if(!PINB.4){return num=10;k++;}            /*be tartib har adadi be keypad ekhtesas midahim*/
if(!PINB.5){return num=0;k++;}             /*va baraye inke tedad adade vared shode ra dashte bashim k ra dar har*/
if(!PINB.6){return num=11;k++;}            /*marhaleye vared shodane adad yek vahed be an ezafe mishavad*/
if(!PINB.7){return num=12;k++;}
PORTB.3=1;
return num;                                /*khorooji ra barmigardanad yani haman adadi ke dar keypad vared shode ast*/ 
}
void main(void)                             /*tabe aslie barname c tarif mishavad*/
{
float a=0;                                  /*moteghayere a ra ba meghdar avalie 0 az noe float moarefi mikonim*/
float b=0;                                  /*moteghayere b ra ba meghdar avalie 0 az noe float moarefi mikonim*/
float result=0;                             /*moteghayere result ra ba meghdar avalie 0 az noe float moarefi mikonim*/
char row1[16],row2[16];                     /*lcd daraye 2 radif ast va ma an ra az noe arayeye 16 taii (16 sotoon darad*/
lcd_init(16);                               /*tarif mikonim_ va inja lcd 16 taii ra tarif kardim*/
DDRB=0x0f;                                  /*nimi az port ra voroodi karde*/
PORTB=0xff;                                 /*va nimi digar ra khorooji mikonim*/
while (1)                                   /* halghei ke hamishe tekrar mishavad ra tariif mikonim*/
    {
    while(num==-1 || num>=10)               /*agar button vared shode az 10 bishtar bashad ya feshorde nashavad*/
	{
        lcd_gotoxy(0,0);                    /*be makane 0,0 dar lcd miravad*/
        lcd_putsf("I");                     /*charactere I ra dar lcd namayesh midahad*/
        key_pad();                          /*adad az karbar gerfte mishavad*/
        lcd_clear();                        /*lcd pak mishavad*/
    }k=1;                                   /*be k meghdar 1 ra midahad*/
    while(num<10)                           /*dar hali ke adade vared shode az 10 kochektar bashad*/
	{
        sprintf(row1,"%d",num);             /*dar satre aval adad ra ba hasbe decimal chap mikonad*/
        lcd_gotoxy(k-1,0);                  /*be khane k-1,0 dar lcd miravad*/
        lcd_puts(row1);                     /*dar satre aval adad ra namyesh midahad*/
        if(n!=k)                            /*agar n mokhalefe k bashad*/
		{
            a=num+10*a;                     /*ragham haye jodagane be yek adad daraye dahgan sadgan... tabdil mishavad*/
            n=k;                            /*meghdar k ra daroone n ghrr midahad*/
        }key_pad();                         /*adad az karbar gerfte mishavad*/
    }m=k;                                   /*meghdar k ra daroone m ghrr midahad*/
    while(num<11)                           /*dar hali ke adade vared shode az 11 kochektar bashad*/
	key_pad();                              /*adad az karbar gerfte mishavad*/
    k=m;                                    /*meghdar m ra daroone k ghrr midahad*/
    n=0;                                    /*be n meghdar 0 ra midahad*/
    lcd_gotoxy(k-1,0);                      /*be khane k-1,0 dar lcd miravad*/
    switch (num)                            /*az dastore switch estefade mikoinim*/
	{
        case 15:lcd_putsf("/");             /*case 15 moatalegh be division ast */
        f=4;                                /*va meghdare 4 ra dar f ghrr midahad*/
        break;                              /*az dastoor kharej mishavad*/
        case 14:lcd_putsf("*");             /*case 14 moatalegh be multipliction ast */
        f=3;                                /*va meghdare 3 ra dar f ghrr midahad*/
        break;                              /*az dastoor kharej mishavad*/
        case 13:lcd_putsf("-");             /*case 14 moatalegh be subtraction ast */
        f=2;                                /*va meghdare 2 ra dar f ghrr midahad*/
        break;                              /*az dastoor kharej mishavad*/
        case 12:lcd_putsf("+");             /*case 14 moatalegh be addition ast */
        f=1;                                /*va meghdare 1 ra dar f ghrr midahad*/
        break;                              /*az dastoor kharej mishavad*/
    }m=k;                                   /*meghdar k ra daroone m ghrr midahad*/
    while(num>=10)                          /*dar hali ke adade vared shode az 10 bozorgtar va mosavi bashad*/
    key_pad();                              /*adad az karbar gerfte mishavad*/
    k=m+1;                                  /*be m yek meghdar zafe karde va hasel ra daroone k ghrr midahad*/
    while(num<10)                           /*dar hali ke adade vared shode az 10 koochektar bashad*/
    {
        sprintf(row1,"%d",num);             /*dar satre aval adad ra ba hasbe decimal chap mikonad*/
        lcd_gotoxy(k-1,0);                  /*be khane k-1,0 dar lcd miravad*/
        lcd_puts(row1);                     /*dar satre aval adad ra namyesh midahad*/
        if(n!=k)                            /*agar n mokhalefe k bashad*/
        {
            b=num+10*b;                     /*ragham haye jodagane be yek adad daraye dahgan sadgan... tabdil mishavad*/
            n=k;                            /*meghdar k ra daroone n ghrr midahad*/
        }key_pad();                         /*adad az karbar gerfte mishavad*/
    }
    while(num!=11)                          /*dar hali ke adade vared shode barabare 11 nabashad*/
    key_pad();                              /*adad az karbar gerfte mishavad*/
    lcd_gotoxy(0,1);                        /*be makane satre dovom va sotoone aval lcd miravad*/
    lcd_putsf("=");                         /*charactere = ra dar lcd namayesh midahad*/
    switch (f)                              /*az dastore switch estefade mikoinim*/
    {        
    case 4:result=a/b;                      /*case 4 motaalegh be amale tagsim ast*/
    ftoa(result,3,row2);                    /*result ra ba 3 raghame ashar hesab karde va dar satr dovom namyesh midahad ba tabdil shodan be string*/
    lcd_gotoxy(3,1);                        /*be satre dovom va sotoone sevom miravad*/
    lcd_puts(row2);                         /*satre dovom ra dar lcd namayesh midahad*/
    break;                                  /*az dastoor kharej mishavad*/
    case 3:result=a*b;                      /*case 3 motaalegh be amale zarb ast*/
    ftoa(result,3,row2);                    /*result ra ba 3 raghame ashar hesab karde va dar satr dovom namyesh midahad ba tabdil shodan be string*/
    lcd_gotoxy(3,1);                        /*be satre dovom va sotoone sevom miravad*/
    lcd_puts(row2);                         /*satre dovom ra dar lcd namayesh midahad*/
    break;                                  /*az dastoor kharej mishavad*/
    case 2:result=a-b;                      /*case 2 motaalegh be amale tafriq ast*/
    ftoa(result,3,row2);                    /*result ra ba 3 raghame ashar hesab karde va dar satr dovom namyesh midahad ba tabdil shodan be string*/
    lcd_gotoxy(3,1);                        /*be satre dovom va sotoone sevom miravad*/
    lcd_puts(row2);                         /*satre dovom ra dar lcd namayesh midahad*/
    break;
    case 1:result=a+b;                      /*case 1 motaalegh be amale jam ast*/
    ftoa(result,3,row2);                    /*result ra ba 3 raghame ashar hesab karde va dar satr dovom namyesh midahad ba tabdil shodan be string*/
    lcd_gotoxy(3,1);                        /*be satre dovom va sotoone sevom miravad*/
    lcd_puts(row2);                         /*satre dovom ra dar lcd namayesh midahad*/
    break;                                  /*az dastoor kharej mishavad*/
    }
    while(num!=10)                          /*dar hali ke adade vared shode barabare 10 nabashad*/
    key_pad();                              /*adad az karbar gerfte mishavad*/
    num=-1;                                 /*meghdare -1 darooe adad ghrr migirad haman halate avalie vared nashode adad*/
    a=0;                                    /*meghdare 0 dar adade aval ghrr dde mishvad*/
    b=0;                                    /*meghdare 0 dar adade dovom ghrr dde mishvad*/
    k=0;                                    /*meghdare 0 dar k ghrr dde mishvad*/
    lcd_clear();                            /*lcd pak mishavad*/
    }
}