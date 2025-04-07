#include "game.h"
Game::Game(QWidget *parent)
    : QWidget(parent)
{
    resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT);
    setWindowTitle("Snake game");
    initGame();
}

Game::~Game() {}

void Game::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    if(isInGame) {
        checkApple();
        move();
        checkField();
    }
    repaint();
}

void Game::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();
    if(key == Qt::Key_Left && direction != right)
        direction = left;
    if(key == Qt::Key_Right && direction != left)
        direction = right;
    if(key == Qt::Key_Up && direction != down)
        direction = up;
    if(key == Qt::Key_Down && direction != up)
        direction = down;
}

void Game::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    draw();
}

void Game::initGame() {
    isInGame = true;
    direction = right;
    body.resize(3);
    for(int i = 0; i < body.size(); ++i) {
        body[i].rx() = body.size() - i - 1;
        body[i].ry() = 0;
    }

    placeApple();

    timerId = startTimer(DELAY);
}

void Game::placeApple()
{
    apple.rx() = QRandomGenerator::global()->bounded(FIELD_WIDTH);
    apple.ry() = QRandomGenerator::global()->bounded(FIELD_HEIGHT);
}

void Game::draw()
{
    QPainter qp(this);

    if(isInGame) {
        qp.setBrush(Qt::red);
        qp.drawEllipse(apple.x() * DOT_WIDTH, apple.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        for(int i = 0; i < body.size(); ++i) {
            if(i == 0)
                qp.setBrush(Qt::white);
            else
                qp.setBrush(Qt::green);
            qp.drawEllipse(body[i].x() * DOT_WIDTH, body[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        }
    }
    else {
        finishGame();
    }
}

void Game::move()
{
    for(int i = body.size() - 1; i > 0; --i) {
        body[i] = body[i - 1];
    }

    switch(direction) {
    case left: body[0].rx()--; break;
    case right: body[0].rx()++; break;
    case up: body[0].ry()--; break;
    case down: body[0].ry()++; break;
    }
}

void Game::checkApple()
{
    if(apple == body[0]) {
        body.push_back(QPoint(0,0));
        placeApple();
    }
}

void Game::checkField()
{
    if(body.size() > 4) {
        for(int i = 1; i < body.size(); ++i) {
            if(body[0] == body[i])
                isInGame = false;
        }
    }
    if(body[0].rx() >= FIELD_WIDTH || body[0].rx() < 0)
        isInGame = false;
    if(body[0].ry() >= FIELD_HEIGHT || body[0].ry() < 0)
        isInGame = false;
    if(!isInGame)
        killTimer(timerId);
}

void Game::finishGame()
{
    QMessageBox msb;
    msb.setText("Game over");
    msb.exec();
    initGame();
}
