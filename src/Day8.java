import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day8 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("/home/konstantinhauser/Documents/Advent of Code/src/Day8_input");
        Scanner scanner = new Scanner(file);
        ArrayList<String> list = new ArrayList<>();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            list.add(line);
        }
        scanner.close();
        String[] map = list.toArray(new String[list.size()]);
        char[][] arr = new char[map.length][];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = map[i].toCharArray();
        }
        long sum = 0;
        boolean[][] visited = new boolean[arr.length][arr[0].length];
        for (int i = 0; i < arr.length-1; i++) {
            for (int j = 0; j < arr[i].length; j++) {
                char c = arr[i][j];
                if (c != '.'){
                    for (int k = i+1; k < arr.length; k++) {
                        for (int l = 0; l < arr[i].length; l++) {
                            char c2 = arr[k][l];
                            if (c == c2){
                                int height_diff = k - i;
                                int width_diff = l - j;
                                for (int m = 0; m < Math.max(arr.length, arr[0].length); m++) {
                                    check(visited,i - m*height_diff, j - m*width_diff);
                                    check(visited,k + m*height_diff, l + m*width_diff);
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[i].length; j++) {
                if (visited[i][j]){
                    sum++;
                }
            }
        }
        System.out.println(sum);
    }
    public static void check(boolean[][] visited, int i, int j){
        if (i >= 0 && i <= visited.length-1 && j >= 0 && j <= visited[0].length-1){
            if (!visited[i][j]){
                visited[i][j] = true;
                System.out.println(i + " " + j);
            }
        }
    }

}
