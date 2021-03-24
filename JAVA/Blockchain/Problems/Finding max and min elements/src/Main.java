import java.util.*;
import java.util.function.*;
import java.util.stream.*;


class MinMax {

    public static <T> void findMinMax(
            Stream<? extends T> stream,
            Comparator<? super T> order,
            BiConsumer<? super T, ? super T> minMaxConsumer) {


        var v = stream.collect(Collectors.toList());
        var a = v.stream().min(order).orElse(null);
        var b = v.stream().max(order).orElse(null);

        minMaxConsumer.accept(a,b);
    }
}