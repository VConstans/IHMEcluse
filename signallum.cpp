#include "signallum.h"

SignalLum::SignalLum(QObject *parent) :
    QObject(parent)
{
}

void SignalLum::setrouge(void){
    couleur = ROUGE;
}

void SignalLum::setvert(void){
    couleur = VERT;
}

int SignalLum::getcouleur(void){
    return couleur;
}
