interface Movable {
    int getX();
    int getY();
    void setX(int newX);
    void setY(int newY);
}

interface Storable {
    int getInventoryLength();
    String getInventoryItem(int index);
    void setInventoryItem(int index, String item);
}

interface Command {
    void execute();
    void undo();
}

class CommandMove implements Command{
    Movable entity;
    int xMovement;
    int yMovement;

    @Override
    public void execute() {
        
    }

    @Override
    public void undo() {

    }
}

class CommandPutItem implements Command{
    Storable entity;
    String item;

    @Override
    public void execute() {

    }

    @Override
    public void undo() {

    }
}