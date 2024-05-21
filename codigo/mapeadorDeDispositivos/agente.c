#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Definindo a estrutura para um Agente
typedef struct Agent {
    char name[50];
    int age;
    int id;
    struct Agent* next;  // Ponteiro para o próximo agente na lista
} Agent;
Agent A1, A2, A3;
Agent MAS[3];

void main(){
}