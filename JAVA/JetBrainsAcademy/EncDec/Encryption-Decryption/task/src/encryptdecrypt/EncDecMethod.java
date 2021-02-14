package encryptdecrypt;

interface EncDecMethod {
    public char decryption(char c, int move);
    public char encryption(char c, int move);
}

class UnicodeEncDecMethod implements EncDecMethod{
    public char decryption(char c, int move) {
        return ((char) (c - move));
    }

    public char encryption(char c, int move) {
        return ((char) (c + move));
    }
}

class ShiftEncDecMethod implements EncDecMethod{
    private boolean isSmallLetter(char c){
        return  (c <= 'z' && c >= 'a');
    }

    private boolean isBigLetter(char c){
        return  (c <= 'Z' && c >= 'A');
    }

    public char decryption(char c, int move) {
        if (isSmallLetter(c)){
            return (char)(c - move >= 'a' ? c - move : c - move + 'z' - 'a' + 1);
        }

        if (isBigLetter(c)){
            return (char)(c - move >= 'A' ? c - move : c - move + 'Z' - 'A' + 1);
        }
        return c;
    }

    public char encryption(char c, int move) {
        if (isSmallLetter(c)){
            return (char)(c + move > 'z' ? c + move -'z' + 'a' - 1 : c + move);
        }

        if (isBigLetter(c)){
            return (char)(c + move > 'Z' ? c + move -'Z' + 'A' - 1 : c + move);
        }
        return c;
    }
}