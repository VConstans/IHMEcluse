#ifndef ETATS_H
#define ETATS_H

#define PANNE_FREQMOYENNE 30

#define FREQ_UPDATE 200
#define TIME_TRANS 10000
#define MAX_OUVERTURE (TIME_TRANS/FREQ_UPDATE)

#define MAX_NIVEAU 200
#define MIN_NIVEAU 0
#define MID_NIVEAU 100
#define DEBIT_EAU 2

enum etat_values {OUVERTE, FERME, OUVERTURE, FERMETURE, ARRETE, ALARME};
enum error_valuer { EPORTE, EVANNE, EEAU };
enum couleur_signaux {ROUGE, VERT };

#endif // ETATS_H
