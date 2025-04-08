/**
 * @file TGA_KLAUS_BECKER.cpp
 * @brief Atividade prática de tabela hash com colisões
 *
 * Universidade do Vale do Rio dos Sinos - UNISINOS  
 * Escola Politécnica  
 * Curso: Engenharia da Computação  
 * Disciplina: Estruturas Avançadas de Dados  
 * Professor: Diógines D'Avilla  
 *
 * Aluno: Klaus Becker  
 * Data: Abril de 2025
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

const int TABLE_SIZE = 8;

typedef struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
} Aluno;

typedef struct hashNode
{
    Aluno data;
    struct hashNode *next;
} HashNode;

typedef struct hash
{
    int qtd;
    HashNode **itens;
} Hash;

Hash *g_hash = NULL;

Hash *createHash()
{
    Hash* ha = (Hash *) malloc(sizeof(Hash));
    if (ha != NULL) {
        ha->itens = (HashNode **) malloc(TABLE_SIZE * sizeof(HashNode *));

        if (ha->itens == NULL)
        {
            free(ha);
            return NULL;
        }

        ha->qtd = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            ha->itens[i] = NULL;
        }
    }

    return ha;
}

void deleteHash(Hash *ha)
{
    if (ha == NULL) return;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *current = ha->itens[i];
        while (current != NULL)
        {
            HashNode *temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(ha->itens);
    free(ha);
}

int divisionMethod(int chave)
{
    return chave % TABLE_SIZE;
}

// Insere um aluno
int insert_SeparateChaining(Hash *ha, Aluno al)
{
    if (ha == NULL) return 0;

    int pos = divisionMethod(al.matricula);

    // Cria um novo nodo para o aluno
    HashNode *newNode = (HashNode *) malloc(sizeof(HashNode));
    if (newNode == NULL) return 0;

    newNode->data = al;
    newNode->next = ha->itens[pos];  // Insere no início da lista encadeada
    ha->itens[pos] = newNode;
    ha->qtd++;

    return 1;
}

// Função para procurar por um aluno a partir de sua matrícula
int search_SeparateChaining(Hash *ha, int mat, Aluno *al)
{
    if (ha == NULL) return 0;

    int pos = divisionMethod(mat);
    HashNode *current = ha->itens[pos];

    // Percorre a lista encadeada do índice específico
    while (current != NULL)
    {
        if (current->data.matricula == mat)
        {
            *al = current->data;
            return 1;
        }
        current = current->next;
    }

    return 0;
}

// Imprime nossa HashTable
void printHash(Hash *ha)
{
    if (ha == NULL) return;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("[%d]: ", i);
        HashNode *current = ha->itens[i];
        while (current != NULL)
        {
            printf("-> [%02d, %-7s] ", current->data.matricula, current->data.nome);
            current = current->next;
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * @brief Create and populate a hash table from an array of Aluno
 * 
 * This function creates a hash table and populates it with the given array of Aluno.
 * It initializes the hash table and inserts each Aluno into it using the
 * insert_SeparateChaining function.
 * 
 * @param al   Array of Aluno
 * @param qtd  Number of elements in the array
 * @return     Pointer to the created hash table, or NULL on failure
 */
Hash* createHashFull(Aluno al[], int qtd)
{
    Hash *ha = createHash();
    
    if (ha == NULL || al == NULL) {
        return NULL;
    }

    for (int i = 0; i < qtd; i++) {
        insert_SeparateChaining(ha, al[i]);
    }

    return ha;
}


/**
 * @brief Insert multiple alunos into an existing hash table
 * 
 * This function inserts the given array of Aluno into the global hash table
 * 'g_hash'. It iterates through the array and calls the insert function
 * for each Aluno.
 * 
 * @param al   Array of Aluno
 * @param qtd  Number of elements in the array
 * @return     0 if successful, -1 on error
 */
int insertMultiple_SeparateChaining(Aluno al[], int qtd)
{
    if (g_hash == NULL || al == NULL) {
        return -1;
    }

    for (int i = 0; i < qtd; i++) {
        insert_SeparateChaining(g_hash, al[i]);
    }

    return 0;
}

