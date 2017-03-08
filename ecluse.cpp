#include "ecluse.h"
#include <iostream>


Ecluse::Ecluse(QObject *parent) :
    QObject(parent)
{
    vanne_bas = new Vanne();
    vanne_bas->moveToThread(&threadVanne_bas);
    threadVanne_bas.start();

    vanne_haut = new Vanne();
    vanne_haut->moveToThread(&threadVanne_haut);
    threadVanne_haut.start();

    porte_haut = new Porte();
    porte_bas = new Porte();

    timer_remplissage = new QTimer(this);
    connect(timer_remplissage,SIGNAL(timeout()),
            this,SLOT(updateNivEau()));
    timer_remplissage->start(FREQ_UPDATE);

    connect(porte_bas, SIGNAL(signaletat(int,int)),this,SLOT(getEtatPorteBas(int,int)));
    connect(porte_haut, SIGNAL(signaletat(int,int)),this,SLOT(getEtatPorteHaut(int,int)));
    connect(vanne_bas, SIGNAL(signaletat(int)),this,SLOT(getEtatVanneBas(int)));
    connect(vanne_haut, SIGNAL(signaletat(int)),this,SLOT(getEtatVanneHaut(int)));

    nivEau = 0;
    alarme = false;
}


Ecluse::~Ecluse()
{
    threadVanne_bas.quit();
    threadVanne_haut.quit();
    threadVanne_bas.wait();
    threadVanne_haut.wait();

    delete vanne_bas;
    delete vanne_haut;
    delete porte_bas;
    delete porte_haut;
}


void Ecluse::ouvertureVanneMontant(void)
{
    if (alarme == true)
    {
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible d'ouvrir vanne montante");
        return;
    } else if (porte_haut->getetat() != FERME ||
               porte_bas->getetat() != FERME  )
    {
        emit baseError("Erreur: impossible d'ouvrir vanne montante");
        emit verbError("--> Porte ouverte");
        return;
    }

    vanne_haut->ouverture();
    emit baseMessage("Bassin en cours de remplissage");
    emit verbMessage("--> Vanne montante ouverte");
}

void Ecluse::ouvertureVanneAvalant(void)
{
    if (alarme == true)
    {
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible d'ouvrir vanne avalante");
        return;
    } if (porte_haut->getetat() != FERME ||
          porte_bas->getetat() != FERME  )
    {
        emit baseError("Erreur: impossible d'ouvrir vanne avalante");
        emit verbError("--> Porte ouverte");
        return;
    }

    vanne_bas->ouverture();
    emit baseMessage("Bassin en cours de vidange");
    emit verbMessage("--> Vanne avalante ouverte");
}

void Ecluse::fermetureVanneMontant(void)
{
    if (alarme == true)
    {
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible de fermer vanne montante");
        return;
    }
    vanne_haut->fermeture();
    emit verbMessage("Fermeture vanne montante");
}

void Ecluse::fermetureVanneAvalant(void)
{
    if (alarme == true)
    {
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible de fermer vanne avalante");
        return;
    }
    vanne_bas->fermeture();
    emit verbMessage("Fermeture vanne avalante");
}

void Ecluse::ouverturePorteBas(void)
{
    if (alarme == true)
    {
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible d'ouvrir porte avalante");
        return;
    } else if (nivEau > MIN_NIVEAU)
    {
        emit baseError("Error: impossible d'ouvrir porte avalante");
        emit verbError("--> Niveau de l'eau trop élevé");
        return ;
    } else if (vanne_bas->getetat() == OUVERTE ||
               vanne_haut->getetat() == OUVERTE)
    {
        emit baseError("Erreur: impossible d'ouvrir porte avalante");
        emit verbError("--> Vanne ouverte");
        return ;
    }
    emit baseMessage("Ouverture porte avalante");
    porte_bas->ouverture();
}

