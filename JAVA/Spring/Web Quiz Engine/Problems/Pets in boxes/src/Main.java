import java.util.ArrayList;

class BoxInside {

    // Complete this method
    public static void showAnimal (Box<? extends Animal> b){
        b.getAnimal().toString();
    }
}

// Don't change the code below
class Animal {

    private String name;

    public Animal(String name) {
        this.name = name;
    }

    public String toString() {
        return name;
    }
}

class Box<T> {

    private T animal;

    void setAnimal(T animal) {
        this.animal = animal;
    }

    T getAnimal() {
        return animal;
    }
}



class Application<T extends Throwable> {

    public static void main(String[] args) {

        Application<RuntimeException> application = new Application<>();
        application.secureRun(() -> System.out.println("Hello!"));

    }

    public void secureRun(Runnable runnable) throws T {
        try {
            runnable.run();
        } catch (T e) {
            System.err.print("Error!");
        }
    }

}