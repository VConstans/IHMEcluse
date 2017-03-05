#ifndef ECLUSE_H
#define ECLUSE_H

#include <QObject>
#include "vanne.h"
#include "porte.h"

class Ecluse : public QObject
{
    Q_OBJECT
    QThread threadVanne_haut, threadVanne_bas;
    Vanne *vanne_haut, *vanne_bas;
    Porte *porte_haut, *porte_bas;

public:
    explicit Ecluse(QObject *parent = 0);
    virtual ~Ecluse();

signals:
    void test_sendSignal();

public slots:
    void test_recoitSignal(int etat, bool alarme);


};

#endif // ECLUSE_H
