import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Day4 {
    public static void puzzle1(char[][] board, long sum){
        String ref = "XMAS";
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if(board[i][j] != 'X') continue;
                boolean space_up = i + 1 - ref.length() >= 0;
                boolean space_right = j + ref.length() <= board[i].length;
                boolean space_down = i + ref.length() <= board.length;
                boolean space_left = j + 1 - ref.length() >= 0;
                if (space_up){
                    // check up
                    if (board[i-1][j] == 'M' && board[i-2][j] == 'A' && board[i-3][j] == 'S'){
                        sum++;
                    }
                }
                if(space_right){
                    //check right
                    if (board[i][j+1] == 'M' && board[i][j+2] == 'A' && board[i][j+3] == 'S'){
                        sum++;
                    }
                }
                if(space_down){
                    //check down
                    if(board[i+1][j] == 'M' && board[i+2][j] == 'A' && board[i+3][j] == 'S'){
                        sum++;
                    }
                }
                if(space_left){
                    //check left
                    if (board[i][j-1] == 'M' && board[i][j-2] == 'A' && board[i][j-3] == 'S'){
                        sum++;
                    }
                }
                if (space_up && space_left){
                    //check up left diagonal
                    if (board[i-1][j-1] == 'M' && board[i-2][j-2] == 'A' && board[i-3][j-3] == 'S'){
                        sum++;
                    }
                }
                if(space_up && space_right){
                    //check up right diagonal
                    if (board[i-1][j+1] == 'M' && board[i-2][j+2] == 'A' && board[i-3][j+3] == 'S'){
                        sum++;
                    }
                }

                if(space_down && space_right){
                    // check down right diagonal
                    if (board[i+1][j+1] == 'M' && board[i+2][j+2] == 'A' && board[i+3][j+3] == 'S'){
                        sum++;
                    }
                }
                if(space_down && space_left){
                    // check down left diagonal
                    if (board[i+1][j-1] == 'M' && board[i+2][j-2] == 'A' && board[i+3][j-3] == 'S'){
                        sum++;
                    }
                }
            }
        }
        System.out.println(sum);
    }

    public static void puzzle2(char[][] board, long sum){
        for (int i = 1; i < board.length - 1; i++) {
            for (int j = 1; j < board[i].length - 1; j++) {
                if (board[i][j] != 'A') continue;
                if (board[i-1][j-1] == 'M' && board[i+1][j+1] == 'S'){
                    if ((board[i+1][j-1] == 'M' && board[i-1][j+1] == 'S')
                    || (board[i+1][j-1] == 'S' &&board[i-1][j+1] == 'M')){
                        sum++;
                    }
                }
                if (board[i-1][j-1] == 'S' && board[i+1][j+1] == 'M'){
                    if ((board[i+1][j-1] == 'M' && board[i-1][j+1] == 'S')
                            || (board[i+1][j-1] == 'S' &&board[i-1][j+1] == 'M')){
                        sum++;
                    }
                }
            }
        }
        System.out.println(sum);
    }
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("src/Day4_input");
        Scanner scanner = new Scanner(file);
        long sum = 0;
        char[][] board;
        ArrayList<String> list = new ArrayList<>();
        while (scanner.hasNextLine()) {
            list.add(scanner.nextLine());
        }
        board = new char[list.size()][list.getFirst().length()];
        for (int i = 0; i < list.size(); i++) {
            board[i] = list.get(i).toCharArray();
        }
        puzzle1(board, sum);
        puzzle2(board, sum);

    }
}
