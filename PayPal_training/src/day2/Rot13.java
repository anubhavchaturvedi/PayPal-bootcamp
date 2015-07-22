/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package day2;

/**
 *
 * @author test
 */
public class Rot13 {
    
    static final String ALPHABETS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    public static char rotSubstitution(char ch) {
        if ( 'A' <= ch && ch <= 'Z') {
            //return (char)( ((ch - 'A' + 13) % 26) + 'A' );
            return ALPHABETS.charAt( ((ch - 'A' + 13) % 26) );
        }
        else {
            return ch;
        }
    }
    
    public static String Rot13(String text) {
        String rot13string = "";
        for ( int i=0; i < text.length(); i++ ) {
            rot13string += rotSubstitution(text.charAt(i));
        }
        return rot13string;
    }
    
    public static void main(String args[]) {
        String plainText = "Why did the chicken 123";
        System.out.println( Rot13(plainText.toUpperCase()) );
    }
}
