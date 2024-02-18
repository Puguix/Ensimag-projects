package org.ensimag;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import java.util.Map;
import org.springframework.web.bind.annotation.*;





import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

@CrossOrigin(origins = "http://localhost:3000")
@RestController
public class ChipsController {



    @Autowired
    private ChipsService chipsService;

    /**
     * Method called from frontend to know the price of the chips they want to buy in the specified currency.
     *
     * @param chipsConversion parameters of conversion (currency and number of chips), from frontend
     * @return result double: the price in the currency asked for the number of chips
     */
    @PostMapping(path = "/getPrice", consumes = MediaType.APPLICATION_JSON_VALUE, produces = MediaType.APPLICATION_JSON_VALUE)
    public double getPrice(@RequestBody ChipsConversion chipsConversion) {
        try {
            double result = chipsService.getConversion(chipsConversion);
            return result;
        } catch (UnsupportedOperationException e) {
            throw e;
        }
    }

    /**
     * Method called from frontend to know the price of one chip in all currencies
     *
     * @return result List<double>: the price off one chip in all currencies
     */
    @GetMapping(path = "/getAllPrices", consumes = MediaType.APPLICATION_JSON_VALUE, produces = MediaType.APPLICATION_JSON_VALUE)
    public Map<String, Double> getAllPrices() {
        try {
            Map<String, Double> result = chipsService.getAllConversionRate();
            return result;
        } catch (UnsupportedOperationException e) {
            
            throw e;
        }
    }


}