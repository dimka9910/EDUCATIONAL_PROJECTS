import java.util.Optional;

class Person {
    // Do not change these fields
    public static final String DEFAULT_NAME = "Unknown";
    public static final int MAX_AGE = 130;
    public static final int MIN_AGE = 0;
    private String name;
    private int age;

    // Fix the constructor to make its code pass the unit tests
    Person(String name, int age) {
        if (name == null || name.isBlank() || name.isEmpty())
            this.name = DEFAULT_NAME;
        else
            this.name = name;
        this.age = Math.min(Math.max(age, MIN_AGE), MAX_AGE);
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }
}