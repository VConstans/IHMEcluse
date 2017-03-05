#include "vanne.h"


Vanne::Vanne(QObject *parent) :
    QObject(parent)
{
    etat = FERME;
    qsrand(0);

}

bool Vanne::simulpanne(void){
   if (qrand() % PANNE_FREQMOYENNE == 0){
       etat = ALARME;
       return true;
   }

   return false;
}

int Vanne::getetat(void){
    return etat;
}

void Vanne::extinction(void){
    etat = FERME;
    emit signaletat(etat);
}


void Vanne::ouverture(void){
   if (etat != ALARME && simulpanne() == false){
       etat = OUVERTE;
   }

   emit signaletat(etat);
}

void Vanne::fermature(void){
   if (etat != ALARME && simulpanne() == false){
       etat = FERME;
   }

   emit signaletat(etat);
}
