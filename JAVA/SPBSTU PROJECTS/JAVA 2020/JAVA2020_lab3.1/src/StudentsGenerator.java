class StudentsGenerator implements Runnable{
    Cabinet store;
    StudentsGenerator(Cabinet store){
        this.store=store;
    }
    public void run(){
        for (int i = 1; i < 100; i++) {
            store.put();
            try
            {
                Thread.sleep(700);
            } catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }
    }
}