import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day3 {
    public static boolean isDigit(char c){
        return c - '0' >= 0 && c - '0' <= 9;
    }
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("src/Day3_input");
        Scanner scanner = new Scanner(file);
        long sum = 0;
        boolean enable = true;
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String min_len = "mul(2,3)";


            for (int i = 0; i < line.length(); i++) {
                if (line.length() - i < min_len.length()) {
                    break;
                }


                if(line.charAt(i) == 'd' && line.charAt(i + 1) == 'o' && line.charAt(i + 2) == 'n'
                && line.charAt(i + 3) == '\'' && line.charAt(i + 4) == 't' && line.charAt(i + 5) == '(' && line.charAt(i + 6) == ')') {
                    enable = false;
                }
                if (line.charAt(i) == 'd' && line.charAt(i+1) == 'o' && line.charAt(i+2) == '(' && line.charAt(i+3) == ')') {
                    enable = true;
                }
                if (enable && line.charAt(i) == 'm' && line.charAt(i + 1) == 'u' && line.charAt(i + 2) == 'l'
                && line.charAt(i + 3) == '(') {
                    String chopped = line.substring(i + 4);
                    if (!isDigit(chopped.charAt(0))) {
                        continue;
                    }
                    boolean next_char_after_is_comma = true;
                    int len_of_num1 = 0;
                    for (int j = 1; j < 4; j++) {
                        if (!isDigit(chopped.charAt(j))) {
                            if(chopped.charAt(j) != ','){
                                next_char_after_is_comma = false;
                            }
                            len_of_num1 = j;
                            break;
                        }
                    }
                    if (!next_char_after_is_comma) {
                        continue;
                    }
                    int num1 = Integer.parseInt(chopped.substring(0, len_of_num1));
                    String chopped2 = chopped.substring(len_of_num1 + 1);
                    if (!isDigit(chopped2.charAt(0))) {
                        continue;
                    }
                    boolean next_char_after_is_bracket = true;
                    int len_of_num2 = 0;
                    for (int j = 1; j < 4; j++) {
                        if (!isDigit(chopped2.charAt(j))) {
                            if(chopped2.charAt(j) != ')'){
                                next_char_after_is_bracket = false;
                            }
                            len_of_num2 = j;
                            break;
                        }
                    }
                    if (!next_char_after_is_bracket) {
                        continue;
                    }
                    int num2 = Integer.parseInt(chopped2.substring(0, len_of_num2));
                    sum += (long) num1 * num2;
                }
            }
        }
        System.out.println(sum);
    }
}
