interface PhoneDetailsFactory {
    Camera createCamera();
    Display createDisplay();
    Processor createProcessor();
    Security createSecurity();
}

class IphoneDetailsFactory implements PhoneDetailsFactory {
    @Override
    public Camera createCamera() {
        return new IphoneCamera();/* write your code here */
    }

    @Override
    public Display createDisplay() {
        return new IphoneDisplay();/* write your code here */
    }

    @Override
    public Processor createProcessor() {
        return new IphoneProcessor();/* write your code here */
    }

    @Override
    public Security createSecurity() {
        return new IphoneSecurity();/* write your code here */
    }
}

class SamsungDetailsFactory implements PhoneDetailsFactory {
    @Override
    public Camera createCamera() {
        return new SamsungCamera();/* write your code here */
    }

    @Override
    public Display createDisplay() {
        return new SamsungDisplay();/* write your code here */
    }

    @Override
    public Processor createProcessor() {
        return new SamsungProcessor();/* write your code here */
    }

    @Override
    public Security createSecurity() {
        return new SamsungSecurity();/* write your code here */
    }
}