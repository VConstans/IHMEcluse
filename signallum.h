#ifndef SIGNALLUM_H
#define SIGNALLUM_H

#include <QObject>
#include "common.h"

class SignalLum : public QObject
{
    Q_OBJECT
    int couleur;

public:
    explicit SignalLum(QObject *parent = 0);
    int getcouleur(void);

public slots:
    void setrouge(void);
    void setvert(void);

};

#endif // SIGNALLUM_H
