#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct {
    char ime[MAX_NAME_LEN];
    char prezime[MAX_NAME_LEN];
    int bodovi;
} Student;

int prebroji_redke(const char* ime_datoteke) {
    FILE* f = fopen(ime_datoteke, "r");
    if (!f) {
        printf("Greška pri otvaranju datoteke.\n");
        return -1;
    }
    int lines = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f) != NULL)
        lines++;
    fclose(f);
    return lines;
}

int main() {
    const char* ime_datoteke = "studenti.txt";
    int broj_studenata = prebroji_redke(ime_datoteke);
    if (broj_studenata <= 0) {
        printf("Datoteka je prazna ili se ne može otvoriti.\n");
        return 1;
    }

    Student* students = (Student*)malloc(broj_studenata * sizeof(Student));
    if (!students) {
        printf("Greška pri alokaciji memorije.\n");
        return 1;
    }

    FILE* datoteka = fopen(ime_datoteke, "r");
    if (!datoteka) {
        printf("Greška pri otvaranju datoteke.\n");
        free(students);
        return 1;
    }

    // Učitavanje podataka
    for (int i = 0; i < broj_studenata; i++) {
        fscanf(datoteka, "%s %s %d", students[i].ime, students[i].prezime, &students[i].bodovi);
    }
    fclose(datoteka);

    // Traženje maksimalnog broja bodova
    int max_bodovi = students[0].bodovi;
    for (int i = 1; i < broj_studenata; i++) {
        if (students[i].bodovi > max_bodovi)
            max_bodovi = students[i].bodovi;
    }

    // Ispis rezultata
    printf("Ime\tPrezime\tApsolutni bodovi\tRelativni bodovi\n");
    for (int i = 0; i < broj_studenata; i++) {
        double relativni = (double)students[i].bodovi / max_bodovi * 100;
        printf("%s\t%s\t%d\t\t\t%.2f\n", students[i].ime, students[i].prezime, students[i].bodovi, relativni);
    }

    free(students);
    return 0;
}
