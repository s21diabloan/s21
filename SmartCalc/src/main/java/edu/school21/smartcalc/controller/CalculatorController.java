package edu.school21.smartcalc.controller;

import edu.school21.smartcalc.model.CalculatorModel;
import edu.school21.smartcalc.model.CreditCalcModel;
import edu.school21.smartcalc.model.HistoryModel;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/calc")
public class CalculatorController {

    private final CalculatorModel calculatorModel;
    private final HistoryModel historyModel;

    public CalculatorController(CalculatorModel calculatorModel, HistoryModel historyModel) {
        this.calculatorModel = calculatorModel;
        this.historyModel = historyModel;
    }

    @PostMapping("/calculate")
    public String calculate(@RequestParam String inputValue, @RequestParam String xValue) {
        try {
            String calcResult = calculatorModel.calculate(inputValue, xValue);
            historyModel.addRecord(inputValue);
            historyModel.saveHistoryToFile();
            return calcResult;
        } catch (IllegalArgumentException e) {
            return "Error: " + e.getMessage();
        }
    }

    @GetMapping("/history")
    public List<String> getHistory() {
        return historyModel.getHistory();
    }

    @PostMapping("/clearHistory")
    public void clearHistory() {
        historyModel.clearHistory();
    }

    @PostMapping("/credit")
    public ResponseEntity<Map<String, Double>> calculateCredit(
            @RequestParam double amount,
            @RequestParam int months,
            @RequestParam double rate,
            @RequestParam int type) {

        CreditCalcModel creditCalcModel = new CreditCalcModel(amount, months, rate, type);
        creditCalcModel.calculate();
        Map<String, Double> result = new HashMap<>();
        result.put("firstPayment", creditCalcModel.getFirstPayment());
        result.put("lastPayment", creditCalcModel.getLastPayment());
        result.put("overpayment", creditCalcModel.getOverpayment());
        result.put("total", creditCalcModel.getTotalPayment());
        return ResponseEntity.ok(result);
    }

    @PostMapping("/chart")
    public List<Map<String, Double>> generateChart(@RequestBody Map<String, String> requestData) {
        String equation = requestData.get("equation");
        List<Map<String, Double>> points = new ArrayList<>();


        double xMin = Double.parseDouble(requestData.getOrDefault("minX", "-10.0"));
        double xMax = Double.parseDouble(requestData.getOrDefault("maxX", "10.0"));
        int maxPoints = 200;
        for (double x = xMin; x <= xMax; x += (xMax - xMin) / maxPoints) {
            try {
                double y = Double.parseDouble(calculatorModel.calculate(equation, String.valueOf(x)));
                if (calculatorModel.calcRes) {
                    Map<String, Double> point = new HashMap<>();
                    point.put("x", x);
                    point.put("y", y);
                    points.add(point);
                }
            } catch (Exception e) {
                System.err.println("Failed to calculate for x = " + x + ": " + e.getMessage());
            }
        }
        historyModel.addRecord(equation);
        historyModel.saveHistoryToFile();
        return points;
    }
}