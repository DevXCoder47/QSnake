#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QMessageBox>
class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();
protected:
    void timerEvent(QTimerEvent* e) override;
    void keyPressEvent(QKeyEvent* e) override;
    void paintEvent(QPaintEvent* e) override;
private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int FIELD_WIDTH = 20;
    static const int FIELD_HEIGHT = 20;
    static const int DELAY = 150;

    int timerId;

    QPoint apple;
    enum Directions {
        left, right, up, down
    };

    Directions direction = down;

    bool isInGame;
    QVector<QPoint> body;

    void initGame();
    void placeApple();
    void draw();
    void move();
    void checkApple();
    void checkField();
    void finishGame();
};
#endif // GAME_H
