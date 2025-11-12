#include <stdio.h>
#include <stdlib.h> // Para malloc, free, system("cls"/"clear")
#include <string.h> // Para strcpy

// --- 1. A Estrutura (Struct) da Sala ---
// (Como pedido: nome e dois ponteiros)
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda; // Ponteiro para o cômodo da esquerda
    struct Sala* direita;  // Ponteiro para o cômodo da direita
} Sala;

// --- Protótipos das Funções ---
// (Avisando ao C que essas funções existem)

Sala* criarSala(const char* nome);
void explorarSalas(Sala* salaInicial);
void liberarMemoria(Sala* sala);

// --- Função Principal ---
int main() {
    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    
    // 1. Criar a Árvore (O Mapa da Mansão)
    // A árvore é criada "manualmente" no código, como pedido.
    
    // Raiz da árvore
    Sala* hall = criarSala("Hall de Entrada");
    
    // Caminho da Esquerda
    hall->esquerda = criarSala("Biblioteca");
    hall->esquerda->esquerda = criarSala("Sala de Estar");
    hall->esquerda->direita = criarSala("Sala de Jantar");
    hall->esquerda->esquerda->esquerda = criarSala("Escritorio Secreto"); // Fim de linha (folha)

    // Caminho da Direita
    hall->direita = criarSala("Cozinha");
    hall->direita->esquerda = criarSala("Despensa"); // Fim de linha (folha)
    hall->direita->direita = criarSala("Jardim de Inverno");
    hall->direita->direita->esquerda = criarSala("Laboratorio"); // Fim de linha (folha)

    
    printf("======================================\n");
    printf("      BEM-VINDO AO DETECTIVE QUEST\n");
    printf("======================================\n");
    printf("Mapa da mansao criado. Voce esta no Hall de Entrada.\n");
    
    printf("\nPressione Enter para continuar...");
    // *** CORREÇÃO AQUI ***
    // Removemos o primeiro loop 'while' desnecessário.
    // Agora este loop aguarda o PRIMEIRO Enter do usuário.
    while (getchar() != '\n' && getchar() != EOF); 

    // 2. Iniciar a Exploração
    // A exploração começa no 'hall' (a raiz da árvore)
    explorarSalas(hall);

    // 3. Limpar a memória (boa prática)
    printf("\n...A investigacao terminou. Saindo da mansao.\n");
    liberarMemoria(hall);

    return 0;
}

// --- Implementação das Funções ---

/**
 * @brief Aloca dinamicamente (cria) uma nova sala (nó).
 * (Função pedida no README)
 */
Sala* criarSala(const char* nome) {
    // 1. Aloca memória do tamanho da nossa struct
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    // 2. Copia o nome para a struct
    strcpy(novaSala->nome, nome);
    
    // 3. Define os caminhos como nulos (sem saída) por padrão
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    // 4. Retorna o ponteiro da sala criada
    return novaSala;
}

/**
 * @brief Inicia o loop de navegação interativa pela mansão.
 * (Função pedida no README)
 */
void explorarSalas(Sala* salaInicial) {
    Sala* salaAtual = salaInicial; // Onde o jogador está agora
    char opcao;

    while (1) { // Loop infinito (vamos sair com 's' ou 'break')
        
        // Limpa a tela
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("======================================\n");
        printf(" Voce esta em: %s\n", salaAtual->nome);
        printf("======================================\n\n");

        // 1. Verifica se é um nó folha (fim de linha)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Este comodo nao tem mais saidas. Fim da exploracao neste caminho.\n");
            break; // Sai do loop 'while'
        }

        // 2. Mostra as opções de navegação válidas
        printf("Para onde deseja ir?\n");
        if (salaAtual->esquerda != NULL) {
            printf("(e) = ir para a Esquerda (%s)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("(d) = ir para a Direita (%s)\n", salaAtual->direita->nome);
        }
        printf("(s) = Sair da mansao\n");
        printf("\nOpcao: ");

        // 3. Lê a escolha do jogador
        scanf(" %c", &opcao);
        while (getchar() != '\n'); // Limpa o buffer

        // 4. Processa a escolha
        switch (opcao) {
            case 'e':
            case 'E':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda; // Move o jogador para a esquerda
                } else {
                    printf("\nNao ha caminho para a esquerda. Tente novamente.\n");
                }
                break;
            
            case 'd':
            case 'D':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita; // Move o jogador para a direita
                } else {
                    printf("\nNao ha caminho para a direita. Tente novamente.\n");
                }
                break;
                
            case 's':
            case 'S':
                printf("\nVoce decide parar a investigacao por agora.\n");
                return; // Sai da função explorarSalas
                
            default:
                printf("\nOpcao invalida! Pressione 'e', 'd' ou 's'.\n");
        }
        
        // Pequena pausa para o jogador ler o resultado antes da tela limpar
        if (opcao != 'e' && opcao != 'E' && opcao != 'd' && opcao != 'D') {
             printf("\nPressione Enter para continuar...");
             while (getchar() != '\n');
        }
    }
}

/**
 * @brief Libera toda a memória alocada para a árvore (recursivamente).
 */
void liberarMemoria(Sala* sala) {
    // Se a sala não existe, não faz nada
    if (sala == NULL) {
        return;
    }
    // Libera primeiro os filhos (recursão)
    liberarMemoria(sala->esquerda);
    liberarMemoria(sala->direita);
    
    // Libera o nó atual
    // printf("Liberando: %s\n", sala->nome); // (Linha para debug)
    free(sala);
}