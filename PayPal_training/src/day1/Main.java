package day1;

import java.util.Scanner;

/**
 *
 * @author test
 */
public class Main {
    public static void main(String args[]) {
        Scanner scan = new Scanner(System.in);
        CollatzGenerator c = new CollatzGenerator(scan.nextInt());
        while( c.hasNext() ) {
            System.out.println(c.next());
        }
    }
}
