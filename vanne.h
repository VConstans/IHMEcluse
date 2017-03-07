#ifndef VANNE_H
#define VANNE_H

#include <QObject>
#include <QThread>
#include "common.h"

class Vanne : public QObject
{
    Q_OBJECT

private:
    int bkpetat;
    int etat;

public:
    explicit Vanne(QObject *parent = 0);
    int getetat(void);

signals:
    void signaletat(int etat);

public slots:
    void extinction(void);
    void arreturgence(void);
    void ouverture(void);
    void fermeture(void);

private:
    bool simulpanne(void);

};

#endif // VANNE_H
