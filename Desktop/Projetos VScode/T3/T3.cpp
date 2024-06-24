#include <iostream>
using namespace std;
#include <locale.h>
#include <ctime>


#define f 5
int main() {  
  srand(time(NULL));
  setlocale(LC_ALL, "pt_BR.UTF-8");

   int Matriz_Espelho[f] [f];
   int linha,coluna;
   int bombas = f -3;  // defino que o numero de bombas ira ser -3 para o numero base do tamanho da matriz
   int t;  //variavel de controle do switch

 do {
    cout << "Deseja  jogar? digite 1:  ";  // crio um switch para eu poder jogar + de 1 vez
    cin >> t;
   switch (t)
   {    
   case 1:

    for(linha=0;linha<f;linha++){
      for(coluna=0;coluna<f;coluna++){
              Matriz_Espelho[linha][coluna]=0;  // Crio a matriz espelho que ira conter as respostas, e gero tudo com 0, ou seja vazia
      }
    }

          int coluna_aleatoria;
          int linha_aleatoria;
          do{
            do {
                   coluna_aleatoria=rand()%10;
            } while (coluna_aleatoria >= 0 && coluna_aleatoria > 4);

            do {
                   linha_aleatoria=rand()%10;
            } while (linha_aleatoria >= 0 && linha_aleatoria > 4);

            
      
             if (Matriz_Espelho[linha_aleatoria][coluna_aleatoria] != 9 ){  // pego as posições aleatória que eu gerei e vejo se nela ja tem uma bomba, se não tiver agora tem
               Matriz_Espelho[linha_aleatoria][coluna_aleatoria] = 9;  // defini que onde tem bomba vai ser igual a 9, ja que no maximo uma posição pode ter 8 bombas ao seu redor
               bombas--; // tiro 1 boma do contador
             } 
            

             int  linha_dica = 0;   
             int coluna_dica = 0;           

               for(linha_dica=-1;linha_dica < 2;linha_dica++){  // inicio o código que ira fazer que todas as posições ao redor da bomba ganhem +1 de valor, ou seja indique que tem uma bomba proxima
                    for(coluna_dica=-1;coluna_dica < 2;coluna_dica++){   

                          if (Matriz_Espelho[linha_aleatoria - linha_dica][coluna_aleatoria - coluna_dica] != 9) {  // garante que ele não vai mexer onde tem uma bomba

                                 if (linha_aleatoria - linha_dica >= 0 && coluna_aleatoria - coluna_dica >= 0 ){  // garante que se a posição for negativa, ou seja não existe, ele não vai fazer nada e bugar o código

                                       if (linha_aleatoria - linha_dica < f  && coluna_aleatoria - coluna_dica < f  ){  // garante que ele não vai ultrapassar o limite da matriz e bugar
                                          Matriz_Espelho[linha_aleatoria - linha_dica][coluna_aleatoria - coluna_dica]++;  // se passou por todos os verificadores a posição vai ganhar +1 de indicador de bomba ao seu redor
                                       }
                                 }
                          }   
                    }
               }




              
          } while (bombas > 0);

         int Matriz_Resposta[f] [f];  // gera matriz que o jogador ira ver
         int jogo = 1;  // variavel pra definir fim do jogo

            for(linha=0;linha<f;linha++){
                    for(coluna=0;coluna<f;coluna++){
                     Matriz_Resposta[linha][coluna]= 10;  // defino 10 como valor para não descoberto
                   }
             }
 
               int linha_resposta;
               int coluna_resposta;
               int posicao = (f * f) -(f - 3); // variavel pra controlar quantas posições estão faltando serem descobertas
               int vitoria = 0; // variavel para controlar mensagem no final do jogo, dizendo se ele acabou pq o jogador perdeu ou ganhou  

        do {
                cout << " Bem vindo ao campo minado, primeiro digite a linha que voce deseja verificar, depois a coluna: ";
                cin >> linha_resposta >> coluna_resposta;
                 system("cls");
                linha_resposta = linha_resposta -1;  // reduz 1 na posição para facilitar o jogo para o jogador
                coluna_resposta = coluna_resposta -1;  
                int matriz_repetidos[f] [f];  // crio uma 3 matriz para verificar os numeros repetidos
            

                 if (coluna_resposta > f || linha_resposta > f || linha_resposta < 0 || coluna_resposta < 0) {  // verifica se o numero digitado é valido
                      cout << "Numero fora do parametro da matriz, digite um numero valido" << endl ;
                    } else   if (matriz_repetidos[linha_resposta][coluna_resposta] == 11){  // verifica se a posição ja não foi digitada
                                 cout << "Posicao ja revelada" << endl;
                          }  else{ 

                                    Matriz_Resposta[linha_resposta][coluna_resposta] = Matriz_Espelho[linha_resposta][coluna_resposta];  // pego a inforamção da matriz espelho (escondida) e passo para a matriz respota (matriz que o jogador ve)
               
                                   if (Matriz_Espelho[linha_resposta][coluna_resposta] == 9) {    
                                      jogo = 0;
                                    } 

                                   matriz_repetidos[linha_resposta][coluna_resposta] = 11; // defino uma posição ja descoberta como 11, assim posso verificar futuramente no código para o jogador não repetir a mesma posição

                                  if (matriz_repetidos[linha_resposta][coluna_resposta] == 11) {  // se a posição for  igual de 11, ou seja não revelada, diminui 1 no contador de posições restante
                                     posicao--;
                                    }
               
                               }

                               if (posicao == 0){    // se o jogador revelar todas as posições o jogo acaba
                                jogo = 0;  // variavel que controla o fim do jogo
                                vitoria = 1;  // variavel para saber no final do jogo se o usuario perdeu ou ganhou
                               }
                 cout << "colunas-> " <<"1       2       3       4       5 "<< endl;  // crio o indicador de colunas pra acilitar a jogabilidade
                 for(linha=0;linha<f;linha++){   // gera matriz pro jogador
                     cout <<linha + 1 << "-\t";  // crio o indicador de linha pra acilitar a jogabilidade

                        for(coluna=0;coluna<f;coluna++){      // for que ira imprimir na tela a matriz pro usuario jogar

                             if (Matriz_Resposta[linha][coluna] == 10) {  // se for = 10, valor que defini para os indefinidos, gera um colchetes em branco
                                cout << "[   ] \t" ;
                              } else{
                                   cout << "  " << Matriz_Espelho[linha][coluna] << " \t";
                                 }
                        }   
                     cout << endl;
                  }                
          } while (jogo == 1);

        if (vitoria == 1) {
            cout << "Voce venceu, descobriu todas as posicoes sem bomba" << endl;
        } else {
            cout << "Voce Perde, descobriu uma bomba" << endl;        
        }

    break;
   }

  } while (t == 1);
  cout << "Programa encerrado";
}