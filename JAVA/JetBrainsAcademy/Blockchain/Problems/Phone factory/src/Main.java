class TestDrive {
    public static void main(String[] args) throws InterruptedException {
        Phone phone;

        PhoneFactory iphoneFactory = new IphoneFactory();
        PhoneFactory samsungFactory = new SamsungFactory();

        System.out.println("-Hello, I need Android phone");
        System.out.println("-Okay! Please wait for a sec, " +
                "- Calling to the SamsungFactory. -Bring me the Samsung Galaxy S10");
        Thread.sleep(1500);

        phone = samsungFactory.createPhone();
        System.out.println(phone.getDescription());
        System.out.println("There it is!\n");

        System.out.println("-Hello, I need iOS phone");
        System.out.println("-Okay! Please wait for a sec, - Calling to the iPhoneFactory. -Bring me the iPhoneXS\"");
        Thread.sleep(1500);

        phone = iphoneFactory.createPhone();
        System.out.println(phone.getDescription());
        System.out.println("There it is!");
    }
}



interface Camera {
    String toString();
}

class IphoneCamera implements Camera {
    @Override
    public String toString() {
        return "12MP";
    }
}

class SamsungCamera implements Camera {
    @Override
    public String toString() {
        return "16MP+12MP+12MP";
    }
}

interface Display {
    String toString();
}

class IphoneDisplay implements Display {
    @Override
    public String toString() {
        return "5.8\" OLED";
    }
}

class SamsungDisplay implements Display {
    @Override
    public String toString() {
        return "6.1\" Dynamic AMOLED";
    }
}

interface Processor {
    String toString();
}

class IphoneProcessor implements Processor {
    @Override
    public String toString() {
        return "A12";
    }
}

class SamsungProcessor implements Processor {
    @Override
    public String toString() {
        return "Exynos 9820";
    }
}

interface Security {
    String toString();
}

class IphoneSecurity implements Security {
    @Override
    public String toString() {
        return "FaceID";
    }
}

class SamsungSecurity implements Security {
    @Override
    public String toString() {
        return "FingerPrint";
    }
}