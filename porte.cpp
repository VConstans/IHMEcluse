#include "porte.h"

Porte::Porte(QObject *parent) :
    QObject(parent)
{
    etat = FERME;
    position = 0;
    timer_transition = new QTimer(this);
    connect(timer_transition,SIGNAL(timeout()),
            this,SLOT(updateposition()));
}

void Porte::ouverture(void){
    if (etat == OUVERTE ||
        etat == ALARME ) return;

    etat = OUVERTURE;
    timer_transition->start(FREQ_UPDATE);

}

void Porte::fermature(void){
    if (etat == FERME ||
        etat == ALARME ) return;

    etat = FERMATURE;
    timer_transition->start(FREQ_UPDATE);
}

void Porte::extinction(void){
    if (etat != ALARME) return;
    etat = ARRETE;
    emit signaletat(position,etat);
}

void Porte::arret(void){
    timer_transition->stop();
    etat = ARRETE;

    emit signaletat(position, etat);
}

void Porte::arreturgence(void){
    timer_transition->stop();
    etat = ALARME;

    emit signaletat(position, etat);
}

bool Porte::simulpanne(void){
   if (qrand() % PANNE_FREQMOYENNE == 0){
       arreturgence();
       return true;
   }

   return false;
}

void Porte::updateposition(void){
    if (simulpanne() == true) return;

    switch(etat){
        case OUVERTURE: position++;
         break;
        case FERMATURE: position--;
         break;
        default: return;
     }

     if (position <= 0){
         etat = FERME;
         timer_transition->stop();
     } else if (position >= MAX_OUVERTURE){
         etat = OUVERTE;
         timer_transition->stop();
     }

     emit signaletat(position, etat);
}
