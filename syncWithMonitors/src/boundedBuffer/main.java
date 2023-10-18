package boundedBuffer;

public class main {

    public static void main(String[] args) {

        int numThreads = 3;
        int insertionsPerThread = 30;
        BoundedBuffer buffer = new BoundedBuffer(15);

        // loop to create and run producer threads
        for (int i = 0; i < numThreads; i++){
            Thread prodThread = new Thread(new producerThread(buffer, insertionsPerThread));
            prodThread.start();
        }

        // create and run a consumer thread
        Thread consThread = new Thread(
                new consumerThread(buffer, numThreads * insertionsPerThread));
        consThread.start();
    }
}
