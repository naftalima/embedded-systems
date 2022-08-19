/******************************
Alunos:
	Eneri D'Angelis (emd)
	Nathalia Lima (npl)
	Rafael Vasconcelos (rjav) 
******************************/

#include <REG51F.H>

bit recebeuString = 0;

char rxBuffer[15];
char txBuffer[15];
char aux; 

int writerRx = 0;
int readerRx = 0;

int writerTx = 0;
int readerTx = 0;

char situation;
char writeFlag = 0;

char RxBufferVazio(){
	if(readerRx == writerRx){
		return 1;
	}else{
		return 0;
	}
}

char receiveChar(){
	return rxBuffer[readerRx];
}
void receiveString(char *s){
	situation = RxBufferVazio();
	while(!situation){
		s[readerRx] = receiveChar();
		readerRx ++;
		situation = RxBufferVazio();
	}
	readerRx = 0;
	writerRx = 0;
}
void sendChar(char c){
	txBuffer[writerTx] = c;
	writerTx++;
}
void sendString(char *s){
	writeFlag = 1;
	do{
		sendChar(s[writerTx]);
	}while(s[writerTx]!='$');
}

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
		if(writeFlag){
				aux = txBuffer[readerTx];
				SBUF = aux;
				readerTx++;
		}
			rxBuffer[writerRx] = SBUF;
		if(rxBuffer[writerRx] == '$'){
			recebeuString = 1;
		}
		writerRx++;
	}
}

void main(){
	char val[15];
	EA = 1;
	serial_inicializa();
	timer1_inicializa();
	while(1){
		if(recebeuString){
			receiveString(val);
			recebeuString = 0;
			sendString(val);
		}
	};
	
	return;
}