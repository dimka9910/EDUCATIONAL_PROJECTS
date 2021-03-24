class Info {

    public static void printCurrentThreadInfo() {
        Thread t = Thread.currentThread(); // main thread

        System.out.println("name: " + t.getName());
        //System.out.println("ID: " + t.getId());
        //System.out.println("Alive: " + t.isAlive());
        System.out.println("priority: " + t.getPriority());
        // get the thread and print its info
    }
}