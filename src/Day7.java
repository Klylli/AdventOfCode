import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class Day7 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("/home/konstantinhauser/Documents/Advent of Code/src/Day7_input");
        Scanner scanner = new Scanner(file);
        long sum = 0;
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] words = line.replace(":","").split(" ");
            long[] nums = new long[words.length];
            for (int i = 0; i < words.length; i++) {
                nums[i] = Long.parseLong(words[i]);
            }
            if (calculate(nums) == 1){
                sum += nums[0];
            }
        }
        System.out.println(sum);
    }
    public static long[] sliceArray(long[] array, long newValue) {
        if (array.length == 1) {
            return array;
        }
        long[] result = new long[array.length - 1];
        result[0] = array[0];
        result[1] = newValue;
        System.arraycopy(array, 3, result, 2, result.length - 2);
        return result;
    }
    public static long calculate(long[] nums) {
        if (nums[0] == nums[1] && nums.length == 2) {
            return 1;
        }
        if (nums[0] != nums[1] && nums.length == 2) {
            return 0;
        }
        if (nums[0] < nums[1]) {
            return 0;
        }
        long[] sum_op = sliceArray(nums, nums[1] + nums[2]);
        long[] mul_op = sliceArray(nums, nums[1] * nums[2]);
        long[] concat_op = sliceArray(nums, Long.parseLong(nums[1] +Long.toString(nums[2])));
        if (calculate(sum_op) == 1) return 1;
        if(calculate(mul_op) == 1) return 1;
        if (calculate(concat_op) == 1) return 1;
        return 0;
    }

}
