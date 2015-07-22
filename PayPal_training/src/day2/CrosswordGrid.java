/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package day2;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 *
 * @author test
 */
public class CrosswordGrid {
    
    static final int BLOCKED = -1;
    static final int EMPTY = 0;
    
    static int hintIndex = 1;
    
    public static boolean needsNumbering( int[][] crossword, int row, int col) {
        if ( crossword[row][col] == BLOCKED ) {
            return false;
        }
        boolean allowAcross = crossword[row][col - 1] == BLOCKED && crossword[row][col + 1] != BLOCKED;
        boolean allowDown = crossword[row - 1][col] == BLOCKED && crossword[row + 1][col] != BLOCKED;
        
        return allowAcross || allowDown;
    }
    
    public static int[][] preprocessCrossword( int[][] crossword ) {
        int rowCount = crossword.length;
        int colCount = crossword[0].length;
        
        int modifiedCrossword[][] = new int[rowCount + 2][colCount + 2];
        
        for ( int i = 0; i < rowCount + 2; i++) {
            for ( int j = 0; j < colCount + 2; j++) {
                if ( i == 0 || j == 0 || i == rowCount + 1 || j == colCount + 1 ) {
                    modifiedCrossword[i][j] = BLOCKED;
                }
                else {
                    modifiedCrossword[i][j] = crossword[i - 1][j - 1];
                }
            }
        }
        System.out.println("================================");
        printCrossword(modifiedCrossword);
        System.out.println("================================");
        return modifiedCrossword;
    }
    
    public static void numberCrossword( int[][] crossword ) {
        
        int[][] modifiedCrossword = preprocessCrossword(crossword);
        for ( int i = 1; i < modifiedCrossword.length; i++ ) {
            for ( int j = 1; j < modifiedCrossword[0].length; j++ ) {
                if ( needsNumbering(modifiedCrossword, i, j) ) {
                    crossword[i - 1][ j - 1 ] = hintIndex++;
                }
            }
        }
    }
    
    public static void printCrossword( int[][] crossword ) {
        for ( int i = 0; i < crossword.length; i++ ) {
            for ( int j = 0; j < crossword[0].length; j++ ) {
                System.out.print( crossword[i][j] + "\t" );
            }
            System.out.println();
        }
    }
    
    public static void main(String args[]) throws FileNotFoundException {
        Scanner scan = new Scanner(new File("crossword.txt"));
        
        int ROWS = scan.nextInt();
        int COLS = scan.nextInt();
        int crossword[][] = new int[ROWS][COLS];
        for ( int i = 0; i < ROWS; i++ ) {
            for ( int j = 0; j < COLS; j++ ) {
                crossword[i][j] = scan.nextInt();
            }
        }
        
        numberCrossword(crossword);
        
        printCrossword(crossword);
    }
}
