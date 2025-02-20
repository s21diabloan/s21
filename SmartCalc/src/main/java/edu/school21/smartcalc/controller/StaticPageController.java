package edu.school21.smartcalc.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

@Controller
@RequestMapping("/calc")
public class StaticPageController {

    @GetMapping
    public String showCalcPage() {
        return "calc/index";
    }

    @GetMapping("/credit")
    public String showCreditPage() {
        return "calc/credit";
    }

    @GetMapping("/deposit")
    public String showDepositPage() {
        return "calc/deposit";
    }
}