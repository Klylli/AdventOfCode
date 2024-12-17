import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.io.File;
import java.util.Scanner;

public class Day1 {
    public static void main2(String[] args) throws FileNotFoundException {
        PriorityQueue<Integer> pq_left = new PriorityQueue<>();
        PriorityQueue<Integer> pq_right = new PriorityQueue<>();
        File file = new File("src/Day1_input");
        Scanner scanner = new Scanner(file);
        while(scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] tokens = line.split(" ");
            pq_left.add(Integer.parseInt(tokens[0]));
            pq_right.add(Integer.parseInt(tokens[tokens.length-1]));
        }
        long diff = 0;
        while(!pq_left.isEmpty()){
            int i = pq_left.remove();
            int j = pq_right.remove();
            diff += Math.abs(i - j);
        }
        System.out.println(diff);
        scanner.close();
    }

    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("/home/konstantinhauser/IdeaProjects/Advent of Code 2024/src/Day1_input");
        Scanner scanner = new Scanner(file);
        HashMap<Integer, Integer> map = new HashMap<>();
        ArrayList<Integer> list = new ArrayList<>();
        while(scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] tokens = line.split(" ");
            list.add(Integer.parseInt(tokens[0]));
            int key = Integer.parseInt(tokens[tokens.length-1]);
            map.put(key, 1 + map.getOrDefault(key, 0));
        }
        long similarity_score = 0;
        for (int i = 0; i < list.size(); i++) {
            if (map.containsKey(list.get(i))) {
                similarity_score += (long) map.get(list.get(i)) * list.get(i);
            }
        }
        System.out.println(similarity_score);
        scanner.close();
    }

}
