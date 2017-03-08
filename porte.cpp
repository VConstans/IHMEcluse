#include "porte.h"

Porte::Porte(QObject *parent) :
    QObject(parent)
{
    etat = FERME;
    bkpetat = etat;
    position = MAX_FERMETURE;
    timer_transition = new QTimer(this);
    connect(timer_transition,SIGNAL(timeout()),
            this,SLOT(updateposition()));
}

int Porte::getetat(void){
    return etat;
}

void Porte::ouverture(void){
    if (etat == ALARME ) return;

    etat = OUVERTURE;
    timer_transition->start(FREQ_UPDATE);
    cout << "Porte: ouverture" << endl;

}

void Porte::fermeture(void){
    if (etat == ALARME ) return;

    etat = FERMETURE;
    timer_transition->start(FREQ_UPDATE);
    cout << "Porte: fermeture"<< endl;
}

void Porte::extinction(void){
    if (etat != ALARME && etat != PANNE) return;
    etat = bkpetat;
    cout << "Extinction porte" << endl;
}

void Porte::arret(void){
    if (etat != FERMETURE &&
        etat != OUVERTURE ) return;

    timer_transition->stop();
    etat = ARRETE;

    emit signaletat(position, etat);
}

void Porte::arreturgence(void){
    if (etat == ALARME || etat == PANNE) return;
    bkpetat = etat;
    etat = ALARME;
    cout << "Porte = ALARME" << endl;
}

bool Porte::simulpanne(void){
   if (freqPannes >  (qrand() % 100)){
       bkpetat = etat;
       etat = PANNE;
       emit signaletat(position, etat);
       return true;
   }

   return false;
}

void Porte::updateposition(void){

    switch(etat){
        case OUVERTURE:
    if (simulpanne() == true) return;
            if (position <= 0){
                etat = OUVERTE;
                timer_transition->stop();
            } else position--;
         break;
        case FERMETURE:
    if (simulpanne() == true) return;
            if (position >= MAX_FERMETURE){
                etat = FERME;
                timer_transition->stop();
            } else position++;
         break;
        default: return;
     }


     emit signaletat(position, etat);
}
