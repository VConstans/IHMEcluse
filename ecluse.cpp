#include "ecluse.h"
#include <iostream>


Ecluse::Ecluse(QObject *parent) :
    QObject(parent)
{
    // Creation des vannes asyncrones
    vanne_bas = new Vanne();
    vanne_bas->moveToThread(&threadVanne_bas);
    threadVanne_bas.start();
    vanne_haut = new Vanne();
    vanne_haut->moveToThread(&threadVanne_haut);
    threadVanne_haut.start();

    // Creation des portes
    porte_haut = new Porte();
    porte_bas = new Porte();

    // Simulation flux d'eau
    timer_remplissage = new QTimer(this);
    connect(timer_remplissage,SIGNAL(timeout()),
            this,SLOT(updateNivEau()));
    timer_remplissage->start(FREQ_UPDATE);

    // Capture mise a jour
    connect(porte_bas, SIGNAL(signaletat(int,int)),this,SLOT(getEtatPorteBas(int,int)));
    connect(porte_haut, SIGNAL(signaletat(int,int)),this,SLOT(getEtatPorteHaut(int,int)));
    connect(vanne_bas, SIGNAL(signaletat(int)),this,SLOT(getEtatVanneBas(int)));
    connect(vanne_haut, SIGNAL(signaletat(int)),this,SLOT(getEtatVanneHaut(int)));

    // Initialisation des attributs
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



// Ouverture de la vanne amont et controls de securite
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




// Ouverture de la vanne aval et controls de securite
void Ecluse::ouvertureVanneAvalant(void)
{
    if (alarme == true)
    {   // Echoue si l'alarme est actif
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible d'ouvrir vanne avalante");
        return;
    } if (porte_haut->getetat() != FERME ||
          porte_bas->getetat() != FERME  )
    {   // Echoue si une porte est ouverte
        emit baseError("Erreur: impossible d'ouvrir vanne avalante");
        emit verbError("--> Porte ouverte");
        return;
    }

    vanne_bas->ouverture();
    emit baseMessage("Bassin en cours de vidange");
    emit verbMessage("--> Vanne avalante ouverte");
}



// Fermature de la vanne amont 
void Ecluse::fermetureVanneMontant(void)
{
    if (alarme == true)
    {   // Echoue si l'alarme est actif
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible de fermer vanne montante");
        return;
    }
    vanne_haut->fermeture();
    emit verbMessage("Fermeture vanne montante");
}



// Fermature vanne aval
void Ecluse::fermetureVanneAvalant(void)
{
    if (alarme == true)
    {   // Echoue si l'alarme est actif
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible de fermer vanne avalante");
        return;
    }
    vanne_bas->fermeture();
    emit verbMessage("Fermeture vanne avalante");
}



// Ouverture porte aval
void Ecluse::ouverturePorteBas(void)
{
    if (alarme == true)
    {   // Echoue si l'alarme est actif
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible d'ouvrir porte avalante");
        return;
    } else if (nivEau > MIN_NIVEAU)
    {   // Echoue si niveau d'eau c'est bas 
        emit baseError("Error: impossible d'ouvrir porte avalante");
        emit verbError("--> Niveau de l'eau trop élevé");
        return ;
    } else if (vanne_bas->getetat() == OUVERTE ||
               vanne_haut->getetat() == OUVERTE)
    {   // Echoue si une vanne est ouverte
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
    {   // Echoue si l'alarme est actif
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible d'ouvrir porte montante");
        return;
    } else if (nivEau < MAX_NIVEAU)
    {   // Echoue si le niveau de l'eau est trop haut
        emit baseError("Erreur: impossible d'ouvrir porte montante");
        emit verbError("--> Niveau de l'eau trop élevé");
        return ;
    } else if(vanne_bas->getetat() == OUVERTE ||
               vanne_haut->getetat() == OUVERTE)
    {   // Echoue si une vanne est ouverte
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
    {   // Echoue si l'alarme est actif
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible de fermer porte avalante");
        return;
    }
    emit baseMessage("Fermeture porte avalante");
    porte_bas->fermeture();
}




// Fermature de la porte amont
void Ecluse::fermeturePorteHaut(void)
{
    if (alarme == true)
    {   // Echoue si l'alarme est actif
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible de fermer porte montante");
        return;
    }
    emit baseMessage("Fermeture porte montante");
    porte_haut->fermeture();
}



// Arret de la porte amont
void Ecluse::arretPorteHaut(void)
{
    if (alarme == true)
    {   // Echoue si l'alarme est actif
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible arrêter porte montante");
        return;
    }
    emit verbMessage("Arrêt porte montante");
    porte_haut->arret();
}



// Arret de la porte aval
void Ecluse::arretPorteBas(void)
{
    if (alarme == true)
    {   // Echoue si l'alarme est actif
        emit baseError("Erreur: alarme actif");
        emit verbError("--> Impossible d'arrêter porte avalante");
        return;
    }
    emit verbMessage("Arrêt porte avalante");
}



// Mise a jour du niveau d'eau
void Ecluse::updateNivEau(void)
{
    if (vanne_bas->getetat() == OUVERTE &&
        vanne_haut->getetat() == OUVERTE)
    {   // Deux vannes ouvertes: demi vitesse

        if (nivEau > MID_NIVEAU) nivEau  -= DEBIT_EAU/2;
        if (nivEau < MID_NIVEAU) nivEau += DEBIT_EAU/2;

    } else if (vanne_bas->getetat() == OUVERTE)
    {   // Vanne aval ouverte: eau qui baisse

        if (nivEau > MIN_NIVEAU) nivEau -= DEBIT_EAU;

    } else if (vanne_haut->getetat() == OUVERTE)
    {   // Vanne amont ouverte: eau qui monte

        if (nivEau < MAX_NIVEAU) nivEau += DEBIT_EAU;

    } else return; // Aucune vanne ouverte

    emit newNivEau(nivEau);

    if (nivEau == MAX_NIVEAU)
    { 
       emit signalEauMax();
    } else if (nivEau == 0)
    {
       emit signalEauMin();
    }
}



// Slot pour recevoir les signaux de la porte aval
void Ecluse::getEtatPorteBas(int position,int etat)
{
    switch (etat)
    {
        case PANNE:  // Declanche alarme ecluse
        case ALARME: alarme = true;
        break;
         case FERME: emit signalPorteBasFerme();
        break;
         case OUVERTE: emit signalPorteBasOuverte();
        break;
    }

    emit signalEtatPorteBas(position,etat);
}



// Slot pour recevoir les signaux de la porte amont
void Ecluse::getEtatPorteHaut(int position,int etat)
{
    switch (etat)
    {
        case PANNE: // Declanche alarme ecluse
        case ALARME: alarme = true;
        break;
        case FERME: emit signalPorteHautFerme();
        break;
        case OUVERTE: emit signalPorteHautOuverte();
        break;
    }
    emit signalEtatPorteHaut(position,etat);
}




void Ecluse::getEtatVanneBas(int etat)
{   // Declanche alarme ecluse si c'est le cas 
    if (etat == ALARME || etat == PANNE) alarme = true;
    emit signalEtatVanneBas(etat);
}




void Ecluse::getEtatVanneHaut(int etat)
{
    // Declanche alarme ecluse si c'est le cas 
    if (etat == ALARME || etat == PANNE) alarme = true;
    emit signalEtatVanneHaut(etat);
}




 int Ecluse::getNivEau(){return nivEau;}



// Arret d'urgence globale 
 void Ecluse::arretUrgence()
 {
     this->alarme=true;

     this->porte_bas->arreturgence();
     this->porte_haut->arreturgence();
     this->vanne_bas->arreturgence();
     this->vanne_haut->arreturgence();
 }



// Extintion de l'arret d'urgence globale 
void Ecluse::stopArretUrgence()
 {
     this->alarme=false;

     this->porte_bas->extinction();
     this->porte_haut->extinction();
     this->vanne_bas->extinction();
     this->vanne_haut->extinction();
 }
