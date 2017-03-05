#include "porte.h"

Porte::Porte(QObject *parent) :
    QObject(parent)
{
    etat = FERME;
    position = MAX_FERMETURE;
    timer_transition = new QTimer(this);
    connect(timer_transition,SIGNAL(timeout()),
            this,SLOT(updateposition()));
}

int Porte::getetat(void){
    return etat;
}

void Porte::ouverture(void){
    if (etat == OUVERTE ||
        etat == ALARME ) return;

    etat = OUVERTURE;
    timer_transition->start(FREQ_UPDATE);
    cout << "Porte: ouverture" << endl;

}

void Porte::fermeture(void){
    if (etat == FERME ||
        etat == ALARME ) return;

    etat = FERMETURE;
    timer_transition->start(FREQ_UPDATE);
    cout << "Porte: fermeture"<< endl;
}

void Porte::extinction(void){
    if (etat != ALARME) return;
    etat = ARRETE;
    emit signaletat(position,etat);
    cout << "Porte: extintion"<< endl;
}

void Porte::arret(void){
    if (etat != FERMETURE ||
        etat != OUVERTURE ) return;

    timer_transition->stop();
    etat = ARRETE;

    cout << "Porte: arret"<< endl;
    emit signaletat(position, etat);
}

void Porte::arreturgence(void){
    timer_transition->stop();
    etat = ALARME;

    emit signaletat(position, etat);
}

bool Porte::simulpanne(void){
   if (qrand() % PANNE_FREQMOYENNE == 0){
    //   cout << "Porte: panne!!"<< endl;
     //  arreturgence();
    //   return true;
   }

   return false;
}

void Porte::updateposition(void){
    cout << "Porte: position "<< position << endl;
    if (simulpanne() == true) return;

    switch(etat){
        case OUVERTURE:
            if (position <= 0){
                etat = OUVERTE;
                cout << "Porte: ouverte" << endl;
                timer_transition->stop();
            } else position--;
         break;
        case FERMETURE:
            if (position >= MAX_FERMETURE){
                etat = FERME;
                cout << "Porte: ferme" << endl;
                timer_transition->stop();
            } else position++;
         break;
        default: return;
     }


     emit signaletat(position, etat);
}
