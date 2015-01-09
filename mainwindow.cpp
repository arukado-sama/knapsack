#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    initWindow();

    restoreSettings();

    connect(ui->buttonExit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonAdd_clicked()
{
    cpt=0;

    nb++;

    //increment line counter
    while(settings->contains("OBJECTS/object"+QString::number(cpt)))
        cpt++;

    //insert new line
    ui->displayObjects->insertItem(cpt,ui->linePoids->text()+" "+ui->lineValeur->text());

    //set new line as current line
    ui->displayObjects->setCurrentItem(ui->displayObjects->item(cpt));

    //save line number
    QString line="OBJECTS/object"+QString::number(cpt);

    //save line into settings file
    settings->setValue(line,ui->displayObjects->currentItem()->text());

    //save
    settings->setValue("PARAMETERS/nb",nb);

    verifSac();
}

void MainWindow::on_buttonDelete_clicked()
{
    cpt=0;

    QString current="OBJECTS/object"+QString::number(cpt);

    while(ui->displayObjects->currentItem()->text()!=settings->value(current))
    {
        cpt++;
        current="OBJECTS/object"+QString::number(cpt);
    }

    settings->remove(current);

    nb--;

    //save
    settings->setValue("PARAMETERS/nb",nb);

    qDeleteAll(ui->displayObjects->selectedItems());

    verifSac();
}

void MainWindow::restoreSettings()
{
    //settings restoration

    nb=0;
    cpt=0;

    //settings file instantiation
    settings = new QSettings("knapsack","knapsack");

    if((settings->contains("KNAPSACK/poids")))
        ui->linePoidsSac->setText(settings->value("KNAPSACK/poids").toString());

    if((settings->contains("PARAMETERS/nb")))
        nb=settings->value("PARAMETERS/nb").toInt();



    for(int i=0; i<nb; i++)
    {
        if(!(settings->contains("OBJECTS/object"+QString::number(cpt))))
            while(!(settings->contains("OBJECTS/object"+QString::number(cpt))))
                cpt++;

         QString line="OBJECTS/object"+QString::number(cpt);
         ui->displayObjects->insertItem(i,settings->value(line).toString());
         cpt++;
    }

    ui->displayObjects->setCurrentRow(0);

    loadText.setDirectory("/");

    verifSac();
}

void MainWindow::on_linePoidsSac_textChanged(const QString &arg1)
{

    settings->setValue("KNAPSACK/poids",arg1);
    verifSac();

}

void MainWindow::on_linePoids_textChanged()
{
    verifSac();
}

void MainWindow::on_lineValeur_textChanged()
{
    verifSac();
}

void MainWindow::verifSac()
{
    if(ui->linePoidsSac->text()=="")
    {
        ui->buttonAdd->setEnabled(0);
        ui->buttonDelete->setEnabled(0);
        ui->buttonSolve->setEnabled(0);
        ui->buttonDisplay->setEnabled(0);
        ui->displayObjects->setEnabled(0);
        ui->displayTree->setEnabled(0);
        ui->linePoids->setEnabled(0);
        ui->lineValeur->setEnabled(0);
    }

    else
    {
        ui->linePoids->setEnabled(1);
        ui->lineValeur->setEnabled(1);

        //if there is no registered objects
        if(nb==0)
        {
            ui->buttonDelete->setEnabled(0);
            ui->displayObjects->setEnabled(0);
            ui->buttonDisplay->setEnabled(0);
            ui->buttonSolve->setEnabled(0);
            ui->displayTree->setEnabled(0);
        }
        else
        {
            ui->buttonDelete->setEnabled(1);
            ui->displayObjects->setEnabled(1);
            ui->buttonDisplay->setEnabled(1);
            ui->buttonSolve->setEnabled(1);
            ui->displayTree->setEnabled(1);
        }

        if((ui->linePoids->text()!="")&&(ui->lineValeur->text()!="")) ui->buttonAdd->setEnabled(1);
        else ui->buttonAdd->setEnabled(0);
    }
}

void MainWindow::initWindow()
{
    //hide resize and close buttons

    Qt::WindowFlags wFlags = this->windowFlags();

    if(Qt::WindowCloseButtonHint == (wFlags & Qt::WindowCloseButtonHint))
    {
        wFlags = wFlags ^ Qt::WindowCloseButtonHint;
        this->setWindowFlags(wFlags);
    }

    if(Qt::WindowMaximizeButtonHint == (wFlags & Qt::WindowMaximizeButtonHint))
    {
        wFlags = wFlags ^ Qt::WindowMaximizeButtonHint;
        this->setWindowFlags(wFlags);
    }

    //resize application window
    setMinimumSize(570,650);
    setMaximumSize(570,650);

    //setting up UI
    ui->setupUi(this);

    ui->displayTree->setLineWrapMode(QTextBrowser::NoWrap);

    ui->buttonClear->setEnabled(0);
}

void MainWindow::on_buttonHow_clicked()
{
    //show how to use information box
    QMessageBox::information(this, "How to use", QString::fromUtf8(reinterpret_cast<const char*>(
    "The sack capacity must be an integer.\n\nIf you want to load a file it have to be a\ntext file and contain this format for objects:\n\nWeight(integer)SPACE(spacebar)Value(integer)\nWeight(integer)SPACE(spacebar)Value(integer)\nWeight(integer)SPACE(spacebar)Value(integer)\n...\n\nYou can also add objects with the button.\nThe weight and value have to be integers.\n\nAfter this you will be able to generate\nthe cut tree and the best solution."
    )));
}

void MainWindow::on_buttonAbout_clicked()
{
    //show about information box
    QMessageBox::information(this, "About", QString::fromUtf8(reinterpret_cast<const char*>("This is KNAPSACK v0.3\n\n©2014 Created by :\n\nClément JARDIN (aka Arukādo)\n<clement.jardin.pro@gmail.com>")));
}

void MainWindow::on_buttonClear_clicked()
{
    ui->displayTree->clear();
    ui->buttonClear->setEnabled(0);
}


void MainWindow::knapsack(QString action)
{
    ListeObjets l = NULL;

    //ajout des objets dans la liste l
    lectureFichier(&l);

    //création arbre de solution
    Arbre a = (Arbre)malloc(sizeof(struct noeud));
    a->fils = NULL;
    a->frere = NULL;

    //création de la pile de solutions
    PileNoeud p = NULL;

    int M = 0; //meilleure valeur du sac
    int capaciteSac = ui->linePoidsSac->text().toInt();

    AlgoDecoupe(&l, &M, a, capaciteSac, 0, &p, 0);

    if(action=="display")
    {
        ui->displayTree->append("Tree :\n\n");
        affichageArbre(&(a->fils), 0);
    }

    if(action=="solve")
    {
        ui->displayTree->append("Best value = "+QString::number(M)+"\n");
        affichageSolution(p);
    }

    ui->displayTree->verticalScrollBar()->setValue(ui->displayTree->verticalScrollBar()->maximum());

    ui->buttonClear->setEnabled(1);

    free_pile(p);
    free_obj(l);
    free_tree(a);
}


void MainWindow::on_buttonDisplay_clicked()
{
    knapsack("display");
}
void MainWindow::on_buttonSolve_clicked()
{
    knapsack("solve");
}

void MainWindow::on_buttonLoad_clicked()
{
    //set up .txt file dialog window
    loadText.setFileMode(QFileDialog::AnyFile);
    loadText.setWindowTitle("Load text file");
    loadText.setNameFilter("text file (*.txt)");

    //if .txt file selected
    if(loadText.exec()==1)
    {
        FILE *data;

        //save .txt path
        QString txtPath=loadText.selectedFiles().first();
        loadText.setDirectory(loadText.directory());

        while(nb>0)
        {
            ui->buttonDelete->click();
        }

        if((data = fopen(txtPath.toStdString().c_str(),"r")) == NULL)
        {
            fprintf(stderr, "Failed to open file.\n");
            exit(1);
        }

        int i=1, val , poids;
        char c;
        while((c=fgetc(data))!=EOF)
        {
            fseek(data, -1, SEEK_CUR); //replace le curseur 1 fois vers l'arriere, à cause de la lecture du premier caractere
            fscanf(data, "%d %d", &poids, &val);
            printf("Objet %d, poids %d, val %d\n", i, poids, val);

            ui->linePoids->setText(QString::number(poids));
            ui->lineValeur->setText(QString::number(val));
            ui->buttonAdd->click();

            i++;
            fseek(data, 1, SEEK_CUR); //se deplace de +1 vers l'avant, c'est a dire vers la ligne suivante

            //lecture peut-etre inefficace, trouver un moyen de ne pas utiliser fseek pour repositioner le curseur
        }

        ui->linePoids->setText("");
        ui->lineValeur->setText("");

        fclose(data);

        verifSac();
    }
}








void MainWindow::free_tree(struct noeud * noeud)
{
    if (noeud == NULL)
        return;

    free_tree((noeud)->fils);
    free_tree((noeud)->frere);

    free(noeud);
}

void MainWindow::free_pile(struct element * el)
{
    if (el == NULL)
        return;

    free_pile(el->suivant);

    free(el);
}

void MainWindow::free_obj(struct objet * o)
{
    if(o->suivant != NULL)
        free_obj(o->suivant);

    free(o);
}

//empiler dans la pile
void MainWindow::empiler(PileNoeud * p, Arbre * a, int poi, int val)
{
    PileNoeud el = (PileNoeud)malloc(sizeof(struct element));
    el->suivant = *p;
    el->noeud = *a;
    el->valeur = val;
    el->poids = poi;
    *p = el;
}

//depile le dernier noeud et récupère les valeurs (poids, valeur) à ce moment
Arbre MainWindow::depiler(PileNoeud * p, int * poi, int * val)
{
    Arbre tmp = (*p)->noeud;
    if (poi != NULL && val != NULL) {
        *poi = (*p)->poids;
        *val = (*p)->valeur;
    }
    *p = (*p)->suivant;
    return tmp;
}

//ajout d'un objet (poids et valeur) par rapport à son efficacité (valeur/poids)
void MainWindow::ajout(ListeObjets * l, int poi, int val)
{
    ListeObjets o, tmp = *l;
    o = (ListeObjets)malloc(sizeof(struct objet));
    o->poids = poi;
    o->valeur = val;

    float efficacite = (float)val/(float)poi;

    if ((*l)==NULL || efficacite >= ((float)(*l)->valeur / (float)(*l)->poids)) {
        o->suivant = *l;
        *l = o;
    } else {
        while((tmp->suivant != NULL) && (efficacite < ((float)tmp->suivant->valeur / (float)tmp->suivant->poids)))
            tmp = tmp->suivant;
        if(tmp->suivant == NULL) {//fin de la liste = pire efficacité
            o->suivant = NULL;
            tmp->suivant = o;
        }
        else { //cas général
            o->suivant = tmp->suivant;
            tmp->suivant = o;
        }
    }
}

void MainWindow::proprieteNoeud(ListeObjets o)
{
    printf("Objet : valeur %d, poids %d \n", o->valeur, o->poids);
}


void MainWindow::lectureFichier(ListeObjets * l)
{
    int val=0, poids=0, i;
    QString objet, charval="", charpoids="";
    cpt=0;

    while(cpt<nb){
        objet=ui->displayObjects->item(cpt)->text();

        for(i=0; objet[i]!=' '; i++)
            charpoids+=objet[i];

        for(i=i+1; objet[i]!='\0'; i++)
            charval+=objet[i];

        poids = charpoids.toInt();
        val = charval.toInt();

        ajout(l, poids, val); //ajout de l'objet dans liste triée par efficacité
        cpt++;

        charpoids="";
        charval="";
    }
}


//       ALGO

//AlgoDecoupe(
//ListeObjets * l : liste des objets
//int * bestVal : meilleure valeur trouvée pour l'instant
//Arbre a : arbre de recherche
//int capacite : capacite restante du sac après ajout des objets precedents
//int valeur : valeur actuelle du sac avec objets precedents
//PileNoeud * solution : pile de noeud composant la solution
//int pasDecoupe : pas de découpage si = 1
//);
void MainWindow::AlgoDecoupe(ListeObjets * l, int * bestVal, Arbre a, int capacite, int valeur, PileNoeud * solution, int pasDecoupe)
{ //parcours branche
    ListeObjets tmpl = *l;

    Arbre tmpa = a;

    PileNoeud p = NULL;//pile de noeud à parcourir

    PileNoeud tmpp = NULL; //eventuelle solution

    while (tmpl != NULL) {
        Arbre tmpn = (Arbre)malloc(sizeof(struct noeud)); //création nouveau noeud pour l'arbre
        tmpn->fils = NULL;
        tmpn->frere = NULL;
        tmpn->nbObjet = capacite / tmpl->poids; //calcul nombre d'objet possible (troncature)
        tmpn->lobjet = tmpl;

        capacite = capacite - tmpn->nbObjet * tmpl->poids; //mise a jour de la capacité du sac
        valeur = valeur + tmpn->nbObjet * tmpl->valeur; //mise a jour de la valeur dans le sac

        if (tmpn->nbObjet > 0 && tmpl->suivant != NULL) //ajout du noeud dans la pile des futurs noeuds à explorer si pas dernier objet
            empiler(&p, &tmpn, capacite, valeur);

        if (a->fils == NULL) { //ajout du premier élément dans l'arbre
            a->fils = tmpn;
            tmpa = a->fils;
        }
        else { //ajout du nouveau noeud à la suite dans l'arbre
            tmpa->fils = tmpn;
            tmpa = tmpa->fils;
        }

        empiler(&tmpp, &tmpn, capacite, valeur); //ajout du noeud dans une pile pour ajout dans la solution si meilleure valeur
        tmpl = tmpl->suivant; //objet suivant
    }

    if(valeur > *bestVal) { //si valeur de cette branche meilleure
        *bestVal = valeur; //mise à jour de LA meilleure valeur

        *solution = NULL; //nouvelle solution écrasant la précédente
        while (tmpp != NULL) { //ajout des noeuds parcourus dans la pile solution
            Arbre q = depiler(&tmpp, NULL, NULL);
            empiler(solution, &q, 0, 0);
        }
    }

    while (p != NULL) { //si des noeuds à parcourir...
        Arbre k = depiler(&p, &capacite, &valeur); //récupération du noeud

        if(pasDecoupe || (((float)valeur + ((float)(k->lobjet->suivant->valeur) / (float)(k->lobjet->suivant->poids)) * (float)capacite) > (float)(*bestVal+1))) { //calcul de l'utilité de continuer dans cette branche

            //mise à jour capacité et valeur si 1 objet en moins
            capacite = capacite + 1 * k->lobjet->poids;
            valeur = valeur - 1 * k->lobjet->valeur;

            //création d'un nouveau noeud = debut d'une nouvelle branche
            Arbre frere = (Arbre)malloc(sizeof(struct noeud));
            frere->fils = NULL;
            frere->frere = NULL;
            frere->lobjet = k->lobjet;//fl;
            frere->nbObjet = k->nbObjet - 1;

            if (frere->nbObjet > 0)
                empiler(&p, &frere, capacite, valeur); //noeud à explorer en suite

            int Mavant = *bestVal; //sauvegarde de la meilleure valeur

            AlgoDecoupe(&k->lobjet->suivant, bestVal, frere, capacite, valeur, solution, pasDecoupe); //Algo sur cette nouvelle branche

            if (*bestVal != Mavant) { //si meilleure valeur trouvée...
                empiler(solution, &frere, 0, 0); //...ajout du noeud courant dans la liste des solutions
            }

            k->frere = frere; //ajout nouvelle branche dans l'arbre
        }
    }
}

void MainWindow::affichageArbre(Arbre *racine, int prof)
{
    int i;

    for (i=0; i < prof; i++)
    {
        ui->displayTree->moveCursor(QTextCursor::End);
        ui->displayTree->insertPlainText("|___ ");
    }

    ui->displayTree->moveCursor(QTextCursor::End);
    ui->displayTree->insertPlainText("["+QString::number((*racine)->lobjet->poids)+" = "+QString::number((*racine)->nbObjet)+"]\n");

    if ((*racine)->fils) affichageArbre(&(*racine)->fils, prof + 1);
    if ((*racine)->frere) affichageArbre(&(*racine)->frere, prof);
}

void MainWindow::affichageSolution(PileNoeud pile)
{
    ui->displayTree->append("Best solution :\n\n");
    while (pile != NULL)
    {
        Arbre a = depiler(&pile, NULL, NULL);
        ui->displayTree->moveCursor(QTextCursor::End);
        ui->displayTree->insertPlainText("("+QString::number(a->lobjet->poids)+", "+QString::number(a->lobjet->valeur)+") = "+QString::number(a->nbObjet)+"\n");
    }
}
