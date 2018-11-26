#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET 26
#define debug 1
#define MAX 10000
#define TRUE 1
#define FALSE 0
#define max_letters 50

typedef struct item_{
	int id;                       // id de 4 digitos 
	char nome[50];
	int rel;                      // relevancia, vai de 0 a 1000
	char link[100];
	int qtd_pc;                  // quantidade de palavras chave
	char palavra_chave[10][50]; 
}item;


typedef struct node_trie_{
    struct node_trie_ *prox[ALPHABET];
    //node_list *head; //inserir a lista do T1 AQUI PONTEIRO PRA LISTA
    LISTA *lista;
    int end; //indicates this is the end cahracter
}node_trie;


node_trie *creat_node_trie(node_trie trie, item site){
		
    node_trie *trie = (node_trie *) malloc(sizeof(node_trie));
    trie->end = FALSE;
    node_trie->lista=inicia_lista();
    int i;
    for(i=0;i<ALPHABET;i++){
        trie->prox[i] = NULL;
    }
    return trie;
}

void insert_key_word(node_trie *trie, char *key, int begin, item site){
	
    node_trie *p = trie; 
    
    int i;
    
    for(i=begin;key[i]!='\0' && key[i]!='\n';i++){
		if(key[i]>='a' && key[i]<='z'){
			if(p->prox[key[i]-'a'] == NULL){
					p->prox[key[i] -'a'] = creat_node_trie();
			}
			p = p->prox[key[i]-'a'];
		}else if(key[i]>='A' && key[i]<='Z'){
			if(p->prox[key[i]-'A'] == NULL){
				p->prox[key[i] -'A'] = creat_node_trie();
			}
			
			p = p->prox[key[i]-'A'];
			
		}else{
			insert_key_word(trie, key, i+1, site);
			return;
		}
    }
    
    p->end=1;
    
    
    //INSERT ON THE END OF THE LIST
    
    return;
}

int search_node (node_trie *trie, char *key){
    node_trie *p = trie;

    if(trie == NULL){
        return FALSE;
    }

    while(*key){
        p = p->prox[*key - 'a'];

        if(p == NULL){
            return FALSE;
        }
        key++;
    }

    if(p->end == TRUE && p != NULL){
		//HERE WE NEED TO RETURN THE LIST THAT IS IN THE NODE P
        return TRUE;
    }else{
        return FALSE;
    }

}



