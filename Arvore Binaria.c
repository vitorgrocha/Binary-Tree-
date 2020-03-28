/*Dupla: Vitor Gomes Rocha | José Carlos Bastos*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h> //getch();

typedef struct arvore {
	int chave;
	char autor[100];
	int num_pag;
	int ano_pub;
	struct arvore *esq;
	struct arvore *dir;
} no;

void inicializa(no **raiz);
int insere(no **raiz, int valor, char autor[], int ano_pub, int num_pag);
int busca(no *raiz, int valor);
void emordem(no *raiz);
void posOrdem(no *raiz);
void preOrdem(no *raiz);
void altura(no *raiz, int *h, int n);
void menu();
void remover(no **raiz, int valor);
no *Maiordir(no **raiz);

int main() {
	int hEsq = 0, hDir = 0, n = 0; //altura
	int op, num_pag, ano_pub, chave, aux;
	char autor[100];
	no *arvore;
	inicializa(&arvore);
    printf("/********Biblioteca********/\n");
    do {
        system("@cls||clear");
		menu();
		scanf("%d",&op);

		switch(op) {
			case 0:
				 break;
			case 1: //inserir
			    printf("Informe Autor do Livro: ");
			    scanf("%s", autor);
			    printf("Informe Ano de Publicacao do Livro: ");
			    scanf("%d", &ano_pub);
			    printf("Informe Numero de Paginas do Livro: ");
			    scanf("%d", &num_pag);
			    printf("Informe o Codigo do Livro: ");
			    scanf("%d", &chave);
			    insere(&arvore, chave, autor, ano_pub, num_pag);
			    hEsq = 0;
			    hDir = 0;
			    altura(arvore->esq, &hEsq, n);
			    altura(arvore->dir, &hDir, n);
			    if(hEsq - hDir > 3 || hEsq - hDir < -3) {
                    printf("\nArvore Desbalanceada!");
			    }
				break;
			case 2:
			    printf("Informe o codigo do livro para a busca: ");
			    scanf("%d", &aux);
				busca(arvore, aux);
				break;
			case 3:
			    printf("Informe o codigo do livro para a remocao: ");
			    scanf("%d", &aux);
			    remover(&arvore, aux);
				if(arvore != NULL) {
                    hEsq = 0;
                    hDir = 0;
					altura(arvore->esq, &hEsq, n);
					altura(arvore->dir, &hDir, n);
					if(hEsq - hDir > 3 || hEsq - hDir < -3) {
						printf("\nArvore Desbalanceada!");
					}
				}
			    break;
			case 4:
				preOrdem(arvore);
                break;
			default:
				printf("\nOpcao Invalida!\n");
				break;
		} getch();
	} while(op!=0);
	return 0;
}

void inicializa(no **raiz) {
	*raiz = NULL;
}

void menu() {//menu
	printf("\n1) Inserir Livro");
	printf("\n2) Buscar Livro");
	printf("\n3) Remover Livro(pelo codigo) Desejado");
	printf("\n4) Imprimir Todo Acervo de Livros");
	printf("\n0) Sair");
	printf("\nOpcao: ");
}

int insere(no **raiz, int valor, char autor[], int ano_pub, int num_pag) {
	no *novo_No;
	if(*raiz == NULL) {
		novo_No = malloc(sizeof(no));
		novo_No->chave = valor;
		strcpy(novo_No->autor, autor);
		novo_No->ano_pub = ano_pub;
		novo_No->num_pag = num_pag;
		novo_No->esq = NULL;
		novo_No->dir = NULL;
		*raiz = novo_No;
		printf("Insercao bem sucedida!");
	} else if(valor > (*raiz)->chave) {
		return insere(&(*raiz)->dir, valor, autor, ano_pub, num_pag);
	} else if(valor < (*raiz)->chave) {
		return insere(&(*raiz)->esq, valor, autor, ano_pub, num_pag);
	} else	printf("Codigo ja esta em uso!");
}

int busca(no *raiz, int valor) {
	if(raiz == NULL) {
		printf("Livro nao encontrado!\n");
	} else if(raiz->chave == valor) {
		printf("Autor: %s\n",raiz->autor);
		printf("Ano Publicacao: %i\n",raiz->ano_pub);
		printf("Numero de Paginas: %i\n",raiz->num_pag);
		printf("Codigo do Livro: %i\n",raiz->chave);
	} else if(valor > raiz->chave) {
		return busca(raiz->dir, valor);
	} else {
		return busca(raiz->esq, valor);
	}
}

void preOrdem(no *raiz){
	if(raiz != NULL){
		printf("Autor: %s\n",raiz->autor);
		printf("Ano Publicacao: %i\n",raiz->ano_pub);
		printf("Numero de Paginas: %i\n",raiz->num_pag);
		printf("Codigo do Livro: %i\n",raiz->chave);
		printf("***********************************\n");
		preOrdem(raiz->esq);
		preOrdem(raiz->dir);
	};
}

void altura(no *raiz, int *h, int n) {
	if (raiz != NULL) {
		altura(raiz->esq, h, n+1);
		altura(raiz->dir, h, n+1);
	} else {
		if(*h < n -1) *h = n-1;
	}
}

no *Maiordir(no **raiz) {
    if((*raiz)->dir != NULL) {
       return Maiordir(&(*raiz)->dir);
    }
    else {
       no *aux = *raiz;

       if((*raiz)->esq != NULL) { // se nao houver essa verificacao, esse no vai perder todos os seus filhos da esq!
          *raiz = (*raiz)->esq;
        }
       else {
            *raiz = NULL;
            return aux;
        }
    }
}

void remover(no **raiz, int valor) {
    if(*raiz == NULL) {   // esta verificacao serve para caso o numero nao exista na arvore.
       printf("Livro nao encontrado para remocao!");
       return;
    }
    if(valor < (*raiz)->chave)
       remover(&(*raiz)->esq, valor);
    else
       if(valor > (*raiz)->chave)
          remover(&(*raiz)->dir, valor);
       else {    // se nao eh menor nem maior, logo, eh o numero que estou procurando!
          no *pAux = *raiz;
          if (((*raiz)->esq == NULL) && ((*raiz)->dir == NULL)){         // se nao houver filhos...
                free(pAux);
                (*raiz) = NULL;
            }
          else {     // so tem o filho da dir
             if ((*raiz)->esq == NULL) {
                (*raiz) = (*raiz)->dir;
                pAux->dir = NULL;
                free(pAux); pAux = NULL;
                }
             else {            //so tem filho da esq
                if ((*raiz)->dir == NULL){
                    (*raiz) = (*raiz)->esq;
                    pAux->esq = NULL;
                    free(pAux); pAux = NULL;
                    }
                else{       //2 filhos, maior filho direito da subarvore esq.
                   pAux = Maiordir(&(*raiz)->esq);
                   pAux->esq = (*raiz)->esq;
                   pAux->dir = (*raiz)->dir;
                   (*raiz)->esq = (*raiz)->dir = NULL;
                   free((*raiz));  *raiz = pAux;  pAux = NULL;
                   }
                }
             }
             printf("Livro removido com sucesso!");
          }
}
