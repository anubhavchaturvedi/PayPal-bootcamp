/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package day3;

import java.util.ArrayList;
import java.util.Arrays;

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
        this.init();
    }
    
    private void init(){
        boolean numbers[];
        numbers = new boolean[ (int)Math.pow( 10, this.numDigits) ];
        for ( int i = 0; i < numbers.length; i++ ) {
            if( isValid(getLeadingZeroString(i)) ) {
                this.validNumbers.add(this.getLeadingZeroString(i));
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
    
    private String getLeadingZeroString(int n) {
        String leadingZeroNumber = Integer.toString(n);
        while ( leadingZeroNumber.length() < this.numDigits ) {
            leadingZeroNumber = "0" + leadingZeroNumber;
        }
        
        return leadingZeroNumber;
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
}
