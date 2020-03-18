#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <conio.h>

#include <windows.h>

#include <locale.h>

/*-----------------------------------------------------*/
/*POSICIONAMENTO DE CURSOR*/
void gotoxy(short x, short y) {
  COORD pos = {
    x,
    y
  };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/*POSICIONAMENTO DE CURSOR*/
/*-----------------------------------------------------*/

/*CABEÇALHO DAS TELAS*/
void cabecalho() {

  gotoxy(20, 2);
  printf("*************************************\n");
  gotoxy(20, 3);
  printf("*   P I Z Z A R I A   N O N A K A   *\n");
  gotoxy(20, 4);
  printf("*************************************\n");
}
/*CABEÇALHO DAS TELAS*/
/*-----------------------------------------------------*/

/*ESTRUTURA DO LOGIN*/
typedef struct login {

    char user_str[50];
    char pass_str[50];
    int acesso;
};
struct login log;
/*ESTRUTURA DO LOGIN*/
/*-----------------------------------------------------*/

/*ESTRUTURA DOS PRODUTOS*/
typedef struct cardapio {

  int cod_prod_stc;
  char nome_prod_stc[150];
  float valor_prod_stc;
  int quant_prod_stc;

};
struct cardapio cad;
/*ESTRUTURA DOS PRODUTOS*/
/*-----------------------------------------------------*/

/* ESTRUTURA DOS CLIENTES*/
typedef struct clientes {

  int cod_cliente_stc;
  char nome_cliente_stc[150];
  char end_cliente_stc[250];
  char compl_cliente_stc[150];
  char bairro_cliente_stc[150];
  char cep_cliente_stc[150];
  char tel_cliente_stc[150];

};
struct clientes cli;
/* ESTRUTURA DOS CLIENTES*/
/*-----------------------------------------------------*/

/* MENU DE PRODUTOS*/
void menu_produtos() {

  int esc;

  esc = 0;

  /*OPÇÕES DO MENU*/
  while (esc != 4) {
    cabecalho();
    gotoxy(25, 6);
    printf("[1] Cadastrar Produtos\n");
    gotoxy(25, 7);
    printf("[2] Buscar Produtos\n");
    gotoxy(25, 8);
    printf("[3] Excluir Produtos\n");
    gotoxy(25, 9);
    printf("[4] Voltar ao Menu Principal\n");
    gotoxy(25, 10);
    printf("\n");
    fflush(stdin);
    gotoxy(25, 11);
    printf("Escolha uma Opção: ");
    scanf("%d", & esc);
    /*OPÇÕES DO MENU*/

    /* FUNÇÕES DO MENU*/
    switch (esc) {
    case 1:
      system("cls");
      arquivo_cadastrar();
      break;
    case 2:
      system("cls");
      buscar_estoque();
      break;
    case 3:
      system("cls");
      gotoxy(25, 13);
      excluir_produtos();
      break;
    case 4:
      system("cls");
      main();
      break;
    default:
      system("cls");
      gotoxy(25, 13);
      printf("Opção inválida!\n");
      break;
    }
    /* FUNÇÕES DO MENU*/
  }
}
/* MENU DE PRODUTOS*/
/*-----------------------------------------------------*/

/* TELA DE CADASTRO DE PRODUTOS*/
void arquivo_cadastrar() {

  char esc = 's';

  FILE * estoque; // DEFINE O ENDEREÇO FÍSICO DO ARQUIVO TXT NA MEMÓRIA
  do {
    cabecalho();

    gotoxy(25, 5);
    printf("Digite o código do produto: \n");
    gotoxy(25, 6);
    scanf("%i", & cad.cod_prod_stc);
    system("cls");
    cabecalho();

    fflush(stdin);
    gotoxy(25, 5);
    printf("Digite o nome do produto: \n");
    gotoxy(25, 6);
    fgets(cad.nome_prod_stc, 100, stdin);
    system("cls");
    cabecalho();

    gotoxy(25, 5);
    printf("Digite o valor do produto: \n");
    gotoxy(25, 6);
    printf("R$");
    scanf("%f", & cad.valor_prod_stc);
    system("cls");
    cabecalho();

    estoque = fopen("estoque.txt", "a"); //CRIA OU EDITA O ARQUIVO TXT
    fprintf(estoque, "%i;%s;%.2f;\n", cad.cod_prod_stc, cad.nome_prod_stc, cad.valor_prod_stc);
    //INSERE AS INFORMAÇÕES DO PRODUTO NO ARQUIVO TXT

    gotoxy(25, 5);
    printf("Cadastro incluido!\n");
    fclose(estoque); //FECHA O ARQUIVO TXT

    /* EXIBE AS INFORMAÇÕES DO CADASTRO DO PRODUTO REALIZADO */
    fflush(stdin);
    gotoxy(25, 7);
    printf("Código do Produto: %i\n", cad.cod_prod_stc);
    gotoxy(25, 8);
    printf("Nome do Produto: %s\n", cad.nome_prod_stc);
    gotoxy(25, 9);
    printf("Valor: R$%.2f", cad.valor_prod_stc);
    /* EXIBE AS INFORMAÇÕES DO CADASTRO DO PRODUTO REALIZADO */

    /* VERIFICA SE USUÁRIO QUER INSERIR OUTRO PRODUTO OU VOLTAR PARA O MENU*/
    gotoxy(25, 10);
    printf("Deseja cadastrar novamente? (S/N) ");
    gotoxy(25, 11);
    esc = getch();
    system("cls");
    fflush(stdin);
    /* VERIFICA SE USUÁRIO QUER INSERIR OUTRO PRODUTO OU VOLTAR PARA O MENU*/
  }

  while (esc == 's' || esc == 'S');

  if (esc != 's' || esc != 'S') {
    menu_produtos();
  }
}
/* TELA DE CADASTRO DE PRODUTOS*/
/*-----------------------------------------------------*/

/*TELA DE BUSCA DE PRODUTOS*/
void buscar_estoque() {

  cabecalho();

  char produto[256];
  char esc;
  int * codrstd;
  int existe = 0;
  int linha = 6;
  int codProdBusca;

  gotoxy(20, linha);
  printf("Insira o código do produto: ");
  gotoxy(50, linha++);
  scanf("%d", & codProdBusca);

  FILE * estoque;

  estoque = fopen("estoque.txt", "r");

  if (estoque != NULL) {
    /*VERIFICA SE O ARQUIVO TXT FOI ABERTO*/

    /*IMPRIME OS DADOS DO ARQUIVO TXT, CASO TENHA SIDO ABERTO*/

    while (!feof(estoque)) {
      char * rstd = fgets(produto, 256, estoque); /*BUSCA AS LINHAS DO ARQUIVO TXT*/
      codrstd = strtok(rstd, ";"); /*DIVIDE A LINHA DO ARQUIVO EM ";"*/
      cad.cod_prod_stc = atoi(codrstd); /*SALVA O CONTEÚDO DO PONTEIRO STRING E CONVERTE PARA INT*/

      if (cad.cod_prod_stc == codProdBusca) {
        existe = 1;
        if (codrstd != NULL) {
          codrstd = strtok(NULL, ";");
          printf("\n\n");
          gotoxy(30, linha++);
          printf("Nome: %s", codrstd);
          printf("\n");
          codrstd = strtok(NULL, ";");
          cad.valor_prod_stc = atof(codrstd);
          gotoxy(30, linha++);
          printf("Preço: R$%.2f", cad.valor_prod_stc);
          printf("\n");
          codrstd = strtok(NULL, ";");
          cad.quant_prod_stc = atoi(codrstd);
          gotoxy(30, linha++);
          printf("Quantidade: %d", cad.quant_prod_stc);
          printf("\n\n");

        }
      }
    }
    if (existe == 0) {
      fflush(stdin);
      gotoxy(25, linha++);
      printf("Produto não encontrado!");
    }

    /* OPÇÃO PARA VOLTAR AO MENU PRINCIPAL*/
    if (feof(estoque)) {
        fclose(estoque);
      gotoxy(20, linha++);
      printf("Pressione 'ENTER' para buscar novamente");
      gotoxy(17, linha++);
      printf("Pressione 'S' para voltar para o menu anterior");
      esc = getch();
      if (esc == 's' || esc == 'S') {
        system("cls");
        menu_produtos();
        fflush(stdin);
      } else {
        system("cls");
        buscar_estoque();
        fflush(stdin);
      }

    }
    /* OPÇÃO PARA VOLTAR AO MENU PRINCIPAL*/
  }

  /*INFORMA QUE NÃO FOI POSSIVEL ABRIR O ARQUIVO TXT*/
  else {
    printf("Não foi possível abrir o arquivo!");
    system("pause");
  }
  /*INFORMA QUE NÃO FOI POSSIVEL ABRIR O ARQUIVO TXT*/
}
/*TELA DE BUSCA DE PRODUTOS*/
/*-----------------------------------------------------*/

/*TELA DE EXCLUSÃO DE PRODUTOS*/
void excluir_produtos() {
      fflush(stdin);
  cabecalho();

  char produto[256];
  char esc;
  int * codrstd;
  int existe = 0;
  int linha = 6;
  int codProdExc = 0;
  char opc[3];

  FILE *estoque;
  FILE *arqTemp;

  gotoxy(20, linha);
  printf("Insira o código do produto a ser excluído: ");
  gotoxy(50, linha++);
  scanf("%d", &codProdExc);



    printf("Digite 'Sim' para confirmar exclusão: ");
    scanf("%s", opc);

    printf("%d", codProdExc);
    system("pause");



  if (estoque != NULL) {
    /*VERIFICA SE O ARQUIVO TXT FOI ABERTO*/

    if (opc != 'SIM' || opc != 'sim') {

            arqTemp = fopen("estoque.tmp", "w");
        estoque = fopen("estoque.txt", "r");

     printf("%d", codProdExc);
    system("pause");

      while (!feof(estoque)) {

        char *rstd = fgets(produto, 256, estoque);

        codrstd = strtok(rstd, ";"); /*DIVIDE A LINHA DO ARQUIVO EM ";"*/
        cad.cod_prod_stc = atoi(codrstd); /*SALVA O CONTEÚDO DO PONTEIRO STRING E CONVERTE PARA INT*/

        if (cad.cod_prod_stc != codProdExc) {

        if (cad.cod_prod_stc != NULL){
        codrstd = strtok(NULL, ";");
        int *nomeprod = codrstd;
        codrstd = strtok(NULL, ";");
        cad.valor_prod_stc = atof(codrstd);
        codrstd = strtok(NULL, ";");
        cad.quant_prod_stc = atoi(codrstd);

        fprintf(arqTemp, "%i;%s;%.2f;%i\n", cad.cod_prod_stc, nomeprod, cad.valor_prod_stc, cad.quant_prod_stc);
        }
        }
      }
        fclose(estoque);
        fclose(arqTemp);
        system("del estoque.txt");
        system("ren estoque.tmp estoque.txt");
        printf("Exclusão efetuada com sucesso!");
    }
    else{
        printf("Exclusão não realizada!");
    }
  }
}
/*TELA DE EXCLUSÃO DE PRODUTOS*/
/*-----------------------------------------------------*/
/*MENU DE ELOGIOS E RECLAMAÇÕES*/
void menu_elog_recl() {

  int esc;

  esc = 0;

  /*OPÇÕES DO MENU*/
  while (esc != 4) {
    cabecalho();
    gotoxy(25, 6);
    printf("[1] Registrar atendimento\n");
    gotoxy(25, 7);
    printf("[2] Buscar Atendimento\n");
    gotoxy(25, 8);
    printf("[3] Voltar ao Menu Principal\n");
    gotoxy(25, 9);
    printf("\n");
    fflush(stdin);
    gotoxy(25, 10);
    printf("Escolha uma Opção: ");
    scanf("%d", & esc);
    /*OPÇÕES DO MENU*/

    /* FUNÇÕES DO MENU*/
    switch (esc) {
    case 1:
      system("cls");
      cad_elog_recl();
      break;
    case 2:
      system("cls");
      buscar_elog_recl();
      break;
    case 3:
      system("cls");
      main();
      break;
    default:
      system("cls");
      gotoxy(25, 13);
      printf("Opção inválida!\n");
      break;
    }
    /* FUNÇÕES DO MENU */
  }
}
/*MENU DE ELOGIOS E RECLAMAÇÕES*/
/*-----------------------------------------------------*/

/*CADASTRO DE ELOGIOS E RECLAMAÇÕES*/
void cad_elog_recl() {

  setlocale(LC_ALL, "");
  char texElogRecl[280];
  char esc;
  FILE * elogRecl;

  elogRecl = fopen("elogiosReclamações.txt", "a");

  do {
    system("cls");
    cabecalho();
    printf("Digite o nome do cliente: ");
    scanf("%s", cli.nome_cliente_stc);

    fflush(stdin);

    printf("Descreva o atendimento: ");
    fgets(texElogRecl, 280, stdin);

    fprintf(elogRecl, "***\nCliente: %s \nAtendimento: %s\n***\n", cli.nome_cliente_stc, texElogRecl);
    printf("Atendimento efetuado com sucesso! \n Cliente: %s \n Atendimento: %s", cli.nome_cliente_stc, texElogRecl);
    printf("\nDeseja registrar outro atendimento? (S/N)");
    esc = getch();
  } while (esc == 's' || esc == 'S');

  fclose(elogRecl);

  if (esc != 's' || esc != 'S') {
    system("cls");
    menu_elog_recl();
  }
}
/*CADASTRO DE ELOGIOS E RECLAMAÇÕES*/
/*-----------------------------------------------------*/

/*BUSCAR DE ELOGIOS E RECLAMAÇÕES*/
void buscar_elog_recl() {

  FILE * elogRecl;

  char texElogRecl[280];
  char * rstd;
  int i = 0;

  elogRecl = fopen("elogiosReclamações.txt", "r");

  while (!feof(elogRecl)) {
    rstd = fgets(texElogRecl, 280, elogRecl);
    printf("%s", rstd);
  }

  system("pause");
  system("cls");
}
/*BUSCAR DE ELOGIOS E RECLAMAÇÕES*/
/*-----------------------------------------------------*/

/* MENU DE CLIENTES */
void menu_clientes() {
  int esc;

  esc = 0;

  /*OPÇÕES DO MENU*/
  while (esc != 4) {
    cabecalho();
    gotoxy(25, 6);
    printf("[1] Cadastrar Cliente\n");
    gotoxy(25, 7);
    printf("[2] Exibir dados do Cliente\n");
    gotoxy(25, 8);
    printf("[3] Voltar para o menu principal\n");
    printf("\n");
    fflush(stdin);
    gotoxy(25, 12);
    printf("Escolha uma Opção: ");
    scanf("%d", & esc);
    /*OPÇÕES DO MENU*/

    /* FUNÇÕES DO MENU*/
    switch (esc) {
    case 1:
      system("cls");
      cadastrar_cliente();
      break;
    case 2:
      system("cls");
      buscar_cliente();
      break;
    case 3:
      system("cls");
      main();
      break;
    default:
      system("cls");
      gotoxy(25, 13);
      printf("Opção inválida!\n");
      break;
    }
    /* FUNÇÕES DO MENU */
  }
}
/* MENU DE CLIENTES */
/*-----------------------------------------------------*/

/* TELA DE CADASTRO DE CLIENTES*/
void cadastrar_cliente() {

      setlocale(LC_ALL, ""); //ACENTUAÇÕES SÃO VISÍVEIS ATRAVÉS DESTE CÓDIGO


  char esc = 's';

  FILE * cliente; // DEFINE O ENDEREÇO FÍSICO DO ARQUIVO TXT NA MEMÓRIA
  do {
    cabecalho();

    gotoxy(25, 5);
    printf("Digite o código do cliente: \n");
    gotoxy(25, 6);
    scanf("%i", & cli.cod_cliente_stc);
    system("cls");
    cabecalho();

    fflush(stdin);
    gotoxy(25, 5);
    printf("Digite o Nome do Cliente: \n");
    gotoxy(25, 6);
    fgets(cli.nome_cliente_stc, 100, stdin);
    system("cls");
    cabecalho();

    fflush(stdin);
    gotoxy(20, 5);
    printf("Digite o Endereço(Inclua o número): \n");
    gotoxy(25, 6);
    fgets(cli.end_cliente_stc, 250, stdin);
    system("cls");
    cabecalho();

    fflush(stdin);
    gotoxy(20, 5);
    printf("Digite o Complemento: \n");
    gotoxy(25, 6);
    fgets(cli.compl_cliente_stc, 100, stdin);
    system("cls");
    cabecalho();

    fflush(stdin);
    gotoxy(20, 5);
    printf("Digite o Bairro: \n");
    gotoxy(25, 6);
    fgets(cli.bairro_cliente_stc, 100, stdin);
    system("cls");
    cabecalho();

    fflush(stdin);
    gotoxy(20, 5);
    printf("Digite o CEP: \n");
    gotoxy(25, 6);
    fgets(cli.cep_cliente_stc, 100, stdin);
    system("cls");
    cabecalho();

    fflush(stdin);
    gotoxy(20, 5);
    printf("Digite o Telefone: \n");
    gotoxy(25, 6);
    fgets(cli.tel_cliente_stc, 100, stdin);
    system("cls");
    cabecalho();

    cliente = fopen("clientes.txt", "a"); //CRIA OU EDITA O ARQUIVO TXT
    fprintf(cliente, "%i;%s;%s;%s;%s;%s;%s\n", cli.cod_cliente_stc, cli.nome_cliente_stc, cli.end_cliente_stc, cli.compl_cliente_stc, cli.bairro_cliente_stc, cli.cep_cliente_stc, cli.tel_cliente_stc);
    //INSERE AS INFORMAÇÕES DO CLIENTE NO ARQUIVO TXT

    gotoxy(25, 5);
    printf("Cadastro incluido!\n");
    fclose(cliente); //FECHA O ARQUIVO TXT

    /* EXIBE AS INFORMAÇÕES DO CADASTRO DO CLIENTE REALIZADO */
    fflush(stdin);
    gotoxy(25, 7);
    printf("Código do Cliente: %i\n", cli.cod_cliente_stc);
    gotoxy(25, 8);
    printf("Nome do Cliente: %s\n", cli.nome_cliente_stc);
    gotoxy(25, 9);
    printf("Endereço: %s\n", cli.end_cliente_stc);
    gotoxy(25, 10);
    printf("Complemento: %s\n", cli.compl_cliente_stc);
    gotoxy(25, 11);
    printf("Bairro: %s\n", cli.bairro_cliente_stc);
    gotoxy(25, 12);
    printf("CEP: %s\n", cli.cep_cliente_stc);
    gotoxy(25, 13);
    printf("Telefone: %s\n", cli.tel_cliente_stc);
    /* EXIBE AS INFORMAÇÕES DO CADASTRO DO CLIENTE REALIZADO */

    /* VERIFICA SE USUÁRIO QUER INSERIR OUTRO CLIENTE OU VOLTAR PARA O MENU*/
    gotoxy(25, 15);
    printf("Deseja cadastrar novamente? (S/N) ");
    gotoxy(25, 16);
    esc = getch();
    system("cls");
    fflush(stdin);
    /* VERIFICA SE USUÁRIO QUER INSERIR OUTRO CLIENTE OU VOLTAR PARA O MENU*/
  }

  while (esc == 's' || esc == 'S');

  if (esc != 's' || esc != 'S') {
    menu_clientes();
  }
}
/* TELA DE CADASTRO DE CLIENTES*/
/*-----------------------------------------------------*/

void buscar_cliente() {

  cabecalho();

  char clienteBusca[256];
  char esc;
  int *codrstd;
  int existe = 0;
  int linha = 6;
  int codCliBusca;

  gotoxy(20, linha);
  printf("Insira o código do cliente: ");
  gotoxy(50, linha++);
  scanf("%d", & codCliBusca);

  FILE * cliente;

  cliente = fopen("clientes.txt", "r");

  if (cliente != NULL) {
    /*VERIFICA SE O ARQUIVO TXT FOI ABERTO*/

    /*IMPRIME OS DADOS DO ARQUIVO TXT, CASO TENHA SIDO ABERTO*/

    while (!feof(cliente)) {
      char * rstd = fgets(clienteBusca, 256, cliente); /*BUSCA AS LINHAS DO ARQUIVO TXT*/
      codrstd = strtok(rstd, ";\n"); /*DIVIDE A LINHA DO ARQUIVO EM ";"*/
      cli.cod_cliente_stc = atoi(codrstd); /*SALVA O CONTEÚDO DO PONTEIRO STRING E CONVERTE PARA INT*/

      if (cli.cod_cliente_stc == codCliBusca) {
        existe = 1;
        if (codrstd != NULL) {
          codrstd = strtok(NULL, ";");
          printf("\n\n");
          gotoxy(20, linha++);
          printf("Nome: %s", codrstd);
          printf("\n");

          codrstd = strtok(NULL, ";");
          gotoxy(20, linha++);
          printf("Endereço: %s", codrstd);
          printf("\n");

          codrstd = strtok(NULL, ";");
          gotoxy(20, linha++);
          printf("Complemento: %s", codrstd);
          printf("\n");

          codrstd = strtok(NULL, ";");
          gotoxy(20, linha++);
          printf("Bairro: %s", codrstd);
          printf("\n");

          codrstd = strtok(NULL, ";");
          gotoxy(20, linha++);
          printf("CEP: %s", codrstd);
          printf("\n");

          codrstd = strtok(NULL, ";");
          gotoxy(20, linha++);
          printf("Telefone: %s", codrstd);
          printf("\n");
        }
      }
    }
    if (existe == 0) {
      fflush(stdin);
      gotoxy(25, linha++);
      printf("Cliente não encontrado!");
    }

    /* OPÇÃO PARA VOLTAR AO MENU PRINCIPAL*/
    if (feof(cliente)) {
        fclose(cliente);
      gotoxy(20, linha++);
      printf("Pressione 'ENTER' para buscar novamente");
      gotoxy(17, linha++);
      printf("Pressione 'S' para voltar para o menu anterior");
      esc = getch();
      if (esc == 's' || esc == 'S') {
        system("cls");
        menu_clientes();
        fflush(stdin);
      } else {
        system("cls");
        buscar_cliente();
        fflush(stdin);
      }

    }
    /* OPÇÃO PARA VOLTAR AO MENU PRINCIPAL*/
  }

  /*INFORMA QUE NÃO FOI POSSIVEL ABRIR O ARQUIVO TXT*/
  else {
    printf("Não foi possível abrir o arquivo!");
    system("pause");
  }
  /*INFORMA QUE NÃO FOI POSSIVEL ABRIR O ARQUIVO TXT*/
}
/*TELA DE BUSCA DE PRODUTOS*/
/*-----------------------------------------------------*/

/* MENU DE PEDIDOS */
void menu_pedidos() {
  int esc;

  esc = 0;

  /*OPÇÕES DO MENU*/
  while (esc != 4) {
    cabecalho();
    gotoxy(25, 6);
    printf("[1] Novo Pedido\n");
    gotoxy(25, 7);
    printf("[2] Buscar Pedido\n");
    gotoxy(25, 8);
    printf("[3] Voltar para o menu principal\n");
    printf("\n");
    fflush(stdin);
    gotoxy(25, 12);
    printf("Escolha uma Opção: ");
    scanf("%d", & esc);
    /*OPÇÕES DO MENU*/

    /* FUNÇÕES DO MENU*/
    switch (esc) {
    case 1:
      system("cls");
      cadastrar_pedido();
      break;
    case 2:
      system("cls");
      buscar_pedido();
      break;
    case 3:
      system("cls");
      main();
      break;
    case 4:
      system("cls");
      main();
      break;
    case 5:
      system("cls");
      main();
      break;
    default:
      system("cls");
      gotoxy(25, 13);
      printf("Opção inválida!\n");
      break;
    }
    /* FUNÇÕES DO MENU */
  }
}
/* MENU DE PEDIDOS */
/*-----------------------------------------------------*/

/* TELA DE CADASTRO DE PEDIDOS*/
void cadastrar_pedido() {

      setlocale(LC_ALL, ""); //ACENTUAÇÕES SÃO VISÍVEIS ATRAVÉS DESTE CÓDIGO


    char esc = 's';
    int codPed;

  FILE * pedido;

  do {
    cabecalho();

    gotoxy(25, 5);
    printf("Digite o código do Pedido: \n");
    gotoxy(25, 6);
    scanf("%i", &codPed);
    system("cls");
    cabecalho();

    fflush(stdin);
    gotoxy(25, 5);
    printf("Digite o Nome do Cliente: \n");
    gotoxy(25, 6);
    fgets(cli.nome_cliente_stc, 150, stdin);
    system("cls");
    cabecalho();

    fflush(stdin);
    gotoxy(25, 5);
    printf("Digite o Nome do Produto: \n");
    gotoxy(25, 6);
    fgets(cad.nome_prod_stc, 150, stdin);
    system("cls");
    cabecalho();



    pedido = fopen("pedido.txt", "a"); //CRIA OU EDITA O ARQUIVO TXT
    fprintf(pedido, "%i;%s;%s\n", codPed, cli.nome_cliente_stc, cad.nome_prod_stc);
    //INSERE AS INFORMAÇÕES DO PEDIDO NO ARQUIVO TXT

    gotoxy(25, 5);
    printf("Cadastro incluido!\n");
    fclose(pedido); //FECHA O ARQUIVO TXT

    /* EXIBE AS INFORMAÇÕES DO CADASTRO DO PEDIDO REALIZADO */
    fflush(stdin);
    gotoxy(25, 7);
    printf("Código do Pedido: %i\n", cli.cod_cliente_stc);
    gotoxy(25, 8);
    printf("Nome do Cliente: %s\n", cli.nome_cliente_stc);
    gotoxy(25, 9);
    printf("Produto adquirido: %s\n", cad.nome_prod_stc);
    /* EXIBE AS INFORMAÇÕES DO CADASTRO DO CLIENTE REALIZADO */

    /* VERIFICA SE USUÁRIO QUER INSERIR OUTRO PEDIDO OU VOLTAR PARA O MENU*/
    gotoxy(25, 15);
    printf("Deseja cadastrar novamente? (S/N) ");
    gotoxy(25, 16);
    esc = getch();
    system("cls");
    fflush(stdin);
    /* VERIFICA SE USUÁRIO QUER INSERIR OUTRO PEDIDO OU VOLTAR PARA O MENU*/
  }

  while (esc == 's' || esc == 'S');

  if (esc != 's' || esc != 'S') {
    menu_pedidos();
  }
}
/* TELA DE CADASTRO DE PEDIDOS*/
/*-----------------------------------------------------*/

void buscar_pedido() {

    cabecalho();

  FILE * pedido;

  char pedidosLinha[280];
  char esc;
  int * codrstd;
  int existe = 0;
  int linha = 6;
  int codPedBusca;
  int resultDivCod;

  gotoxy(20, linha);
  printf("Insira o código do pedido: ");
  gotoxy(50, linha++);
  scanf("%d", & codPedBusca);

  pedido = fopen("pedido.txt", "r");

  if (pedido != NULL) {
    /*VERIFICA SE O ARQUIVO TXT FOI ABERTO*/

    /*IMPRIME OS DADOS DO ARQUIVO TXT, CASO TENHA SIDO ABERTO*/

    while (!feof(pedido)) {
      char * rstd = fgets(pedidosLinha, 256, pedido); /*BUSCA AS LINHAS DO ARQUIVO TXT*/
      codrstd = strtok(rstd, ";"); /*DIVIDE A LINHA DO ARQUIVO EM ";"*/
      resultDivCod = atoi(codrstd); /*SALVA O CONTEÚDO DO PONTEIRO STRING E CONVERTE PARA INT*/

      if (resultDivCod == codPedBusca) {
        existe = 1;
        if (codrstd != NULL) {

          codrstd = strtok(NULL, ";");
          gotoxy(20, linha++);
          printf("Nome do Cliente: %s", codrstd);
          printf("\n");

          codrstd = strtok(NULL, ";");
          gotoxy(20, linha++);
          printf("Produto: %s", codrstd);
          printf("\n");
        }
      }
    }
    if (existe == 0) {
      fflush(stdin);
      gotoxy(25, linha++);
      printf("Pedido não encontrado!");
    }

    /* OPÇÃO PARA VOLTAR AO MENU PRINCIPAL*/
    if (feof(pedido)) {
        fclose(pedido);
      gotoxy(20, linha++);
      printf("Pressione 'ENTER' para buscar novamente");
      gotoxy(17, linha++);
      printf("Pressione 'S' para voltar para o menu anterior");
      esc = getch();
      if (esc == 's' || esc == 'S') {
        system("cls");
        menu_pedidos();
        fflush(stdin);
      } else {
        system("cls");
        buscar_pedido();
        fflush(stdin);
      }

    }
    /* OPÇÃO PARA VOLTAR AO MENU PRINCIPAL*/
  }

  /*INFORMA QUE NÃO FOI POSSIVEL ABRIR O ARQUIVO TXT*/
  else {
    printf("Não foi possível abrir o arquivo!");
    system("pause");
  }
  /*INFORMA QUE NÃO FOI POSSIVEL ABRIR O ARQUIVO TXT*/
}
/*TELA DE BUSCA DE PRODUTOS*/
/*-----------------------------------------------------*/

/*BUSCAR DE ELOGIOS E RECLAMAÇÕES*/
/*-----------------------------------------------------*/
/*MENU PRINCIPAL ADM*/
int main() {

system("mode 80, 25");
  //system("color 71");
  setlocale(LC_ALL, ""); //ACENTUAÇÕES SÃO VISÍVEIS ATRAVÉS DESTE CÓDIGO

  int esc;

  esc = 0;

  /*OPÇÕES DO MENU PRINCIPAL*/
  while (esc != 4) {
    cabecalho();
    gotoxy(25, 6);
    printf("[1] Estoque\n");
    gotoxy(25, 7);
    printf("[2] Pedidos\n");
    gotoxy(25, 8);
    printf("[3] Clientes\n");
    gotoxy(25, 9);
    printf("[4] Elogios e Reclamações\n");
    gotoxy(25, 10);
    printf("[0] Encerrar app\n");
    gotoxy(25, 11);
    printf("\n");
    fflush(stdin);
    gotoxy(25, 13);
    printf("Escolha uma Opção: ");
    scanf("%d", & esc);
    /*OPÇÕES DO MENU PRINCIPAL*/

    /* FUNÇÕES DO MENU PRINCIPAL*/
    switch (esc) {
    case 0:
      gotoxy(25, 16);
      printf("Saindo da aplicação\n");
      gotoxy(20, 17);
      system("pause");
      exit(0);
      break;
    case 1:
      system("cls");
      menu_produtos();
      break;
    case 2:
      system("cls");
      menu_pedidos();
      break;
    case 3:
      system("cls");
      gotoxy(25, 16);
      menu_clientes();
      break;
    case 4:
      system("cls");
      gotoxy(25, 16);
      menu_elog_recl();
      break;
    default:
      system("cls");
      gotoxy(25, 16);
      printf("Opção inválida!\n");
      break;
    }
    /* FUNÇÕES DO MENU PRINCIPAL*/
  }
  return 0;
}
