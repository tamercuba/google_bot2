
typedef struct item_g ITEM;

ITEM *inicia_item(void);
void libera_item(ITEM *item);
int insere_id(ITEM *item, int valor);
void insere_nome(ITEM *item, char *nome);
int insere_rel(ITEM *item, int rel);
void insere_link(ITEM *item, char *link);
int insere_pc(ITEM *item, char *palavra);
int retorna_id(ITEM *item);
int retorna_rel(ITEM *item);
char *retorna_nome(ITEM *item);
char *retorna_link(ITEM *item);
//novas 
int retorna_qtd_pc(ITEM *item);
char *retorna_pc(ITEM *item, int i);
