#ifndef VANNE_H
#define VANNE_H

#include <QObject>
#include <QThread>
#include "etats.h"

class Vanne : public QObject
{
    Q_OBJECT

private:
    int etat;
    bool alarme;


public:
    explicit Vanne(QObject *parent = 0);

signals:
    void envoiEtat(int etat, bool alarme);

public slots:
    void extinction(void);
    void ouverture(void);
    void fermature(void);

private:
    bool simulpanne(void);

};

#endif // VANNE_H
