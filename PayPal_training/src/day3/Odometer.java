/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package day3;

import java.util.ArrayList;

/**
 *
 * @author Team 4
 */
public class Odometer {
    private int numDigits;
    private int currentPosition = 0;
    private ArrayList<String> validNumbers;
    
    Odometer(int numDigits) {
        this.numDigits = numDigits;
        this.validNumbers = new ArrayList<String>();
        
        final int UPPER_BOUND = (int)Math.pow( 10, this.numDigits);
        final int LOWER_BOUND = (int)Math.pow( 10, this.numDigits - 1);
        
        for ( int i = LOWER_BOUND; i < UPPER_BOUND; i++ ) {
            if( isValid(Integer.toString(i)) ) {
                this.validNumbers.add(Integer.toString(i));
            }
        }
    }
    
    private boolean isValid(String n) {
        if ( n.contains("0"))
            return false;
        
        for ( int i = 1; i < n.length(); i++ ) {
            if ( n.charAt(i) <= n.charAt(i-1) ) {
                return false;
            }
        }
        
        return true;
    }
    
    public String getCurrentValue() {
        return this.validNumbers.get(currentPosition);
    }
    
    public String nextValue() {
        currentPosition = currentPosition + 1 >= this.validNumbers.size() ? 0 : currentPosition + 1;
        return this.validNumbers.get( currentPosition );
    }
    
    public String previousValue() {
        currentPosition = currentPosition - 1 < 0 ? this.validNumbers.size() - 1 : currentPosition - 1;
        return this.validNumbers.get( currentPosition );
    }
    
    public int computeDistance(String reading1, String reading2) {
        return Math.abs(validNumbers.indexOf(reading1) - validNumbers.indexOf(reading2));
    }
    
    public int getDistance() {
        return this.currentPosition;
    }

    public boolean reset() {
        this.currentPosition = 0;
        return true;
    }
    
}