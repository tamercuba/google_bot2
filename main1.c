#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tad_item.h"
#include "tad_lista.h"
#include "tad_trie.h"

#define ERRO -32

int main(void){      /*antes do while começar, devemos criar */
	int aux,aux2, i, id, rel;      /* a lista e ler o arquivo */
        int flag=0;
        LISTA *lista;
        node_trie *trie = creat_node_trie();
        char nome[51], site[101];
        char pc_buscada[50];
        lista=lista_inicia();


        i=ler_dados(lista, trie);

        if(i!=1){
        	return ERRO;
        }
      	else{
      		aux=0;
      		//printf("%d", busca(busca_id(lista, 7325) ) );
		while(1){
			printf("Pressione um dos números para dar início a uma operação: \n");
			printf("1-Inserir um site \n2-Remover um site \n3-Inserir palavra-chave\n4-Atualizar relevancia\n5-Sair\n6-BUscar palavra-chave\n7-Buscar palavras relacionadas\n");
			scanf("%d",&aux);
			if(aux < 0 || aux > 7){
				printf("Valor incorreto, insira novamente:");
				scanf("%d",&aux);
			}
			switch(aux){
				case 1:
					printf("Insira o nome do site\n");
					scanf(" %s", nome);
					printf("insira o id do site:\n");
					scanf(" %d", &id);
					printf("Insira o link do site:\n");
					scanf(" %s", site);
					i=lista_insere_site(lista, id, site, nome);
					if(i==0){
						printf("Id invalido\n");
					}
					else if(i==ERRO){
						printf("Ja existe um site com esse id\n");
					}
					else{
						printf("Site inserido com sucesso\n");
						
						printf("Deseja inserir a relevancia do site? (0/1) \n");
						scanf("%d",&aux1);
						if(aux1==1){
							printf("Insira a relevancia: \n");
							scanf("%d",&rel);
							if(atualiza_rel(lista, id, rel) != 1){
								printf("Relevancia invalida, site inserido com relevancia zero\n");
								break;
							}
						}
						aux1=0;
						printf("Deseja inserir uma(s) palavra(s) chave? (0/1) \n");
						scanf("%d",&aux1);
						if(aux1==1){
							while(1){
								printf("Digite a palavra chave a ser inserida: \n");
								scanf("%s", pc_buscada);
								if(insere_lista_pc(lista, id, pc_buscada) != 1 ){
									printf("Nao foi possivel inserir a palavra chave \n");
									break;
								}		
								insert_key_word(trie, pc_buscada,0,id,site,nome, ); // PAREI AQUI 
								printf("Palavra inserida com sucesso! \n");
								printf("Deseja inserir outra palavra chave ? (0/1) \n");
								scanf("%d", &aux1);
								if(aux==0){
									break;
								}
							}
							break;
						}
						else{
								
						}
					}
					break;
				case 2:
					printf("Insira o site a ser removido:\n");
					scanf("%d", &id);
					i=remove_site(lista, id);
					if(i==0){
						printf("Nao foi encontrado um site com o id fornecido\n");
					}
					else{
						printf("Site removido com sucesso\n");
					}
					break;
				case 3:
					printf("Insira o id do site desejado:\n");
					scanf("%d", &id);
					printf("Insira a palavra chave desejada:\n");
					scanf("%s", nome);
					i=insere_lista_pc(lista, id, nome);
					if(i==0){
						printf("Site não encontrado\n");
					}
					else{
						printf("Palavra-chave inserida com sucesso\n");
					}
					break;
				case 4:
					printf("Insira o id do site desejado:\n");
					scanf("%d", &id);
					printf("Insira a relevancia nova do site inserido:\n");
					scanf("%d", &rel);
					i=atualiza_rel(lista, id, rel);
					if(i==0){
						printf("Site nao encontrado\n");
					}
					else{
						printf("Relevancia atualizada\n");
					}
					break;
				case 5:
					i=finaliza_lista(&lista);
					if(i!=1){
						printf("erro ao sair do programa");
						return ERRO;
					}
					else{
						system("clear");
						return 1;
					}
					break;

		                case 6:
					printf("Digite a Palavra Chave a ser Buscada\n");
					scanf("%s", pc_buscada);
					imprime_sites(trie, pc_buscada);
					break;

				case 7: //procurar por palavras relacionadas
					printf("Digite a palavra chave a ser buscada:");
					scanf("%s", pc_buscada);
					sugestao(trie, pc_buscada);									
				break;
			}
		}
	}
}
