#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#include "dataABP.h"

int main(int argc, char *argv[]){

    setlocale(LC_ALL, ""); // PARA MINIMIZAR OS ERROS COM ACENTUAÇÃO
    clock_t start, end;  // DECLARANDO PARA CONTAGEM DO TEMPO

    if(argc != 4){      // VERIFICANDO SE TODOS OS PARÂMETROS FORAM PASSADOS NA CHAMADA DO PROGRAMA .EXE
        printf("Faltando parametros!");
        return 0;
    }

    int calorias, value, totalC = 0, qtdNodos = 0;   // DECLARAÇÃO DAS VARIÁVEIS
    char linhaArquivo[SIZE] = "";
    char name[SIZE_NAME] = "";


    // ABERTURA DE ARQUIVOS CONFORME PASSAGEM DOS PARÂMETROS
    FILE *BD = fopen (argv[1], "r");      // BD
    if (BD == NULL){
        printf("Nao consegui abrir o arquivo.");
        return 0;
    }
    // =====================================
    FILE *Day = fopen (argv[2], "r");     // DIA
    if (Day == NULL){
        printf("Nao consegui abrir o arquivo.");
        return 0;
    }
    // =====================================
    FILE *Saida = fopen (argv[3], "w+");    // TXT  
    if (Saida == NULL){
        printf("Nao consegui abrir o arquivo.");
        return 0;
    }else
    // ======================================

    // IMPRIME NO ARQUIVO DE SAIDA AS PRIMEIRAS INFORMAÇÕES
    fprintf(Saida, "%s %s %s %s\n\n", "Calorias calculadas para", argv[2], "usando", argv[1]);

    start = clock(); // INICIA A CONTAGEM DE TEMPO DE EXECUÇÃO (O IMPORTANTE É ESTAR NO MESMO LOCAL DA AVL)

    estruturaABP *ABP; // CRIAÇÃO DA ESTRUTURA ABP

    do {
        fseek(BD, -1, SEEK_CUR);            // RETORNANDO O MARCADOR DE LEITURA PARA O INICIO DA LINHA CASO NÃO ESTEJA
        fgets(linhaArquivo, SIZE, BD);      // PEGANDO UMA LINHA DO ARQUIVO DO BANCO DE DADOS
        
        char *p = strtok(linhaArquivo, ";");    // REALIZANDO A PASSAGEM PARA O PONTEIRO P COM STRTOK
        int aux = 0;

        do {
            if(aux == 0){
                strcpy(name, p);    // SE AUX = 0 AINDA É A PRIMEIRA CHAMADA, LOGO PRIMEIRA INFORMAÇÃO, LOGO NOME
            }else{
                value = atoi(p);    // SENÃO CONVERTE O TEXTO (NUMERO) EM UM INTEIRO
            }
            aux++;                  
        }while((p = strtok(NULL, ";"))); 

        ABP = InsereNodos(ABP, value, name); // APÓS CHEGAR NO FIM DA LINHA, INSERE AS INFORMAÇÕES NA ARVORE
        qtdNodos++;       // CONTA O NODO INSERIDO

    }while(fgetc(BD) != EOF);   // FAZ ISSO ENQUANTO O ARQUIVO NÃO CHEGAR NO FIM (EOF "End Of File")

    printf("\n[ LEITURA GRAVACAO OK ]\n");

    int auxCalcC = 0;
    do {
        fseek(Day, -1, SEEK_CUR);
        fgets(linhaArquivo, SIZE, Day);
        
        char *p = strtok(linhaArquivo, ";");       // REALIZA A MESMA COISA, POREM DO ARQUIVO DAY
        int aux = 0;

        do {
            if(aux == 0){
                strcpy(name, p);
            }else{
                value = atoi(p);
            }
            aux++;
        }while((p = strtok(NULL, ";")));

        calorias = VerificaCalorias(ABP, name);     // AGORA FAZ A BUSCA NA ABP DO NOME LIDO PARA PEGAR AS CALORIAS

        // PRINT PADRÃO INSERINDO AS INFORMAÇÕES RECEBIDAS (JÁ COM O CALCULO P 100G) NO ARQUIVO DE SAIDA
        fprintf(Saida, "%d%s %s %s %s %d %s %d %s\n", value,"g", "de", name, "(", calorias, "calorias por 100g ) = ", (value*calorias)/100 , "calorias");

        Consulta(ABP, name); // CHAMANDO A FUNÇÃO DE CONSULTA

        totalC = (value*calorias)/100; // CRIANDO UM TOTALCALORIAS PARA REALIZAR O CALCULO
        auxCalcC += totalC;            // PARA QUE POSSA SER ARMAZENADO PARA TER O CALCULO TOTAL 

    }while(fgetc(Day) != EOF);
    
    end = clock();  // ENCERRA A CONTAGEM DE TEMPO
    float seconds = (float)(end - start)/CLOCKS_PER_SEC *1000;  // TRANSFORMA A INFORMAÇÃO DO TEMPO


    // PRINTA AS INFORMAÇÕES SOBRE A ABP NO ARQUIVO
    fprintf(Saida, "\n%s %d %s", "Total de", auxCalcC, "calorias consumidas no dia.");
    fprintf(Saida, "\n\n%s\n%s %d\n%s %d\n%s %d\n%s %d\n\n\n%s %.5f %s", "========  ESTATÍSTICAS ABP ============",
    "Numero de nodos: ", qtdNodos, "Altura: ", Altura(ABP), "Rotações: ", 0, "Comparações: ", comp, "Tempo de execução: ", seconds, "milisegundos");

    fclose(BD);     // FECHA TODOS OS ARQUIVOS ABERTOS
    fclose(Day);
    fclose(Saida);

    printf("ARQUIVO PRONTO\n");     // TUDO CERTO :)
    return 0;
}