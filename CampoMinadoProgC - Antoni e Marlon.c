// alteracoes em relacao ao codigo orinal foram feitas no intervalo(201 - 303)
//Antoni e Marlon
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _QtBombas_  5
#define _Height_   10
#define _Width_    10
#define _BOMBA_    -8
#define _ABERTA_    0
#define _FECHADA_  -1
#define _VAZIA_    -2

#define _FLAG_    -3
#define _PERDEU_  -4

int AbreArea( int Tabuleiro[_Height_][_Width_],
              int TabVisual[_Height_][_Width_],
              int X /*coluna */,
              int Y /* linha */,
			  bool celulaAntVazia){
    int cont = 0;
    
    
    // verifica se posição selecionada pode ser aberta.
    if( TabVisual[Y][X] == _FECHADA_ && Tabuleiro[Y][X] == _VAZIA_ ){
    	
        TabVisual[Y][X] = _ABERTA_;
        cont++;
       
        if( Y > 0 )              if( TabVisual[Y-1][X] == _FECHADA_ ) cont+= AbreArea(Tabuleiro, TabVisual, X, Y-1, true); // conta acima
        if( Y < (_Height_ - 1))  if( TabVisual[Y+1][X] == _FECHADA_ ) cont+= AbreArea(Tabuleiro, TabVisual, X, Y+1, true); // conta abaixo
        if( X < (_Width_ - 1 ))  if( TabVisual[Y][X+1] == _FECHADA_ ) cont+= AbreArea(Tabuleiro, TabVisual, X+1, Y, true); // conta a direita
        if( X > 0 )              if( TabVisual[Y][X-1] == _FECHADA_ ) cont+= AbreArea(Tabuleiro, TabVisual, X-1, Y, true); // conta a direita
       
		}else if ( TabVisual[Y][X] == _FECHADA_ && Tabuleiro[Y][X] > 0 && Tabuleiro[Y][X] <=8 && celulaAntVazia ){
        TabVisual[Y][X] = _ABERTA_;
        cont++;
     	}
    
    return ( cont );
  
}

void MostraTabuleiro(int Tabuleiro[_Height_][_Width_],int TabVisual[_Height_][_Width_],int pontos)
{
    int i, L, C;
    
    printf("Pontuacao: %d\n",pontos);
    
    printf("      ");
    
    //if para aumentar o tamanho do tabuleiro sem problemas
    for (C = 0; C < _Width_; C++){
        if(C < 9){
        	printf("  %d  ", C+1); 
		}else{
			if(C < 99){//so funciona ate 999
				printf(" %d  ", C+1); 
			}
		} 
    }
    
	printf("\n");
	
	
    // parte superior da moldura
    printf("     %c", 201);
    for (i = 0; i < _Width_; i++)
    {
        printf("%c%c%c%c%c", 205, 205, 205, 205, 205);
    }
    printf("%c\n", 187);

    for (L = 0; L < _Height_; L++)
    {
    	//if para aumentar o tamanho do tabuleiro sem problemas
    	if(L < 9){
    		printf("  %d  ", L+1);
		}else{
			if(L < 99){
				printf(" %d  ", L+1);
			}else{
				if(L < 99){//so funciona ate 999
					printf(" %d  ", L+1);
				}	
			}
		}
        printf("%c", 186);
        for (C = 0; C < _Width_; C++)
        {
            if (TabVisual[L][C] == _ABERTA_)
            {
                switch (Tabuleiro[L][C])
                {
                case -8: printf("  %c  ", 225); break;
                case 1:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 2:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 3:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 4:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 5:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 6:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 7:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 8:  printf("  %d  ", Tabuleiro[L][C]); break;
                default: printf("  .  "); break;
                }
            }
            else
            {
            	if(TabVisual[L][C] == _FLAG_){
            		printf("  %c  ", 232);
				}else{
					if(TabVisual[L][C] == _PERDEU_){
						printf("  %c  ", 207);
					}else{
						printf("  %c  ", 254);
					}
				}
            }
        }
        printf("%c\n", 186);
    }

    // parte inferior da moldura
    printf("     %c", 200);
    for (i = 0; i < _Width_; i++)
    {
        printf("%c%c%c%c%c", 205, 205, 205, 205, 205);
    }
    printf("%c\n", 188);

}


