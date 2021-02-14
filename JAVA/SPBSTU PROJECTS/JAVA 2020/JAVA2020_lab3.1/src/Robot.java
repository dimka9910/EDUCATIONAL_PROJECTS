class Robot implements Runnable{

    Cabinet cabinet;
    Cabinet.Subj subject;

    Robot(Cabinet cabinet, Cabinet.Subj subject){
        this.cabinet =cabinet;
        this.subject=subject;
    }

    @Override
    public void run()
    {
        while (true)
        {
            try
            {
                Thread.currentThread().setName("ROBOT " + subject);
                Thread.sleep(700);
                Cabinet.Student student = cabinet.get(subject);
                if (student != null)
                {
                    while (student.labsCount > 0)
                    {
                        Thread.sleep(700);
                        System.out.println(" осталось " + student.labsCount + " у: " + Thread.currentThread().getName());
                        student.labsCount -= 10;
                    }
                    Thread.sleep(700);
                    System.out.println(Thread.currentThread().getName() + " освободился");
                    Thread.sleep(700);
                }
            } catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }
    }
}