/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *IHMAuto;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *buttonMontant;
    QPushButton *buttonAvalant;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *buttonEnter;
    QPushButton *buttonExit;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_5;
    QPushButton *buttonStopAuto;
    QGraphicsView *display;
    QWidget *IHMMan;
    QLabel *label_2;
    QLabel *label_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *ecluse;
    QLabel *vanne_montant;
    QLabel *vanne_avalant;
    QLabel *signal_montant;
    QLabel *signal_avalant;
    QProgressBar *waterLevel;
    QLabel *porteAvalant;
    QLabel *porteMontant;
    QWidget *tab_2;
    QLabel *label;
    QLabel *label_4;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *groupeButtonVannes;
    QVBoxLayout *vanneMontant;
    QPushButton *vanneMontantOuv;
    QPushButton *vanneMontantFerm;
    QVBoxLayout *vanneAvalant;
    QPushButton *vanneAvalantOuv;
    QPushButton *vanneAvalantFerm;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *groupeButtonPortes;
    QProgressBar *progressPorteMontant;
    QVBoxLayout *groupePorteMontant;
    QPushButton *porteMontantOuv;
    QPushButton *porteMontantArret;
    QPushButton *porteMontantFerm;
    QVBoxLayout *groupePorteAvalant;
    QProgressBar *progressBar_2;
    QPushButton *porteAvalantOuv;
    QPushButton *porteAvalantArret;
    QPushButton *porteAvalantFerm;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *groupeButtonSignaux;
    QVBoxLayout *signauxMontant;
    QPushButton *vertMontant;
    QPushButton *rougeMontant;
    QVBoxLayout *signauxAvalant;
    QPushButton *vertAvalant;
    QPushButton *rougeAvalant;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *groupeButtonUrgence;
    QLabel *alarme;
    QPushButton *buttonStopMan;
    QLabel *label_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1107, 843);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1091, 771));
        IHMAuto = new QWidget();
        IHMAuto->setObjectName(QStringLiteral("IHMAuto"));
        horizontalLayoutWidget = new QWidget(IHMAuto);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 210, 581, 261));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        buttonMontant = new QPushButton(horizontalLayoutWidget);
        buttonMontant->setObjectName(QStringLiteral("buttonMontant"));
        buttonMontant->setMinimumSize(QSize(77, 50));
        buttonMontant->setStyleSheet(QLatin1String("#buttonMontant{\n"
"border-image: url(/home/victor/cours/IHM/IHMEcluse/images/haut.png);\n"
"}"));

        verticalLayout_2->addWidget(buttonMontant);

        buttonAvalant = new QPushButton(horizontalLayoutWidget);
        buttonAvalant->setObjectName(QStringLiteral("buttonAvalant"));
        buttonAvalant->setMinimumSize(QSize(89, 74));
        buttonAvalant->setStyleSheet(QLatin1String("#buttonAvalant{\n"
"border-image: url(/home/victor/cours/IHM/IHMEcluse/images/bas.png);\n"
"}"));

        verticalLayout_2->addWidget(buttonAvalant);


        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        buttonEnter = new QPushButton(horizontalLayoutWidget);
        buttonEnter->setObjectName(QStringLiteral("buttonEnter"));

        horizontalLayout_4->addWidget(buttonEnter);

        buttonExit = new QPushButton(horizontalLayoutWidget);
        buttonExit->setObjectName(QStringLiteral("buttonExit"));

        horizontalLayout_4->addWidget(buttonExit);


        horizontalLayout_3->addLayout(horizontalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        buttonStopAuto = new QPushButton(horizontalLayoutWidget);
        buttonStopAuto->setObjectName(QStringLiteral("buttonStopAuto"));
        buttonStopAuto->setMinimumSize(QSize(172, 170));
        buttonStopAuto->setStyleSheet(QLatin1String("#buttonStopAuto{\n"
"border-image: url(/home/victor/cours/IHM/IHMEcluse/images/urgence_relache.png);\n"
"}\n"
"\n"
"\n"
"#buttonStopAuto:pressed{\n"
"border-image: url(/home/victor/cours/IHM/IHMEcluse/images/arret_urgence.png);\n"
"}"));

        gridLayout_5->addWidget(buttonStopAuto, 0, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_5);

        display = new QGraphicsView(IHMAuto);
        display->setObjectName(QStringLiteral("display"));
        display->setGeometry(QRect(30, 20, 581, 171));
        stackedWidget->addWidget(IHMAuto);
        IHMMan = new QWidget();
        IHMMan->setObjectName(QStringLiteral("IHMMan"));
        label_2 = new QLabel(IHMMan);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(300, 360, 67, 17));
        label_3 = new QLabel(IHMMan);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(500, 360, 67, 17));
        tabWidget = new QTabWidget(IHMMan);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(30, 10, 881, 331));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        ecluse = new QLabel(tab);
        ecluse->setObjectName(QStringLiteral("ecluse"));
        ecluse->setGeometry(QRect(70, 40, 521, 231));
        ecluse->setMinimumSize(QSize(500, 200));
        ecluse->setStyleSheet(QLatin1String("#ecluse{\n"
"border-image: url(/home/victor/cours/IHM/IHMEcluse/images/ecluse.png)\n"
"}"));
        vanne_montant = new QLabel(tab);
        vanne_montant->setObjectName(QStringLiteral("vanne_montant"));
        vanne_montant->setGeometry(QRect(180, 10, 21, 21));
        vanne_montant->setStyleSheet(QLatin1String("#vanne_montant{\n"
"border-image: url(/home/victor/cours/IHM/IHM_Ecluse/voyant_allume.png)\n"
"}"));
        vanne_avalant = new QLabel(tab);
        vanne_avalant->setObjectName(QStringLiteral("vanne_avalant"));
        vanne_avalant->setGeometry(QRect(460, 10, 21, 21));
        vanne_avalant->setStyleSheet(QLatin1String("#vanne_avalant{\n"
"border-image: url(/home/victor/cours/IHM/IHM_Ecluse/voyant_allume.png)\n"
"}"));
        signal_montant = new QLabel(tab);
        signal_montant->setObjectName(QStringLiteral("signal_montant"));
        signal_montant->setGeometry(QRect(80, 250, 21, 21));
        signal_montant->setStyleSheet(QLatin1String("#signal_montant{\n"
"border-image: url(/home/victor/cours/IHM/IHM_Ecluse/voyant_allume.png)\n"
"}"));
        signal_avalant = new QLabel(tab);
        signal_avalant->setObjectName(QStringLiteral("signal_avalant"));
        signal_avalant->setGeometry(QRect(560, 250, 21, 21));
        signal_avalant->setStyleSheet(QLatin1String("#signal_avalant{\n"
"border-image: url(/home/victor/cours/IHM/IHM_Ecluse/voyant_allume.png)\n"
"}"));
        waterLevel = new QProgressBar(tab);
        waterLevel->setObjectName(QStringLiteral("waterLevel"));
        waterLevel->setGeometry(QRect(710, 40, 41, 231));
        waterLevel->setLayoutDirection(Qt::LeftToRight);
        waterLevel->setValue(24);
        waterLevel->setTextVisible(false);
        waterLevel->setOrientation(Qt::Vertical);
        waterLevel->setTextDirection(QProgressBar::TopToBottom);
        porteAvalant = new QLabel(tab);
        porteAvalant->setObjectName(QStringLiteral("porteAvalant"));
        porteAvalant->setGeometry(QRect(450, 140, 21, 91));
        porteAvalant->setStyleSheet(QLatin1String("#porteAvalant{\n"
"background-color: black\n"
"}"));
        porteMontant = new QLabel(tab);
        porteMontant->setObjectName(QStringLiteral("porteMontant"));
        porteMontant->setGeometry(QRect(190, 140, 21, 91));
        porteMontant->setStyleSheet(QLatin1String("#porteMontant{\n"
"background-color: black\n"
"}"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        label = new QLabel(IHMMan);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 350, 67, 17));
        label_4 = new QLabel(IHMMan);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 480, 67, 17));
        horizontalLayoutWidget_2 = new QWidget(IHMMan);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(70, 380, 791, 371));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        groupeButtonVannes = new QVBoxLayout();
        groupeButtonVannes->setSpacing(6);
        groupeButtonVannes->setObjectName(QStringLiteral("groupeButtonVannes"));
        vanneMontant = new QVBoxLayout();
        vanneMontant->setSpacing(6);
        vanneMontant->setObjectName(QStringLiteral("vanneMontant"));
        vanneMontantOuv = new QPushButton(horizontalLayoutWidget_2);
        vanneMontantOuv->setObjectName(QStringLiteral("vanneMontantOuv"));
        vanneMontantOuv->setStyleSheet(QStringLiteral("#vanneMontantOuv{background-image: url(:/fleche.png)}"));

        vanneMontant->addWidget(vanneMontantOuv);

        vanneMontantFerm = new QPushButton(horizontalLayoutWidget_2);
        vanneMontantFerm->setObjectName(QStringLiteral("vanneMontantFerm"));

        vanneMontant->addWidget(vanneMontantFerm);


        groupeButtonVannes->addLayout(vanneMontant);

        vanneAvalant = new QVBoxLayout();
        vanneAvalant->setSpacing(6);
        vanneAvalant->setObjectName(QStringLiteral("vanneAvalant"));
        vanneAvalantOuv = new QPushButton(horizontalLayoutWidget_2);
        vanneAvalantOuv->setObjectName(QStringLiteral("vanneAvalantOuv"));

        vanneAvalant->addWidget(vanneAvalantOuv);

        vanneAvalantFerm = new QPushButton(horizontalLayoutWidget_2);
        vanneAvalantFerm->setObjectName(QStringLiteral("vanneAvalantFerm"));

        vanneAvalant->addWidget(vanneAvalantFerm);


        groupeButtonVannes->addLayout(vanneAvalant);


        horizontalLayout->addLayout(groupeButtonVannes);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        groupeButtonPortes = new QVBoxLayout();
        groupeButtonPortes->setSpacing(6);
        groupeButtonPortes->setObjectName(QStringLiteral("groupeButtonPortes"));
        progressPorteMontant = new QProgressBar(horizontalLayoutWidget_2);
        progressPorteMontant->setObjectName(QStringLiteral("progressPorteMontant"));
        progressPorteMontant->setValue(24);

        groupeButtonPortes->addWidget(progressPorteMontant);

        groupePorteMontant = new QVBoxLayout();
        groupePorteMontant->setSpacing(6);
        groupePorteMontant->setObjectName(QStringLiteral("groupePorteMontant"));
        porteMontantOuv = new QPushButton(horizontalLayoutWidget_2);
        porteMontantOuv->setObjectName(QStringLiteral("porteMontantOuv"));
        porteMontantOuv->setStyleSheet(QStringLiteral(""));

        groupePorteMontant->addWidget(porteMontantOuv);

        porteMontantArret = new QPushButton(horizontalLayoutWidget_2);
        porteMontantArret->setObjectName(QStringLiteral("porteMontantArret"));
        porteMontantArret->setMinimumSize(QSize(0, 0));
        porteMontantArret->setStyleSheet(QLatin1String("#porteMontantArret{\n"
"color: red\n"
"}"));

        groupePorteMontant->addWidget(porteMontantArret);

        porteMontantFerm = new QPushButton(horizontalLayoutWidget_2);
        porteMontantFerm->setObjectName(QStringLiteral("porteMontantFerm"));
        porteMontantFerm->setStyleSheet(QStringLiteral(""));

        groupePorteMontant->addWidget(porteMontantFerm);


        groupeButtonPortes->addLayout(groupePorteMontant);

        groupePorteAvalant = new QVBoxLayout();
        groupePorteAvalant->setSpacing(6);
        groupePorteAvalant->setObjectName(QStringLiteral("groupePorteAvalant"));
        progressBar_2 = new QProgressBar(horizontalLayoutWidget_2);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        progressBar_2->setValue(24);

        groupePorteAvalant->addWidget(progressBar_2);

        porteAvalantOuv = new QPushButton(horizontalLayoutWidget_2);
        porteAvalantOuv->setObjectName(QStringLiteral("porteAvalantOuv"));
        porteAvalantOuv->setStyleSheet(QStringLiteral(""));

        groupePorteAvalant->addWidget(porteAvalantOuv);

        porteAvalantArret = new QPushButton(horizontalLayoutWidget_2);
        porteAvalantArret->setObjectName(QStringLiteral("porteAvalantArret"));
        porteAvalantArret->setStyleSheet(QLatin1String("#porteAvalantArret{\n"
"color: red\n"
"}"));

        groupePorteAvalant->addWidget(porteAvalantArret);

        porteAvalantFerm = new QPushButton(horizontalLayoutWidget_2);
        porteAvalantFerm->setObjectName(QStringLiteral("porteAvalantFerm"));
        porteAvalantFerm->setStyleSheet(QStringLiteral(""));

        groupePorteAvalant->addWidget(porteAvalantFerm);


        groupeButtonPortes->addLayout(groupePorteAvalant);


        horizontalLayout->addLayout(groupeButtonPortes);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        groupeButtonSignaux = new QVBoxLayout();
        groupeButtonSignaux->setSpacing(6);
        groupeButtonSignaux->setObjectName(QStringLiteral("groupeButtonSignaux"));
        signauxMontant = new QVBoxLayout();
        signauxMontant->setSpacing(6);
        signauxMontant->setObjectName(QStringLiteral("signauxMontant"));
        vertMontant = new QPushButton(horizontalLayoutWidget_2);
        vertMontant->setObjectName(QStringLiteral("vertMontant"));
        vertMontant->setStyleSheet(QStringLiteral("#pushButton_3{color: green}"));

        signauxMontant->addWidget(vertMontant);

        rougeMontant = new QPushButton(horizontalLayoutWidget_2);
        rougeMontant->setObjectName(QStringLiteral("rougeMontant"));
        rougeMontant->setStyleSheet(QStringLiteral("#pushButton_4{color: red}"));

        signauxMontant->addWidget(rougeMontant);


        groupeButtonSignaux->addLayout(signauxMontant);

        signauxAvalant = new QVBoxLayout();
        signauxAvalant->setSpacing(6);
        signauxAvalant->setObjectName(QStringLiteral("signauxAvalant"));
        vertAvalant = new QPushButton(horizontalLayoutWidget_2);
        vertAvalant->setObjectName(QStringLiteral("vertAvalant"));
        vertAvalant->setStyleSheet(QStringLiteral("#pushButton_2{color: green}"));

        signauxAvalant->addWidget(vertAvalant);

        rougeAvalant = new QPushButton(horizontalLayoutWidget_2);
        rougeAvalant->setObjectName(QStringLiteral("rougeAvalant"));
        rougeAvalant->setStyleSheet(QStringLiteral("#pushButton{color: red}"));

        signauxAvalant->addWidget(rougeAvalant);


        groupeButtonSignaux->addLayout(signauxAvalant);


        horizontalLayout->addLayout(groupeButtonSignaux);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        groupeButtonUrgence = new QVBoxLayout();
        groupeButtonUrgence->setSpacing(6);
        groupeButtonUrgence->setObjectName(QStringLiteral("groupeButtonUrgence"));
        alarme = new QLabel(horizontalLayoutWidget_2);
        alarme->setObjectName(QStringLiteral("alarme"));
        alarme->setMaximumSize(QSize(100, 100));
        alarme->setStyleSheet(QLatin1String("#alarme{\n"
"border-image: url(/home/victor/cours/IHM/IHMEcluse/images/voyant_eteind.png)\n"
"}"));

        groupeButtonUrgence->addWidget(alarme);

        buttonStopMan = new QPushButton(horizontalLayoutWidget_2);
        buttonStopMan->setObjectName(QStringLiteral("buttonStopMan"));
        buttonStopMan->setMinimumSize(QSize(172, 170));
        buttonStopMan->setStyleSheet(QLatin1String("#buttonStopMan{\n"
"border-image: url(/home/victor/cours/IHM/IHMEcluse/images/urgence_relache.png);\n"
"}\n"
"\n"
"\n"
"#buttonStopMan:pressed{\n"
"border-image: url(/home/victor/cours/IHM/IHMEcluse/images/arret_urgence.png);\n"
"}"));

        groupeButtonUrgence->addWidget(buttonStopMan);


        horizontalLayout->addLayout(groupeButtonUrgence);

        label_5 = new QLabel(IHMMan);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 670, 67, 17));
        stackedWidget->addWidget(IHMMan);
        label_2->raise();
        label_3->raise();
        tabWidget->raise();
        label->raise();
        label_4->raise();
        horizontalLayoutWidget_2->raise();
        label_5->raise();
        buttonStopMan->raise();
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1107, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        buttonMontant->setText(QString());
        buttonAvalant->setText(QString());
        buttonEnter->setText(QApplication::translate("MainWindow", "Entrer", 0));
        buttonExit->setText(QApplication::translate("MainWindow", "Sortir", 0));
        buttonStopAuto->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Portes", 0));
        label_3->setText(QApplication::translate("MainWindow", "Signaux", 0));
        ecluse->setText(QString());
        vanne_montant->setText(QString());
        vanne_avalant->setText(QString());
        signal_montant->setText(QString());
        signal_avalant->setText(QString());
        porteAvalant->setText(QString());
        porteMontant->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
        label->setText(QApplication::translate("MainWindow", "Vannes", 0));
        label_4->setText(QApplication::translate("MainWindow", "Montant", 0));
        vanneMontantOuv->setText(QApplication::translate("MainWindow", "Ouverture", 0));
        vanneMontantFerm->setText(QApplication::translate("MainWindow", "Fermeture", 0));
        vanneAvalantOuv->setText(QApplication::translate("MainWindow", "Ouverture", 0));
        vanneAvalantFerm->setText(QApplication::translate("MainWindow", "Fermeture", 0));
        porteMontantOuv->setText(QApplication::translate("MainWindow", "Ouverture", 0));
        porteMontantArret->setText(QApplication::translate("MainWindow", "Arr\303\252t", 0));
        porteMontantFerm->setText(QApplication::translate("MainWindow", "Fermeture", 0));
        porteAvalantOuv->setText(QApplication::translate("MainWindow", "Ouverture", 0));
        porteAvalantArret->setText(QApplication::translate("MainWindow", "Arr\303\252t", 0));
        porteAvalantFerm->setText(QApplication::translate("MainWindow", "Fermeture", 0));
        vertMontant->setText(QApplication::translate("MainWindow", "Vert", 0));
        rougeMontant->setText(QApplication::translate("MainWindow", "Rouge", 0));
        vertAvalant->setText(QApplication::translate("MainWindow", "Vert", 0));
        rougeAvalant->setText(QApplication::translate("MainWindow", "Rouge", 0));
        alarme->setText(QString());
        buttonStopMan->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "Avalant", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
