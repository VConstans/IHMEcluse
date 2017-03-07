#include "signallum.h"

SignalLum::SignalLum(QWidget *parent) :
    QLabel(parent)
{
    setRouge();
}

void SignalLum::setVert(){
    c = VERT;
    setPixmap(QPixmap(":/images/feu_vert.png"));
}

void SignalLum::setRouge(){
    c = ROUGE;
    setPixmap(QPixmap(":/images/feu_rouge.png"));
}
