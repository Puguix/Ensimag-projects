//
//package org.ensimag;
//
//import static org.junit.jupiter.api.Assertions.assertEquals;
//import static org.junit.jupiter.api.Assertions.assertTrue;
//import static org.junit.jupiter.api.Assertions.assertThrows;
//import org.junit.jupiter.api.Test;
//import org.junit.jupiter.api.extension.ExtendWith;
//import org.mockito.junit.jupiter.MockitoExtension;
//
//@ExtendWith(MockitoExtension.class)
//public class ChipsServiceTest {
//
//
//    @Test
//	public void getConversionValue() throws InterruptedException {
//
//        CurrencyConversion currencyConversion = new CurrencyConversion(1,"EUR");
//        CurrencyConversion currencyConversion1 = new CurrencyConversion(1,"USD");
//        CurrencyConversion currencyConversion2 = new CurrencyConversion(1,"CHF");
//        CurrencyConversion currencyConversion3 = new CurrencyConversion(1,"CAD");
//        CurrencyConversion currencyConversion4 = new CurrencyConversion(1,"AUD");
//        CurrencyConversion currencyConversion5 = new CurrencyConversion(1,"JPY");
//        CurrencyConversion currencyConversion6 = new CurrencyConversion(1,"TRY");
//        CurrencyConversion currencyConversion7 = new CurrencyConversion(1,"GBP");
//
//        Thread.sleep(20000); //le temps que l'api charge les valeurs des taux pour les 7 classes
//
//        double resultat = currencyConversion.getCurrency();
//        double resultat1 = currencyConversion1.getCurrency();
//
//        double resultat2 = currencyConversion2.getCurrency();
//        double resultat3 = currencyConversion3.getCurrency();
//
//
//        double resultat4 = currencyConversion4.getCurrency();
//        double resultat5 = currencyConversion5.getCurrency();
//
//        double resultat7 = currencyConversion7.getCurrency();
//
//        double DELTA = 0.2;
//
//        assertEquals(1.0, resultat, DELTA);
//        assertEquals(1.07, resultat1, DELTA);
//        assertEquals(0.93, resultat2, DELTA);
//        assertEquals(1.46, resultat3, DELTA);
//        assertEquals(1.66, resultat4, DELTA);
//        assertEquals(159.43, resultat5, DELTA);
//        assertEquals(0.86, resultat7, DELTA);
//
//        UnsupportedOperationException exception = assertThrows(UnsupportedOperationException.class, () -> {
//            double resultat6 = currencyConversion6.getCurrency();
//        });
//
//        assertTrue(exception.getMessage().contains("Conversion not possible for this currency"));
//
//	}
//}