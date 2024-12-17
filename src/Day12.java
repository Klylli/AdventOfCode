import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Day12 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("src/Day12_input");
        Scanner scanner = new Scanner(file);
        ArrayList<String> list = new ArrayList<>();
        while (scanner.hasNextLine()) {
            list.add(scanner.nextLine());
        }
        scanner.close();
        String line = "";
        char[][] map = new char[list.size()][list.getFirst().length()];
        for (int i = 0; i < list.size(); i++) {
            line += list.get(i);
            map[i] = list.get(i).toCharArray();
        }
        int count = 0;
        HashMap<Character, area_perim> dict = new HashMap<>();
        for (int i = 0; i < line.length(); i++) {
            boolean unique = true;
            for (int j = 0; j < i; j++) {
                if (line.charAt(j) == line.charAt(i)) {
                    unique = false;
                    break;
                }
            }
            if (unique) {
                dict.put(line.charAt(i), new area_perim(0, 0));
                count++;
            }
        }
        boolean[][] counted = new boolean[map.length][map[0].length];
        long sum = 0;

        char previous = '0';
        for (int i = 0; i < map.length; i++) {
            for (int j = 0; j < map[0].length; j++) {
                char current = map[i][j];
                int area = 0;
                int perim = 0;
                area_perim area_perim = dict.get(current);
                if (area_perim.area != 0 || area_perim.perim != 0 && !counted[i][j]) {
                    for (char key : dict.keySet()) {
                        area_perim value = dict.get(key);
                        if (value.area != 0 || value.perim != 0) System.out.println(key + " " + value.area + " " + value.perim);
                        sum += (long) value.area *value.perim;
                        dict.put(key, new area_perim(0,0));
                    }
                }
                area_perim = dict.get(current);
                if (current != previous && !counted[i][j]) {
                    calc_area_and_perimeter(map, counted, i, j, area_perim, current);
                    dict.put(current, area_perim);
                }
                previous = current;
            }
        }
        for (char key : dict.keySet()) {
            area_perim value = dict.get(key);
            if (value.area != 0 || value.perim != 0) System.out.println(key + " " + value.area + " " + value.perim);
            sum += (long) value.area * value.perim;
        }
        System.out.println(sum);
    }

    private static void calc_area_and_perimeter(char[][] map, boolean[][] counted, int i, int j, area_perim areaPerim, char current) {
        boolean out_of_bounds = i < 0 || i >= map.length || j < 0 || j >= map[0].length;
        if (out_of_bounds || map[i][j] != current || counted[i][j]) {
            if (out_of_bounds) areaPerim.perim += 1;
            return;
        }
        counted[i][j] = true;
        areaPerim.area += 1;
        if (i > 0 && map[i - 1][j] != current) {
            areaPerim.perim += 1;
        }
        if (j > 0 && map[i][j - 1] != current) {
            areaPerim.perim += 1;
        }
        if (j < map[0].length - 1 && map[i][j + 1] != current) {
            areaPerim.perim += 1;
        }
        if (i < map.length - 1 && map[i + 1][j] != current) {
            areaPerim.perim += 1;
        }
        calc_area_and_perimeter(map, counted, i - 1, j, areaPerim, current);
        calc_area_and_perimeter(map, counted, i + 1, j, areaPerim, current);
        calc_area_and_perimeter(map, counted, i, j - 1, areaPerim, current);
        calc_area_and_perimeter(map, counted, i, j + 1, areaPerim, current);
    }
}

class area_perim {
    int area;
    int perim;

    public area_perim(int area, int perim) {
        this.area = area;
        this.perim = perim;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        area_perim areaPerim = (area_perim) o;
        return area == areaPerim.area && perim == areaPerim.perim;
    }

    @Override
    public int hashCode() {
        return Objects.hash(area, perim);
    }
}
