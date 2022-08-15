/******************************
Alunos:
	Eneri D'Angelis (emd)
	Nathalia Lima (npl)
	Rafael Vasconcelos (rjav) 
******************************/

#include <REG51F.H>

char c;

bit recebeuString = 0;

char rxBuffer[15];
char txBuffer[15];

int writerRx = 0;
int readerRx = 0;

int writerTx = 0;
int readerTx = 0;

char receiveChar(){
	return rxBuffer[readerRx];
}
void receiveString(char *s){
	char key = receiveChar();
	readerRx ++;
	s = rxBuffer;
}
void serial_inicializa(){
	ES = 1; 					// Habilita a interrupção da serial
	REN = 1; 					// Habilita a recepção da serial
	PCON |= 0x80; 		// SMOD = 1
	
	SM0 = 0;					// SCON configuração 
	SM1 = 1;					// SCON configuração
	SM2 = 0;					// SCON configuração
}

void isr_serial() interrupt 4 using 2{
	if(TI){
	TI = 0; // Tem que setar manualmente pra 0
	// --------------
	}
	if(RI){
	RI = 0; // Tem que setar manualmente pra 0
	rxBuffer[writerRx] = SBUF;
	if(rxBuffer[writerRx] == '$'){
		recebeuString = 1;
	}
	writerRx += 1;
	}
}

void main(){
	char *val;
	EA = 1;
	serial_inicializa();
	while(1){
		if(recebeuString){
			recebeuString = 0;
			receiveString(val);
//		sendString();
		}
	};
	
	return;
}