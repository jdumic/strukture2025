#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ime[50];
    char prezime[50];
    int godiste;
} Osoba;

typedef struct Node {
    Osoba osoba;
    struct Node* next;
} Node;

Osoba unosOsobe() {
    Osoba o;
    printf("Unesi ime: ");
    scanf("%s", o.ime);
    printf("Unesi prezime: ");
    scanf("%s", o.prezime);
    printf("Unesi godinu rodenja: ");
    scanf("%d", &o.godiste);
    return o;
}

Node* dodajNaPocetak(Node* head, Osoba novaOsoba) {
    Node* novi = (Node*)malloc(sizeof(Node));
    novi->osoba = novaOsoba;
    novi->next = head;
    return novi;
}

Node* dodajNaKraj(Node* head, Osoba novaOsoba) {
    Node* novi = (Node*)malloc(sizeof(Node));
    novi->osoba = novaOsoba;
    novi->next = NULL;
    if (!head) return novi;
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = novi;
    return head;
}

void ispisiListu(Node* head) {
    Node* temp = head;
    if (!temp) {
        printf("Lista je prazna.\n");
        return;
    }
    while (temp) {
        printf("%s %s, %d\n", temp->osoba.ime, temp->osoba.prezime, temp->osoba.godiste);
        temp = temp->next;
    }
}

Node* pronadjiPoPrezimenu(Node* head, const char* prezime) {
    Node* temp = head;
    while (temp) {
        if (strcmp(temp->osoba.prezime, prezime) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

Node* brisiIzListe(Node* head, const char* prezime) {
    Node* temp = head, * prev = NULL;
    while (temp) {
        if (strcmp(temp->osoba.prezime, prezime) == 0) {
            if (prev == NULL) {
                Node* noviHead = temp->next;
                free(temp);
                return noviHead;
            }
            else {
                prev->next = temp->next;
                free(temp);
                return head;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Osoba s prezimenom %s nije pronađena.\n", prezime);
    return head;
}

int main() {
    Node* lista = NULL;
    int izbor;
    char prezimePretraga[50];

    do {
        printf("\n1. Dodaj na pocetak\n2. Dodaj na kraj\n3. Ispisi listu\n4. Pretrazi po prezimenu\n5. Brisi po prezimenu\n0. Izlaz\nIzbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            lista = dodajNaPocetak(lista, unosOsobe());
            break;
        case 2:
            lista = dodajNaKraj(lista, unosOsobe());
            break;
        case 3:
            ispisiListu(lista);
            break;
        case 4:
            printf("Unesi prezime za pretragu: ");
            scanf("%s", prezimePretraga);
            Node* nadjena = pronadjiPoPrezimenu(lista, prezimePretraga);
            if (nadjena) {
                printf("Nađena osoba: %s %s, %d\n", nadjena->osoba.ime, nadjena->osoba.prezime, nadjena->osoba.godiste);
            }
            else {
                printf("Osoba nije pronađena.\n");
            }
            break;
        case 5:
            printf("Unesi prezime za brisanje: ");
            scanf("%s", prezimePretraga);
            lista = brisiIzListe(lista, prezimePretraga);
            break;
        case 0:
            // Oslobodi memoriju
            while (lista) {
                Node* temp = lista;
                lista = lista->next;
                free(temp);
            }
            printf("Izlaz.\n");
            break;
        default:
            printf("Neispravan izbor.\n");
        }
    } while (izbor != 0);

    return 0;
}
