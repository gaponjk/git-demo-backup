#include "game.h"


Room::Room()//задаю область виждета, где будет
{
    setFixedSize(500,500);
    setFocusPolicy(Qt::StrongFocus);
    snakeSize=10;
    roomSize=width()/snakeSize;
    start();//потому что часть инициализаций  у старта повторяется
}

void Room::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter;
    painter.begin(this);
    if(!isAlive){//смерть
        QRect cellRect(0,0,width()-1,height()-1);
        painter.setPen(Qt::black);
        painter.drawLine(cellRect.topLeft(), cellRect.bottomRight());
        painter.drawLine(cellRect.topRight(), cellRect.bottomLeft());
        painter.setFont (QFont ("Arial", 10, 700));
        painter.drawText (QRect (0, -150, width(), height()), Qt::AlignCenter, "ИГРА ПРОИГРАНА\n нажмите пробел, чтобы начать снова\nСчет:"
                                                                                 +QString::number(count));
        return;
    }
    painter.drawRect(0,0,width()-1,height()-1);//рисуем
    painter.setBrush(Qt::red);
    QPolygon headPolygon;//рисую видимую голову
    int headX = snake->sections[0]->x * snakeSize;
    int headY = snake->sections[0]->y * snakeSize;

    if (snake->direction == UP) {
        headPolygon << QPoint(headX + snakeSize / 2, headY)
                    << QPoint(headX, headY + snakeSize)
                    << QPoint(headX + snakeSize, headY + snakeSize);
    } else if (snake->direction == DOWN) {
        headPolygon << QPoint(headX, headY)
                    << QPoint(headX + snakeSize, headY)
                    << QPoint(headX + snakeSize / 2, headY + snakeSize);
    } else if (snake->direction == LEFT) {
        headPolygon << QPoint(headX, headY + snakeSize / 2)
                    << QPoint(headX + snakeSize, headY)
                    << QPoint(headX + snakeSize, headY + snakeSize);
    } else if (snake->direction == RIGHT) {
        headPolygon << QPoint(headX, headY)
                    << QPoint(headX, headY + snakeSize)
                    << QPoint(headX + snakeSize, headY + snakeSize / 2);
    }

    painter.drawPolygon(headPolygon);
    painter.setBrush(Qt::green);
    for (int var = 1; var < snake->sections.size(); ++var) {//туловище
        painter.drawRect(snake->sections[var]->x*snakeSize,snake->sections[var]->y*snakeSize,snakeSize,snakeSize);//рисую змейку
    }
    painter.setBrush(Qt::gray);//мышь
    painter.drawEllipse(mouse->x*snakeSize,mouse->y*snakeSize,snakeSize,snakeSize);
    painter.end();
}

void Room::keyPressEvent(QKeyEvent *event)//управление стрелками, можно умереть повернув обратно
{
    if(event->key()==Qt::Key_Space){
        if(!isAlive){
            start();
            return;
        }
    }
    if (event->key() == Qt::Key_Left )
        snake->direction = LEFT;
    if (event->key() == Qt::Key_Right )
        snake->direction = RIGHT;
    if (event->key() == Qt::Key_Up)
        snake->direction = UP;
    if (event->key() == Qt::Key_Down )
        snake->direction = DOWN;
}

void Room::dead()//удаляю все лишнее и оставливаю время
{
    isAlive=false;
    timer->stop();
    delete mouse;
    delete timer;
    delete snake;
}

void Room::start()
{
    snake=new Snake();
    mouse=new SnakeSection(rand()%roomSize,rand()%roomSize);
    isAlive=true;
    timer=new QTimer();
    connect(timer,&QTimer::timeout,this,&Room::moveSnake);
    timer->start(100);//10 кадров в секунду
    count=0;
}

void Room::createMouse()
{
    mouse->x=QRandomGenerator::global()->bounded(0,roomSize-1);
    mouse->y=QRandomGenerator::global()->bounded(0,roomSize-1);
    for (int var = 0; var < snake->sections.size(); ++var) {//проверяю на контакты со змеей
        if(mouse->x==snake->sections[var]->x&&mouse->y==snake->sections[var]->y)
            return createMouse();
    }
}

void Room::moveSnake()//движение змейки
{
    SnakeSection* head;
    if (snake->direction == UP)
        head=new SnakeSection(snake->sections[0]->x,snake->sections[0]->y-1);
    else if (snake->direction == RIGHT)
        head=new SnakeSection(snake->sections[0]->x+1,snake->sections[0]->y);
    else if (snake->direction == DOWN)
        head=new SnakeSection(snake->sections[0]->x,snake->sections[0]->y+1);
    else
        head=new SnakeSection(snake->sections[0]->x-1,snake->sections[0]->y);
    //об поле нельзя удариться
    if(head->x>=roomSize)
        head->x=0;
    else if(head->x<0)
        head->x=roomSize-1;
    else if(head->y>=roomSize)
        head->y=0;
    else if(head->y<0)
        head->y=roomSize-1;
     // Проверяем столкновение с телом змеи
    for (int var = 0; var < snake->sections.size(); ++var) {
        if(head->x==snake->sections[var]->x&&head->y==snake->sections[var]->y){
            dead();
        }
    }
    if(isAlive){
    //eatMouse()
    if(head->x==mouse->x&&head->y==mouse->y){
        count++;
        createMouse();
    }
    else
        snake->sections.removeLast();
    snake->sections.insert(0,head);
    }
    delete head;
    update();
}

SnakeSection::SnakeSection(int x, int y)
{
    this->x=x;
    this->y=y;
}

Snake::Snake()
{//инициализация змеи
    snakeBeginSize=20;
    int random =QRandomGenerator::global()->bounded(0,499-snakeBeginSize*2);
    for (int var = random; var <random+ snakeBeginSize; ++var) {
        sections.insert(0,new SnakeSection(var,random));
    }
    direction=DOWN;
}
