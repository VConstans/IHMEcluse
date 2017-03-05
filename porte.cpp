#include "porte.h"

Porte::Porte(QObject *parent) :
    QObject(parent)
{
    etat = FERME;
    position = 0;
    alarme = false;
    timer_transition = new QTimer(this);
    connect(timer_transition,SIGNAL(timeout()),
            this,SLOT(updateposition()));
}

void Porte::ouverture(void){
    if (etat == OUVERTE ||
        alarme == true ) return;

    etat = OUVERTURE;
    timer_transition->start(FREQ_UPDATE);

}

void Porte::fermature(void){
    if (etat == FERME ||
        alarme == true ) return;

    etat = FERMATURE;
    timer_transition->start(FREQ_UPDATE);
}

void Porte::extinction(void){
    alarme = false;
    emit signalalarme(alarme);
}

void Porte::arret(void){
    timer_transition->stop();
    etat = ARRETE;

    emit signaletat(position, etat);
}

void Porte::arreturgence(void){
    arret();
    alarme = true;
    emit signalalarme(alarme);

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
