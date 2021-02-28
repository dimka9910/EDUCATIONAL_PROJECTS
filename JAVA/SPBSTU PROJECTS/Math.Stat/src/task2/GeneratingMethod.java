package task2;

public interface GeneratingMethod {
    int generate(double a, double b);

    default double gaussrand(double mo, double sko){
        double sum = 0.0;
        double x;
        for (int i = 0; i < 28; i++){
            sum += Math.random();
        }
        return (Math.sqrt(2.0) * sko * (sum - 14.)) / 2.11233 + mo;
    }
}

class rnnorm implements GeneratingMethod {
    @Override
    public int generate(double a_, double p) {
        int n = (int)Math.round(a_);
        if (n>=100){
            return (int)Math.round(gaussrand(n * p, Math.sqrt(n * p * (1.0 -p))) + 0.5);
        } else {
            double a = Math.random();
            double temp = Math.pow(1 - p, n);
            int m = 0;
            while (a - temp >= 0){
                a -= temp;
                temp *= ((p*(n - m)) / ((m+1) * (1 - p)));
                m++;
            }
            return m;
        }
    }
}

class irngeo1 implements GeneratingMethod {
    @Override
    public int generate(double p, double b_) {
        double a = Math.random();
        double temp = p;
        int m = 0;
        while (a - temp >= 0){
            a -= temp;
            temp *= (1 - p);
            m++;
        }
        return m + 1;
    }
}

class irngeo2 implements GeneratingMethod {
    @Override
    public int generate(double p, double b_) {
        double a = Math.random();
        int m = 0;
        while (a > p){
            a = Math.random();;
            m++;
        }
        return m + 1;
    }
}

class irngeo3 implements GeneratingMethod {
    @Override
    public int generate(double p, double b_) {
        double a = Math.random();
        return (int)(Math.log(a) / Math.log(1 - p)) + 1;
    }
}

class irnpoi implements GeneratingMethod {
    @Override
    public int generate(double mu, double b_) {
        if (mu < 88){
            double a = Math.random();
            double temp = Math.exp(-mu);
            int m = 1;
            while (a - temp >= 0){
                a -= temp;
                temp *= mu / m;
                m++;
            }
            return m;
        } else {
            return (int)Math.round(gaussrand(mu, mu));
        }
    }
}

class irnpsn implements GeneratingMethod {
    @Override
    public int generate(double mu, double b_) {
        if (mu < 88){
            double a = Math.random();
            double temp = a;
            int m = 1;
            while (temp >= Math.exp(-mu)){
                a = Math.random();
                temp *= a;
                m++;
            }
            return m;
        } else {
            return (int)Math.round(gaussrand(mu, mu));
        }
    }
}

class irnlog implements GeneratingMethod {
    @Override
    public int generate(double q, double b_) {
        double a = Math.random();
        double temp = -(1.0 / Math.log(q)) * (1 - q);
        int m = 1;
        while (a - temp >= 0){
            a -= temp;
            temp *= (m * 1.0 / (m + 1)) * (1 - q);
            m++;
        }
        return m;
    }
}

class irnuni implements GeneratingMethod {
    @Override
    public int generate(double a_, double b_) {
        int iLow = (int)Math.round(a_);
        int iUp = (int)Math.round(b_);
        return iLow - 1 + (int) (Math.random() * iUp + 1);
    }
}




