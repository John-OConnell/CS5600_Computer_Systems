package boundedBuffer;

import java.util.Random;

public class producerThread implements Runnable {

    private final BoundedBuffer buffer;
    private final int insertions;

    public producerThread(BoundedBuffer buffer, int insertions) {
        this.buffer = buffer;
        this.insertions = insertions;
    }

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

    public String genRandNums(){
        // create instance of Random class
        Random rand = new Random();
        // Generate random integers in range 0 to 999
        int result = rand.nextInt(90000) + 10000;
        return String.valueOf(result);
    }
}