int main() 
{
    Aluno turma1[] = {
        {8,  "Ana",      7.0, 8.0, 9.0},
        {16, "Bruno",    6.0, 7.5, 8.5},
        {24, "Carlos",   5.0, 6.0, 7.0},
        {1,  "Daniela",  9.0, 8.0, 7.5},
        {9,  "Eduardo",  6.5, 7.0, 6.5},
        {17, "Clovis",   8.5, 9.0, 9.5},
        {25, "Gustavo",  5.5, 6.5, 7.5},
        {2,  "Helena",   8.0, 8.5, 9.0},
        {10, "Igor",     7.0, 7.5, 8.0},
        {18, "Joana",    6.0, 6.0, 6.5},
        {26, "Kleber",   7.5, 8.0, 8.0},
        {3,  "Laura",    9.0, 9.5, 9.0},
        {11, "Marcos",   6.0, 7.0, 7.0},
        {19, "Nina",     8.5, 8.5, 8.0},
        {27, "Otavio",   5.0, 6.0, 6.5},
        {4,  "Paula",    7.0, 7.5, 8.0},
        {12, "Klaus",    6.5, 6.5, 6.0},
        {20, "Rafaela",  7.5, 7.0, 7.0},
        {28, "Samuel",   9.0, 8.5, 8.5},
        {5,  "Tatiane",  8.0, 7.5, 7.0},
        {13, "Ulisses",  7.0, 7.5, 8.0},
        {21, "Vanessa",  5.5, 6.0, 6.0},
        {29, "Wagner",   6.5, 7.0, 7.5},
        {6,  "Xuxa",     8.5, 8.0, 8.0},
        {14, "Yasmin",   6.0, 6.5, 6.5},
        {22, "Zeca",     7.5, 8.0, 8.0},
        {30, "Alana",    5.5, 5.0, 6.0},
        {7,  "Brenda",   7.0, 7.5, 7.5},
        {15, "Caio",     6.0, 6.0, 6.0},
        {23, "Debora",   8.0, 8.0, 8.5}
    };
    int qtd1 = sizeof(turma1) / sizeof(turma1[0]);

    Aluno turma2[] = {
        {31, "Elias",    7.0, 7.5, 7.5},
        {39, "Fabiana",  6.5, 6.0, 6.5},
        {47, "Giovana",  8.0, 7.5, 7.0},
        {55, "Laiza",    5.0, 5.5, 6.0},
        {63, "Isis",     6.5, 7.0, 7.5},
        {71, "Jonas",    8.5, 8.0, 8.0},
        {32, "Karen",    7.5, 7.5, 7.5},
        {40, "Lucas",    6.0, 6.5, 7.0},
        {48, "Marta",    9.0, 8.5, 8.0},
        {56, "Nando",    7.0, 7.0, 7.5},
        {64, "Olga",     5.5, 5.5, 6.0},
        {72, "Pedro",    8.0, 8.5, 9.0},
        {33, "Quesia",   6.0, 6.5, 6.5},
        {41, "Rogerio",  7.5, 7.0, 7.0},
        {49, "Sabrina",  6.0, 6.0, 6.0},
        {57, "Tiago",    8.5, 9.0, 9.0},
        {65, "Ursula",   7.0, 7.5, 8.0},
        {73, "Vitor",    6.5, 7.0, 7.0},
        {34, "Wesley",   7.5, 7.5, 8.0},
        {42, "Ximena",   6.0, 6.5, 6.5},
        {50, "Yuri",     8.0, 8.5, 8.5},
        {58, "Zuleika",  5.0, 5.5, 6.0},
        {66, "Alan",     7.5, 7.0, 7.5},
        {74, "Beatriz",  6.5, 7.0, 7.5},
        {35, "Cesar",    8.0, 8.0, 8.0},
        {43, "Diana",    6.0, 6.0, 6.5},
        {51, "Eduarda",  7.5, 7.5, 7.0},
        {59, "Felipe",   6.5, 6.5, 6.0},
        {67, "Georgia",  8.5, 8.0, 8.5},
        {75, "Hugo",     7.0, 7.0, 7.5}
    };
    int qtd2 = sizeof(turma2) / sizeof(turma2[0]);

    g_hash = createHashFull(turma1, qtd1);
    if (g_hash == NULL) {
        printf("Erro ao criar hash com Turma 1\n");
        return -1;
    }

    printf(">>> HashTable global após criação completa da Turma 1:\n");
    printHash(g_hash);

    insertMultiple_SeparateChaining(turma2, qtd2);
    printf(">>> HashTable global após inserção multipla da Turma 2:\n");
    printHash(g_hash);

    deleteHash(g_hash);

    return 0;
}
