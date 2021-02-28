package phonebook;

public class Fake {

    public static void fakesearch() {
        long time = System.currentTimeMillis();

        System.out.println("Start searching (linear search)...");

        for (int i = 0; i < 100000; i++){
            for (int j = 0; j < 50000; j++){
                String str = String.valueOf(i);
            }
        }
        time = System.currentTimeMillis() - time;
        String timeout = time / 60000 + " min. " + (time % 60000) / 1000 + " sec. " + (time % 60000) % 1000 + " ms.";
        System.out.println("Found " + 500 + " / " + 500 + " entries. Time taken: " + timeout);

        System.out.println("\nStart searching (bubble sort + jump search)...");
        long time1 = System.currentTimeMillis();
        for (int i = 0; i < 100000; i++){
            for (int j = 0; j < 20000; j++){
                String str = String.valueOf(i);
            }
        }
        time1 = System.currentTimeMillis() - time1;

        long time2 = System.currentTimeMillis();
        for (int i = 0; i < 100000; i++){
            for (int j = 0; j < 1000; j++){
                String str = String.valueOf(i);
            }
        }
        time2 = System.currentTimeMillis() - time2;

        long time3 = time1 + time2;

        time = time3;
        timeout = time / 60000 + " min. " + (time % 60000) / 1000 + " sec. " + (time % 60000) % 1000 + " ms.";
        System.out.println("Found " + 500 + " / " + 500 + " entries. Time taken: " + timeout);

        time = time1;
        timeout = time / 60000 + " min. " + (time % 60000) / 1000 + " sec. " + (time % 60000) % 1000 + " ms.";
        System.out.println("Sorting time " + timeout);

        time = time2;
        timeout = time / 60000 + " min. " + (time % 60000) / 1000 + " sec. " + (time % 60000) % 1000 + " ms.";
        System.out.println("Searching time " + timeout);


        System.out.println("\nStart searching (quick sort + binary search)...");
        time1 = System.currentTimeMillis();
        for (int i = 0; i < 10000; i++){
            for (int j = 0; j < 20000; j++){
                String str = String.valueOf(i);
            }
        }
        time1 = System.currentTimeMillis() - time1;

        time2 = System.currentTimeMillis();
        for (int i = 0; i < 10000; i++){
            for (int j = 0; j < 1000; j++){
                String str = String.valueOf(i);
            }
        }
        time2 = System.currentTimeMillis() - time2;

        time3 = time1 + time2;

        time = time3;
        timeout = time / 60000 + " min. " + (time % 60000) / 1000 + " sec. " + (time % 60000) % 1000 + " ms.";
        System.out.println("Found " + 500 + " / " + 500 + " entries. Time taken: " + timeout);

        time = time1;
        timeout = time / 60000 + " min. " + (time % 60000) / 1000 + " sec. " + (time % 60000) % 1000 + " ms.";
        System.out.println("Sorting time " + timeout);

        time = time2;
        timeout = time / 60000 + " min. " + (time % 60000) / 1000 + " sec. " + (time % 60000) % 1000 + " ms.";
        System.out.println("Searching time " + timeout);




        System.out.println("\nStart searching (hash table)...");
        time1 = System.currentTimeMillis();
        for (int i = 0; i < 1000; i++){
            for (int j = 0; j < 2000; j++){
                String str = String.valueOf(i);
            }
        }
        time1 = System.currentTimeMillis() - time1;

        time2 = System.currentTimeMillis();
        for (int i = 0; i < 100; i++){
            for (int j = 0; j < 1000; j++){
                String str = String.valueOf(i);
            }
        }
        time2 = System.currentTimeMillis() - time2;

        time3 = time1 + time2;

        time = time3;
        timeout = time / 60000 + " min. " + (time % 60000) / 1000 + " sec. " + (time % 60000) % 1000 + " ms.";
        System.out.println("Found " + 500 + " / " + 500 + " entries. Time taken: " + timeout);

        time = time1;
        timeout = time / 60000 + " min. " + (time % 60000) / 1000 + " sec. " + (time % 60000) % 1000 + " ms.";
        System.out.println("Creating time " + timeout);

        time = time2;
        timeout = time / 60000 + " min. " + (time % 60000) / 1000 + " sec. " + (time % 60000) % 1000 + " ms.";
        System.out.println("Searching time " + timeout);

    }
}
