/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package day1;

/**
 *
 * @author test
 */
public class FizzBuzz {
    
    static String[] LIST = {"", "FIZZ", "BUZZ", "FIZZBUZZ"};
    
    public static int indexSelector(int n) {
        int divisibleBy3 = n % 3 == 0 ? 1 : 0;
        int divisibleBy5 = n % 5 == 0 ? 1 : 0;
        
        return divisibleBy3 + 2 * divisibleBy5;
    }
    
    public static void main(String args[]) {
        final int START = 1;
        final int END = 50;
        
        for ( int i=START; i < END; i++ ) {
            LIST[0] = Integer.toString(i);
            System.out.print( LIST[indexSelector(i)] + '\t' );
        }
    }
}
