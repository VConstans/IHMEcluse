#include "signallum.h"

SignalLum::SignalLum(QWidget *parent, Qt::WindowFlags f) :
    QLabel(parent, f)
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
