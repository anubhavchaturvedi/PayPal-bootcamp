package day1;

/**
 * The generator for Collatz Sequence.
 * @author Anubhav
 */
public class CollatzGenerator {
    int START;
    int current;
    int closureSeqIndex = 3;
    boolean closureSequenceStarted = false;
    
    public CollatzGenerator(int start) {
        this.START = start;
        this.current = start;
        checkClosureSequenceStarted();
    }
    
    private void checkClosureSequenceStarted() {
        if ( current == 4 ) {
            closureSequenceStarted = true;
        }
        if ( closureSequenceStarted ) {
            closureSeqIndex--;
        }
    }
    
    public Integer next() {
        if ( !hasNext() ) {
            return null;
        }
        
        current = current % 2 == 0 ? ( current / 2 ) : ( 3 * current + 1 );
        checkClosureSequenceStarted();
        return current;
    }
    
    public boolean hasNext() {
        if ( closureSeqIndex == 0 ) {
            return false;
        }
        return true;
    }
    
    public int getStart() {
        return this.START;
    }
}