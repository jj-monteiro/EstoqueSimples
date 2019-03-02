#include <stdio.h>
#include <stdlib.h>
#include "pressanykey.h"


//variaveis e estruturas globais---------
struct cliente{
       char nome[30];
       int cpf,telefone;
};
struct produto{
       int codigo, quantidade;
       char nome[15];
       float precovenda;
};
struct fornecedor{
       char nome[20];
       int cnpj,telefone;
};

FILE *cli,*produt,*forn;
struct cliente client;
struct produto prod;
struct fornecedor forneced;

//----------------------------------------

//funcoes e metodos
void cadastra_produto(){
     //solicita dados
     rewind(produt);
	 printf("CADASTRO DE PRODUTOS\n");
     printf("--------------------\n");
     printf("Codigo: ");
     scanf("%d", &prod.codigo);
     printf("Nome: ");
     scanf("%s", &prod.nome);
     printf("Preco de venda: ");
     scanf("%f", &prod.precovenda);
     printf("Obs: quantidade inicial sera zero (0)\n.");
     prod.quantidade = 0;
     //system("PAUSE");
	 myPause(stdin);

     //grava arquivo
     fseek(produt,0,SEEK_END);
     fprintf(produt,"%d %s %f %d\n", prod.codigo, prod.nome, prod.precovenda, prod.quantidade);
     rewind(produt);
	 //system("CLS");
	 system("tput reset");
}

void cadastra_cliente(){
     //solicita dados
     rewind(cli);
	 printf("CADASTRO DE CLIENTES\n");
     printf("--------------------\n");
     printf("Nome: ");
     scanf("%s", &client.nome);
     printf("CPF: ");
     scanf("%d", &client.cpf);
     printf("Telefone: ");
     scanf("%d", &client.telefone);
     //grava arquivo
     fseek(cli,0,SEEK_END);
     fprintf(cli,"%s %d %d\n", client.nome, client.cpf, client.telefone);
     rewind(cli);
     //system("CLS");
	 system("tput reset");
}

void cadastra_fornecedor(){
     //solicita dados
     rewind(forn);
     printf("CADASTRO DE FORNECEDORES\n");
     printf("------------------------\n");
     printf("Nome: ");
     scanf("%s", &forneced.nome);
     printf("CNPJ: ");
     scanf("%d", &forneced.cnpj);
     printf("Telefone: ");
     scanf("%d", &forneced.telefone);
     //grava arquivo
     fseek(forn,0,SEEK_END);
     fprintf(forn,"%s %d %d\n", forneced.nome, forneced.cnpj, forneced.telefone);
     rewind(forn);
     //system("CLS");
	 system("tput reset");
}

void compra_material(){
     int codigo,novaquant,i,j,cnpjfornecedor;
     struct produto vetor[100];
     i=0;
     int achou=0;
     
	 printf("COMPRA DE MATERIAL\n");
     printf("------------------\n");
	 
	 produt=fopen("PRODUTOS.txt","r+");
	 rewind(produt);     
     while (!feof(produt)){
	 	fscanf(produt,"%d %s %f %d\n", &prod.codigo, &prod.nome, &prod.precovenda, &prod.quantidade);
	 	printf("Codigo:%d\n Nome:%s\n Preco venda:%f\n Quantidade em estoque:%d\n------------------------------------\n", prod.codigo, prod.nome, prod.precovenda, prod.quantidade);
		vetor[i] = prod;
	 	i = i + 1; //contar linhas ou produtos
	 }
	 prod.codigo=-1;
	 printf("Codigo do produto:");
     scanf("%d",&codigo);
     //verifica fornecedores
     printf("\nFornecedores disponiveis:\n");
	 rewind(forn);
	 while (!feof(forn)){
   		fscanf(forn,"%s %d %d\n", &forneced.nome, &forneced.cnpj, &forneced.telefone);
     	printf("Nome:%s\n CNPJ:%d\n Telefone:%d\n\n", forneced.nome, forneced.cnpj, forneced.telefone);
     }	 
	 printf("\nCNPJ do fornecedor desejado:");
     scanf("%d", &cnpjfornecedor);
     
	 rewind(forn);
	 while (!feof(forn)){
		fscanf(forn,"%s %d %d\n", &forneced.nome, &forneced.cnpj, &forneced.telefone);
		if(cnpjfornecedor==forneced.cnpj){
			achou=1;
		}
     }
	     
    if(achou==1){
     	for (j=0;j<i;j++){
	 		if (codigo==vetor[j].codigo){
	 			printf("Quantidade em estoque: %d\n", vetor[j].quantidade);
        		printf("Digite a quantidade a ser comprada:");
    	    	scanf("%d", &novaquant);
    	    	vetor[j].quantidade = vetor[j].quantidade + novaquant; //atualiza o valor da quantidade
 	         }	 	
		 }
	 
		 produt=fopen("PRODUTOS.txt","w+");
		 for (j=0;j<i;j++){
		 	fprintf(produt,"%d %s %f %d\n", vetor[j].codigo, vetor[j].nome, vetor[j].precovenda, vetor[j].quantidade);
		 }
		 //system("PAUSE");
		 myPause(stdin);
		 fclose(produt);
		 
	}
	else{
 	 	 printf("Fornecedor nao encontrado. Tente novamente\n");
 	 	 //system("PAUSE");
		 myPause(stdin);
	}

}

