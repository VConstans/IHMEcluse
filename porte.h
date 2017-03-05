#ifndef PORTE_H
#define PORTE_H

#include <QObject>
#include <QTimer>
#include "etats.h"

#define FREQ_UPDATE 200
#define TIME_TRANS 10000
#define MAX_OUVERTURE (TIME_TRANS/FREQ_UPDATE)


class Porte : public QObject
{
    Q_OBJECT
    int etat;
    int position;
    bool alarme;
    QTimer *timer_transition;

public:
    explicit Porte(QObject *parent = 0);

signals:
    void signalalarme(bool alarme);
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
