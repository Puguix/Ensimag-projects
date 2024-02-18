package org.ensimag;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import org.springframework.stereotype.Service;

import lombok.Data;

import static org.ensimag.RouletteBet.BLACK_INTEGERS;
import static org.ensimag.RouletteBet.RED_INTEGERS;

@Data
@Service
public class RouletteService {

    /**
     * Method called by endpoint in RouletteController, params given in request body.
     * @param rouletteBetList list of the player's bets (types, values and amounts).
     * @return a list of 2 Integers: the final position of the roulette (random), and the player's payoff.
     */
    public List<Integer> getResults(List<RouletteBet> rouletteBetList) {
        List<Integer> result = new ArrayList<>();
        int position = new Random().nextInt(37);
        int payOff = 0;
        for (RouletteBet rouletteBet:rouletteBetList){
            //payOff += rouletteBet.getPayOff(position);
            payOff += getPayOff(rouletteBet, position);
        }
        result.add(position);
        result.add(payOff);
        return result;
    }

    /**
     * Calculates the payoff of a certain bet, depending on the type of bet.
     * @param roulette a single bet (type, value, amount)
     * @param result i.e. the roulette's position after spin.
     * @return the player's payOff.
     */
    public int getPayOff(RouletteBet roulette, int result){
        switch (roulette.getType()) {
            case "inside" -> {
                return getPayOffInside(roulette, result);
            }
            case "column" -> {
                return getPayOffColumn(roulette, result);
            }
            case "dozen" -> {
                return getPayOffDozen(roulette, result);
            }
            case "blackRed" -> {
                return getPayOffColors(roulette, result);
            }
            case "oddEven" -> {
                return getPayOffOddEven(roulette, result);
            }
            case "lowHigh" -> {
                return getPayOffHighLow(roulette, result);
            }
            default -> {
                throw new RuntimeException("Bet type is incorrect");
            }
        }
    }

    /**
     * For inside bet
     * @param roulette play's bet
     * @param result roulette's position after spin
     * @return corresponding payoff.
     */
    public int getPayOffInside(RouletteBet roulette, int result){
        for (int i = 0; i<roulette.getValue().size(); i++){
            if ((result == roulette.getValue().get(i)))
                return roulette.getAmount() * 36 / roulette.getValue().size();
        }
        return 0;
    }

    /**
     * For column bet
     * @param roulette play's bet
     * @param result roulette's position after spin
     * @return corresponding payoff.
     */
    public int getPayOffColumn(RouletteBet roulette, int result){
        if (result == 0) return 0;
        if ((result % 3 == roulette.getValue().get(0)))
            return roulette.getAmount() * 3;
        return 0;
    }

    /**
     * For dozen bet
     * @param roulette play's bet
     * @param result roulette's position after spin
     * @return corresponding payoff.
     */
    public int getPayOffDozen(RouletteBet roulette, int result){
        if (result == 0) return 0;
        if ((result - 1) / 12 == roulette.getValue().get(0)) return roulette.getAmount() * 3;
        return 0;
    }

    /**
     * For high/low bet
     * @param roulette play's bet
     * @param result roulette's position after spin
     * @return corresponding payoff.
     */
    public int getPayOffHighLow(RouletteBet roulette, int result){
        if (result == 0) return 0;
        if ((result-1) / 18 == roulette.getValue().get(0)) return roulette.getAmount() * 2;
        return 0;
    }

    /**
     * For even/odd bet
     * @param roulette play's bet
     * @param result roulette's position after spin
     * @return corresponding payoff.
     */
    public int getPayOffOddEven(RouletteBet roulette, int result){
        if (result == 0) return 0;
        if (result % 2 == roulette.getValue().get(0)) return roulette.getAmount() * 2;
        return 0;
    }

    /**
     * For color bet
     * @param roulette play's bet
     * @param result roulette's position after spin
     * @return corresponding payoff.
     */
    public int getPayOffColors(RouletteBet roulette, int result){
        if (result == 0) return 0;
        if (roulette.getValue().get(0) == 0){
            for (Integer redInteger : RED_INTEGERS) {
                if (result == redInteger) return roulette.getAmount() * 2;
            }
        }
        if (roulette.getValue().get(0) == 1){
            for (Integer blackInteger : BLACK_INTEGERS) {
                if (result == blackInteger) return roulette.getAmount() * 2;
            }
        }
        return 0;
    }

}