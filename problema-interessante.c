/********
Alunos:
Eneri D'Angelis (emd)
Nathalia Lima (npl)
Rafael Vasconcelos (rjav) 

*********/
#include <reg51.h>

#define FrClk 12000000
#define FreqTimer0_emHz 100
#define VALOR_TH0 ((65536 - (FrClk / (12 * FreqTimer0_emHz))) >>8)
#define VALOR_TL0 ((65536 - (FrClk / (12 * FreqTimer0_emHz))) & 0xFF)



unsigned int contador;

void timer0_inicializa() 
  {
  TR0 = 0;              // Desliga Timer0
  TMOD = (TMOD & 0xF0) | 0x01;  // Timer 0 programado como timer de 16 bits
  TH0 = VALOR_TH0;  // Programa contagem do Timer0
  TL0 = VALOR_TL0;
  ET0 = 1;      // Habilita interrupcao do timer 0
  TR0 = 1;      // Habilita contagem do timer 0
  }

void timer0_int (void) interrupt 1 using 2
  {
  TR0 = 0;              // Desliga Timer0
  TL0 += VALOR_TL0;
  TH0 += VALOR_TH0 + (unsigned char) CY;   // Programa contagem do Timer0
  TR0 = 1;      // Habilita contagem do timer 0

  if (contador != 0)
     contador --;
  }

void main()
	{
  timer0_inicializa();
	EA=1; //Habilita o tratamento de interrup��es

	while (1)
      {
      contador = 300;
			
      while(1){
			EA = 0;
			if(contador == 0)
				break;
			EA = 1;
			} // Fica em loop enquanto "contador != 0"
			
      if (contador == 0) // Testa se contador � igual a zero.
         P0 = 0;

      else
        P0 = 0xFF;	// ESTA INSTRU��O NUNCA DEVERIA SER EXECUTADA!
      }
	}
	

