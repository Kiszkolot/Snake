#include "MainSnak.h"
#include "QPainter"
#include <QPushButton>

#include "QTime"

Widget::Widget(QWidget *parent): QWidget(parent){
    setStyleSheet("background-color:lightblue;");
    setFixedSize(BOARDWIDTH,BOARDHEIGHT);
    facingDOWN = false;
    facingRIGHT = false;
    facingLEFT = false;
    facingUP = true;
    alive = true;

    loadGraphics();
    beginGame();
}

void Widget::loadGraphics(){
    head.load(":/pictures/Head.png");
    body.load(":/pictures/Body.png");
    apple.load(":/pictures/Apple.png");
    return;
}

void Widget::beginGame(){
    segments = 3;
    for(int i=0; i< segments; i++){
        X[i] = 150 - i*10;
        Y[i] = 150;
    }

    placeAppleRandomly();
    timer = startTimer(DELAY);
}

void Widget::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);
    draw();
}

void Widget::draw(){
    QPainter pain(this);
    if(alive){
        pain.drawImage(jablkoX, jablkoY, apple);

        for(int i=0; i< segments; i++){
            if (i ==0){
                pain.drawImage(X[i],Y[i], head);
            }
            else{
                pain.drawImage(X[i],Y[i], body);
            }
        }
    }
    else{
        endTheGame(pain);
    }
}

void Widget::endTheGame(QPainter &pain){
    QString endMess = "Game Over!\n You scored %1 points";
    QFont font("Sans", 10, QFont::DemiBold);
    QFontMetrics fontMetric(font);
    int textWidth = fontMetric.horizontalAdvance(endMess);
    pain.setFont(font);
    int h = height();
    int w = width();
    pain.translate(QPoint(w/2, h/4));
    pain.drawText(-textWidth/2, 0, endMess.arg(segments));

}

void Widget::appleEater(){
    if(jablkoX == X[0] && jablkoY == Y[0]){
        segments+=1;
        placeAppleRandomly();
    }
}

void Widget::placeAppleRandomly(){
    QTime timmy = QTime::currentTime();
    qsrand((uint) timmy.msec());
    int base = qrand() % RANDOMIZER;
    jablkoX = base*IMAGESIZE;
    base = qrand() % RANDOMIZER;
    jablkoY = base*IMAGESIZE;
}

void Widget::move(){

    for(int i = segments; i>0 ; i--){
        X[i] = X[i-1];
        Y[i] = Y[i-1];
    }
    if(facingLEFT){
        X[0] -= IMAGESIZE;
    }

    if(facingRIGHT){
        X[0] += IMAGESIZE;
    }

    if(facingDOWN){
        Y[0] += IMAGESIZE;
    }

    if (facingUP){
        Y[0] -= IMAGESIZE;
    }

}

void Widget::deathCheck(){
    for(int i = segments; i >0; i--){
        if(X[0]==X[i] && Y[0] == Y[i]){
            alive = false;
        }
    }
    if(X[0] >= BOARDWIDTH){
        alive = false;
    }
    if(X[0] < 0){
        alive = false;
    }
    if(Y[0] >= BOARDHEIGHT){
        alive = false;
    }
    if(Y[0] < 0){
        alive = false;
    }
    if(! alive){
        killTimer(timer);
    }
}

void Widget:: keyPressEvent(QKeyEvent *e){
    int key = e->key();

    if((key == Qt::Key_Left || key == Qt::Key_A ) && !facingRIGHT){
        facingLEFT = true;
        facingDOWN = false;
        facingUP = false;
    }

    if((key == Qt::Key_Right || key == Qt::Key_D )&& !facingLEFT){
        facingRIGHT = true;
        facingDOWN = false;
        facingUP = false;
    }

    if((key == Qt::Key_Up|| key == Qt::Key_W ) && !facingDOWN){
        facingLEFT = false;
        facingRIGHT = false;
        facingUP = true;
    }

    if((key == Qt::Key_Down|| key == Qt::Key_S ) && !facingUP){
        facingLEFT = false;
        facingRIGHT = false;
        facingDOWN= true;
    }

    QWidget::keyPressEvent(e);

}

void Widget::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    if(alive){
       appleEater();
       deathCheck();
       move();
    }

    repaint();
}
