#include <REG51F.H>

#define FrClk 12000000
#define FreqTimer0_emHz 100

void serial_inicializa(){
	ES = 1; 					// Habilita a interrupção da serial
	REN = 1; 					// Habilita a recepção da serial
	PCON |= 0x80; 		// SMOD = 1
	
	SM0 = 0;					// SCON configuração 
	SM1 = 1;					// SCON configuração
	SM2 = 0;					// SCON configuração
}

void timer1_inicializa(){
  TR1 = 0;              						//Desliga Timer1
  TMOD = (TMOD & 0xF0)|0x01; 				//Timer 1 programado no Modo 2 (8 bits)
  TH1 = 0xCC; 											// Programa valor de contagem do Timer1
  TR1 = 1;      										// Habilita contagem do timer 0
  }

void isr_serial() interrupt 4 using 2{
if(TI){
	TI = 0; // Tem que setar manualmente pra 0
	SBUF = 0x41;
	
// --------------
}
if(RI){
	RI = 0; // Tem que setar manualmente pra 0
// ---------------
}
}

void main(){
	timer_inicializa();
	serial_inicializa();
	
	SBUF = 0x41; //Carregou o char 'a' no buffer
	char c = SBUF; //Carrega no char c oque está salvo no buffer
	
	return;
}
