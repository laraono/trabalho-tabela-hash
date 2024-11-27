#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Contact {
    char name[50];
    char phone[20];
    struct Contact *next;
} Contact;

Contact *hashTable[TABLE_SIZE];

unsigned int hashFunction(const char *name) {
    unsigned int hash = 0;
    while (*name) {
        hash += *name++;
    }
    return hash % TABLE_SIZE;
}

int isDuplicate(const char *name) {
    unsigned int index = hashFunction(name);
    Contact *current = hashTable[index];

    while (current) {
        if (strcmp(current->name, name) == 0) {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}

Contact *createContact(const char *name, const char *phone) {
    Contact *newContact = (Contact *)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = NULL;
    return newContact;
}

void adicionarContato() {
    char name[50], phone[20];

    printf("Nome: ");
    scanf(" %[^\n]", name);
    printf("Telefone: ");
    scanf(" %[^\n]", phone);

    if (isDuplicate(name)) {
        printf("Erro: Contato com nome '%s' já existe.\n", name);
        return;
    }

    unsigned int index = hashFunction(name);
    Contact *newContact = createContact(name, phone);

    newContact->next = hashTable[index];
    hashTable[index] = newContact;

    printf("Contato adicionado com sucesso.\n");
}

void buscarContato() {
    char name[50];
    printf("Nome: ");
    scanf(" %[^\n]", name);

    unsigned int index = hashFunction(name);
    Contact *current = hashTable[index];

    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Telefone de %s: %s\n", name, current->phone);
            return;
        }
        current = current->next;
    }

    printf("Erro: Contato '%s' não encontrado.\n", name);
}

void removerContato() {
    char name[50];
    printf("Nome: ");
    scanf(" %[^\n]", name);

    unsigned int index = hashFunction(name);
    Contact *current = hashTable[index];
    Contact *previous = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                hashTable[index] = current->next;
            }
            free(current);
            printf("Contato '%s' removido com sucesso.\n", name);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Erro: Contato '%s' não encontrado.\n", name);
}

void exibirContatos() {
    int found = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Contact *current = hashTable[i];
        while (current) {
            if (!found) {
                printf("\nLista de contatos:\n");
                found = 1;
            }
            printf("  Nome: %s, Telefone: %s\n", current->name, current->phone);
            current = current->next;
        }
    }

    if (!found) {
        printf("Nenhum contato armazenado.\n");
    }
}

int main() {
    int opcao;

    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    for (int i = 0; i < TABLE_SIZE; i++) {
        Contact *current = hashTable[i];
        while (current) {
            Contact *temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
