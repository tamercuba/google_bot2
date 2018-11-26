#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tad_item.h"
#include "tad_lista.h"
#define ERRO -32

int main(void){      /*antes do while começar, devemos criar */
	int aux, i, id, rel;      /* a lista e ler o arquivo */
        LISTA *lista;
        char nome[51], site[101];
        lista=lista_inicia();
        i=ler_dados(lista);
        
        if(i!=1){
        	return ERRO;
        }
      	else{
      		aux=0;
      		printf("%d", busca(busca_id(lista, 7325) ) );
		while(1){
			printf("Pressione um dos números para dar início a uma operação: \n");
			printf("1-Inserir um site \n2-Remover um site \n3-Inserir palavra-chave\n4-Atualizar relevancia\n5-Sair\n");
			scanf("%d",&aux);
			if(aux < 0 || aux > 5){
				printf("Valor incorreto, insira novamente:");
				scanf("%d",&aux);
			}
			switch(aux){
				case 1:
					printf("Insira o nome do site:\n");
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
						printf("Relevancia atualizada");
					}
					break;
				case 5: 
					printf("a1");
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
			}
		}
	}
}