void Ecluse::ouverturePorteHaut(void)
{
    if (alarme == true)
    {
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible d'ouvrir porte montante");
        return;
    } else if (nivEau < MAX_NIVEAU)
    {
        emit baseError("Erreur: impossible d'ouvrir porte montante");
        emit verbError("--> Niveau de l'eau trop élevé");
        return ;
    } else if(vanne_bas->getetat() == OUVERTE ||
               vanne_haut->getetat() == OUVERTE)
    {
        emit baseError("Erreur: impossible d'ouvrir porte montante");
        emit verbError("--> Vanne ouverte");
        return ;
    }
    emit baseMessage("Ouverture porte montante");
    porte_haut->ouverture();
}

void Ecluse::fermeturePorteBas(void)
{
    if (alarme == true)
    {
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible de fermer porte avalante");
        return;
    }
    emit baseMessage("Fermeture porte avalante");
    porte_bas->fermeture();
}

void Ecluse::fermeturePorteHaut(void)
{
    if (alarme == true)
    {
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible de fermer porte montante");
        return;
    }
    emit baseMessage("Fermeture porte montante");
    porte_haut->fermeture();
}

void Ecluse::arretPorteHaut(void)
{
    if (alarme == true)
    {
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible arrêter porte montante");
        return;
    }
    emit verbMessage("Arrêt porte montante");
    porte_haut->arret();
}

void Ecluse::arretPorteBas(void)
{
    if (alarme == true)
    {
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible d'arrêter porte avalante");
        return;
    }
    emit verbMessage("Arrêt porte avalante");
}

void Ecluse::updateNivEau(void)
{
    if (vanne_bas->getetat() == OUVERTE &&
        vanne_haut->getetat() == OUVERTE)
    {

        if (nivEau > MID_NIVEAU) nivEau  -= DEBIT_EAU/2;
        if (nivEau < MID_NIVEAU) nivEau += DEBIT_EAU/2;

    } else if (vanne_bas->getetat() == OUVERTE)
    {

        if (nivEau > MIN_NIVEAU) nivEau -= DEBIT_EAU;

    } else if (vanne_haut->getetat() == OUVERTE)
    {

        if (nivEau < MAX_NIVEAU) nivEau += DEBIT_EAU;

    } else return;

    emit newNivEau(nivEau);

    if (nivEau == MAX_NIVEAU)
    {
       emit signalEauMax();
    } else if (nivEau == 0)
    {
       emit signalEauMin();
    }
}

void Ecluse::getEtatPorteBas(int position,int etat)
{
    switch (etat)
    {
        case ALARME: alarme =true;
        break;
         case FERME: emit signalPorteBasFerme();
        break;
         case OUVERTE: emit signalPorteBasOuverte();
        break;
    }

    emit signalEtatPorteBas(position,etat);
}

void Ecluse::getEtatPorteHaut(int position,int etat)
{
    switch (etat)
    {
        case ALARME: alarme =true;
        break;
        case FERME: emit signalPorteHautFerme();
        break;
        case OUVERTE: emit signalPorteHautOuverte();
        break;
    }
    emit signalEtatPorteHaut(position,etat);
}

void Ecluse::getEtatVanneBas(int etat)
{
    if (etat == ALARME) alarme = true;
    emit signalEtatVanneBas(etat);
}

void Ecluse::getEtatVanneHaut(int etat)
{
    if (etat == ALARME) alarme = true;
    emit signalEtatVanneHaut(etat);
}

 int Ecluse::getNivEau()
 {
     return nivEau;
 }

 void Ecluse::arretUrgence()
 {
     this->alarme=true;

     this->porte_bas->arreturgence();
     this->porte_haut->arreturgence();
     this->vanne_bas->arreturgence();
     this->vanne_haut->arreturgence();
 }

void Ecluse::stopArretUrgence()
 {
     this->alarme=false;

     this->porte_bas->extinction();
     this->porte_haut->extinction();
     this->vanne_bas->extinction();
     this->vanne_haut->extinction();
 }
