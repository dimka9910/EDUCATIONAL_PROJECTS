class Vehicle {

    private String name;

    // create constructor

    public Vehicle(String name) {
        this.name = name;
    }

    class Engine {
        void start() {
            System.out.println("RRRrrrrrrr....");
        }
    }

    public class Body{
        String color;
        public Body(String color) {
            this.color = color;
        }

        public void printColor(){
            System.out.println("Vehicle " + name + " has " + color + " body.");
        }
    }
    // create class Body
}

// this code should work
class EnjoyVehicle {

    public static void main(String[] args) {

        Vehicle vehicle = new Vehicle("Dixi");
        Vehicle.Body body = vehicle.new Body("red");
        body.printColor();
    }
}