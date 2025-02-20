package edu.school21.smartcalc.model;


import org.springframework.stereotype.Component;

@Component
public class CalculatorModel {

    public boolean calcRes = true;

    public String calculate(String inputValue, String xValue) {
        double xValueDouble = 0.0;
        String result;
        try {
            SmartCalcNative smartCalcNative = new SmartCalcNative();
            double[] answer = new double[1];
            if (xValue != null && !xValue.trim().isEmpty()) {
                try {
                    xValueDouble = Double.parseDouble(xValue);
                } catch (NumberFormatException e) {
                    xValueDouble = 0.0;
                }
            }
            int res = smartCalcNative.calc(xValueDouble, inputValue, answer);
            if (res == 0) {
                calcRes = true;
                result = Double.toString(answer[0]);
            } else if (res == 1) {
                calcRes = false;
                result = "INPUT ERROR";
            } else if (res == 2) {
                calcRes = false;
                result = "CALC ERROR";
            } else {
                result = "Unknown error occurred.";
            }
        } catch (Exception e) {
            result = "Error: " + e.getMessage();
        }
        return result;
    }
}