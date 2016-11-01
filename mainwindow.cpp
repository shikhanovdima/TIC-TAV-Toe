#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QProcess>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(playerMove()));
    QObject::connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(playerMove()));
    QObject::connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(playerMove()));
    QObject::connect(ui->pushButton_4,SIGNAL(clicked(bool)),this,SLOT(playerMove()));
    QObject::connect(ui->pushButton_5,SIGNAL(clicked(bool)),this,SLOT(playerMove()));
    QObject::connect(ui->pushButton_6,SIGNAL(clicked(bool)),this,SLOT(playerMove()));
    QObject::connect(ui->pushButton_7,SIGNAL(clicked(bool)),this,SLOT(playerMove()));
    QObject::connect(ui->pushButton_8,SIGNAL(clicked(bool)),this,SLOT(playerMove()));
    QObject::connect(ui->pushButton_9,SIGNAL(clicked(bool)),this,SLOT(playerMove()));



    ui->pushButton_10->setIcon(QIcon(":resource/3.png"));
    ui->pushButton_10->setIconSize(QSize(70,70));

    QPushButton *buttons[3][3] = {
        {ui->pushButton,   ui->pushButton_2, ui->pushButton_3},
        {ui->pushButton_4, ui->pushButton_5, ui->pushButton_6},
        {ui->pushButton_7, ui->pushButton_8, ui->pushButton_9}
    };

    for (int i=0; i<3; ++i)
        for (int j=0; j<3; ++j)
            m_buttons[i][j] = buttons[i][j];
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::Mark MainWindow::mark(int i, int j) const
{
    QPushButton *btn = m_buttons[i][j];

    return mark(btn);
}

MainWindow::Mark MainWindow::mark(QPushButton *btn) const
{
    if (btn->icon().cacheKey() == xIcon().cacheKey()) {
        return X;
    } else if (btn->icon().cacheKey() == oIcon().cacheKey()) {
        return O;
    }

    return Nothing;
}

void MainWindow::setMark(int i, int j, MainWindow::Mark m)
{
    QPushButton *btn = m_buttons[i][j];

    setMark(btn, m);
}

void MainWindow::setMark(QPushButton *btn, MainWindow::Mark m)
{
    if (m == X) {
        btn->setIcon(xIcon());
    } else if (m == O) {
        btn->setIcon(oIcon());
    } else {
        btn->setIcon(nothingIcon());
    }
}

void MainWindow::playerMove()
{   //////////////////////////
    ///////ИгрокVSИгрок///////
    //////////////////////////
    if(type==1){
    QPushButton* btn = qobject_cast<QPushButton*>(sender());

   if (w)
        return;
   if (!btn)
        return;

    if (mark(btn) != Nothing)
        return;

    switch (m_currentPlayer) {
    case Player1:
        btn->setIcon(xIcon());
        btn->setIconSize(QSize(70,70));
        m_currentPlayer = Player2;
        HOD++;
        Win();
        if(HOD==9&&!w)
          ui->label->setText("НИЧЬЯ");

        return;
    case Player2:
        btn->setIcon(oIcon());
        btn->setIconSize(QSize(70,70));
        m_currentPlayer = Player1;
        HOD++;
        Win();
        if(HOD==9&&!w)
          ui->label->setText("НИЧЬЯ");

        return;
    default:
        return;
    }
}
    //////////////////////////
    ///////ИгрокVSБОТ/////////
    //////////////////////////
    if(type==2){
        QPushButton* btn = qobject_cast<QPushButton*>(sender());

       if (w)
            return;
       if (!btn)
            return;

        if (mark(btn) != Nothing)
            return;

        switch (m_currentPLBOT) {
        case Pl1:
            btn->setIcon(xIcon());
            btn->setIconSize(QSize(70,70));
            m_currentPLBOT = PC;

            HOD++;
            Win();
             if(HOD==9&&!w)
                 ui->label->setText("НИЧЬЯ");

            return;
        case PC:
           // mark(i=random%8,j=random%8);

            m_currentPLBOT = Pl1;
            HOD++;
            Win();
            if(HOD==9&&!w)
              ui->label->setText("НИЧЬЯ");

            return;
        default:
            return;
        }
    }
}

///////////////////////
////Проверка Победы////
///////////////////////
void MainWindow::Win()
{
if ( (mark(0,0)==X && mark(1,1)==X && mark(2,2)==X)||
     (mark(0,0)==X && mark(0,1)==X && mark(0,2)==X)||
     (mark(1,0)==X && mark(1,1)==X && mark(1,2)==X)||
     (mark(2,0)==X && mark(2,1)==X && mark(2,2)==X)||
     (mark(0,0)==X && mark(1,0)==X && mark(2,0)==X)||
     (mark(0,1)==X && mark(1,1)==X && mark(2,1)==X)||
     (mark(0,2)==X && mark(1,2)==X && mark(2,2)==X)||
     (mark(2,0)==X && mark(1,1)==X && mark(0,2)==X) ){
       w=true;
       ui->label->setText("Win-X");}

if( (mark(0,0)==O && mark(1,1)==O && mark(2,2)==O)||
    (mark(0,0)==O && mark(0,1)==O && mark(0,2)==O)||
    (mark(1,0)==O && mark(1,1)==O && mark(1,2)==O)||
    (mark(2,0)==O && mark(2,1)==O && mark(2,2)==O)||
    (mark(0,0)==O && mark(1,0)==O && mark(2,0)==O)||
    (mark(0,1)==O && mark(1,1)==O && mark(2,1)==O)||
    (mark(0,2)==O && mark(1,2)==O && mark(2,2)==O)||
    (mark(2,0)==O && mark(1,1)==O && mark(0,2)==O) ){
        w=true;
        ui->label->setText("Win-O");
}
}

 QIcon MainWindow::xIcon()
{
    static QIcon icon(":resource/1.png");

    return icon;
}

QIcon MainWindow::oIcon()
{
    static QIcon icon(":resource/0.png");

    return icon;
}

QIcon MainWindow::nothingIcon()
{
    static QIcon icon;

    return icon;
}
void MainWindow::on_pushButton_10_clicked(bool checked)
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

///////////////////////////
////Кнопка "ДВА ИГРОКА"////
///////////////////////////

void MainWindow::on_PvP_clicked()
{
   type=1;

}
//////////////////////////////////
////Кнопка"ИГРА С КОМПЬЮТЕРОМ"////
//////////////////////////////////

void MainWindow::on_PvE_clicked()
{
   type=2;
}

