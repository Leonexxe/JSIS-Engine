import java.util.ArrayList;
import java.util.List;

public class main {
    static void exec()
    {
        for(int I=0;I<1000000;I++)
        {
            System.out.print('A');
        }
        System.out.print('B');
        System.out.print('\n');
    }
    public static void main(String[] args)
    {
        List<Long> times = new ArrayList<Long>();
        int runs = 100;
        for(int I = 0;I<runs;I++)
        {
            long startTime = System.currentTimeMillis();
            exec();
            long stopTime = System.currentTimeMillis();
            System.out.println(stopTime - startTime);
            times.add(stopTime - startTime);
        }
        int total = 0;
        for(Long I : times)
        {
            total+=I;
        }
        total/=runs;
        System.out.println("time elapsed: "+total);
    }
}