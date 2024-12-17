import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Day11 {
    public static void naive_solution(long[] numbers){
        for (int i = 0; i < 75; i++) {
            System.out.println(i + 1);
            for (int j = 0; j < numbers.length; j++) {
                String c = "";
                if (numbers[j] == 0) {
                    numbers[j] = 1;
                } else if ((c = numbers[j] + "").length() % 2 == 0) {
                    long[] new_numbers = new long[numbers.length + 1];
                    for (int k = 0; k < new_numbers.length; k++) {
                        if (k == j){
                            long num1 = 0;
                            long num2 = 0;
                            int idx = 0;
                            while(numbers[j] != 0){
                                if (idx < c.length()/2) {
                                    num1 += (long) ((numbers[j] % 10)*Math.pow(10,idx));
                                    idx++;
                                }
                                else {
                                    num2 += (long) ((numbers[j] % 10)*Math.pow(10,idx-c.length()/2));
                                    idx++;
                                }
                                numbers[j] = numbers[j] / 10;
                            }
                            new_numbers[k] = num2;
                            new_numbers[k+1] = num1;
                        } else if (k > j) {
                            if (k != j + 1) new_numbers[k] = numbers[k - 1];
                        }
                        else {
                            new_numbers[k] = numbers[k];
                        }
                    }
                    numbers = new_numbers;
                    j++;
                }
                else{
                    numbers[j] *= 2024;
                }
            }
        }
        System.out.println(numbers.length);
    }
    public static long improved_solution(long number, int depth){
        if (depth == 25){
            //System.out.println(number);
            return 1;
        }
        String c = "";
        if (number == 0){
            return improved_solution(1, depth + 1);
        } else if ((c = number+"").length() % 2 == 0) {
            long num1 = 0;
            long num2 = 0;
            int idx = 0;
            while(number != 0){
                if (idx < c.length()/2) {
                    num1 += (long) ((number % 10)*Math.pow(10,idx));
                    idx++;
                }
                else {
                    num2 += (long) ((number % 10)*Math.pow(10,idx-c.length()/2));
                    idx++;
                }
                number = number / 10;
            }
            return improved_solution(num1, depth + 1) + improved_solution(num2, depth + 1);
        }
        else{
            return improved_solution(number*2024, depth + 1);
        }
    }

    public static long some_caching(long number, int depth, HashMap<numdepth, Long> cache){
        numdepth nmd = new numdepth(number, depth);
        if (cache.containsKey(nmd)){
            //System.out.println("cached");
            return cache.get(nmd);
        }
        if (depth == 75){
            return 1;
        }
        String c = "";
        if (number == 0){
            long help = some_caching(1, depth + 1, cache);
            cache.put(nmd, help);
            return help;
        } else if ((c = number+"").length() % 2 == 0) {
            long num1 = 0;
            long num2 = 0;
            int idx = 0;
            while(number != 0){
                if (idx < c.length()/2) {
                    num1 += (long) ((number % 10)*Math.pow(10,idx));
                    idx++;
                }
                else {
                    num2 += (long) ((number % 10)*Math.pow(10,idx-c.length()/2));
                    idx++;
                }
                number = number / 10;
            }
            long help = some_caching(num1, depth + 1, cache);
            if (num1 == num2){
                return 2*help;
            }
            long help2 = some_caching(num2, depth + 1, cache);
            return help + help2;
        }
        else{
            long help = some_caching(number*2024, depth + 1,cache);
           if (number >= 0 && number < 10){
                cache.put(nmd, help);
            }
            return help;
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("src/Day11_input");
        Scanner scanner = new Scanner(file);
        String line = scanner.nextLine();
        scanner.close();
        String[] nums = line.split(" ");
        long[] numbers = new long[nums.length];
        for (int i = 0; i < nums.length; i++) {
            numbers[i] = Long.parseLong(nums[i]);
        }
        long sum = 0;
        for (int i = 0; i < numbers.length; i++) {
            System.out.println(i);
            HashMap<numdepth,Long> set = new HashMap<>();
            sum += some_caching(numbers[i], 0, set);
        }
        System.out.println(sum);
    }
}
class numdepth{
    long number;
    int depth;
    public numdepth(long number, int depth) {
        this.number = number;
        this.depth = depth;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        numdepth numdepth = (numdepth) o;
        return number == numdepth.number && depth == numdepth.depth;
    }

    @Override
    public int hashCode() {
        return (int) (number*1000 + depth);
    }
}
