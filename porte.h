#ifndef PORTE_H
#define PORTE_H

#include <QObject>
#include <QTimer>
#include "common.h"



class Porte : public QObject
{
    Q_OBJECT
    int etat;
    int position;
    QTimer *timer_transition;

public:
    explicit Porte(QObject *parent = 0);
    int getetat(void);

signals:
    void signaletat(int position, int etat);

private slots:
    void updateposition(void);

public slots:
    void ouverture(void);
    void fermature(void);
    void extinction(void);
    void arret(void);
    void arreturgence(void);

 private:
    bool simulpanne(void);
};

#endif // PORTE_H
