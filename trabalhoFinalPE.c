#include <stdio.h>
#include <string.h>
// trojs
#define MAXCLIENTES 200 // numero maximo de clientes permitido

// registro da ultima compra
typedef struct {
    float totalValor;
    int compraCancelada;
    int bonusUtilizado;
    int valortBonus;
} tCompra;

// registro do bonus
typedef struct {
    int tetotBonus;
    float valorInicialtBonus;
    float valorRecebertBonus;
} tBonus;

// registro do cliente
typedef struct {
    char nome[100];
    char cpf[12];
    char telefone[15];
    int bonus;
    float totaltCompras;
    tCompra ultimatCompra;
} tCliente;


// 01 - funcao de configurar o bonus
// altera as configuracoes iniciais dos bonus 
void configurartBonus(tBonus *b, tCliente *clientes, int quantidadetClientes) {
    int opcao, i;
    float mudarReceber, mudartBonus, mudarTeto;
    do {
        printf("MENU CONFIGURAR BONUS\n");
        printf("1- Alterar teto\n");
        printf("2- Alterar valor de um bonus\n");
        printf("3- Alterar valor para receber bonus\n");
        printf("0- Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        printf("\n");
        
        switch (opcao) {
            case 1:
                do {
                    printf("Qual o novo valor do teto?: ");
                    scanf("%f", &mudarTeto);
                    if (mudarTeto < 0) 
                        printf("Erro: valor negativo. Digite novamente\n");
                } while (mudarTeto < 0);
                
                b->tetotBonus = mudarTeto; // guarda o novo valor no espaco da memoria

                printf("Novo valor de teto: %d\n", b->tetotBonus);
                 for (i=0; i < quantidadetClientes; i++){
                if (clientes[i].bonus > b->tetotBonus){
                    clientes[i].bonus = b->tetotBonus;
                }
            }
                break;

            case 2:
                do {
                    printf("Qual o novo valor de 1 bonus?: ");
                    scanf("%f", &mudartBonus);
                    if (mudartBonus < 0) 
                        printf("Erro: valor negativo. Digite novamente\n");
                } while (mudartBonus < 0);
                
                b->valorInicialtBonus = mudartBonus; // mesma coisa do anterior 
                
                printf("Novo valor de 1 bonus: %.2f\n", b->valorInicialtBonus);
                break;

            case 3:
                do {
                    printf("Qual o novo valor para receber bonus?: ");
                    scanf("%f", &mudarReceber);
                    if (mudarReceber < 0) 
                        printf("Erro: valor negativo. Digite novamente\n");
                } while (mudarReceber < 0);
                
                b->valorRecebertBonus = mudarReceber; // mesma coisa do anterior
                
                printf("Novo valor para receber bonus: %.2f\n", b->valorRecebertBonus);
                break;

            case 0:
                printf("Voltando ao Menu Principal.\n");
                break;

            default:
                printf("OpcA£o Invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// 02 - funcao de cadastrar cliente
// cadastra os clientes no sistema da loja
void cadastrartCliente(tCliente *clientes, int *quantidadetClientes) {
    char cpf[12];
    int igual = 0;
    int i;// outra flag (0 =  nao achou  1 = achou)
    
    while (getchar() != '\n'); // funciona pegando tds os caracteres atA© que ele seja um espaco, a partir disso, nA£o pega mais nada
    
    printf("Qual o CPF (tudo junto)? ");
    scanf("%12s", cpf);  // Usa scanf para garantir que o CPF nA£o ultrapasse 11 caracteres
    while (getchar() != '\n');  // Limpa o buffer atA© o fim da linha
// funciona pegando tds os caracteres atA© que ele seja um espaco, a partir disso, nA£o pega mais nada e nA£o dar erro na hora de receber o nome

    // Verifica se o CPF tem exatamente 11 caracteres
    if (strlen(cpf) != 11) {
        printf("Erro: CPF deve ter exatamente 11 caracteres.\n");
        return; // Retorna imediatamente se o CPF for invalido
    }
    
  //  printf("CPF lido: '%s'\n", cpf); // conferindo...

    
    for ( i = 0; i < *quantidadetClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            igual = 1;
            printf("Erro: CPF ja cadastrado\n");
            break;
        }
    }

    if (igual) {
        return;
        
    } else {

        strcpy(clientes[*quantidadetClientes].cpf, cpf); // quantidadetClientes = i
        printf("Qual o nome? ");
        fgets(clientes[*quantidadetClientes].nome, 100, stdin);
// fgets pega os nomes com espacos, nome com sobrenome

        // remove o '\n' que fgets pode adicionar no final da string e nao da pra usar o strtok 
        // porque ele pode adicionar um \0, alterando a string
// ðYY¥ðYY¥ðYY¥ðYY¥ðYY¥ðYY¥ tentar substituir essas 2 linhas abaixo pelo while getchar
       if (clientes[*quantidadetClientes].nome[strlen(clientes[*quantidadetClientes].nome) - 1] == '\n') { // -1 pq a contagem do indice comeca sempre no 0
            clientes[*quantidadetClientes].nome[strlen(clientes[*quantidadetClientes].nome) - 1] = '\0'; // -1 pq a contagem do indice comeca sempre no 0
        }
        
    //    printf("Nome lido: '%s'\n", clientes[*quantidadetClientes].nome);// conferindo ... dnv

     // while (getchar() != '\n');  // Limpa o buffer atA© o fim da linha


        printf("Qual o telefone (tudo junto) ? ");
        scanf("%s", clientes[*quantidadetClientes].telefone);
        //    printf("Telefone lido: '%s'\n", clientes[*quantidadetClientes].telefone);

        printf("Cadastro bem sucedido!\n");
        
        clientes[*quantidadetClientes].bonus = 0; // pra alterar a quantidade de bonus previo tem que trocar o 0 por 
                                                  // outro valor desejado, ou toda vez os bonus vao comecar no 0
                                                 
        clientes[*quantidadetClientes].totaltCompras = 0;
        (*quantidadetClientes)++; // atua como indice 
    }
}

// XX- funcao alternativa pra nao precisar conferir o cpf toda hora
int encontrartClientePeloCPF(tCliente *clientes, int quantidadetClientes, const char *cpf) {
    int i;
    for (i = 0; i < quantidadetClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            return i; // Retorna o indice do cliente encontrado
        }
        if (strlen(cpf) != 11) {
        printf("Erro: CPF deve ter exatamente 11 caracteres.\n");
        break; // Retorna imediatamente se o CPF for invalido
        }
    }
    return -1; // Retorna -1 se nA£o encontrar o cliente
}

// 03 - funcao de alterar alguma informacao do cadastro
// possibilita a correcA£o de algum erro durante o cadastro na funcao 2 no registro de cada cliente
void alterarCadastro(tCliente *clientes, int quantidadetClientes) {
    char cpf[12];
    int encontrado = -1; // vai guardar o indice se achar, ai vai subir de -1 pra 0
                         // que A© onde comeca a contabilizar os indices

    printf("Qual o CPF do cliente? ");
    scanf("%11s", cpf);

    // procura o cliente pelo cpf
    encontrado = encontrartClientePeloCPF(clientes, quantidadetClientes, cpf);
        if (encontrado == -1) {
        printf("\nErro: CPF nao cadastrado.");
        return;
        }
        
    int opcao;
    int i;
    do {
        
        printf("\nMENU ALTERA CLIENTE\n");
        printf("1 - Alterar CPF\n");
        printf("2 - Alterar nome\n");
        printf("3 - Alterar telefone\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        printf("\n");
        
        switch (opcao) {
            
            // altera o cpf
            case 1: {
                char novoCPF[12];
                printf("Qual o novo CPF? ");
                scanf("%s", novoCPF);

                // verifica se o cpf 'novo' nao A© igual a algum ja cadastrado 
                int cpfExiste = 0; // flag
                for ( i = 0; i < quantidadetClientes; i++) {
                    if (strcmp(clientes[i].cpf, novoCPF) == 0) {
                        cpfExiste = 1;
                        break;
                    }
                }
                if (cpfExiste) { // cpfExiste = 1
                    printf("Erro: CPF ja cadastrado.\n");
                } else { // cpfExiste = 0
                    strcpy(clientes[encontrado].cpf, novoCPF);
                    printf("CPF alterado com sucesso!\n");
                }
                break;
            }

            // altera o nome
            case 2: {
                printf("Qual o novo nome? ");
                getchar(); // limpa o lixo do teclado
                fgets(clientes[encontrado].nome, 100, stdin);
                // remove o '\n' que pode ser adicionado pelo fgets
                if (clientes[encontrado].nome[strlen(clientes[encontrado].nome) - 1] == '\n') {
                    clientes[encontrado].nome[strlen(clientes[encontrado].nome) - 1] = '\0';
                }
                printf("Nome alterado com sucesso!\n");
                break;
            }

            // altera o telefone
            case 3: {
                printf("Qual o novo telefone? ");
                scanf("%s", clientes[encontrado].telefone); // encontrado = i
                printf("Telefone alterado com sucesso!\n");
                break;
            }

            case 0:
                printf("Voltando ao menu principal.\n");
                break;

            default:
                printf("OpcA£o invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// 04 - funcao de efetivar uma compra 
// realiza a compra do usuario e registra no cpf dele q esta no vetor e da acesso a todas as 
// outras informacoes dele
void efetivartCompra(tCliente *clientes, int quantidadetClientes, tBonus *b, int *bonusUsado, int *bonusNovo) {
    char cpf[12];
    int encontrado = -1; // vai guardar o indice se achar, comeca com -1 (nao encontrado)
    int usartBonus = 0, desistirtCompra = 0;
    float valortCompra = 0, valorFinal = 0;
    float valorPagamento = 0; 
    *bonusUsado = 0, *bonusNovo = 0;
    int remendo = 0;
     
        printf("Qual o CPF do cliente? ");
        scanf("%11s", cpf);

        // procura o cliente pelo cpf (pergunta 1)
        encontrado = encontrartClientePeloCPF(clientes, quantidadetClientes, cpf);
        if (encontrado == -1) {
            printf("Erro: CPF nao cadastrado.\n");
            return; // retorna valor porque a funcao nao A© void
        }

        // pergunta 2
        do {
            printf("Qual o valor da compra? R$ ");
            scanf("%f", &valortCompra);
            if (valortCompra < 0) {
                printf("Erro: valor negativo. Digite novamente.\n");
            }
        } while (valortCompra < 0);

        // se o cliente tem bonus disponivel
        float bonusCorrespondente = clientes[encontrado].bonus * b->valorInicialtBonus;
        
        printf("BONUS ATUAL = %d. VALOR CORRESPONDENTE = R$ %.2f\n", clientes[encontrado].bonus, bonusCorrespondente);

        valorFinal = valortCompra;
        // pergunta 3
        if (clientes[encontrado].bonus > 0) {
            do {
                printf("Deseja utilizar seu bonus? [1- sim, 0- nao]: ");
                scanf("%d", &usartBonus);
            } while (usartBonus != 0 && usartBonus != 1);
            if (usartBonus) {
                remendo = clientes[encontrado].bonus - ((int)(valortCompra/b->valorInicialtBonus));
                if (remendo < 0) remendo = 0;
                
                valorFinal -= bonusCorrespondente;
                
                if (valorFinal < 0) valorFinal = 0;
                
                printf("BONUS ATUAL = %d. VALOR DA COMPRA ATUALIZADO = R$ %.2f\n", remendo, valorFinal);
            } 
        }
        
     

        // pergunta 4
        if (valorFinal > 0 ){
        do {
           printf("Qual o valor de pagamento do cliente? R$ ");
           scanf("%f", &valorPagamento);
            
            if (valorPagamento < 0) { // se ele digitar valor negativo
                printf("Erro: valor negativo. Digite novamente.\n");
                
            } else if (valorPagamento < valorFinal) { // se ele digitar um valor menor que o valor da compr
            
                do {
                    printf("Erro: Valor do pagamento inferior ao valor da compra. Deseja desistir da compra? [1-sim 0-nao]: ");
                    scanf("%d", &desistirtCompra);
                } while (desistirtCompra != 1 && desistirtCompra != 0);

                if (desistirtCompra) {
                    printf("tCompra cancelada! Voltando ao menu principal.\n");
                    clientes[encontrado].ultimatCompra.compraCancelada = 1;
                    if (clientes[encontrado].bonus < 0) // garantir que nao vai virar negativo
                        clientes[encontrado].bonus = 0;
                    return; // retorna pro menu principal sem finalizar o programa
                    
                } else {
                    printf("Reiniciando processo de compra.\n"); // reinicia o processo de compra
                }
            }
        } while (valorPagamento < valorFinal);
        } else {
            return;
        }
        
        float troco = valorPagamento - valorFinal;
        
        if (troco > 0) {
            // exibe o valor final pro cliente
            printf("TROCO = R$ %.2f\n", troco);
        }
        
        printf("\nVALOR FINAL DA COMPRA = R$ %.2f\n", valorFinal);

        int bonusTemporario = 0;
        clientes[encontrado].totaltCompras += valortCompra; // vai incremnetar o valor sem bonus nas compras totais
        
            if (usartBonus){
                *bonusUsado = (int)(valortCompra/ b->valorInicialtBonus);// atualizando
                // bonusTemporario = *bonusUsado - clientes[encontrado].bonus;
                clientes[encontrado].bonus -= *bonusUsado;
            } else{
                if (valorFinal >= b->valorRecebertBonus) 
                    *bonusNovo = (int)(valortCompra / b->valorRecebertBonus);
                    clientes[encontrado].bonus += *bonusNovo;
            }
            
            printf("Sucesso!\n");
            
            if (clientes[encontrado].bonus < 0) // garantir que nao vai virar negativo
                clientes[encontrado].bonus = 0;
            if (clientes[encontrado].bonus > b->tetotBonus )
                clientes[encontrado].bonus = b->tetotBonus;
                
            //clientes[encontrado].ultimatCompra.bonusUtilizado = *bonusUsado;
            clientes[encontrado].ultimatCompra.totalValor = valortCompra;
            clientes[encontrado].ultimatCompra.bonusUtilizado = *bonusUsado;
            clientes[encontrado].ultimatCompra.valortBonus = *bonusNovo;
            clientes[encontrado].ultimatCompra.compraCancelada = 0;
}

// 05 - funcao de cancelar compra
// cancela alguma compra especifica do cliente de escolha do usuario e desconta os bonus correspondentes
void cancelartCompra(tCliente *clientes, int quantidadetClientes, tBonus *b){
    char cpf[12];
    int encontrado = -1; // vai guardar o indice se achar, ai vai subir de -1 pra 0
                         // que e onde comeca a contabilizar os indices
    int cancelar = -1;
    int bonusRemovido = 0;
    float valortCompraCancel = 0;
    float valorRemovido=0;

    do{ 
        printf("Qual o CPF do cliente? ");
        scanf("%11s", cpf);

    // procurar o cliente pelo cpf
    encontrado= encontrartClientePeloCPF(clientes, quantidadetClientes, cpf);
    if (encontrado == -1) {
        printf("Erro: CPF nao cadastrado. Deseja informar outro CPF [1-sim, 0-nao]: ");
        scanf("%d", &cancelar);
        
        if (cancelar == 0) {
            return; // sai da funcA£o se cancelar for 0
        }
    } else {
        cancelar = 0; // define cancelar como 0 para encerrar o loop do cpf certo ou errado
    }
    } while (cancelar != 0);
    
    cancelar = 0;
    int opcao;
    do {
        printf("\nMENU CANCELA COMPRA\n");
        printf("1 - Ultima compra\n");
        printf("2 - Outra compra\n");
        printf("3 - Exibir dados da ultima compra\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:{
                if (clientes[encontrado].ultimatCompra.compraCancelada == 1) {
                    printf("\nERRO: Ultima compra ja cancelada!\n");
                } else {
                    // Confirma o cancelamento
                    printf("\nTem certeza que deseja cancelar a ultima compra? [1-sim, 0-nao]: ");
                    scanf("%d", &cancelar);
                  
                        // atualiza o bonus e o total de compras
                    if (cancelar) {
                        
                        //bonusRemovido = clientes[encontrado].ultimatCompra.bonusUtilizado;
                        bonusRemovido = (int)(clientes[encontrado].ultimatCompra.totalValor / b->valorRecebertBonus);
                        valorRemovido = clientes[encontrado].ultimatCompra.totalValor;
    
                        clientes[encontrado].bonus -= bonusRemovido; // exclui os bonus da ultima compra
                        if (clientes[encontrado].bonus < 0) // garantir que nao vai virar negativo
                            clientes[encontrado].bonus = 0;
                        
                        clientes[encontrado].totaltCompras -= valorRemovido; // exclui o valor da ultima compra do total
                        clientes[encontrado].ultimatCompra.compraCancelada = 1; // flag

                        printf("COMPRA CANCELADA!\n");
                    } else {
                        printf("COMPRA NAƒO CANCELADA!\n");
                         clientes[encontrado].ultimatCompra.compraCancelada = 0;
                    }
                }  
        
             break;
            }
        
            case 2:{
                do{ 
                    printf("\nQual o valor da compra que deseja cancelar? ");
                    scanf("%f", &valortCompraCancel);
                    
                    if (valortCompraCancel < 0)
                    printf("\nErro: valor negativo. Digite novamente.");
                } while (valortCompraCancel < 0);
                
                bonusRemovido = (int)(valortCompraCancel / b->valorRecebertBonus) * 2; // duplica os bonus perdidos
                
                printf("BONUS A SER DESCONTADO = %d. Tem certeza que deseja cancelar a compra? [1-sim, 0-nao]: ", bonusRemovido);
                // confirmar se o cliente vai querer cancelar e perder o dobro de bonus
                scanf("%d", &cancelar);

                if (cancelar) {
                    // atualizando a quantidade de bonus caso o usuario cancele mesmo a compra
                    clientes[encontrado].bonus -= bonusRemovido;
                    
                    if (clientes[encontrado].bonus == bonusRemovido)
                        clientes[encontrado].bonus = 0;
                    
                    if (clientes[encontrado].bonus < 0) // garantir que nao vai virar negativo
                        clientes[encontrado].bonus = 0;
                        
                    clientes[encontrado].totaltCompras -= valortCompraCancel;
                   
                    printf("COMPRA CANCELADA!\n");
                } else {
                    printf("COMPRA NAO CANCELADA!\n");
                }
                break;
            }
            
            case 3:{ // exibir os dados da ultima compra
            if (clientes[encontrado].ultimatCompra.compraCancelada == 1) {
                    printf("\nUltima compra cancelada!\n");
                } else {
                printf("NOME DO CLIENTE: %s\n", clientes[encontrado].nome);
                printf("CPF DO CLIENTE: %s\n", clientes[encontrado].cpf);
                printf("VALOR DA COMPRA: R$ %.2f\n", clientes[encontrado].ultimatCompra.totalValor);
                printf("PONTOS ADQUIRIDOS COM A COMPRA: %d\n", clientes[encontrado].ultimatCompra.valortBonus);
                printf("VALOR DE UM BONUS NA EPOCA DA COMPRA: R$ %.2f\n", b->valorInicialtBonus);
                break;
                }
            }
            
            case 0: {// retornar pro menu
                printf("Voltando ao menu principal...\n");
                break;
            }
            
            default:
                printf("Opcao invalida! Tente novamente.\n");
        } 
    }while (opcao != 0);
}

// 06 - funcao de consultar tBonus
// mostra o bonus de um cliente so a partir do cpf dele
void consultartBonus(tCliente *clientes, int quantidadetClientes, tBonus *b, int *bonusUsado, int *bonusNovo){
    char cpf[12];
    int encontrado = -1; // vai guardar o indice se achar, ai vai subir de -1 pra 0
                         // que e onde comeca a contabilizar os indices

    printf("Qual o CPF do cliente? ");
    scanf("%11s", cpf);

    // procurar o cliente pelo cpf
    encontrado = encontrartClientePeloCPF(clientes, quantidadetClientes, cpf);
    if (encontrado == -1) {
    printf("\nErro: CPF nao cadastrado.");
    return;
    }
    
    float bonusCorrespondente = clientes[encontrado].bonus * b->valorInicialtBonus;;
    
    printf("BONUS DEPOIS DA ULTIMA COMPRA = %d. VALOR CORRESPONDENTE = R$ %.2f\n", clientes[encontrado].bonus, bonusCorrespondente);
}

// 07 - funcao de listar os dados de todos os clientes
// mostra os dados de todos os clentes cadastrados na loja
void listartClientes(tCliente *clientes, int quantidadetClientes) {
    int i;
    printf("LISTA DE CLIENTES\n");
    for ( i = 0; i < quantidadetClientes; i++) {
        printf("tCliente %d:\n", i + 1);
        printf("  Nome: %s\n", clientes[i].nome);
        printf("  CPF: %s\n", clientes[i].cpf);
        printf("  Telefone: %s\n", clientes[i].telefone);
        if(clientes[i].totaltCompras < 0)
            clientes[i].totaltCompras = 0;
        printf("  Total de compras: %.2f\n", clientes[i].totaltCompras);
        if(clientes[i].bonus < 0)
            clientes[i].bonus = 0;
        printf("  Bonus: %d\n", clientes[i].bonus);
    }
    if (quantidadetClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
    }
}

// 08 - funcao de mostrar os bonus do cliente
// mostra os bonus de todos os clientes cadastrados na loja
void listartBonus(tCliente *clientes, int quantidadetClientes, tBonus *b){
    int i;
    printf("\nRELATORIO BONUS DOS CLIENTES\n");
    
    for( i = 0; i < quantidadetClientes; i++){
        printf("Nome: %s\n", clientes[i].nome);
        printf("CPF: %11s\n", clientes[i].cpf);
        printf("tBonus: %d\n", clientes[i].bonus);
        printf("Valor do tBonus: R$ %.2f\n", clientes[i].bonus * b->valorInicialtBonus);
        printf("------------------------------------------------------------\n");  
    }
}

// 09 - funcao de listar os clientes pelo valor de compra (maior pro menor)
// encontra os clientes que cumprem os requisitos que o usuario escolher baseado no valor total de compras
void rankingtClientes(tCliente *clientes, int quantidadetClientes){
    
    int opcao;
    int i;
    do {
        printf("RELATORIO DE COMPRAS\n");
        printf("1- Total de compras inferior a um valor\n");
        printf("2- Total de compras superior a um valor\n");    
        printf("3- Total de compras igual a um valor\n");
        printf("4- Total de compras em uma faixa\n");
        printf("0- Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        printf("\n");
        
        switch (opcao) {
            
            // acha os inferiores
            case 1: {
                float inferiorValor = 0;
                int encontrado = 0; // vai guardar o indice se achar, ai vai subir de -1 pra 0
                                    // que A© onde comeca a contabilizar os indices
                do{
                    printf("\nQual o valor? ");
                    scanf("%f", &inferiorValor);
                    
                    if (inferiorValor < 1) 
                    printf("Erro: valor negativo. Digite novamente: ");
                    
                } while (inferiorValor < 1);
                
                printf("\nRELATORIO DE COMPRAS\n");
                for ( i = 0; i < quantidadetClientes; i++) {
                    if (clientes[i].totaltCompras < inferiorValor) {
                    encontrado = 1; 

                    printf("Nome: %s\n", clientes[i].nome);
                    printf("CPF: %s\n", clientes[i].cpf);
                    printf("Total em compras: R$ %.2f\n", clientes[i].totaltCompras);
                    printf("------------------------------------------------------------\n");
                    }
                }
                if (!encontrado) {
                printf("Nenhum cliente encontrado com compras acima de R$ %.2f.\n", inferiorValor);
                }
                break;
            }

            // acha os superiores
            case 2: {
                float superiorValor = 0;
                int encontrado = 0; // vai guardar o indice se achar, ai vai subir de -1 pra 0
                                    // que e onde comeca a contabilizar os indices
                do{
                    printf("\nQual o valor? ");
                    scanf("%f", &superiorValor);
                    
                    if (superiorValor < 1) 
                    printf("Erro: valor negativo. Digite novamente: ");
                    
                } while (superiorValor < 1);
                
                printf("\nRELATORIO DE COMPRAS\n");
                for ( i = 0; i < quantidadetClientes; i++) {
                    
                    if (clientes[i].totaltCompras > superiorValor) {
                    encontrado = 1; 
                    
                    printf("Nome: %s\n", clientes[i].nome);
                    printf("CPF: %s\n", clientes[i].cpf);
                    printf("Total em compras: R$ %.2f\n", clientes[i].totaltCompras);
                    printf("------------------------------------------------------------\n");
                    }
                }
                
                if (!encontrado) {
                printf("Nenhum cliente encontrado com compras acima de R$ %.2f.\n", superiorValor);
                }
                break;
            }
            // acha os iguais
            case 3: {
            float igualValor = 0;
                int encontrado = 0; // vai guardar o indice se achar, ai vai subir de -1 pra 0
                                    // que e onde comeca a contabilizar os indices
                do{
                    printf("\nQual o valor? ");
                    scanf("%f", &igualValor);
                    
                    if (igualValor < 1) 
                    printf("Erro: valor negativo. Digite novamente: ");
                    
                } while (igualValor < 1);
                
                for ( i = 0; i < quantidadetClientes; i++) {
                
                printf("\nRELATORIO DE COMPRAS\n");
                if (clientes[i].totaltCompras == igualValor) {
                    encontrado = 1; 

                    printf("Nome: %s\n", clientes[i].nome);
                    printf("CPF: %s\n", clientes[i].cpf);
                    printf("Total em compras: R$ %.2f\n", clientes[i].totaltCompras);
                    printf("------------------------------------------------------------\n");
                    }
                }
                if (!encontrado) {
                printf("Nenhum cliente encontrado com compra igual a R$ %.2f.\n", igualValor);
                }
                break;
            }
            
            // acha o que e maior q X e menor que Y
            case 4: {
                float inicialValor = 0;
                float finalValor = 0;
                int encontrado = 0; // vai guardar o indice se achar, ai vai subir de -1 pra 0
                                    // que e onde comeca a contabilizar os indices
                do{
                    printf("\nQual o valor inicial? ");
                    scanf("%f", &inicialValor);
                    
                    if (inicialValor < 1) 
                    printf("Erro: valor negativo. Digite novamente: ");
                    
                    printf("Qual o valor final? ");
                    scanf("%f", &finalValor);
                    
                    if (finalValor < 1) 
                    printf("Erro: valor negativo. Digite novamente: ");
                    
                } while (inicialValor < 1 || finalValor < 1);
                
              
                
                
                // invertendo os valores caso o inicial seja maior que o final
                float aux = 0; 
                if (inicialValor > finalValor) {
                    aux = inicialValor;
                    inicialValor = finalValor;
                    finalValor = aux;
                }
                
                printf("\nRELATORIO DE COMPRAS\n");
                for ( i = 0; i < quantidadetClientes; i++) {
                    if (clientes[i].totaltCompras > inicialValor && clientes[i].totaltCompras < finalValor) {
                        encontrado = 1;
            
                        printf("Nome: %s\n", clientes[i].nome);
                        printf("CPF: %s\n", clientes[i].cpf);
                        printf("Total em compras: R$ %.2f\n", clientes[i].totaltCompras);
                        printf("------------------------------------------------------------\n");
                    }
                }
                
                if (!encontrado) {
                    printf("Nenhum cliente encontrado com compras entre R$ %.2f e R$ %.2f.\n", inicialValor, finalValor);
                }
                break;
            }

            case 0:{
                printf("Voltando ao menu principal.\n");
                break;
            }
            
            default:{
                printf("Opcao invalida! Tente novamente.\n");
            }
        }
    } while (opcao != 0);
}

// funcao do menu principal
// une a chamada de todas as funcoes pra atender aos pedidos do usuario
void menuPrincipal() {
    int opcao;
    tCliente clientes[MAXCLIENTES];
    int quantidadetClientes = 0, bonusUsado = 0, bonusNovo = 0;

    tBonus b = {1000, 0.50, 100};
    do {
        printf("\nMENU PRINCIPAL\n");
        printf("01 - Configurar bonus\n"); // check  --------------------------------- 32
        printf("02 - Cadastrar cliente\n"); // check --------------------------------- 97
        printf("03 - Alterar cadastro do cliente\n"); // check ----------------------- 179
        printf("04 - Efetivar compra\n"); // check ----------------------------------- 265
        printf("05 - Cancelar compra\n"); // check ----------------------------------- 388
        printf("06 - Consultar bonus\n"); // check ----------------------------------- 519
        printf("07 - Listar dados de todos os clientes\n"); //check ------------------ 541
        printf("08 - Listar bonus de todos os clientes\n"); // check ----------------- 563
        printf("09 - Listar clientes pelo valor total de compras\n"); // check ------- 577
        printf("00 - Sair\n"); // check
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        if (opcao == 1 || opcao == 01){
            configurartBonus(&b, clientes, quantidadetClientes);
        } else if (opcao == 2 || opcao == 02) {
            cadastrartCliente(clientes, &quantidadetClientes);
        } else if (opcao == 3 || opcao == 03) {
            alterarCadastro(clientes, quantidadetClientes);
        } else if (opcao == 4 || opcao == 04) {
            efetivartCompra(clientes, quantidadetClientes, &b, &bonusUsado, &bonusNovo);
        } else if (opcao == 5 || opcao == 05) {
            cancelartCompra(clientes, quantidadetClientes, &b);
        } else if (opcao == 6 || opcao == 06) { 
            consultartBonus(clientes, quantidadetClientes, &b, &bonusUsado, &bonusNovo);
        } else if (opcao == 7 || opcao == 07) {
            listartClientes(clientes, quantidadetClientes);
        } else if (opcao == 8) {
            listartBonus(clientes, quantidadetClientes, &b);
        } else if (opcao == 9) {
            rankingtClientes(clientes, quantidadetClientes);
        } else if (opcao == 0) {
            printf("Encerrando...");
            break;
        }
    } while (opcao != 0);
}

int main() {
    menuPrincipal();
    return 0;
}