#ifndef cabecalho_h
#define cabecalho_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[40];
    double valorMensalidade;
    char dataNascimento[11];
    char sexo[2];
    char estadoCivil[20];
    char cpf[12];
    int idade[3];
} Paciente; 

typedef struct Node {
    Paciente paciente;
    struct Node* proximo;
    struct Node* anterior;
} Node;

typedef struct {
    int quantidadePacientes;
    Node* inicio;
    Node* fim;
} FilaDupla; 

typedef struct {
    int quantidadePacientes;
    Paciente *pacientes;
} Plano;

void RealizarCadastro(Plano *plano);
void RealizarExclusao(Plano *plano);
void RealizarListagem(Plano *plano);
void criar_arq(Plano *plano);


#endif
