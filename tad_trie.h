typedef struct node_trie_ node_trie;

node_trie *creat_node_trie (void);
void insert_key_word(node_trie *trie, char *key, int begin, int id, char *link, char *nome, int rel);
LISTA *search_node_trie (node_trie *trie, char *key);
int ler_dados(LISTA *lista, node_trie *trie);
void print_trie (node_trie *trie);
void insere_trie(LISTA *lista, node_trie *trie);
void remove_pc_trie(node_trie *trie, NODE *no);
void imprime_sites(node_trie *trie, char *key);
/*FUNÇÃO NOVA PRA IMPRIMIR NO SUGESTAO SEM REPETIR*/
void imprime_sites2(node_trie *trie, char *key, int **check);
void sugestao(LISTA *lista,node_trie *trie, char *key);
int finaliza_trie(node_trie **trie);
