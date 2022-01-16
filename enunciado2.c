#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// a solucao que criei foi criar uma lista de nos para calcular os impostos e imprimir os relatorios

typedef struct cli No;
struct cli{
  char cliente[50];
  int qt;
  float icms;
  float ipi;
  float pis;
  float cofins;
  float vt;
  float impostos;
  float total_geral;
  float totalMerc;
  struct cli *proximo;

};


 typedef struct {
  float total_impostos;
  float Total_mercadorias;
  float total_geral;
   
}gastos;


//funcao quem aloca um no
No* criar_no (){ 
  No* no = (No*)malloc(sizeof(No));
  return no;
}

// função que insere dados dos clientes
No* listar_nomes(No*lista, char nome[],int qt){
  No *no = criar_no();

  char string[50];
 // strcpy(string, nome);

  strcpy(no->cliente, nome);
  no->qt=qt;
  
  if(lista == NULL){
    no->proximo = NULL; 
    lista=no;

  }else{
   
    No* aux=lista;

    while(aux->proximo != NULL){
      aux=aux->proximo;
    }

    no->proximo=NULL;
    aux->proximo=no;
  }
  return lista;
}

void calcular_impostos(No *Lista, gastos *nf){
  No* aux = Lista;
  
  float icms,ipi,pis,cofins,valorUniQt,tmercadorias=0,tImpostos,incImp, incGeral;

  while(aux != NULL){
    // Calculo para Total Mercadorias
    valorUniQt = 4.50 * aux->qt;
    tmercadorias = valorUniQt+valorUniQt;

    
    

    // Calculo dos Impostos
    icms = valorUniQt * 0.18;
    ipi = valorUniQt * 0.04;
    pis = valorUniQt * 0.0186;
    cofins = valorUniQt * 0.0854;

    // Calculo do incremento dos impostos
    float imp = icms + ipi + pis + cofins;
    incImp = imp + imp;

    // calculo para o custo total de cada cliente

    float custoTotal = valorUniQt + icms + ipi + pis + cofins; 

    //Calculo para o total  total_geral
    incGeral = custoTotal + custoTotal;

    //Atribuindo valores
    aux->vt=custoTotal;
    aux->icms=icms;
    aux->ipi=ipi;
    aux->pis=pis;
    aux->cofins=cofins;

    aux=aux->proximo;// incrementa se nao fica no loop
  }

  // atribuindo valores para a scruct gastos finais
  nf->Total_mercadorias=tmercadorias;
  nf->total_impostos= incImp;
  nf->total_geral = incGeral;

}

// imprime relatorio
void imprimir_lista (No *Lista, gastos notaFiscal){
  No* aux = Lista;
  printf("\n\n\n");
  printf("\t================ Relatório de Impostos ===============\n\n\t*Na compra acima de 1500 o cliente é beneficiado com desconto de 10 porcento*\n\n");
  while(aux != NULL){

    printf("Cliente: %s\n",aux->cliente);
    printf("ICMS: R$ %.2f; IPI: R$ %.2f; PIS: R$ %.2f; COFINS: R$ %.2f; Total: R$ %.2f\n\n",aux->icms,aux->ipi,aux->pis,aux->cofins,aux->vt);


    aux=aux->proximo;
  }
  printf("\n\n");
  printf("Total Impostos: R$%.2f\n",notaFiscal.total_impostos);
  printf("Total Mercadorias: R$%.2f\n",notaFiscal.Total_mercadorias);
  printf("Total Geral: R$%.2f\n",notaFiscal.total_geral);

  if(notaFiscal.total_geral > 1500){
    float bonificacao = notaFiscal.total_geral*0.1;
  printf("Total com desconto: R$%.2f\n", notaFiscal.total_geral-bonificacao);
  printf("Este cliente teve uma bonificação de 10 porcento de desconto!\n");
  }

}



int main (){

  No *lista = NULL;
  gastos notaFinal;

  char cliente[50];
  int qt, flag = 0;
 
  printf("\nCálculos de impostos para Nota Fiscal \n");
  while(flag == 0){


    printf("Cliente:\n");
    scanf("%[^\n]", cliente);
    printf("Digite a quantidade: \n");
    scanf("%i",&qt);
    

    lista=listar_nomes(lista, cliente,qt);

    printf("Digite 1 para sair ou 0  para continuar...\n");
    scanf("%i",&flag);
    getchar();


  }

  calcular_impostos(lista, &notaFinal);
  imprimir_lista(lista,notaFinal);


    return 0;
}
