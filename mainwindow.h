#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <QScrollBar>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QTextBrowser>
#include <QTimer>
#include <unistd.h>
#include <stdio.h>


//--- STRUCTURES ---//

//objet
struct objet {
    int poids;
    int valeur;
    struct objet * suivant;
};
typedef struct objet * ListeObjets;

//arbre
struct noeud{
    struct objet * lobjet;
    int nbObjet;
    struct noeud * fils;
    struct noeud * frere;
};
typedef struct noeud * Arbre;

//pile de noeud pour les noeud à continuer à explorer
struct element {
    struct noeud * noeud;
    int poids;
    int valeur;
    struct element * suivant;
};
typedef struct element * PileNoeud;






namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

    void on_buttonDisplay_clicked();

    void on_buttonSolve_clicked();

    void on_linePoidsSac_textChanged(const QString &arg1);

    void on_linePoids_textChanged();

    void on_lineValeur_textChanged();

    void on_buttonAbout_clicked();

    void on_buttonClear_clicked();

    void on_buttonLoad_clicked();

    void on_buttonHow_clicked();

private:
    Ui::MainWindow *ui;

    void verifSac();
    void restoreSettings();
    void initWindow();


    void knapsack(QString action);

    void free_tree(struct noeud * noeud);
    void free_pile(struct element * el);
    void free_obj(struct objet * o);
    void empiler(PileNoeud * p, Arbre * a, int poi, int val);
    Arbre depiler(PileNoeud * p, int * poi, int * val);
    void ajout(ListeObjets * l, int poi, int val);
    void proprieteNoeud(ListeObjets o);
    void lectureFichier(ListeObjets * l);
    void AlgoDecoupe(ListeObjets * l, int * bestVal, Arbre a, int capacite, int valeur, PileNoeud * solution, int pasDecoupe);
    void affichageArbre(Arbre *racine, int prof);
    void affichageSolution(PileNoeud pile);

    //settings file object
    QSettings *settings;

    //text file dialog
    QFileDialog loadText;

    //line counter
    int cpt;

    //number of objects
    int nb;
};

#endif // MAINWINDOW_H
