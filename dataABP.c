#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dataABP.h"

estruturaABP* InsereNodos(estruturaABP *arv,  int calories, char nome[SIZE_NAME]){ // FUNÇÃO PARA INSERIR OS NODOS NA ABP
    int compare;

    if (arv == NULL){
        arv = (estruturaABP *)malloc(sizeof(estruturaABP));
        arv->calories = calories;
        strcpy(arv->name, nome);

        arv->esq = NULL;
        arv->dir = NULL;
        return arv;
        
    }else{

        // compare = strcmp(strlwr(nome), strlwr(arv->name));
        // for (int i = 0; i < strlen(nome) + 1; i++) {
        //     if (i == 0 || nome[i - 1] == ' ')
        //         nome[i] = toupper(nome[i]);
        //     else
        //         nome[i] = nome[i];
        // }
        // for (int i = 0; i < strlen(arv->name) + 1; i++) {
        //     if (i == 0 || arv->name[i - 1] == ' ')
        //         arv->name[i] = toupper(arv->name[i]);
        //     else
        //         arv->name[i] = arv->name[i];
        // }

        // O CÓDIGO COMENTADO ACIMA REALIZA A COMPARAÇÃO DAS STRINGS NO CASE-SENSITIVE 
        // OS LAÇOS FORAM RETIRADOS DO GOOGLE PARA RETORNAR AS PALAVRAS A TER APENAS A PRIMEIRA LETRA MAIUSCULA
        // , PORÉM ALGUMAS PALAVRAS NO BD NÃO INICIAM COM LETRAS MAIUSCULAS, LOGO APRESENTARIA ERRO

        compare = strcmp(nome, arv->name); // COMPARE GUARDA O VALOR DA COMPARAÇÃO DAS STRINGS 
        if (compare < 0){
            arv->esq = InsereNodos(arv->esq, calories, nome);
        }else if (compare >= 0){
            arv->dir = InsereNodos(arv->dir, calories, nome);
        }
    }
    return arv;
}

int Altura (estruturaABP *arv){ // FUNÇÃO PARA CALCULAR A ALTURA DA ÁRVORE 
    int Alt_Esq, Alt_Dir; // FUNÇÃO APRESENTADA EM AULA
    
    if (arv == NULL){
        return 0;
    }else{
        Alt_Esq = Altura (arv->esq);
        Alt_Dir = Altura (arv->dir);
        if (Alt_Esq > Alt_Dir){
            return (1 + Alt_Esq);
        }else{
            return (1 + Alt_Dir);
        }
    }
}


estruturaABP* Consulta(estruturaABP *a, char *chave){ // FUNÇÃO APRESENTANDA PELA PROFESSORA PARA O TRABALHO
while (a!=NULL){
    comp++;
    if (!strcmp(a->name,chave)){
        comp++;
        return a;
    }else {
        comp++;
        if (strcmp(a->name,chave)>0)
            a = a->esq;
        else
            a = a->dir;
    }
}
    return NULL;
}

int VerificaCalorias(estruturaABP *arv, char item[SIZE_NAME]){ // FUNÇÃO CHAMADA PARA VERIFICAR AS CALORIAS DOS ALIMENTOS
    int calorias;   // RECEBE A ÁRVORE DO BD E O ALIMENTO PRESENTE NO ARQUIVO DAY

    if(arv != NULL){
        if(strcmp(arv->name, item) == 0){ // CASO AS PALAVRAS SEJAM IGUAIS
            calorias =  arv->calories; // RETORNA A QUANTIDADE DE CALORIAS/100G DO ALIMENTO 
            return calorias;
        }else{
            if(strcmp(item, arv->name) < 0){ // SENÃO SE VERIFICA SE DEVE PROCURAR NO LADO DIREITO OU ESQUERDO DA ÁRVORE
                calorias = VerificaCalorias(arv->esq, item);
            }else{
                calorias = VerificaCalorias(arv->dir, item);
            }
        }
    }else{
        return 0;
    }

}