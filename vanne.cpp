#include "vanne.h"


Vanne::Vanne(QObject *parent) :
    QObject(parent)
{
    etat = FERME;
    alarme = false;
    qsrand(0);

}

bool Vanne::simulpanne(void){
   if (qrand() % PANNE_FREQMOYENNE == 0){
       etat = ARRETE;
       alarme = true;
       return true;
   }

   return false;
}

void Vanne::extinction(void){
    alarme = false;
    etat = FERME;
    emit envoiEtat(etat, alarme);
}


void Vanne::ouverture(void){
   if (alarme == false && simulpanne() == false){
       etat = OUVERTE;
   }

   emit envoiEtat(etat, alarme);
}

void Vanne::fermature(void){
   if (alarme == false && simulpanne() == false){
       etat = FERME;
   }

   emit envoiEtat(etat, alarme);
}
