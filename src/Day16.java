import java.io.File;
import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.*;

public class Day16 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("src/Day16_input");
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
        int start_x = 0, start_y = 0;
        HashSet<node> seen = new HashSet<>();
        for (int i = 0; i < map.length; i++) {
            for (int j = 0; j < map[i].length; j++) {
                if (map[i][j] == 'S') {
                    start_x = j;
                    start_y = i;
                }
            }
        }
        PriorityQueue<node> q = new PriorityQueue<>((o1, o2) -> {
            if (o1.distance < o2.distance) {
                return -1;
            } else if (o1.distance > o2.distance) {
                return 1;
            }
            return 0;
        });
        q.add(new node(start_x,start_y,0,0,1, new ArrayList<>()));
        int lowest_cost = Integer.MAX_VALUE;
        int sum = 0;
        HashSet<node> best_tiles = new HashSet<>();
        while(!q.isEmpty()) {
            node curr = q.poll();
            seen.add(curr);
            if (map[curr.y][curr.x] == 'E') {
                if (curr.distance > lowest_cost) {
                    break;
                }
                lowest_cost = (int) curr.distance;
                System.out.println(curr.distance);
                best_tiles.addAll(curr.path);
            }
            int new_y = curr.y + curr.dr;
            int new_x = curr.x + curr.dc;
            ArrayList<node> new_list = (ArrayList<node>) curr.path.clone();
            new_list.add(curr);
            if (map[new_y][new_x] != '#' && !seen.contains(new node(new_x,new_y,curr.distance + 1, curr.dr, curr.dc, (ArrayList<node>) new_list.clone())))
                q.add(new node(new_x,new_y,curr.distance + 1, curr.dr, curr.dc, (ArrayList<node>) new_list.clone()));
            new_y = curr.y - curr.dc;
            new_x = curr.x + curr.dr;
            if(map[new_y][new_x] != '#' && !seen.contains(new node(new_x,new_y,curr.distance + 1001, -curr.dc, curr.dr, (ArrayList<node>) new_list.clone())))
                q.add(new node(new_x,new_y,curr.distance + 1001, -curr.dc, curr.dr, (ArrayList<node>) new_list.clone()));
            new_y = curr.y + curr.dc;
            new_x = curr.x - curr.dr;
            if(map[new_y][new_x] != '#' && !seen.contains(new node(new_x, new_y, curr.distance + 1001, curr.dc, -curr.dr, (ArrayList<node>) new_list.clone())))
                q.add(new node(new_x, new_y, curr.distance + 1001, curr.dc, -curr.dr, (ArrayList<node>) new_list.clone()));
        }
        System.out.println(best_tiles.size());
        node[] nodes = (node[]) best_tiles.toArray(new node[best_tiles.size()]);
        for (int i = 0; i < best_tiles.size(); i++) {
            node curr = nodes[i];
            if (map[curr.y][curr.x] != 'O') sum++;
            map[curr.y][curr.x] = 'O';
        }
        for (int i = 0; i < map.length; i++) {
            for (int j = 0; j < map[i].length; j++) {
                System.out.print(map[i][j]);
            }
            System.out.println();
        }
        System.out.println(sum + 1);
    }
}

class node{
    int x, y;
    long distance;
    int dr, dc;
    ArrayList<node> path = new ArrayList<>();
    public node(int x, int y, long distance, int dr, int dc, ArrayList<node> path) {
        this.x = x;
        this.y = y;
        this.distance = distance;
        this.dr = dr;
        this.dc = dc;
        this.path = path;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        node node = (node) o;
        return x == node.x && y == node.y && dr == node.dr && dc == node.dc;
    }

    @Override
    public int hashCode() {
        return 141*141*y + 3*x + dr + dc;
    }
}            System.out.println(curr.y + " " + curr.x);
