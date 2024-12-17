import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day5 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("src/Day5_input");
        Scanner scanner = new Scanner(file);
        boolean pages = false;
        ArrayList<instructions> instructions = new ArrayList<>();
        ArrayList<int[]> data = new ArrayList<>();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (line.isBlank()) {
                pages = true;
                continue;
            }
            if (pages) {
                String[] tokens = line.split(",");
                int[] nums = new int[tokens.length];
                for (int j = 0; j < tokens.length; j++) {
                    nums[j] = Integer.parseInt(tokens[j]);
                }
                data.add(nums);
            }
            else {
                String[] tokens = line.split("\\|");
                int num1 = Integer.parseInt(tokens[0]);
                int num2 = Integer.parseInt(tokens[1]);
                instructions.add(new instructions(num1, num2));
            }
        }
        scanner.close();
        long sum = 0;
        long incorrect_sum = 0;
        ArrayList<int[]> incorrect = new ArrayList<>();
        for (int i = 0; i < data.size(); i++) {
            int[] nums = data.get(i);
            boolean valid = true;
            for (int j = 0; j < nums.length; j++) {
                for (int k = 0; k < j; k++) {
                    for (instructions instruction : instructions) {
                        if (instruction.before == nums[j] && instruction.after == nums[k]) {
                            valid = false;
                            int h = nums[j];
                            nums[j] = nums[k];
                            nums[k] = h;
                            data.add(nums);
                        }
                        if (!valid) break;
                    }
                    if (!valid) break;
                }
                if (!valid) break;
                for (int k = j+1; k < nums.length; k++) {
                    for (instructions instruction : instructions) {
                        if (instruction.after == nums[j] && instruction.before == nums[k]) {
                            valid = false;
                            int h = nums[j];
                            nums[j] = nums[k];
                            nums[k] = h;
                            data.add(nums);
                        }
                        if (!valid) break;
                    }
                    if (!valid) break;
                }
                if (!valid) break;
            }
            if (valid) {
                sum += nums[nums.length/2];
            }
        }
        System.out.println(sum - 6242);
    }

}

class instructions{
    int before;
    int after;
    public instructions(int before, int after) {
        this.before = before;
        this.after = after;
    }
}
