package org.ensimag;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.*;

import static org.assertj.core.api.Assertions.assertThat;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
public class RouletteServiceTest {

    RouletteService rouletteService = new RouletteService();
    @Mock
    RouletteBet rouletteBet;


    @Test
    public void getPayOffInside_SingleBet_Win(){
            when(rouletteBet.getValue()).thenReturn(Collections.singletonList(5));
            when(rouletteBet.getAmount()).thenReturn(2);

            int res = rouletteService.getPayOffInside(rouletteBet, 5);

            verify(rouletteBet).getAmount();
            verify(rouletteBet, times(3)).getValue();
            assertThat(res).isEqualTo(72);
    }

    @Test
    public void getPayOffInside_SingleBet_Loss(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(5));

        int res = rouletteService.getPayOffInside(rouletteBet, 1);

        verify(rouletteBet, times(3)).getValue();
        assertThat(res).isEqualTo(0);
    }


    @Test
    public void getPayOffInside_Split_Win(){
        when(rouletteBet.getValue()).thenReturn(Arrays.asList(8, 9));
        when(rouletteBet.getAmount()).thenReturn(2);

        int res = rouletteService.getPayOffInside(rouletteBet, 9);

        verify(rouletteBet).getAmount();
        verify(rouletteBet, times(5)).getValue();
        assertThat(res).isEqualTo(36);
    }

    @Test
    public void getPayOffInside_Split_Loss(){
        when(rouletteBet.getValue()).thenReturn(Arrays.asList(8, 9));

        int res = rouletteService.getPayOffInside(rouletteBet, 5);

        verify(rouletteBet, times(5)).getValue();
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffInside_Street_Win(){
        when(rouletteBet.getValue()).thenReturn(Arrays.asList(10, 11, 12));
        when(rouletteBet.getAmount()).thenReturn(2);

        int res = rouletteService.getPayOffInside(rouletteBet, 12);

        verify(rouletteBet).getAmount();
        verify(rouletteBet, times(7)).getValue();
        assertThat(res).isEqualTo(24);
    }

    @Test
    public void getPayOffInside_Street_Loss(){
        when(rouletteBet.getValue()).thenReturn(Arrays.asList(10, 11, 12));

        int res = rouletteService.getPayOffInside(rouletteBet, 6);

        verify(rouletteBet, times(7)).getValue();
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffInside_Sixline_Win(){
        when(rouletteBet.getValue()).thenReturn(Arrays.asList(4, 5, 6, 7, 8, 9));
        when(rouletteBet.getAmount()).thenReturn(2);

        int res = rouletteService.getPayOffInside(rouletteBet, 8);

        verify(rouletteBet).getAmount();
        verify(rouletteBet, times(11)).getValue();
        assertThat(res).isEqualTo(12);
    }

    @Test
    public void getPayOffInside_Sixline_Loss(){
        when(rouletteBet.getValue()).thenReturn(Arrays.asList(4, 5, 6, 7, 8, 9));

        int res = rouletteService.getPayOffInside(rouletteBet, 10);

        verify(rouletteBet, times(13)).getValue();
        assertThat(res).isEqualTo(0);
    }


    @Test
    public void getPayOffOddEven_Even_Zero(){
        int res = rouletteService.getPayOffOddEven(rouletteBet, 0);
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffOddEven_Even_Win(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(0));
        when (rouletteBet.getAmount()).thenReturn(2);
        int res = rouletteService.getPayOffOddEven(rouletteBet, 10);
        assertThat(res).isEqualTo(4);
    }

    @Test
    public void getPayOffOddEven_Even_Loss(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(0));
        int res = rouletteService.getPayOffOddEven(rouletteBet, 9);
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffOddEven_Odd_Win(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(1));
        when (rouletteBet.getAmount()).thenReturn(2);
        int res = rouletteService.getPayOffOddEven(rouletteBet, 11);
        assertThat(res).isEqualTo(4);
    }

    @Test
    public void getPayOffOddEven_Odd_Loss(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(1));
        int res = rouletteService.getPayOffOddEven(rouletteBet, 8);
        assertThat(res).isEqualTo(0);
    }


    @Test
    public void getPayOffColumn_Win(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(2));
        when (rouletteBet.getAmount()).thenReturn(2);
        int res = rouletteService.getPayOffColumn(rouletteBet, 8);
        assertThat(res).isEqualTo(6);
    }

    @Test
    public void getPayOffColumn_Zero(){
        int res = rouletteService.getPayOffColumn(rouletteBet, 0);
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffColumn_Loss(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(2));
        int res = rouletteService.getPayOffColumn(rouletteBet, 5);
        assertThat(res).isEqualTo(0);
    }


    @Test
    public void getPayOffDozen_Zero(){
        int res = rouletteService.getPayOffDozen(rouletteBet, 0);
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffDozen_Loss(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(2));
        int res = rouletteService.getPayOffDozen(rouletteBet, 4);
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffDozen_Win(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(1));
        when (rouletteBet.getAmount()).thenReturn(2);
        int res = rouletteService.getPayOffDozen(rouletteBet, 21);
        assertThat(res).isEqualTo(6);
    }

    @Test
    public void getPayOffHighLow_Zero(){
        int res = rouletteService.getPayOffHighLow(rouletteBet, 0);
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffHighLow_High_Win(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(1));
        when (rouletteBet.getAmount()).thenReturn(2);
        int res = rouletteService.getPayOffHighLow(rouletteBet, 26);
        assertThat(res).isEqualTo(4);
    }

    @Test
    public void getPayOffHighLow_Low_Win(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(0));
        when (rouletteBet.getAmount()).thenReturn(2);
        int res = rouletteService.getPayOffHighLow(rouletteBet, 15);
        assertThat(res).isEqualTo(4);
    }

    @Test
    public void getPayOffHighLow_High_Loss(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(1));
        int res = rouletteService.getPayOffHighLow(rouletteBet, 13);
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffHighLow_Low_Loss(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(0));
        int res = rouletteService.getPayOffHighLow(rouletteBet, 23);
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffColors_Zero(){
        int res = rouletteService.getPayOffColors(rouletteBet, 0);
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffColors_Red_Win(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(0));
        when (rouletteBet.getAmount()).thenReturn(2);
        int res = rouletteService.getPayOffColors(rouletteBet, 12);
        assertThat(res).isEqualTo(4);
    }

    @Test
    public void getPayOffColors_Black_Win(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(1));
        when (rouletteBet.getAmount()).thenReturn(2);
        int res = rouletteService.getPayOffColors(rouletteBet, 17);
        assertThat(res).isEqualTo(4);
    }

    @Test
    public void getPayOffColors_Red_Loss(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(0));
        int res = rouletteService.getPayOffColors(rouletteBet, 17);
        assertThat(res).isEqualTo(0);
    }

    @Test
    public void getPayOffColors_Black_Loss(){
        when(rouletteBet.getValue()).thenReturn(Collections.singletonList(1));
        int res = rouletteService.getPayOffColors(rouletteBet, 12);
        assertThat(res).isEqualTo(0);
    }



    @Test
    public void getPayOffTest_Inside(){
        when(rouletteBet.getType()).thenReturn("inside");
        RouletteService rouletteService1 = Mockito.spy(rouletteService);
        Mockito.doReturn(0).when(rouletteService1).getPayOffInside(rouletteBet, 5);
        rouletteService1.getPayOff(rouletteBet, 5);
        verify(rouletteService1).getPayOffInside(rouletteBet, 5);
    }

    @Test
    public void getPayOffTest_Column(){
        when(rouletteBet.getType()).thenReturn("column");
        RouletteService rouletteService1 = Mockito.spy(rouletteService);
        Mockito.doReturn(0).when(rouletteService1).getPayOffColumn(rouletteBet, 5);
        rouletteService1.getPayOff(rouletteBet, 5);
        verify(rouletteService1).getPayOffColumn(rouletteBet, 5);
    }



    @Test
    public void getResultsTest_2Bets_2Loss(){
        RouletteBet rouletteBet1 = mock(RouletteBet.class);
        RouletteBet rouletteBet2 = mock(RouletteBet.class);
        List<RouletteBet> rouletteBetList = new ArrayList<>();
        rouletteBetList.add(rouletteBet1);
        rouletteBetList.add(rouletteBet2);
        RouletteService rouletteService1 = Mockito.spy(rouletteService);

        Mockito.doReturn(0).when(rouletteService1).getPayOff(any(RouletteBet.class), anyInt());

        List<Integer> res = rouletteService1.getResults(rouletteBetList);
        assertThat(res.get(0)).isNotNegative();
        assertThat(res.get(1)).isEqualTo(0);
    }


    @Test
    public void getResultsTest_4Bets_2Loss2Win(){
        RouletteBet rouletteBet1 = mock(RouletteBet.class);
        RouletteBet rouletteBet2 = mock(RouletteBet.class);
        RouletteBet rouletteBet3 = mock(RouletteBet.class);
        RouletteBet rouletteBet4 = mock(RouletteBet.class);
        List<RouletteBet> rouletteBetList = new ArrayList<>();
        rouletteBetList.add(rouletteBet1);
        rouletteBetList.add(rouletteBet2);
        rouletteBetList.add(rouletteBet3);
        rouletteBetList.add(rouletteBet4);
        RouletteService rouletteService1 = Mockito.spy(rouletteService);

        Mockito.doReturn(0).when(rouletteService1).getPayOff(eq(rouletteBet1), anyInt());
        Mockito.doReturn(6).when(rouletteService1).getPayOff(eq(rouletteBet2), anyInt());
        Mockito.doReturn(0).when(rouletteService1).getPayOff(eq(rouletteBet3), anyInt());
        Mockito.doReturn(34).when(rouletteService1).getPayOff(eq(rouletteBet4), anyInt());

        List<Integer> res = rouletteService1.getResults(rouletteBetList);
        assertThat(res.get(0)).isNotNegative();
        assertThat(res.get(1)).isEqualTo(40);
    }

}
