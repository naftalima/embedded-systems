/********
Alunos:
Eneri D'Angelis (emd)
Nathalia Lima (npl)
Rafael Vasconcelos (rjav) 

*********/


#include <REG51F.H>

sbit b0 = P2^0;
sbit b1 = P2^1;

int count = 0;
int count1;
int count2;

void watchingP0(){
	static char pEstado = 0x00;
	switch (pEstado){
		case  0x00: if (b0==0x01){ /* bit 0 de P2 passa de 0 -> 1*/
			P1 = (P1 & 0xF0) | (P0 & 0x0F);
			pEstado = 0x01;
			count2 = count;
		}
		break;
		case  0x01 : if (count - count2 > 10000){/* espera 1s */
			P1 = (P1 & 0xF0) | 0x00;
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
			count1 = count;
		}
		break;
		case  0x01 : if (count - count1 > 10000){/* espera 1s */
			P1 = 0x00 | (P1 & 0x0F);
			pEstado = 0x02;
		}
		break;
		case  0x02 : if (b1==0x00){/* bit 0 de P2 passa de 1 -> 0*/
			pEstado = 0x00;
		}
		break;
	}
}


void main() 
{
	while (1){
		watchingP0();
		watchingP1();
		count ++;
	}
}

/*
Sistema embarcado é um sistema reativo.
*/

/*
AULA 2

Experimento:
Usando o 80C51FA da Intel, com 12MHz, implemente a especificação abaixo 
usando uma função para cada lado com o modelo de Maquinas de Estados. 
O main() deve ter um loop infinito que chama as duas funções.

Se o bit 1 de P2 mudar de 0 para 1
   Atribua os 4 bits mais significativos de P0 
     aos 4 bits mais significativos de P1
     Após 1 segundo (conte via software)
   Atribua zero aos 4 bits mais significativos
     de P1 e retorne para esperar nova transição
		 
Se o bit 0 de P2 mudar de 0 para 1
   Atribua os 4 bits menos significativos
    de P0 aos 4 bits menos significativos de P1
    Após 1 segundo (conte via software) 
   Atribua zero aos 4 bits menos significativos
    de P1 e retorne para esperar nova transição

*/