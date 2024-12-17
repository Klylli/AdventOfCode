import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigInteger;
import java.util.Scanner;


public class Day13 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("src/Day13_input");
        Scanner scanner = new Scanner(file);
        String help = "Button A: X+";
        String help2 = "Button A: X+94, Y+";
        String help3 = "Prize: X=";
        long sum = 0;
        while (scanner.hasNextLine()) {
            String buttonA = scanner.nextLine();
            String buttonB = scanner.nextLine();
            String dest = scanner.nextLine();
            scanner.nextLine();
            int button_a_x = Integer.parseInt(buttonA.substring(help.length(), help.length() + 2));
            int button_a_y = Integer.parseInt(buttonA.substring(help2.length()));
            int button_b_x = Integer.parseInt(buttonB.substring(help.length(), help.length() + 2));
            int button_b_y = Integer.parseInt(buttonB.substring(help2.length()));
            int cnt = 0;
            for (int i = 0; i < dest.length(); i++) {
                if (isDigit(dest.charAt(help3.length() + i))) {
                    cnt++;
                }else{
                    break;
                }
            }
            long dest_x = Long.parseLong(dest.substring(help3.length(), help3.length() + cnt)) + 10000000000000L;
            long dest_y = Long.parseLong(dest.substring(help3.length() + cnt +4)) + 10000000000000L;
            int determinant = button_a_x * button_b_y - button_a_y*button_b_x;
            if (determinant != 0) {
                double a = (dest_x*button_b_y - dest_y*button_b_x)*1.0/determinant;
                double b = (dest_y - a*button_a_y)/button_b_y;
                if (b == Math.floor(b) && a == Math.floor(a)) sum += (long) (3*a + b);
            }
        }
        System.out.println(sum);
        scanner.close();
    }
    public static boolean isDigit(char c) {
        return c >= '0' && c <= '9';
    }
}
