package main;

public final class PrintData {

    private static PrintData instance;
    private DeviceManager devMan;
    private SourceManager sourceManager;
    private Buffer buffer;

    private PrintData (DeviceManager devMan, SourceManager sourceManager, Buffer buffer) {
        this.devMan = devMan;
        this.sourceManager = sourceManager;
        this.buffer = buffer;
    }

    public static PrintData getInstance(DeviceManager devMan, SourceManager sourceManager, Buffer buffer) {
        if (instance == null) {
            instance = new PrintData(devMan, sourceManager, buffer);
        }
        return instance;
    }

    public static void resetInstance() {
        instance = null;
    }

    public void printTotal() {

        System.out.println("источники");
        System.out.println("  Номер |  id  |     time        |refuse| total|  P Refuse  |avg T in Sys| avg Wait T | avg Proc T | ");
        int totalAmount = 0;
        int obr = -1;
        for (int i = 0; i < sourceManager.getSourceAmount(); i++) {

            int id = 0;
            int refuse = 0;
            int amount = 0;
            double time = 0;
            double pRefuse = 0;
            double averageTimeInSystem = 0;
            double averageWaitInSystem = 0;
            double avgProcTime = 0;


            if (sourceManager.getSource()[i] != null){
                id = sourceManager.getSource()[i].getId();
                time = sourceManager.getSource()[i].getTime();
                refuse = sourceManager.getSource()[i].getRefuse();
                amount = sourceManager.getSource()[i].getRequestCounter();
                if (amount - refuse != 0) {
                    pRefuse = refuse * 1.0 / amount;
                    averageTimeInSystem = sourceManager.getSource()[i].getTimeInSystem() / (amount - refuse);
                    averageWaitInSystem = sourceManager.getSource()[i].getWaitTime() / (amount - refuse);
                    avgProcTime = sourceManager.getSource()[i].getProcessingTime() / (amount - refuse);
                }
                totalAmount += amount;
                obr += amount - refuse;
            }

            System.out.println(String.format(
                    "%1$7d | %2$4d | %3$15.8f | %4$4d | %5$4d | %6$10.5f | %7$10.5f | %8$10.5f | %9$10.5f |",
                    i+1, id+1, time, refuse, amount, pRefuse, averageTimeInSystem, averageWaitInSystem, avgProcTime));
        }

        System.out.println("Девайсы");
        System.out.println("  Номер |    K Isp    |");
        for (int i = 0; i < devMan.getDeviceAmount(); i++) {

               double procTime = devMan.getDevices()[i].getProcessingTime();
               double time = devMan.getMaxTime();
               double kUse = procTime/time;
                System.out.println(String.format(
                        "%1$7d | %2$10.5f  |",
                        i + 1, kUse));

        }

        System.out.println("Device Alpha " + Simulation.getInstance().getDeviceAlpha());
        System.out.println("Device Beta " + Simulation.getInstance().getDeviceBeta());
        System.out.println("Source Lam " + Simulation.getInstance().getSourceLam());
        System.out.println("Total Amount " + totalAmount);
        System.out.println("Total obr " + obr);
    }

    public void printStep(){

        System.out.println();
        System.out.println("Буфер");
        System.out.println("  Номер | Req_id   |      time       |");
        for (int i = 0; i < buffer.getSize_(); i++) {

            int id = -1;
            double time = -1;

            if (buffer.getBuffer_()[i] != null){
                id = buffer.getBuffer_()[i].getId();
                time = buffer.getBuffer_()[i].getTime();
            }

            if (id > 0) {
                System.out.println(String.format(
                        "%1$7d | %2$8d | %3$15.8f |",
                        i + 1, id, time));
            } else {
            System.out.println(String.format("%1$7d | FREE",i + 1));
            }

        }
        System.out.println("источники");
        System.out.println("  Номер |  id  |     time        |refuse| total| ");
        for (int i = 0; i < sourceManager.getSourceAmount(); i++) {

            int id = -1;
            int refuse = -1;
            int amount = -1;
            double time = -1;

            if (sourceManager.getSource()[i] != null){
                id = sourceManager.getSource()[i].getId();
                time = sourceManager.getSource()[i].getTime();
                refuse = sourceManager.getSource()[i].getRefuse();
                amount = sourceManager.getSource()[i].getRequestCounter();
            }

            System.out.println(String.format(
                    "%1$7d | %2$4d | %3$15.8f | %4$4d | %5$4d |",
                    i+1, id+1, time, refuse, amount));
        }
        System.out.println("Девайсы");
        System.out.println("  Номер | req_id | start time |  end time  |amount|  Work Time | ");
        for (int i = 0; i < devMan.getDeviceAmount(); i++) {

            int id = -1;
            double time = -1;
            double startTime = -1;
            int amount = -1;
            double workTime = -1;

            if (devMan.getDevices()[i].getRequest() != null){
                id = devMan.getDevices()[i].getRequest().getId();
                startTime = devMan.getDevices()[i].getStartTime();
                time = devMan.getDevices()[i].getTime();
                amount = devMan.getDevices()[i].getRequestAmount();
                workTime = devMan.getDevices()[i].getProcessingTime();
            }
            if (id > 0) {
                System.out.println(String.format(
                        "%1$7d | %2$4d | %3$10.5f | %4$10.5f | %5$4d | %6$10.5f |",
                        i + 1, id, startTime, time, amount, workTime));
            } else {
                System.out.println(String.format("%1$7d | FREE",i + 1));
            }
        }
    }

    public void printAvg(int k)
    {
        int totalAmount = 0;
        int obr = -1;
        double pRefuse = 0;
        double kUse = 0;
        for (int i = 0; i < sourceManager.getSourceAmount(); i++) {
            int amount = -1;
            if (sourceManager.getSource()[i] != null){
                amount = sourceManager.getSource()[i].getRequestCounter();
                pRefuse += sourceManager.getSource()[i].getRefuse()*1.0 / amount;
            }
        }
        pRefuse = pRefuse / sourceManager.getSourceAmount();



        for (int i = 0; i < devMan.getDeviceAmount(); i++) {
            double procTime = devMan.getDevices()[i].getProcessingTime();
            double time = devMan.getMaxTime();
            kUse += procTime/time;
        }
        kUse /= devMan.getDeviceAmount();

        System.out.println(String.format(
                "%1$7d|  pRefuse: %2$10.5f | kUse:  %3$10.5f ",
                k, pRefuse, kUse));
    }

    public double getP(){
        double pRefuse = 0;
        for (int i = 0; i < sourceManager.getSourceAmount(); i++) {
            int amount = -1;
            if (sourceManager.getSource()[i] != null){
                amount = sourceManager.getSource()[i].getRequestCounter();
                pRefuse += sourceManager.getSource()[i].getRefuse()*1.0 / amount;
            }
        }
        pRefuse = pRefuse / sourceManager.getSourceAmount();
        return pRefuse;
    }

}
