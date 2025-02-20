package edu.school21.smartcalc.model;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;

public class SmartCalcNative {
    static {
        try {
            String libName = "libsmartcalc.so";
            InputStream in = SmartCalcNative.class.getResourceAsStream("/native/" + libName);
            if (in == null) {
                throw new UnsatisfiedLinkError("Библиотека " + libName + " не найдена в ресурсах.");
            }

            File tempFile = File.createTempFile("libsmartcalc", ".so");
            tempFile.deleteOnExit();
            Files.copy(in, tempFile.toPath(), java.nio.file.StandardCopyOption.REPLACE_EXISTING);

            System.load(tempFile.getAbsolutePath());
        } catch (IOException e) {
            throw new UnsatisfiedLinkError("Ошибка при извлечении библиотеки: " + e.getMessage());
        }
    }

    public native double[] calculateCredit(double amount, int months, double rate, int type);

    public native int calc(double x, String infix, double[] answer);

    public native void calcDeposit(double principalAmount, int termMonths, double interestRate, double taxRate,
                                   int paymentFrequency, int capitalizeInterest, Transaction[] transactions,
                                   Deposit result);

    public static class Deposit {
        public double interestEarned;
        public double taxAmount;
        public double finalBalance;
    }

    public static class Transaction {
        public int period;
        public double amount;

        public Transaction(int period, double amount) {
            this.period = period;
            this.amount = amount;
        }
    }
}