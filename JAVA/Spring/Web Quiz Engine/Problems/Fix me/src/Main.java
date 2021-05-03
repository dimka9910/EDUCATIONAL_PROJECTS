import java.util.*;     

/** Observable */

interface Observable {
    void addObserver(Observer observer);

    void removeObserver(Observer observer);

    void notifyObservers();
}

/**
 * Concrete Observable - Rockstar Games
 **/
class RockstarGames implements Observable {

    public String releaseGame;
    private List<Observer> observers = new ArrayList<>();

    public void release(String releaseGame) {
        this.releaseGame = releaseGame;
        notifyObservers();
    }

    @Override
    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers() {
        for (Observer observer : observers) {
            System.out.println("Inform message to : " + observer);
            observer.update(releaseGame);
        }
    }
}

/** Observer */

/** Concrete Observer */
interface Observer {
    public void update(String domain);

}

/**
 * Concrete observer - Gamer
 **/
class Gamer implements Observer {

    private String name;
    private String message;
    private Observable observable;
    private Set<String> games = new HashSet<>();

    public Gamer(String name, String message, Observable observable) {
        this.name = name;
        this.observable = observable;
        this.message = message;
    }

    @Override
    public void update(String game) {
        buyGame(game);
    }


    public void buyGame(String game) {
        if (games.add(game))
            System.out.println(name + " says: " + message);
        else
            System.out.println("What? They've already released this game ... I don't understand");
    }

    @Override
    public String toString() {
        return this.name;
    }
}

/** Main Class */

public class Main {
    public static void main(String[] args) {

        final Scanner scanner = new Scanner(System.in);

        String game = null;
        RockstarGames rockstarGames = new RockstarGames();
        /** write your code here ... */

        Gamer garry = new Gamer("Garry Rose", "I want to pre-order", rockstarGames);
        Gamer peter = new Gamer("Peter Johnston", "Pinch me...", rockstarGames);
        Gamer helen = new Gamer("Helen Jack", "Jesus, it's new game from Rockstar!", rockstarGames);

        /** write your code here ... */
        game = scanner.nextLine();
        System.out.println("It's happened! RockstarGames releases new game - " + game + "!");

        rockstarGames.addObserver(garry);
        rockstarGames.addObserver(peter);
        rockstarGames.addObserver(helen);

        rockstarGames.release(game);

        /** write your code here ... */ 

        scanner.close();
    }
}