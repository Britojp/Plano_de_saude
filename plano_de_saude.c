#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "cabecalho.h"


#define MAX 10000

//verificações
bool Data_de_nascimentoo_valida(const char* data) {
    int dia, mes, ano;
    return sscanf(data, "%d/%d/%d", &dia, &mes, &ano) == 3;
}

bool Masculino_ou_Feminino(const char* sexo_biologico) {
    char sexo;
    return sscanf(sexo_biologico, "%c", &sexo) == 1 && (sexo == 'M' || sexo == 'F');
}
bool CPF_valido(const char* CPF) {
    int digitos = 0;
    while (*CPF) {
        if (*CPF >= '0' && *CPF <= '9') {
            digitos++;
        } else {
            return false;
        }
        CPF++;
    }
    return digitos == 11;
}




//funções
void inicializarFilaDupla(FilaDupla* fila) { 
    fila->quantidadePacientes = 0;
    fila->inicio = NULL;
    fila->fim = NULL; 
}

void inserirPaciente(FilaDupla* fila, Paciente paciente) {
    if (fila->quantidadePacientes == MAX) {
        printf("O Plano esta cheio!\n"); //fila cheia
        return;
    }
    Node* novo = (Node*) malloc(sizeof(Node));
    if (novo == NULL) {
        printf("Erro de operacao!\n");//erro ao alocar memoria
        return;
    }
    novo->paciente = paciente;
    novo->proximo = NULL;
    if (fila->quantidadePacientes == 0) {
        novo->anterior = NULL;
        fila->inicio = novo;
    } else {
        novo->anterior = fila->fim;
        fila->fim->proximo = novo;
    }
    fila->fim = novo;
    fila->quantidadePacientes++;
}
void quantidadePacientes(FilaDupla* fila) {
    printf("Quantidade de pacientes: %d\n", fila->quantidadePacientes);
}
void RemoverPaciente(FilaDupla* fila, Paciente paciente) {
    if (fila->quantidadePacientes == 0) {
        printf("Nao existe pacientes registrados!\n");
        return;
    }
    Node* atual = fila->inicio;
    while (atual != NULL && strcmp(atual->paciente.cpf, paciente.cpf) != 0) {
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Paciente nao encontrado!\n");
        return;
    }
    if (atual->anterior == NULL) {
        fila->inicio = atual->proximo;
    } else {
        atual->anterior->proximo = atual->proximo;
    }
    if (atual->proximo == NULL) {
        fila->fim = atual->anterior;
    } else {
        atual->proximo->anterior = atual->anterior;
    }
    free(atual);
    printf("\n");
    printf("Paciente removido com sucesso!\n");
    printf("\n");

    fila->quantidadePacientes--;
}

void imprimirPacientes(FilaDupla* fila) {
    if (fila->quantidadePacientes == 0) {
        printf("A fila esta vazia!\n");
        return;
    }
    Node* atual = fila->inicio;
    while (atual != NULL) {
        printf("\n");
        printf("Nome: %s\n", atual->paciente.nome);
        printf("CPF: %s\n", atual->paciente.cpf);
        printf("Data de nascimento: %s\n", atual->paciente.dataNascimento);
        printf("Sexo: %s\n", atual->paciente.sexo);
        printf("Valor do plano: %.2f\n", atual->paciente.valorMensalidade);
        printf("\n");
        atual = atual->proximo;
    }
}

void CalcularValorPlano(FilaDupla* fila, Paciente paciente) {
    if (fila->quantidadePacientes == 0) {
        printf("A fila esta vazia!\n");
        return;
    }
    
    Node* atual = fila->inicio;
    while (atual != NULL && strcmp(atual->paciente.cpf, paciente.cpf) != 0) {
        atual = atual->proximo;
    }
    
    if (atual == NULL) {
        printf("Paciente nao encontrado!\n");
        return;
    }
    
    int anoNascimento = atoi(paciente.dataNascimento + 6);
    int idade = 2024 - anoNascimento;
    paciente.valorMensalidade = 0;
    if (idade < 18) {
        atual->paciente.valorMensalidade = 100;
    } else if (idade >= 18 && idade <= 33) {
        atual->paciente.valorMensalidade = 150;
    } else if (idade >= 34 && idade <= 60) {
        atual->paciente.valorMensalidade = 195;
    } else {
        atual->paciente.valorMensalidade = 230;
    }
}



