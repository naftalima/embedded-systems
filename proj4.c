/******************************
Alunos:
	Eneri D'Angelis (emd)
	Nathalia Lima (npl)
	Rafael Vasconcelos (rjav) 
******************************/

#include <REG51F.H>

char c;

void serial_inicializa(){
	ES = 1; 					// Habilita a interrupção da serial
	REN = 1; 					// Habilita a recepção da serial
	PCON |= 0x80; 		// SMOD = 1
	
	SM0 = 0;					// SCON configuração 
	SM1 = 1;					// SCON configuração
	SM2 = 0;					// SCON configuração
}

void timer1_inicializa(){
  TR1 = 0;              						// Desliga Timer 1
  TMOD = (TMOD & 0x0F)|0x20; 				// Timer 1 programado no Modo 2 (8 bits)
  TH1 = 0xCC; 											// Programa valor de contagem do Timer1
  TR1 = 1;      										// Habilita contagem do Timer 1
  }

void isr_serial() interrupt 4 using 2{
	if(TI){
	TI = 0; // Tem que setar manualmente pra 0
	// --------------
	}
	if(RI){
	RI = 0; // Tem que setar manualmente pra 0
	c = SBUF;
	SBUF = c + 1;
	// ---------------
	}
}

void main(){
	EA = 1;
	serial_inicializa();
	timer1_inicializa();
	while(1);
	return;
}