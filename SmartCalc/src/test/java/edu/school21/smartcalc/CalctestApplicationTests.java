package edu.school21.smartcalc;

import edu.school21.smartcalc.model.CalculatorModel;
import edu.school21.smartcalc.model.CreditCalcModel;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class CalculatorTests {
        @Test
        void testSimpleExpressions() {
            String inputValue = "2+2";
            String xValue = null;
            String result = new CalculatorModel().calculate(inputValue, xValue);
            assertEquals("4.0", result, "Expression 2+2 should return 4.0");

            inputValue = "3^3^2+2";
            result = new CalculatorModel().calculate(inputValue, xValue);
            assertEquals("731.0", result, "Expression 3^3^2+2 should return 731.0");

            inputValue = "18/2+2.2";
            result = new CalculatorModel().calculate(inputValue, xValue);
            assertEquals("11.2", result, "Expression 18/2+2.2 should return 11.2");
        }
        @Test
        void testExpressionsWithX() {
            String inputValue = "x+x";
            String xValue = "5";
            String result = new CalculatorModel().calculate(inputValue, xValue);
            assertEquals("10.0", result, "Expression x+x with x=5 should return 10.0");

            inputValue = "sin(x)";
            xValue = "90";
            result = new CalculatorModel().calculate(inputValue, xValue);
            assertTrue(result.startsWith("0."), "Expression sin(x) with x=90 should return approximately 0");
        }

        @Test
        void testInputErrors() {
            String inputValue = "2/0";
            String xValue = null;
            String result = new CalculatorModel().calculate(inputValue, xValue);
            assertEquals("CALC ERROR", result, "Expression 2/0 should return CALC ERROR");

            inputValue = "17.344.2+1";
            result = new CalculatorModel().calculate(inputValue, xValue);
            assertEquals("INPUT ERROR", result, "Invalid input should return INPUT ERROR");

            inputValue = "";
            result = new CalculatorModel().calculate(inputValue, xValue);
            assertEquals("CALC ERROR", result, "Empty input should return CALC ERROR");
        }

        @Test
        void testCreditCalculation() {
            CreditCalcModel calculator = new CreditCalcModel();

            calculator.setAmount(100000);
            calculator.setMonths(60);
            calculator.setRate(12);
            calculator.setType(0);
            calculator.calculate();

            assertEquals(2224.44, calculator.getFirstPayment(), 0.01,
                    "First payment should be approximately 2224.44");
            assertEquals(133466.68, calculator.getTotalPayment(), 0.01,
                    "Total payment should be approximately 133466.68");

            calculator.setType(1);
            calculator.calculate();
            assertEquals(2666.67, calculator.getFirstPayment(), 0.01,
                    "First payment should be approximately 2666.67");
        }

    @Test
    void testCreditErrors() {
        CreditCalcModel calculator = new CreditCalcModel();

        calculator.setAmount(100000);
        calculator.setMonths(60);
        calculator.setRate(12);
        calculator.setType(2); // Invalid type
        calculator.calculate();

        assertEquals(0, calculator.getFirstPayment(), "Invalid type should result in zero values");
        assertEquals(0, calculator.getTotalPayment(), "Invalid type should result in zero values");
    }
}
