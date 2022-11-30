#define SIZE_NAME 60
#define SIZE 80
int comp;

typedef struct structABP{
        int calories;
        char name[SIZE_NAME];
        struct structABP *esq;
        struct structABP *dir;
}estruturaABP;

estruturaABP* InsereNodos(estruturaABP *arv, int calories, char name[]);
estruturaABP* Consulta(estruturaABP *arv, char *chave); // FUNÇÃO DISPONIBILIZADA PELA PROFESSORA
int Altura (estruturaABP *arv);
int VerificaCalorias(estruturaABP *arv, char item[]);