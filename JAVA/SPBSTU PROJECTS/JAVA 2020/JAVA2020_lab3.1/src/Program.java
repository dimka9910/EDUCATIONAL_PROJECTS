public class Program {

    public static void main(String[] args) {

        Cabinet cabinet=new Cabinet();
        StudentsGenerator studentsGenerator = new StudentsGenerator(cabinet);
        Robot mathRobot = new Robot(cabinet, Cabinet.Subj.MATH);
        Robot physRobot = new Robot(cabinet, Cabinet.Subj.PHYTHICS);
        Robot oopRobot = new Robot(cabinet, Cabinet.Subj.OOP);

        new Thread(mathRobot).start();
        new Thread(physRobot).start();
        new Thread(oopRobot).start();
        new Thread(studentsGenerator).start();
    }
}
