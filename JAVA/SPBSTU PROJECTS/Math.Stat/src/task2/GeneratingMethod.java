package task2;

public interface GeneratingMethod {
    int generate(double a, double b);
}

class Uniform implements GeneratingMethod {
    @Override
    public int generate(double a_, double b_) {
        int a = (int)Math.round(a_);
        int b = (int)Math.round(b_);
        return a - 1 + (int) (Math.random() * b + 1);
    }
}

class Normal implements GeneratingMethod {
    @Override
    public int generate(double a_, double b_) {
        int a = (int)Math.round(a_);
        int b = (int)Math.round(b_);
        return a - 1 + (int) (Math.random() * b + 1);
    }
}

