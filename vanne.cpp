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
       etat = PANNE;
       return true;
   }

   return false;
}

int Vanne::getetat(void){
    return etat;
}

void Vanne::arreturgence(void){
    if (etat == ALARME || etat == PANNE) return;
    bkpetat = etat;
    etat = ALARME;
    cout << "Etat vanne = ALARME" << endl;
    emit signaletat(etat);
}

void Vanne::extinction(void){
    cout << "Test extinction vanne" << endl;
    if (etat != ALARME && etat != PANNE) return;
    etat = bkpetat;
    cout << "!!!!! Extinction vanne" << endl;
    emit signaletat(etat);
}


void Vanne::ouverture(void){

   if (etat != ALARME && etat != PANNE){
       if (simulpanne() == true) return;
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
