/********
Alunos:
Eneri D'Angelis (emd)
Nathalia Lima (npl)

*********/

#include <REG51F.H>

/* mascara de bit */
sbit b0 = P2^0;
sbit b1 = P2^1;

void main()
{
	
	while(1){
		if (b0){
			P1 = (P1 & 0xF0) | (P0 & 0x0F);
		} else {
			P1 = (P1 & 0xF0);
		}		
		if (b1){
		P1 = (P1 & 0x0F) | (P0 & 0xF0);
		} else {
		P1 = (P1 & 0x0F);
		}
	}
}