void MontaTabuleiro(int Tabuleiro[_Height_][_Width_])
{
    int L, C;
    int qtBombasAlocadas = 0;
    bool achei = false;

    // "limpar" a matriz
    for (L = 0; L < _Height_; L++)
    {
        for (C = 0; C < _Width_; C++)
        {
            Tabuleiro[L][C] = _VAZIA_;
        }
    }

    // sorteia as posições das bombas
    while (qtBombasAlocadas < _QtBombas_)
    {
        achei = false;
        int X = rand() % (_Width_  - 1); // sorteia uma posição X (coluna)
        int Y = rand() % (_Height_ - 1); // sorteia uma posição Y (linha)

        if (Tabuleiro[Y][X] == _BOMBA_)
        {
            achei = true;
        }

        if (!achei)
        {
            Tabuleiro[Y][X] = _BOMBA_;
            qtBombasAlocadas++;
        }

    }

    // contagem de bombas para cada célula
    int contBombas = 0;
    for (L = 0; L < _Height_; L++)
    {
        for (C = 0; C < _Width_; C++)
        {
            if (Tabuleiro[L][C] != _BOMBA_)
            {
                contBombas = 0;
                if (L > 0)              if (Tabuleiro[L - 1][C] == _BOMBA_) contBombas++; // conta acima
                if (L < (_Height_ - 1)) if (Tabuleiro[L + 1][C] == _BOMBA_) contBombas++; // conta abaixo
                if (C < (_Width_ - 1))  if (Tabuleiro[L][C + 1] == _BOMBA_) contBombas++; // conta a direita
                if (C > 0)              if (Tabuleiro[L][C - 1] == _BOMBA_) contBombas++; // conta a esquerda

                if (L < (_Height_ - 1) && C < (_Width_ - 1)) if (Tabuleiro[L + 1][C + 1] == _BOMBA_) contBombas++; // diag inf direita
                if (L < (_Height_ - 1) && C > 0)             if (Tabuleiro[L + 1][C - 1] == _BOMBA_) contBombas++; // diag inf esquerda
                if (L > 0 && (C < _Width_ - 1))              if (Tabuleiro[L - 1][C + 1] == _BOMBA_) contBombas++; // diag sup direita
                if (L > 0 && C > 0)							 if (Tabuleiro[L - 1][C - 1] == _BOMBA_) contBombas++; // diag sup esquerda

                Tabuleiro[L][C] = (contBombas == 0 ? _VAZIA_ : contBombas);
                // caso não exista nenhuma bomba ou contagem igual a zero, entao inicia a célula com o status _VAZIA_.
            }
        }
    }

}

void gameplay(int Tabuleiro[_Height_][_Width_],int TabVisual[_Height_][_Width_]){
	bool perdeu = false,ganhou = false;//variavel pra testar vitoria ou derrota
	int op, x, y, flag = 0, ponto = 0;
 	do{
 		printf("Digite de acordo com a opcao:\n");
 		printf("Digite 1 para fazer jogada\n");
 		printf("Digite 2 para colocar flag\n");
 		printf("Digite 3 para tirar flag\n");
 		scanf("%d", &op);
 		if(op == 1){//jogada normal
 			printf("Digite a linha\n");
 			scanf("%d", &x);//digita linha
 			printf("Digite a coluna:\n");
 			scanf("%d", &y);//digita coluna
 			x-=1;y-=1;//sincroniza entrada com valor na matriz
 			
			system("cls");
 			if(Tabuleiro[x][y] == _BOMBA_){//achou bomba
	 			TabVisual[x][y] = _ABERTA_;
				perdeu = true;
				for (x = 0; x < _Height_; x++){//mostrando bombas apos perder
			        for (y = 0; y < _Width_; y++){
			            if(TabVisual[x][y] == _FECHADA_ && Tabuleiro[x][y] == _BOMBA_){
			            	TabVisual[x][y] = _PERDEU_;
						}
			        }
			    }
			}else{
				if(Tabuleiro[x][y] > 0){//achou contador
					TabVisual[x][y] = _ABERTA_;//abre celula
					ponto+=100;//aumenta pontos
				}else{
					if(Tabuleiro[x][y] == _VAZIA_){//abre area
						ponto+= (50*AbreArea(Tabuleiro, TabVisual, x, y, false));
					}
				}
			}
		}else{
			if(op == 2){//coloca flag
				int x, y;
	
				printf("Digite a linha para colocar a flag:\n");
			 	scanf("%d", &x);
			 	printf("Digite a coluna para colocar a flag:\n");
			 	scanf("%d", &y);
			 	
			 	TabVisual[x-1][y-1] = _FLAG_;
			 	
			 	flag++;
			}else{
				if(op == 3){//tira flag
					int x, y;
	
					printf("Digite a linha para tirar a flag:\n");
				 	scanf("%d", &x);
				 	printf("Digite a coluna para tirar a flag:\n");
				 	scanf("%d", &y);
				 	
				 	TabVisual[x-1][y-1] = _FECHADA_;
				 	flag--;
				}
			}
		}
		ganhou = true;//muda para true para testar vitoria
		int i, j;
		for (i = 0; i < _Height_; i++){
	        for (j = 0; j < _Width_; j++){
	            if(TabVisual[i][j] == _FECHADA_ && Tabuleiro[i][j] != _BOMBA_){//testa se tem celula fechada que nao seja bomba
	            	ganhou = false;
				}
	        }
	    }
		if(flag != _QtBombas_){//testa se quantidade de flag eh igual quantidade de bomba
			ganhou = false;
		}
		system("cls");
		MostraTabuleiro(Tabuleiro, TabVisual, ponto);
	}while(!perdeu && !ganhou );//while
	if(ganhou){//testa se saiu do loop por vitoria
		printf("Parabens, voce venceu!\n");
	}else{
		if(perdeu){//testa se saiu do loop por derrota
			printf("voce perdeu!\n");
		}
	}
 }//gameplay

void inicio(int Tabuleiro[_Height_][_Width_],int TabVisual[_Height_][_Width_]){
    int i, j;

    srand(time(NULL)); // inicia a semente do randomizador

    for (i = 0; i < _Height_; i++){
        for (j = 0; j < _Width_; j++){
            TabVisual[i][j] = _FECHADA_; // todas as células estao fechadas!
        }
    }
    MontaTabuleiro(Tabuleiro);
    
  
    MostraTabuleiro(Tabuleiro, TabVisual,0);

}//inicio

int main(){
	int Tabuleiro[_Height_][_Width_];
    int TabVisual[_Height_][_Width_];
    inicio(Tabuleiro, TabVisual);
    gameplay(Tabuleiro, TabVisual);
}

