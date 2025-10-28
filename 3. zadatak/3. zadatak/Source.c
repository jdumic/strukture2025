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

Osoba unosOsobe();
Node* dodajNaPocetak(Node* head, Osoba novaOsoba);
Node* dodajNaKraj(Node* head, Osoba novaOsoba);
void ispisiListu(Node* head);
Node* pronadjiPoPrezimenu(Node* head, const char* prezime);
Node* brisiIzListe(Node* head, const char* prezime);
Node* dodajIza(Node* head, const char* prezime, Osoba novaOsoba);
Node* dodajIspred(Node* head, const char* prezime, Osoba novaOsoba);
void sortirajPoPrezimenu(Node** head);
void upisiUDatoteku(Node* head, const char* filename);
Node* citajIzDatoteke(const char* filename);

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
    if (!novi) {
        printf("greska\n");
        return head;
    }
    novi->osoba = novaOsoba;
    novi->next = head;
    return novi;
}


Node* dodajNaKraj(Node* head, Osoba novaOsoba) {
    Node* novi = (Node*)malloc(sizeof(Node));
    if (!novi) {
        printf("greska\n");
        return head;
    }
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

Node* dodajIza(Node* head, const char* prezime, Osoba novaOsoba) {
    Node* temp = head;
    while (temp) {
        if (strcmp(temp->osoba.prezime, prezime) == 0) {
            Node* novi = (Node*)malloc(sizeof(Node));
            if (!novi) {
                printf("greska\n");
                return head;
            }
            novi->osoba = novaOsoba;
            novi->next = temp->next;
            temp->next = novi;
            return head;
        }
        temp = temp->next;
    }
    printf("Osoba za dodavanje iza nije pronađena.\n");
    return head;
}

Node* dodajIspred(Node* head, const char* prezime, Osoba novaOsoba) {
    Node* temp = head, * prev = NULL;
    while (temp) {
        if (strcmp(temp->osoba.prezime, prezime) == 0) {
            Node* novi = (Node*)malloc(sizeof(Node));
            if (!novi) {
                printf("greska\n");
                return head;
            }
            novi->osoba = novaOsoba;
            novi->next = temp;
            if (prev == NULL)
                return novi; 
            prev->next = novi;
            return head;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Osoba za dodavanje ispred nije pronađena.\n");
    return head;
}


void sortirajPoPrezimenu(Node** head) {
    if (!(*head) || !(*head)->next) return;
    Node* i, * j;
    for (i = *head; i->next; i = i->next) {
        for (j = i->next; j; j = j->next) {
            if (strcmp(i->osoba.prezime, j->osoba.prezime) > 0) {
                Osoba temp = i->osoba;
                i->osoba = j->osoba;
                j->osoba = temp;
            }
        }
    }
}


void upisiUDatoteku(Node* head, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) { printf("Greska pri otvaranju datoteke.\n"); return; }
    Node* temp = head;
    while (temp) {
        fprintf(f, "%s %s %d\n", temp->osoba.ime, temp->osoba.prezime, temp->osoba.godiste);
        temp = temp->next;
    }
    fclose(f);
    printf("Lista je upisana u datoteku.\n");
}


Node* citajIzDatoteke(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) { printf("Greska pri otvaranju datoteke.\n"); return NULL; }
    Node* head = NULL, * last = NULL;
    Osoba o;
    while (fscanf(f, "%s %s %d", o.ime, o.prezime, &o.godiste) == 3) {
        Node* novi = (Node*)malloc(sizeof(Node));
        if (!novi) continue;
        novi->osoba = o;
        novi->next = NULL;
        if (!head) head = novi;
        else last->next = novi;
        last = novi;
    }
    fclose(f);
    printf("Lista je učitana iz datoteke.\n");
    return head;
}

int main() {
    Node* lista = NULL;
    int izbor;
    char prezimePretraga[50];

    do {
        printf("\n1. Dodaj na pocetak\n2. Dodaj na kraj\n3. Ispisi listu\n4. Pretrazi po prezimenu\n5. Brisi po prezimenu");
        printf("\n6. Dodaj iza\n7. Dodaj ispred\n8. Sortiraj po prezimenu\n9. Upisi u datoteku\n10. Citaj iz datoteke\n0. Izlaz\nIzbor: ");
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
        case 6:
            printf("Unesi prezime osobe iza koje dodajes: ");
            scanf("%s", prezimePretraga);
            lista = dodajIza(lista, prezimePretraga, unosOsobe());
            break;
        case 7:
            printf("Unesi prezime osobe ispred koje dodajes: ");
            scanf("%s", prezimePretraga);
            lista = dodajIspred(lista, prezimePretraga, unosOsobe());
            break;
        case 8:
            sortirajPoPrezimenu(&lista);
            printf("Lista sortirana po prezimenima.\n");
            break;
        case 9:
            upisiUDatoteku(lista, "lista.txt");
            break;
        case 10:
            lista = citajIzDatoteke("lista.txt");
            break;
        case 0:
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
