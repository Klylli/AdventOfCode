import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;
import java.io.File;

public class Day9 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("src/Day9_input");
        Scanner scanner = new Scanner(file);
        String line = "";
        while (scanner.hasNextLine()) {
            line += scanner.nextLine();
        }
        scanner.close();
        int[] nums = new int[line.length()];
        int len = 0;
        for (int i = 0; i < line.length(); i++) {
            nums[i] = line.charAt(i) - '0';
            len += nums[i];
        }
        int[] spaces = new int[nums.length];
        int[] full = new int[len];
        int idx = 0;
        int id = 0;
        for (int i = 0; i < nums.length; i++) {
            if (i % 2 == 0) {
                int num = nums[i];
                for (int j = 0; j < num; j++) {
                    full[idx++] = id;
                }
                id++;
            }
            else{
                int num = nums[i];
                for (int j = 0; j < num; j++) {
                    full[idx++] = -1;
                }

            }
        }
        int highest_id = full[full.length - 1];
        int index = nums.length - 1;
        int[] new_nums = nums.clone();
        for (int i = full.length - 1; i >= 0 && highest_id >= 0; i--) {
            if (full[i] == highest_id) {
                int amt = new_nums[index];
                index -= 2;
                for (int j = 0; j <= i - amt; j++) {
                    boolean space = true;
                    for (int k = j; k < j + amt; k++) {
                        if (full[k] != -1) {
                            space = false;
                            break;
                        }
                    }
                    if (space && amt != 0) {
                        for (int k = j; k < j + amt; k++) {
                            full[k] = highest_id;
                        }
                        for (int k = i; k > i - amt ; k--) {
                            full[k] = -1;
                        }
                        break;
                    }
                }
                highest_id--;
            }
        }
        long result = 0;
        for (int i = 0; i < full.length; i++) {
            if(full[i] != -1) result += (long) i * full[i];
        }
        System.out.println(result);
    }
}
