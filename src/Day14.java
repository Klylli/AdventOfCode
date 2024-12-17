import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Day14 {
    static int cnt = 103*101;

    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("src/Day14_input");
        Scanner scanner = new Scanner(file);
        int height = 103;
        int width = 101;
        int upper_left = 0;
        int upper_right = 0;
        int lower_left = 0;
        int lower_right = 0;
        char[][][] fields = new char[cnt + 1][height][width];
        coords[][] pos = new coords[500][width*height];
        for (int i = 0; i < fields.length; i++) {
            for (int j = 0; j < fields[i].length; j++) {
                Arrays.fill(fields[i][j], '.');
            }
        }
        int counter = 0;
        while (scanner.hasNextLine()) {
            char[][] field = new char[height][width];
            String line = scanner.nextLine();
            String[] tokens = line.split(" ");
            String[] positions = tokens[0].split(",");
            String[] velocities = tokens[1].split(",");
            int x = Integer.parseInt(positions[0].substring(2));
            int y = Integer.parseInt(positions[1]);
            int x_vel = Integer.parseInt(velocities[0].substring(2));
            int y_vel = Integer.parseInt(velocities[1]);
            //int[] end_positions = calcEndPosition(x,y,x_vel,y_vel,width, height, 0, fields);
            int [] end_positions = {x,y};

            for (int i = 0; i < width*height; i++) {
                fields[i][end_positions[1]][end_positions[0]] = '*';
                end_positions[0] = ((end_positions[0] + x_vel) % width + width) % width;
                end_positions[1] = ((end_positions[1] + y_vel) % height + height) % height;
                pos[counter][i] = new coords(end_positions[0], end_positions[1]);
            }
            int end_x = end_positions[0];
            int end_y = end_positions[1];
            //System.out.println(end_x + " " + end_y);
            if (end_x < width/2 && end_y < height/2) {
                upper_left++;
            } else if (end_x < width/2 && end_y > height/2) {
                lower_left++;
            } else if (end_x > width/2 && end_y < height/2) {
                upper_right++;
            } else if (end_x > width/2 && end_y > height/2) {
                lower_right++;
            }
            counter++;
        }

        for (int i = 0; i < width*height; i++) {
            boolean unique = true;
            HashSet<coords> set = new HashSet<>();
            for (int j = 0; j < pos.length; j++) {
                if (set.contains(pos[j][i])) {
                    unique = false;
                    break;
                }
                set.add(pos[j][i]);
            }
            if (unique) {
                System.out.println(i + 1);
                printArray(fields[i + 1]);
            }
        }
        //System.out.println(cnt);
        System.out.println(upper_right*upper_left*lower_left*lower_right);
        scanner.close();
    }

    private static void printArray(char[][] field) {
        for (int i = 0; i < field.length; i++) {
            for (int j = 0; j < field[i].length; j++) {
                System.out.print(field[i][j]);
            }
            System.out.println();
        }
    }

    private static int[] calcEndPosition(int x, int y, int xVel, int yVel, int width, int height, int i, char[][][] fields) {
        fields[i][y][x] = '*';
        if (i == cnt) {
            return new int[]{x, y};
        }
        int new_x = ((x + xVel) % width + width) % width;
        int new_y = ((y + yVel) % height + height) % height;
        return calcEndPosition(new_x,new_y,xVel,yVel,width,height,i + 1, fields);
    }
}
class coords{
    int x;
    int y;
    public coords(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        coords coords = (coords) o;
        return x == coords.x && y == coords.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }
}
