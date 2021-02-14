package encryptdecrypt;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

public class Program {
    private EncDecMethod method;

    private String type;
    private String str;
    private int move;

    public void setMethod(EncDecMethod method) {
        this.method = method;
    }

    public Program(String type, String str, int move) {
        this.type = type;
        this.str = str;
        this.move = move;
    }

    public String start() {
        switch (type) {
            case "dec":
                return decryption();
            case "enc":
            default:
                return encryption();
        }
    }

    public String decryption() {
        String outStr = "";
        char[] ch = str.toCharArray();
        for (char c : ch) {
            outStr += method.decryption(c, move);
        }
        return outStr;
    }

    public String encryption() {
        String outStr = "";
        char[] ch = str.toCharArray();
        for (char c : ch) {
            outStr += method.encryption(c, move);
        }
        return outStr;
    }
}
