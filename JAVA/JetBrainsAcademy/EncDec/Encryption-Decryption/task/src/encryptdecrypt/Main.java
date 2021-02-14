package encryptdecrypt;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {

        String type = "enc";
        String str = "";
        String inFile = "";
        String outFile = "";
        String alg = "";
        int move = 0;


        //System.out.println(args[0]);
        for (int i = 0; i < args.length; i += 2) {
            switch (args[i]) {
                case "-mode":
                    type = args[i + 1];
                    break;
                case "-key":
                    move = Integer.parseInt(args[i + 1]);
                    break;
                case "-data":
                    str = args[i + 1];
                    break;
                case "-in":
                    inFile = args[i + 1];
                    File file = new File(inFile);
                    Scanner scanner = new Scanner(file);
                    str = scanner.nextLine();
                    System.out.println(str); ////////
                    scanner.close();
                    break;
                case "-out":
                    outFile = args[i + 1];
                    break;
                case "-alg":
                    alg = args[i+1];
                    break;
            }
        }

        Program program = new Program(type, str, move);

        switch (alg){
            case "unicode":
                program.setMethod(new UnicodeEncDecMethod());
                break;
            case "shift":
            default:
                program.setMethod(new ShiftEncDecMethod());
                break;
        }


        File file;
        PrintWriter printWriter = null;

        if (!outFile.equals("")) {
            file = new File(outFile);
            try {
                printWriter = new PrintWriter(file);
            } catch (IOException e){
                System.out.printf("An exception occurs %s", e.getMessage());
            }
        }

        String outStr = program.start();
        System.out.println(outStr);
        if (printWriter != null) {
            printWriter.print(outStr);
            printWriter.close();
        }
        else
            System.out.println(outStr);
    }

}
