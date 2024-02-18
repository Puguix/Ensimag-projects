package org.ensimag;

import org.springframework.context.annotation.Configuration;

@Configuration
public class BlackJackConfig {

    public static final int BLACKJACK = 21;
    public static final int MAX_VALUE_OF_DEALER_HAND = 17;
    public static final int ADDED_ACE_VALUE = 10;
    public static final int NUMBER_OF_CARDS_DEALT = 11;
    public static final double BLACKJACK_PAYOFF = 2.5;

}
