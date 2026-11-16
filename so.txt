int processos[11];
int setorInicial[11];
int tamanho[11];
int setorFinal[11];
int filaRR[11];
int processoAtual;

void iniciaTabela(void){
	/*gcdbinario*/
	setorInicial[1] = 10;
	tamanho[1] = 65;
	setorFinal[1] = 10;
	/*fatorial*/
	setorInicial[2] = 11;
	tamanho[2] = 72;
	setorFinal[2] = 11;
	/*fibonacci*/
	setorInicial[3] = 12;
	tamanho[3] = 70;
	setorFinal[3] = 12;
	/*mmc*/
	setorInicial[4] = 13;
	tamanho[4] = 83;
	setorFinal[4] = 13;
	/*media*/
	setorInicial[5] = 14;
	tamanho[5] = 90;
	setorFinal[5] = 14;
	/*potencia*/
	setorInicial[6] = 15;
	tamanho[6] = 65;
	setorFinal[6] = 15;
	/*inverter*/
	setorInicial[7] = 16;
	tamanho[7] = 124;
	setorFinal[7] = 16;
	/*maxvetor*/
	setorInicial[8] = 17;
	tamanho[8] = 104;
	setorFinal[8] = 17;
	/*buscabinbinario*/
	setorInicial[9] = 18;
	tamanho[9] = 146;
	setorFinal[9] = 19;
	/*sort*/
	setorInicial[10] = 20;
	tamanho[10] = 203;
	setorFinal[10] = 21;
	processoAtual = 0;
}


void carregaPrograma(int p){
	int setorAtual; int tamanhoprogramAtual; int setorFinalAtual;
	setorAtual = setorInicial[p];
	tamanhoprogramAtual = tamanho[p];
	setorFinalAtual = setorFinal[p];
	setSetorInicial(setorAtual);
	setTam(tamanhoprogramAtual);
	setSetorFinal(setorFinalAtual);
	buscaPrograma();
}


void executaProcesso(int p){
	int i; 
	i = 0;
	exibelcd(2);
	carregaPrograma(p);
	exibelcd(9);
	setPid(p);
	while(i < 64){
		savereg(i, i);
		i = i + 1;
	}
	/*carregaOffset(p);*/
	executa(p);
	cleanMem();
}

void executaComPreempcao(int n){
    int i; int numHalts; int pAtual; int haltsAtual; int j;
    i = 0; numHalts = 0; haltsAtual = 0; 
	contHalts();
    while(numHalts < n){
        pAtual = filaRR[i];

        if(pAtual != 0){
            carregaPrograma(pAtual);
            j = 0;
			while(j < 64){
				savereg(j, j);
				i = i + 1;
			}
            setPid(pAtual);
            executaProcess(pAtual);
            cleanMem();
			
            numHalts = verificaHalt();
            if(haltsAtual < numHalts){
                filaRR[i] = 0;
                haltsAtual = haltsAtual + 1;
            }
            else{
            }
        }
        else{
        }

        i = i + 1;
        if (i == n) {
            i = 0;
        }
        else {
        }
    }
	contHalts();
}

void renomearProcesso(int p){
	int i;
}

void deletaProcesso(int p){
	int i;
}

void main(void)
{
	int i; int p; int n; int j;
	iniciaTabela();
	i = 0; n = 0; j = 0;
	while(i != 32){
		exibelcd(0);
		i = input();
		if(i == 1){
			exibelcd(1);
			p = input();
			executaProcesso(p);
			exibelcd(4);
		}
		else if(i == 2){
			exibelcd(5);
			n = input();
			while(j < n){
				filaRR[j] = input();
				j = j + 1;
			}
			exibelcd(6);
			executaComPreempcao(n);
			exibelcd(10);
			j = 0;
		}
		else if(i == 3){
			exibelcd(11);
			p = input();
			renomearProcesso(p);
		}
		else if(i == 4){
			exibelcd(12);
			p = input();
			exibelcd(13);
			deletaProcesso(p);
		}
	}
}