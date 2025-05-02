
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NB_BUS_X 5
#define NB_BUS_Y 4
#define ALLER_RETOUR 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int sens_XY = 0; // nombre de bus dans le sens X -> Y
int sens_YX = 0; // nombre de bus dans le sens Y -> X

// Fonction pour pause aléatoire entre 1 et 1.5 secondes
void pause_aleatoire() {
    usleep((rand() % 501 + 1000) * 1000); // entre 1000 ms et 1500 ms
}

// Affichage du trajet
void afficher_trajet(const char* id, const char* ville, const char* depart, const char* arrivee, int trajet) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    printf("[%02d:%02d:%02d] Bus %s de %s : %s -> %s (Trajet %d)\n",
           t->tm_hour, t->tm_min, t->tm_sec, id, ville, depart, arrivee, trajet);
    fflush(stdout);
}

// Entrée dans le tunnel
void entrer_tunnel(const char* direction) {
    int ok = 0;
    while (!ok) {
        pthread_mutex_lock(&mutex);
        if (direction[0] == 'X') {
            if (sens_YX == 0) {
                sens_XY++;
                ok = 1;
            }
        } else {
            if (sens_XY == 0) {
                sens_YX++;
                ok = 1;
            }
        }
        pthread_mutex_unlock(&mutex);
        if (!ok) usleep(100000); // Attente 0.1s avant de réessayer
    }
}

// Sortie du tunnel
void sortir_tunnel(const char* direction) {
    pthread_mutex_lock(&mutex);
    if (direction[0] == 'X') {
        sens_XY--;
    } else {
        sens_YX--;
    }
    pthread_mutex_unlock(&mutex);
}

// Structure pour passer les données au thread
typedef struct {
    char id[10];
    char ville[20];
    char direction_initiale[3];
} Bus;

void* routine_bus(void* arg) {
    Bus* bus = (Bus*)arg;
    for (int i = 1; i <= ALLER_RETOUR; i++) {
        if (bus->direction_initiale[0] == 'X') {
            entrer_tunnel("XY");
            afficher_trajet(bus->id, bus->ville, "X", "Y", i);
            pause_aleatoire();
            sortir_tunnel("XY");

            entrer_tunnel("YX");
            afficher_trajet(bus->id, bus->ville, "Y", "X", i);
            pause_aleatoire();
            sortir_tunnel("YX");
        } else {
            entrer_tunnel("YX");
            afficher_trajet(bus->id, bus->ville, "Y", "X", i);
            pause_aleatoire();
            sortir_tunnel("YX");

            entrer_tunnel("XY");
            afficher_trajet(bus->id, bus->ville, "X", "Y", i);
            pause_aleatoire();
            sortir_tunnel("XY");
        }
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    pthread_t threads[NB_BUS_X + NB_BUS_Y];
    Bus bus_data[NB_BUS_X + NB_BUS_Y];

    // Création des bus de la ville X
    for (int i = 0; i < NB_BUS_X; i++) {
        snprintf(bus_data[i].id, sizeof(bus_data[i].id), "X%d", i + 1);
        snprintf(bus_data[i].ville, sizeof(bus_data[i].ville), "Ville X");
        snprintf(bus_data[i].direction_initiale, sizeof(bus_data[i].direction_initiale), "XY");
        pthread_create(&threads[i], NULL, routine_bus, &bus_data[i]);
    }

    // Création des bus de la ville Y
    for (int i = 0; i < NB_BUS_Y; i++) {
        snprintf(bus_data[NB_BUS_X + i].id, sizeof(bus_data[NB_BUS_X + i].id), "Y%d", i + 1);
        snprintf(bus_data[NB_BUS_X + i].ville, sizeof(bus_data[NB_BUS_X + i].ville), "Ville Y");
        snprintf(bus_data[NB_BUS_X + i].direction_initiale, sizeof(bus_data[NB_BUS_X + i].direction_initiale), "YX");
        pthread_create(&threads[NB_BUS_X + i], NULL, routine_bus, &bus_data[NB_BUS_X + i]);
    }

    // Attente de fin des threads
    for (int i = 0; i < NB_BUS_X + NB_BUS_Y; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
