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
    Vanne *vanne_haut, *vanne_bas;
    Porte *porte_haut, *porte_bas;

public:
    explicit Ecluse(QObject *parent = 0);
    virtual ~Ecluse();

signals:
    void error(int ecode);

public slots:
    void ouvertureVanneMontant(void);
    void ouvertureVanneAvalant(void);


};

#endif // ECLUSE_H
