#ifndef VANNE_H
#define VANNE_H

#include <QObject>
#include <QThread>
#include "common.h"

class Vanne : public QObject
{
    Q_OBJECT

private:
    int etat;

public:
    explicit Vanne(QObject *parent = 0);

signals:
    void signaletat(int etat);

public slots:
    void extinction(void);
    void ouverture(void);
    void fermature(void);

private:
    bool simulpanne(void);

};

#endif // VANNE_H
