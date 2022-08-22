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

int writerRx = 0;
int readerRx = 0;

int writerTx = 0;
int readerTx = 0;

char aux;

char RxBufferVazio(){
	if(readerRx == writerRx){
		return 1;
	}else{
		return 0;
	}
}
void zeraString(char *s){
	int i;
	for(i=0;i < 15; i++){
		s[i] = '_';
	}
}
void escreveRx(){
	if(SBUF == '$'){
		recebeuString = 1;
	}
	if((writerRx + 1)%15 != readerRx){
		rxBuffer[writerRx] = SBUF;
		writerRx = (writerRx + 1)%15;
	}
	return;
}
void sendChar(char c){
	txBuffer[writerTx] = c;
	writerTx = (writerTx + 1)%15;
	TI = 1;
	readerTx = (readerTx + 1)%15;
}	
void sendString(char *s){
	while(s[writerTx] != '$'){
			sendChar(s[writerTx]);
	};
	return;
	
}	
char receiveChar(){
	return rxBuffer[readerRx];
}
void receiveString(char *s){
	int count = 0;
	while(!RxBufferVazio()){
		s[count] = receiveChar();
		count ++;
		readerRx = (readerRx + 1)%15;
	}
	recebeuString = 0;
	return;
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
	RI = 1;
	// --------------
	}
	if(RI){
	RI = 0; // Tem que setar manualmente pra 0
	if(readerTx != writerTx){
		SBUF = txBuffer[readerTx];
	}else{
		escreveRx();
	}
	// --------------
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
			sendString(val);
			zeraString(val);
		}
	};
	
	return;
}