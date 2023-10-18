package boundedBuffer;

import java.util.Random;

public class producerThread implements Runnable {
    private final BoundedBuffer buffer;
    private final int insertions;

    public producerThread(BoundedBuffer buffer, int insertions) {
        this.buffer = buffer;
        this.insertions = insertions;
    }

    /**
     * Overriding the Runnable run() member function
     * Runs a producerThread, inserting a string into the BoundedBuffer
     *
     */
    @Override
    public void run() {
        for (int i = 0; i < insertions; i++) {
            String data = Thread.currentThread().getId() + "-" + genRandNums();
            try {
                buffer.deposit(data);
                System.out.println("Produced: " + data);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    /**
     * Helper function to generate random number for input string
     *
     */
    public String genRandNums(){
        // create instance of Random class
        Random rand = new Random();
        //gGenerate random integers in range 10000 to 99999
        int result = rand.nextInt(90000) + 10000;
        return String.valueOf(result);
    }
}
