package edu.school21.smartcalc.app;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication(scanBasePackages = "edu.school21.smartcalc")
public class CalcTestApplication {

    public static void main(String[] args) {
        SpringApplication.run(CalcTestApplication.class, args);
    }
}