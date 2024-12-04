import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day2 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("/home/konstantinhauser/Documents/Advent of Code/src/Day2_input");
        Scanner scanner = new Scanner(file);
        int count = 0;
        ArrayList<String[]> list = new ArrayList<>();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] tokens = line.split(" ");
            if (Integer.parseInt(tokens[0]) > Integer.parseInt(tokens[1])) {
                boolean dampened = false;
                boolean safe = true;
                for (int i = 0; i < tokens.length - 1; i++) {
                    int num1 = Integer.parseInt(tokens[i]);
                    int num2 = Integer.parseInt(tokens[i + 1]);
                    if (!(num1 == num2 + 1 || num1 == num2 + 2 || num1 == num2 + 3)) {
                            safe = false;
                            list.add(tokens);
                            break;
                    }
                }
                if (safe) count++;
            } else if (Integer.parseInt(tokens[0]) < Integer.parseInt(tokens[1])) {
                boolean safe = true;

                for (int i = 0; i < tokens.length - 1; i++) {
                    int num1 = Integer.parseInt(tokens[i]);
                    int num2 = Integer.parseInt(tokens[i + 1]);
                    if (!(num1 == num2 - 1 || num1 == num2 - 2 || num1 == num2 - 3)) {
                            safe = false;
                            list.add(tokens);
                            break;
                    }
                }
                if (safe) count++;
            }
            else{
                list.add(tokens);
            }
        }
        System.out.println(list.size());
        for (String[] strings : list) {

            for (int j = 0; j < strings.length; j++) {
                String[] new_tokens = new String[strings.length - 1];
                for (int k = 0; k < new_tokens.length; k++) {
                    if (k < j) {
                        new_tokens[k] = strings[k];
                    } else {
                        new_tokens[k] = strings[k + 1];
                    }
                }
                if (Integer.parseInt(new_tokens[0]) > Integer.parseInt(new_tokens[1])) {
                    boolean safe = true;
                    for (int l = 0; l < new_tokens.length - 1; l++) {
                        int num1 = Integer.parseInt(new_tokens[l]);
                        int num2 = Integer.parseInt(new_tokens[l + 1]);
                        if (!(num1 == num2 + 1 || num1 == num2 + 2 || num1 == num2 + 3)) {
                            safe = false;
                            break;
                        }
                    }
                    if (safe) {
                        count++;
                        break;
                    }
                } else if (Integer.parseInt(new_tokens[0]) < Integer.parseInt(new_tokens[1])) {
                    boolean safe = true;
                    for (int l = 0; l < new_tokens.length - 1; l++) {
                        int num1 = Integer.parseInt(new_tokens[l]);
                        int num2 = Integer.parseInt(new_tokens[l + 1]);
                        if (!(num1 == num2 - 1 || num1 == num2 - 2 || num1 == num2 - 3)) {
                            safe = false;
                            break;
                        }
                    }
                    if (safe) {
                        count++;
                        break;
                    }
                }

            }

        }


            System.out.println(count);
            scanner.close();
        }
    }

