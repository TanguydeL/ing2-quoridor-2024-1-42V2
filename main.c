#include "biblio.h"


int main() {
    ReseauTrophique *monReseau = initReseau();
    char filename[256];

    printf("Entrez le nom du fichier du réseau trophique : ");
    scanf("%255s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n') continue;
        char type;
        char nom[100];
        int niveau, from, to;
        float poids;

        if (sscanf(line, "%c, %99[^,], %d", &type, nom, &niveau) == 3 && type == 'S') {
            ajouterSommet(monReseau, nom, niveau);
        } else if (sscanf(line, "%c, %d, %d, %f", &type, &from, &to, &poids) == 4 && type == 'A') {
            ajouterArc(monReseau, from, to, poids);
        }
    }

    fclose(file);
    afficherReseau(monReseau);
    ecrireCSV(monReseau);


    for (int i = 0; i < monReseau->nbSommets; i++) {
        free(monReseau->sommets[i].nom);
    }
    free(monReseau->sommets);
    free(monReseau->arcs);
    free(monReseau);

    return 0;
}

