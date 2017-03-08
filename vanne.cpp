#include "vanne.h"


Vanne::Vanne(QObject *parent) :
    QObject(parent)
{
    etat = FERME;
    bkpetat = etat;
    qsrand(QTime::currentTime().msec());

}


//Simulation des pannes d'une vanne

bool Vanne::simulpanne(void)
{
   if (freqPannes >  (qrand() % 100))
   {
       bkpetat = etat;
       etat = PANNE;
       return true;
   }

   return false;
}

int Vanne::getetat(void)
{
    return etat;
}


//Mise en état d'urgence de la vanne

void Vanne::arreturgence(void)
{
    if (etat == ALARME || etat == PANNE) return;
    bkpetat = etat;
    etat = ALARME;
    emit signaletat(etat);
}


//Arrêt de l'alarme

void Vanne::extinction(void)
{
    if (etat != ALARME && etat != PANNE) return;
    etat = bkpetat;
    emit signaletat(etat);
}


//Ouverture de la vanne

void Vanne::ouverture(void)
{

   if (etat != ALARME && etat != PANNE)
   {
       if (simulpanne() == true) return;
       etat = OUVERTE;
   }

   emit signaletat(etat);
}



//Fermeture de la vanne

void Vanne::fermeture(void)
{
   if (etat != ALARME && simulpanne() == false)
   {
       etat = FERME;
   }

   emit signaletat(etat);
}
