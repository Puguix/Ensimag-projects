package org.ensimag;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.io.IOException;
import java.util.concurrent.ScheduledExecutorService;
import java.util.Map;
import java.util.HashMap;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import lombok.Data;

@Data
public class CurrencyConversion {

    int nbChip;
    String type;

    double EUR = 1.00;
    double EURUSD = 1;
    double EURJPY = 1;
    double EURGBP = 1;
    double EURAUD = 1;
    double EURCAD = 1;
    double EURCHF = 1;

    private static final ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
    private static final int INITIAL_DELAY = 0; // Démarrer immédiatement
    private static final int PERIOD = 2; // Période de 2 heures (en heures)

    public CurrencyConversion(int nbChip, String type) {
        this.nbChip = nbChip;
        this.type = type;
        scheduler.scheduleAtFixedRate(this::updateCurrency, INITIAL_DELAY, PERIOD, TimeUnit.HOURS);
    }

    public void stopScheduler() {
        scheduler.shutdown();
    }

    public void updateCurrency() {
        String[] currencies = { "USD", "JPY", "GBP", "AUD", "CAD", "CHF" };

        for (String currency : currencies) {
            double exchangeRate = getExchangeRate("EUR", currency);
            switch (currency) {
                case "USD":
                    this.EURUSD = exchangeRate;
                    break;
                case "JPY":
                    this.EURJPY = exchangeRate;
                    break;
                case "GBP":
                    this.EURGBP = exchangeRate;
                    break;
                case "AUD":
                    this.EURAUD = exchangeRate;
                    break;
                case "CAD":
                    this.EURCAD = exchangeRate;
                    break;
                case "CHF":
                    this.EURCHF = exchangeRate;
                    break;
                default:
                    System.out.println("Conversion not possible");
            }
        }

    }

    public Map<String, Double> getAllCurrencies() {

        // Créer un dictionnaire associant chaque devise à son taux de change
        Map<String, Double> exchangeRates = new HashMap<>();
        exchangeRates.put("EUR", roundUpToTwoDecimalPlaces(EUR));
        exchangeRates.put("USD", roundUpToTwoDecimalPlaces(EURUSD));
        exchangeRates.put("JPY", roundUpToTwoDecimalPlaces(EURJPY));
        exchangeRates.put("GBP", roundUpToTwoDecimalPlaces(EURGBP));
        exchangeRates.put("AUD", roundUpToTwoDecimalPlaces(EURAUD));
        exchangeRates.put("CAD", roundUpToTwoDecimalPlaces(EURCAD));
        exchangeRates.put("CHF", roundUpToTwoDecimalPlaces(EURCHF));
        return exchangeRates;

    }

    public double getCurrency() {

        switch (this.type) {
            case "EUR":
                return roundUpToTwoDecimalPlaces(this.nbChip * 1.0);

            case "USD":
                return roundUpToTwoDecimalPlaces(this.nbChip * this.EURUSD);
            case "JPY":
                return roundUpToTwoDecimalPlaces(this.nbChip * this.EURJPY);

            case "GBP":
                return roundUpToTwoDecimalPlaces(this.nbChip * this.EURGBP);

            case "AUD":
                return roundUpToTwoDecimalPlaces(this.nbChip * this.EURAUD);

            case "CAD":
                return roundUpToTwoDecimalPlaces(this.nbChip * this.EURCAD);

            case "CHF":
                return roundUpToTwoDecimalPlaces(this.nbChip * this.EURCHF);

            default:
                throw new UnsupportedOperationException("Conversion not possible for this currency");
        }
    }

    private double roundUpToTwoDecimalPlaces(double value) {
        return Math.ceil(value * 100.0) / 100.0;
    }

    private double getExchangeRate(String fromCurrencyCode, String toCurrencyCode) {
        String CURRENT_RATE_URL = "http://currencies.apps.grandtrunk.net/getlatest/%s/%s";
        String url = String.format(CURRENT_RATE_URL, fromCurrencyCode, toCurrencyCode);

        HttpClient httpClient = HttpClient.newHttpClient();
        HttpRequest httpRequest = HttpRequest.newBuilder()
                .uri(URI.create(url))
                .build();

        try {
            HttpResponse<String> response = httpClient.send(httpRequest, HttpResponse.BodyHandlers.ofString());

            return Double.parseDouble(response.body());
        } catch (IOException | InterruptedException e) {
            throw new UnsupportedOperationException("Error conversion");
        }
    }

    public void updateParamConversion(int nbChip, String type) {

        this.type = type;
        this.nbChip = nbChip;

    }

}