void BuscarPaciente(FilaDupla* fila, Paciente paciente) {
    if (fila->quantidadePacientes == 0) {
        printf("A fila esta vazia!\n");
        return;
    }
    Node* atual = fila->inicio;
    while (atual != NULL && strcmp(atual->paciente.cpf, paciente.cpf) != 0) {
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Paciente nao encontrado!\n");
        return;
    }
    printf('\n');
    printf("Paciente encontrado!\n");
    printf('\n');
    printf("Nome: %s\n", atual->paciente.nome);
    printf("CPF: %s\n", atual->paciente.cpf);
    printf("Data de nascimento: %s\n", atual->paciente.dataNascimento);
    printf("Sexo: %s\n", atual->paciente.sexo);
    printf("Valor do plano: %.2f\n", atual->paciente.valorMensalidade);
    printf("\n");
    
}

void Menu() {
    printf("1 - Inserir paciente\n");
    printf("2 - Remover paciente\n");
    printf("3 - Imprimir pacientes\n");
    printf("4 - Buscar paciente\n");
    printf("5 - Quantidade de pacientes cadastrados\n");
    printf("6 - Sair\n");
    printf("Digite a opcao desejada: ");
}

//funções de salvar e carregar
void salvar_plano(FilaDupla *fila) {
    FILE *fp;
    
    fp = fopen("Plano_de_saude.dat", "wb"); // Abrir arquivo para escrita binária
    if (fp == NULL) {  
        printf("Erro ao abrir o arquivo para salvar.\n");  
        return;  
    } else if (fila->quantidadePacientes == 0) {
        printf("Nenhum paciente para salvar.\n");
        fclose(fp);
        return;
    } else {  
        printf("Salvando dados do plano de saude no arquivo...\n");

        Node *atual = fila->inicio;
        while (atual != NULL) {
            fwrite(&(atual->paciente), sizeof(Paciente), 1, fp);
            atual = atual->proximo;
        }

        fclose(fp);
    }         
}
    
void carregar_plano(FilaDupla *fila) {
    FILE *fp;
    
    fp = fopen("Plano_de_saude.dat", "rb"); // Abrir arquivo para leitura binária
    if (fp == NULL) {  
        printf("Erro ao abrir o arquivo para carregar.\n");  
        return;  
    } else {  
        printf("Carregando dados do plano de saude do arquivo...\n");

        Paciente paciente;
        while (fread(&paciente, sizeof(Paciente), 1, fp) == 1) {
            inserirPaciente(fila, paciente);
        }

        fclose(fp);
    }         
}

int main() { 
    FilaDupla fila;
    inicializarFilaDupla(&fila);
    carregar_plano(&fila);

    int opcao;
    do {
        Menu();
        scanf("%d", &opcao);
        switch (opcao) {
 case 1: {
    Paciente paciente;
    printf("Digite o nome do paciente: ");
    scanf("%s", paciente.nome); 

printf("Digite o CPF do paciente(sem pontuacoes): ");
    scanf("%s", paciente.cpf); 
    while (!CPF_valido(paciente.cpf)) {
        printf("CPF invalido!\n" );
        printf("Digite o CPF do paciente (sem pontuacoes): ");
        scanf("%s", paciente.cpf);
    }

    printf("Digite a data de nascimento do paciente (DD/MM/AAAA): ");
    scanf("%s", paciente.dataNascimento); 
    while (!Data_de_nascimentoo_valida(paciente.dataNascimento)) {
        printf("Data de nascimento invalida!\n" );
        printf("Digite a data de nascimento do paciente (DD/MM/AAAA): ");
        scanf("%s", paciente.dataNascimento);
    }

    printf("Digite o sexo do paciente (M/F): ");
    scanf("%s", paciente.sexo); 
    while (!Masculino_ou_Feminino(paciente.sexo)) {
        printf("Sexo invalido!\n" );
        printf("Digite o sexo do paciente (M/F): ");
        scanf("%s", paciente.sexo);
    }


    inserirPaciente(&fila, paciente);
    CalcularValorPlano(&fila, paciente);

    break;
}


        
            case 2: {
                Paciente paciente;  
                printf("Digite o CPF do paciente: ");
                scanf("%s", paciente.cpf);
                RemoverPaciente(&fila, paciente);
                break;
            }
            case 3: {
                imprimirPacientes(&fila);
                break;
            }
            
            case 4: {
                Paciente paciente;
                printf("Digite o CPF do paciente: ");
                scanf("%s", paciente.cpf);
                getchar();
                BuscarPaciente(&fila, paciente);
                break;
            }
             case 5: {
                printf("Quantidade de pacientes: %d\n", fila.quantidadePacientes);
                break;
            }
            case 6: {
          
                    salvar_plano(&fila); // Salva os dados antes de sair
                    printf("Saindo...\n");
                    break;
                }
            default: {
                printf("Opcao invalida!\n");
                break;
            }

        }
    } while (opcao != 6);
    return 0;
}
