package edu.school21.smartcalc.model;

import org.springframework.stereotype.Component;

@Component
public class CreditCalcModel {
    private double amount;
    private int months;
    private double rate;
    private int type;
    private double firstPayment;
    private double lastPayment;
    private double overpayment;
    private double totalPayment;

    public CreditCalcModel() {
    }

    public CreditCalcModel(double amount, int months, double rate, int type) {
        this.amount = amount;
        this.months = months;
        this.rate = rate;
        this.type = type;
    }


    public void setAmount(double amount) {
        this.amount = amount;
    }

    public void setMonths(int months) {
        this.months = months;
    }

    public void setRate(double rate) {
        this.rate = rate;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public double getFirstPayment() {
        return firstPayment;
    }

    public double getLastPayment() {
        return lastPayment;
    }

    public double getTotalPayment() {
        return totalPayment;
    }

    public double getOverpayment() {
        return overpayment;
    }

    public void calculate() {
        SmartCalcNative calcNative = new SmartCalcNative();
        double[] result = calcNative.calculateCredit(amount, months, rate, type);

        this.firstPayment = result[0];
        this.lastPayment = result[1];
        this.overpayment = result[2];
        this.totalPayment = result[3];
    }
}