package main;

public final class SourceManager {

    private static SourceManager instance;

    private Source[] source;
    private int sourceAmount;
    private Buffer buffer;
    private int requestCounter = 0;
    private DeviceManager devman;

    private SourceManager(int reqAmount, Buffer buffer, double sourceLam){
        this.buffer = buffer;
        this.sourceAmount = reqAmount;
        source = new Source[reqAmount];
        devman = DeviceManager.getInstance(0, null, 0, 0);
        for (int i = 0; i < reqAmount; i++){
            source[i] = new Source(sourceLam, i);
        }
    }

    public static SourceManager getInstance(int reqAmount, Buffer buffer, double sourceLam) {
        if (instance == null) {
            instance = new SourceManager(reqAmount,buffer,sourceLam);
        }
        return instance;
    }

    public static void resetInstance() {
        instance = null;
    }

    public static SourceManager getInstance() {
        return instance;
    }


    public void GenNew(){
        Source src = source[0];
        for (int i = 1; i < sourceAmount; i++) {
            if (source[i].getTime() < src.getTime()) {
                src = source[i];
            }
        }
        Request r = src.GenNew();
//        if (r.getStartTime() > devman.getMinTime())
//            devman.takeRequest(r);
//        else
            buffer.PlaceInBuffer(r);
    }

    public double getMinTime(){
        double time = source[0].getTime();
        for (int i = 1; i < sourceAmount; i++) {
            if (source[i].getTime() < time) {
                time = source[i].getTime();
            }
        }
        return time;
    }

    public void refuseHandler(Request request){
        source[request.getId_source()].incRefuse();
    }

    public void requestInfoHandler(Request request){
        int id = request.getId_source();
        source[id].incWaitTime(request.getWaitTime());
        source[id].incTimeInSystem(request.getEndTime()-request.getTime());
        source[id].incProcessingTime(request.getEndTime()-request.getStartTime());
    }



    public Source[] getSource() {
        return source;
    }

    public int getSourceAmount() {
        return sourceAmount;
    }
}
