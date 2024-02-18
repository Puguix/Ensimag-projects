package org.ensimag;

import java.util.Map;

import org.springframework.stereotype.Service;

import lombok.Data;

@Data
@Service
public class ChipsService {

    private final CurrencyConversion currencyConversion;

    
    public ChipsService() {
        this.currencyConversion = new CurrencyConversion(1,"EUR");
    }


    public Double getConversion(ChipsConversion chipsConversion) {
        try {
            currencyConversion.updateParamConversion(chipsConversion.nbChip, chipsConversion.type);
            double result = currencyConversion.getCurrency();
            return result;
        } catch (UnsupportedOperationException e) {
            
            throw new UnsupportedOperationException("Error: " + e.getMessage());
        }
    }

    public Map<String, Double> getAllConversionRate() {
        try {
            Map<String, Double> result = currencyConversion.getAllCurrencies();
            return result;
        } catch (UnsupportedOperationException e) {
            
            throw new UnsupportedOperationException("Error: " + e.getMessage());
        }
    }

}