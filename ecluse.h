#ifndef ECLUSE_H
#define ECLUSE_H

#include <QObject>
#include "vanne.h"
#include "porte.h"
#include "common.h"

class Ecluse : public QObject
{
    Q_OBJECT
    QThread threadVanne_haut, threadVanne_bas;
    QTimer *timer_remplissage;
    int nivEau;
    bool alarme;

public:
    Vanne *vanne_haut, *vanne_bas;
    Porte *porte_haut, *porte_bas;

    explicit Ecluse(QObject *parent = 0);
    virtual ~Ecluse();

signals:
    void error(int ecode);
    void message(int mcode);
    void newNivEau(int nivEau);
    void signalEauMax(void);
    void signalEauMin(void);
    void signalEtatPorteHaut(int position, int etat);
    void signalEtatPorteBas(int position, int etat);
    void signalEtatVanneHaut(int etat);
    void signalEtatVanneBas(int etat);
    void signalPorteBasFerme();
    void signalPorteBasOuverte();
    void signalPorteHautOuverte();
    void signalPorteHautFerme();

public slots:
    void ouvertureVanneMontant(void);
    void ouvertureVanneAvalant(void);
    void fermetureVanneMontant(void);
    void fermetureVanneAvalant(void);

    void ouverturePorteBas(void);
    void ouverturePorteHaut(void);
    void fermeturePorteBas(void);
    void fermeturePorteHaut(void);
    void arretPorteBas(void);
    void arretPorteHaut(void);
    int getNivEau();

private slots:
    void updateNivEau(void);
    void getEtatPorteHaut(int position,int etat);
    void getEtatPorteBas(int position,int etat);
    void getEtatVanneHaut(int etat);
    void getEtatVanneBas(int etat);

};

#endif // ECLUSE_H
