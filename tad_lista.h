#include "tad_item.h"

typedef struct node_ NODE;
typedef struct lista_ LISTA;


LISTA *lista_inicia(void);
int lista_vazia(LISTA *lista);
NODE *retorna_topo(LISTA *lista);
NODE *busca_id(LISTA *lista, int id);
int lista_insere_site(LISTA *lista, int id, char *site, char *nome);
int lista_insere_site_rel(LISTA *lista, int id, char *site, char *nome, int rel);
int remove_site(LISTA *lista, NODE *no);
int insere_lista_pc(LISTA *lista, int id, char *pc);
int atualiza_rel(LISTA *lista, int id, int rel);
int finaliza_lista(LISTA **a);
int busca(NODE *no);
void libera_node(NODE *no);
void imprime_id_lista(LISTA *lista);
void imprime_toda_lista(LISTA *lista);
//novas
NODE *retorna_prox(NODE *no);
NODE *retorna_topo(LISTA *lista);
int node_retorna_qtd_pc(NODE *no);
char *node_retorna_pc(NODE *no, int i);

