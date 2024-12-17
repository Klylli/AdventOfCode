import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day15 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("src/Day15_input");
        Scanner scanner = new Scanner(file);
        ArrayList<String> list = new ArrayList<>();
        int cnt = 0;
        int number_of_map_lines = 0;
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            list.add(line);
            if(line.isBlank()) number_of_map_lines = cnt;
            cnt++;
        }
        scanner.close();
        char[][] map = new char[number_of_map_lines][list.getFirst().length()];


        for (int i = 0; i < number_of_map_lines; i++) {
            map[i] = list.get(i).toCharArray();
        }
        int robot_x = 0;
        int robot_y = 0;
        boolean found = false;
        for (int i = 0; i < map.length && !found; i++) {
            for (int j = 0; j < map[i].length && !found; j++) {
                if(map[i][j] == '@') {
                    robot_y = i;
                    robot_x = j;
                    found = true;
                }
            }
        }

        String inst = "";
        for (int i = number_of_map_lines + 1; i < list.size(); i++) {
            inst += list.get(i);
        }
        char[] instructions = inst.toCharArray();

        for (int i = 0; i < instructions.length; i++) {
            char dir = instructions[i];

            //printArray(map);
            //System.out.println(dir);
            if (dir == '<') {
                for (int j = robot_x - 1; j >= 0 ; j--) {
                    if (map[robot_y][j] == '#') break;
                    if (map[robot_y][j] == '.'){
                        for (int k = j + 1; k <= robot_x ; k++) {
                            map[robot_y][k - 1] = map[robot_y][k];
                        }
                        map[robot_y][robot_x] = '.';
                        robot_x--;
                        break;
                    }
                }
            } else if (dir == '^') {


                for (int j = robot_y - 1; j >= 0 ; j--) {
                    if (map[j][robot_x] == '#') break;
                    if (map[j][robot_x] == '.') {
                        for (int k = j + 1; k <= robot_y; k++) {
                            map[k - 1][robot_x] = map[k][robot_x];
                        }
                        map[robot_y][robot_x] = '.';
                        robot_y--;
                        break;
                    }
                }
            } else if (dir == '>') {
                for (int j = robot_x + 1; j < map[robot_y].length ; j++) {
                    if (map[robot_y][j] == '#') break;
                    if (map[robot_y][j] == '.'){
                        for (int k = j - 1; k >= robot_x ; k--) {
                            map[robot_y][k + 1] = map[robot_y][k];
                        }
                        map[robot_y][robot_x] = '.';
                        robot_x++;
                        break;
                    }
                }
            }else if(dir == 'v') {
                for (int j = robot_y + 1; j < map.length; j++) {
                    if (map[j][robot_x] == '#') break;
                    if (map[j][robot_x] == '.') {

                        for (int k = j - 1; k >= robot_y; k--) {
                            map[k + 1][robot_x] = map[k][robot_x];
                        }
                        map[robot_y][robot_x] = '.';
                        robot_y++;
                        break;
                    }
                }
            }
        }
        printArray(map);
        long sum_of_gps_coords = 0;
        for (int i = 0; i < map.length; i++) {
            for (int j = 0; j < map[i].length; j++) {
                if(map[i][j] == 'O') {
                    sum_of_gps_coords += 100L *i + j;
                }
            }
        }
        System.out.println(sum_of_gps_coords);
    }
    private static void printArray(char[][] field) {
        for (int i = 0; i < field.length; i++) {
            for (int j = 0; j < field[i].length; j++) {
                System.out.print(field[i][j]);
            }
            System.out.println();
        }
        System.out.println();
    }
}
