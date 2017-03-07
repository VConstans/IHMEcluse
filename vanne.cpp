#include "vanne.h"


Vanne::Vanne(QObject *parent) :
    QObject(parent)
{
    etat = FERME;
    bkpetat = etat;
    qsrand(0);

}

bool Vanne::simulpanne(void){
   if (freqPannes >  (qrand() % 100)){
       bkpetat = etat;
       etat = ALARME;
       return true;
   }

   return false;
}

int Vanne::getetat(void){
    return etat;
}

void Vanne::arreturgence(void){
    bkpetat = etat;
    etat = ALARME;
}

void Vanne::extinction(void){
    etat = bkpetat;
    emit signaletat(etat);
}


void Vanne::ouverture(void){
   if (etat != ALARME && simulpanne() == false){
       etat = OUVERTE;
   }

   emit signaletat(etat);
}

void Vanne::fermeture(void){
   if (etat != ALARME && simulpanne() == false){
       etat = FERME;
   }

   emit signaletat(etat);
}
