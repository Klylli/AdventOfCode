import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Day6 {
    public static char[][] copy(char[][] to_copy){
        char[][] copy = new char[to_copy.length][to_copy[0].length];
        for(int i = 0; i < to_copy.length; i++){
            System.arraycopy(to_copy[i], 0, copy[i], 0, to_copy[i].length);
        }
        return copy;
    }

    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("src/Day6_input");
        Scanner scanner = new Scanner(file);
        ArrayList<String> list = new ArrayList<>();
        while (scanner.hasNextLine()) {
            list.add(scanner.nextLine());
        }
        scanner.close();
        int y = 0;
        int x = 0;
        String[] map = list.toArray(new String[list.size()]);
        char[][] help = new char[map.length][map[0].length()];
        for (int i = 0; i < map.length; i++) {
            help[i] = map[i].toCharArray();
            for (int j = 0; j < map[i].length(); j++) {
                if (map[i].charAt(j) == '^') {
                    y = i;
                    x = j;
                }
            }
        }
        long num = 0;
        for (int i = 0; i < help.length; i++) {
            for (int j = 0; j < help[0].length; j++) {
                if(i!=y || j != x) {
                    char[][] h = copy(help);
                    h[i][j] = '#';
                    long cnt = 0;
                    cnt = calculatePath(h, y, x, num);
                    num += cnt;
                }
            }
        }

        System.out.println(num);

    }

    private static long calculatePath(char[][] map, int y, int x, long num) {
        HashSet<state> visited = new HashSet<>();
        char c = map[y][x];

        while (!((y == 0 && c == '^') || (y == map.length - 1 && c == 'v') || (x == 0 && c == '<') || (x == map[0].length - 1 && c == '>'))) {
            c = map[y][x];
            if (visited.contains(new state(x,y,c))){
                //System.out.println(y + " " + x + " " + c);
                return 1;
            }
            visited.add(new state(x,y,c));
            if (c == '^'){
                if (map[y - 1][x] != '#'){

                    map[y - 1][x] = '^';
                    map[y][x] = 'X';
                    y--;
                }
                else {
                    map[y][x] = '>';
                }
            } else if (c == '>') {
                if (map[y][x + 1] != '#'){

                    map[y][x + 1] = '>';
                    map[y][x] = 'X';
                    x++;
                }
                else {
                    map[y][x] = 'v';
                }
            } else if (c == 'v') {
                if (map[y + 1][x] != '#'){

                    map[y + 1][x] = 'v';
                    map[y][x] = 'X';
                    y++;
                }
                else {
                    map[y][x] = '<';
                }
            }else{
                if (map[y][x - 1] != '#'){

                    map[y][x - 1] = '<';
                    map[y][x] = 'X';
                    x--;
                }
                else {
                    map[y][x] = '^';
                }
            }
        }
        return 0;
    }
}
class state{
    int x;
    int y;
    char c;

    public state(int x, int y, char c){
        this.x = x;
        this.y = y;
        this.c = c;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        state state = (state) o;
        return x == state.x && y == state.y && c == state.c;
    }

    @Override
    public int hashCode() {
        return 1000*y + 100*x + c;
    }
}
