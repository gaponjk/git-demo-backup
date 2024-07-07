#ifndef GAME_H
#define GAME_H
#include<QWidget>
#include<QPainter>
#include<QTimer>
#include<QKeyEvent>
#include<QRandomGenerator>
enum SnakeDirection {//для направлений
    UP,
    RIGHT,
    DOWN,
    LEFT
};
class SnakeSection{//чтобы не писать гэттеры и сеттеры я решил просто сделла их друг для друга дружественными
    friend  class Room;
    friend  class Snake;
private:
    int x;
    int y;
public:
    SnakeSection(int x,int y);
};
class Snake{
    friend class Room;
private:
    QList<SnakeSection*>sections;//тело змейки
    int snakeBeginSize;//для своего удобства
    SnakeDirection direction;//напрвление
public:
    Snake();
};

class Room:public QWidget{
    Q_OBJECT
public:
    Room();
protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
private:
    Snake*snake;//сама змея
    int snakeSize;//ее размер
    QTimer *timer;//как часто будет обновляться картинка
    SnakeSection *mouse;//мышь(еда)
    int roomSize;
    bool isAlive;//для того чтобы удаленные объекты после проигрыша не исползовались
    void dead();//окончание игры
    void start();//для того чтобы после смерти можно было продолжить
    int count;//счет
    void createMouse();
private slots:
    void moveSnake();//логика обновления работы
};

#endif // GAME_H
