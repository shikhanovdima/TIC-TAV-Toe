#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QIcon>
#include<QStackedWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Mark {Nothing, X, O};

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Mark mark(int i, int j) const;
    Mark mark(QPushButton* btn) const;

    void setMark(int i, int j, Mark m);
    void setMark(QPushButton* btn, Mark m);
    int type=0;//тип игры

private:
    Ui::MainWindow *ui;
    enum Player {Player1, Player2};

    Player m_currentPlayer = Player1;

    enum BOTPC {Pl1,PC};

    BOTPC m_currentPLBOT = Pl1;

    QPushButton *m_buttons[3][3];

    static QIcon xIcon();
    static QIcon oIcon();
    static QIcon nothingIcon();
    bool w = false;
    int HOD=0;


private slots:
    void playerMove();
    void on_PvP_clicked();
    void on_PvE_clicked();
    void on_pushButton_10_clicked(bool checked);
    void Win();
};

#endif // MAINWINDOW_H
