#pragma once
#include <QWidget>
#include <QKeyEvent>

class Widget : public QWidget
{

public:
    Widget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    QImage head;
    QImage apple;
    QImage body;

    //stałe
    static const int BOARDHEIGHT = 300;
    static const int BOARDWIDTH = 300;
    static const int IMAGESIZE = 10;
    static const int DELAY = 150;
    static const int RANDOMIZER = 23;
    static const int MAXDOTS = 900;

    // zmienne związane z grą
    int timer;
    int segments;
    int jablkoX;
    int jablkoY;

    //określenie położenia głowy
    bool facingUP;
    bool facingDOWN;
    bool facingRIGHT;
    bool facingLEFT;
    bool alive;

    //położenie segmentów ciała
    int X[MAXDOTS];
    int Y[MAXDOTS];

    //funkcje
    void loadGraphics();
    void beginGame();
    void placeAppleRandomly();
    void appleEater();
    void deathCheck();
    void move();
    void draw();
    void endTheGame(QPainter &);
    void handleButton();


};

