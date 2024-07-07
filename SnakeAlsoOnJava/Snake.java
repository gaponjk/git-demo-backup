import java.util.ArrayList;
import java.util.List;

public class Snake {
    //Направление движения
    private SnakeDirection direction;
    // жива змея или нет.
    private boolean isAlive;
    //тело змеи.
    private List<SnakeSection> sections;

    public Snake(int x, int y) {
        sections = new ArrayList<>();
        sections.add(new SnakeSection(x, y));
        isAlive = true;
    }

    public boolean isAlive() {
        return isAlive;
    }

    public int getX() {
        return sections.get(0).getX();
    }

    public int getY() {
        return sections.get(0).getY();
    }

    public SnakeDirection getDirection() {
        return direction;
    }

    public void setDirection(SnakeDirection direction) {
        this.direction = direction;
    }

    public List<SnakeSection> getSections() {
        return sections;
    }


    public void move() {
        if (!isAlive) return;

        if (direction == SnakeDirection.UP)
            move(0, -1);
        else if (direction == SnakeDirection.RIGHT)
            move(1, 0);
        else if (direction == SnakeDirection.DOWN)
            move(0, 1);
        else if (direction == SnakeDirection.LEFT)
            move(-1, 0);
    }


    void move(int dx, int dy) {
        //Создаем новую голову - новый "кусочек змеи".
        SnakeSection head = sections.get(0);
        head = new SnakeSection(head.getX() + dx, head.getY() + dy);


        checkBorders(head);
        if (!isAlive) return;


        checkBody(head);
        if (!isAlive) return;

        // не съела ли змея мышь.
        Mouse mouse = Room.game.getMouse();
        if (head.getX() == mouse.getX() && head.getY() == mouse.getY())
        {
            sections.add(0, head);
            Room.game.eatMouse();
        } else //просто движется
        {
            sections.add(0, head);
            sections.remove(sections.size() - 1);
        }
    }

    //не вылезла ли голова за границу комнаты
    void checkBorders(SnakeSection head) {
        if ((head.getX() < 0 || head.getX() >= Room.game.getWidth()) || head.getY() < 0 || head.getY() >= Room.game.getHeight()) {
            isAlive = false;
        }
    }

    //не пересекает ли змея  саму себя
    void checkBody(SnakeSection head) {
        if (sections.contains(head)) {
            isAlive = false;
        }
    }
}

