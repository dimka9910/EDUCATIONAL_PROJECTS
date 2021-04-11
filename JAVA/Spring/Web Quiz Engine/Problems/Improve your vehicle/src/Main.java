class Vehicle {

    private String name;

    // create constructor


    public Vehicle(String name) {
        this.name = name;
    }

    class Engine {

        // add field horsePower
        // create constructor

        int horsePower;


        public Engine(int horsePower) {
            this.horsePower = horsePower;
        }
        void start() {
            System.out.println("RRRrrrrrrr....");
        }

        public void printHorsePower(){
            System.out.println("Vehicle " + name + " has " + horsePower + " horsepower.");
        }
        // create method printHorsePower()
    }
}

// this code should work
class EnjoyVehicle {

    public static void main(String[] args) {

        Vehicle vehicle = new Vehicle("Dixi");
        Vehicle.Engine engine = vehicle.new Engine(15);
        engine.printHorsePower();
    }
}