void vende_material(){
	int codigo,quantvenda,i,j;
     struct produto vetor[100];
     i=0;
	 produt=fopen("PRODUTOS.txt","r+");
	 
	 printf("VENDA DE MATERIAL\n");
     printf("-----------------\n");
	 rewind(produt);     
     while (!feof(produt)){
	 	fscanf(produt,"%d %s %f %d\n", &prod.codigo, &prod.nome, &prod.precovenda, &prod.quantidade);
	 	printf("Codigo:%d\n Nome:%s\n Preco venda:%f\n Quantidade em estoque:%d\n------------------------------------\n", prod.codigo, prod.nome, prod.precovenda, prod.quantidade);
		vetor[i] = prod;
	 	i = i + 1; //contar linhas ou produtos
	 }
	 prod.codigo=-1;
	 
     printf("Codigo do produto:");
     scanf("%d",&codigo);
     
	 for (j=0;j<i;j++){
	 	if (codigo==vetor[j].codigo){
	 		if(vetor[j].quantidade>0){
	 		
			printf("Quantidade em estoque: %d\n", vetor[j].quantidade);
        	printf("Digite a quantidade a ser vendida:");
        	scanf("%d", &quantvenda);
        	while (quantvenda>vetor[j].quantidade){
        		printf("Quantidade superior ao estoque\n");
        		printf("Digite a quantidade a ser vendida:");
        		scanf("%d", &quantvenda);
        	}
        	vetor[j].quantidade = vetor[j].quantidade - quantvenda; //atualiza o valor da quantidade
        	}
        	else{
        		printf("Nao ha produto no estoque\n");
        		//system("PAUSE");
				  myPause(stdin);
        	}
        }
	}
	 
	 produt=fopen("PRODUTOS.txt","w+");
	 for (j=0;j<i;j++){
	 	fprintf(produt,"%d %s %f %d\n", vetor[j].codigo, vetor[j].nome, vetor[j].precovenda, vetor[j].quantidade);
	 }
	 
	 //system("PAUSE");
	 myPause(stdin);
	 fclose(produt);
	 produt=fopen("PRODUTOS.txt","r+");
	 
}

int lista_material(){
     
	 if (!feof(produt)){
          fscanf(produt,"%d %s %f %d\n", &prod.codigo, &prod.nome, &prod.precovenda, &prod.quantidade);
          printf("Codigo: %d\nNome: %s\nPreco de venda: %f\nQuantidade: %d\n--------------------------------\n", prod.codigo, prod.nome, prod.precovenda, prod.quantidade);
     }
     else{
          rewind(produt);
		  //system("PAUSE");
		  myPause(stdin);
		  return 0;
     }
     lista_material();
}

void mostramenu(){
	 int opmenu=-1;
	 char pause_char = 0;

	 while (opmenu!=0){
     	//system("CLS");
		system("tput reset");
		printf("PROGRAMA DE ESTOQUE\n");
     	printf("-------------------\n\n");
     	printf("Escolha a acao:\n");
     	printf("1-Cadastrar produto\n");
     	printf("2-Cadastrar cliente\n");
     	printf("3-Cadastrar fornecedor\n");
     	printf("4-Comprar materiais\n");
     	printf("5-Vender materiais\n");
     	printf("6-Lista de produtos\n");
     	printf("0-SAIR\n\n");
     	printf("Digite: ");
     	scanf("%i",&opmenu);
     
     	if (opmenu == 1){
        	//system("CLS");
			system("tput reset");
        	cadastra_produto();
     	}
	     if (opmenu == 2){
    	    //system("CLS");
        	system("tput reset");
			cadastra_cliente();
	     }
    	 if (opmenu == 3){
        	//system("CLS");
			system("tput reset");
        	cadastra_fornecedor();
	     }
    	 if (opmenu == 4){
        	//system("CLS");
			system("tput reset");
        	compra_material();
     	}
     	if (opmenu == 5){
        	//system("CLS");
			system("tput reset");
        	vende_material();
     	}           
     	if (opmenu == 6){
        	//system("CLS");
			system("tput reset");
        	printf("LISTA DE MATERIAL\n");
     		printf("-----------------\n");
     		produt=fopen("PRODUTOS.txt","r+");
        	lista_material();
	     }
     }
     printf("Ate mais!\n");
	   fclose(cli);
     fclose(produt);
     fclose(forn);
	   myPause(stdin);
}


int main(){
	cli=fopen("CLIENTES.txt","r+");
    if(cli==NULL)
       	printf("ERRO AO CRIAR ARQUIVO");
	produt=fopen("PRODUTOS.txt","r+");
    if(cli==NULL)
    	printf("ERRO AO CRIAR ARQUIVO");
	forn=fopen("FORNECEDOR.txt","r+");
    if(cli==NULL)
		printf("ERRO AO CRIAR ARQUIVO");
    
	mostramenu();
  
  }
