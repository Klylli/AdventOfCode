import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day10 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("/home/konstantinhauser/Documents/Advent of Code/src/Day10_input");
        Scanner scanner = new Scanner(file);
        ArrayList<String> list = new ArrayList<>();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            list.add(line);
        }
        scanner.close();
        char[][] map = new char[list.size()][list.getFirst().length()];
        for (int i = 0; i < list.size(); i++) {
            map[i] = list.get(i).toCharArray();
        }
        long sum = 0;
        for (int i = 0; i < map.length; i++) {
            for (int j = 0; j < map[i].length; j++) {
                boolean[][] visited = new boolean[map.length][map[0].length];
                char c = map[i][j];
                if (c == '0') {
                    long h = sum;
                    // part 1 sum += checkPaths(map, 0, i, j, visited);
                    //part 2
                    sum += checkPaths(map, 0 ,i,j);
                    System.out.println(sum - h);
                }
            }
        }
        System.out.println(sum);
    }

    private static long checkPaths(char[][] map, int c, int i, int j, boolean[][] visited) {
        if(i < 0 || i >= map.length || j < 0 || j >= map[i].length) {
            return 0;
        }
        if (map[i][j]-'0' != c) {
            return 0;
        }
        if (map[i][j] == '9' && c == 9 && visited[i][j]) {
            return 0;
        }
        if(map[i][j] == '9' && c == 9 && !visited[i][j]) {
            visited[i][j] = true;
            return 1;
        }
        return checkPaths(map, c+1, i-1, j, visited) + checkPaths(map, c+1, i+1, j,visited) + checkPaths(map, c+1, i, j-1, visited) + checkPaths(map, c+1, i, j+1, visited);
    }
    private static long checkPaths(char[][] map, int c, int i, int j) {
        if(i < 0 || i >= map.length || j < 0 || j >= map[i].length) {
            return 0;
        }
        if (map[i][j]-'0' != c) {
            return 0;
        }
        if(map[i][j] == '9' && c == 9) {
            return 1;
        }
        return checkPaths(map, c+1, i-1, j) + checkPaths(map, c+1, i+1, j) + checkPaths(map, c+1, i, j-1) + checkPaths(map, c+1, i, j+1);
    }
}
