/********

Alunos:
Eneri D'Angelis (emd)
Rafael Vasconcelos (rjav)

*********/

#include <REG51F.H>

#define FrClk 12000000
#define FreqTimer0_emHz 100
#define CORRECAO 9
#define TH0_Inicial ((65536-(FrClk/(12*FreqTimer0_emHz))+CORRECAO)>>8)
#define TL0_Inicial ((65536-(FrClk/(12*FreqTimer0_emHz))+CORRECAO)&0xFF)

sbit b0 = P2^0;
sbit b1 = P2^1;

int counter1;
int counter2;

void timer0_inicializa(){
  TR0 = 0;                  //Desliga Timer0
  TMOD = (TMOD & 0xF0)|0x01; //Timer 0 programado no Modo 1 (16 bits)
  TH0 = TH0_Inicial;          // Programa valor de contagem do Timer0
  TL0 = TL0_Inicial;
  ET0 = 1;                    // Habilita interrupcao do timer 0
  TR0 = 1;                    // Habilita contagem do timer 0
}

void timer0_int (void) interrupt 1 using 2 {
  TR0 = 0;              // Desliga Timer0
TL0 += TL0_Inicial;   // Faz recarga da contagem do Timer0
  TH0 += TH0_Inicial + (unsigned char) CY;  
  TR0 = 1;      // Habilita contagem do timer 0
counter1 ++;
counter2 ++;
}



void watchingP0(){
static char pEstado = 0x00;
switch (pEstado){
case  0x00: if (b0==0x01){ /* bit 0 de P2 passa de 0 -> 1*/
P1 = (P1 & 0xF0) | (P0 & 0x0F);
pEstado = 0x01;
counter1 = 0;
}
break;
case  0x01 : if(counter1 > 100){/* espera 1s */
P1 = (P1 & 0xF0);
pEstado = 0x02;
}
break;
case  0x02 : if (b0==0x00){/* bit 0 de P2 passa de 1 -> 0*/
pEstado = 0x00;
}
break;
}
}

void watchingP1(){
static char pEstado = 0x00;
switch (pEstado){
case  0x00: if (b1==0x01){ /* bit 0 de P2 passa de 0 -> 1*/
P1 = (P0 & 0xF0) | (P1 & 0x0F);
pEstado = 0x01;
counter2 = 0;
}
break;
case  0x01 : if (counter2 > 100){/* espera 1s */
P1 = (P1 & 0x0F);
pEstado = 0x02;
}
break;
case  0x02 : if (b1==0x00){/* bit 0 de P2 passa de 1 -> 0*/
pEstado = 0x00;
}
break;
}
}


void main(){
timer0_inicializa();
EA=1; //Habilita o tratamento de interrupções
while(1){
watchingP0();
watchingP1();
}
return;
}
