#ifndef SIGNALLUM_H
#define SIGNALLUM_H

#include <QLabel>
enum couleur_feu {ROUGE, VERT};

class SignalLum : public QLabel
{
    Q_OBJECT
private:
    couleur_feu c;
public:
    explicit SignalLum(QWidget *parent, Qt::WindowFlags f);

public slots:
    void setVert(void);
    void setRouge(void);

};

#endif // SIGNALLUM_H
