#include "signallum.h"

SignalLum::SignalLum(QWidget *parent) :
    QLabel(parent)
{
    setRouge();
}

void SignalLum::setVert(){
    c = VERT;
    setPixmap(QPixmap(":/images/feu_vert_montant.png"));
}

void SignalLum::setRouge(){
    c = ROUGE;
    setPixmap(QPixmap(":/images/feu_rouge_montant.png"));
}
