package org.ensimag;

import lombok.Data;

import java.util.Arrays;
import java.util.List;

@Data
public class RouletteBetdto {

    public static final List<Integer> RED_INTEGERS = Arrays.asList(1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36);
    public static final List<Integer> BLACK_INTEGERS = Arrays.asList(2,4,6,8,10,11,13,15,17,20,22,24,28,29,31,33,35);

    public String type;
    public int amount;
    public List<Integer> value;

}

