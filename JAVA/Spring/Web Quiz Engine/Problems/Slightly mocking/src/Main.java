class Calculator {
    private CalculatorEngine engine;

    public Calculator(CalculatorEngine engine) {
        this.engine = engine;
    }

    public String divide(int a, int b) {
        try {
            return "Division of " + a + " by " + b + " = " + engine.divide(a, b);
        } catch (Exception e){
            return "Division by zero is prohibited";
        }
        // Implement me using engine field
    }
}