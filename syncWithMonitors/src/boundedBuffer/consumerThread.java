package boundedBuffer;

public class consumerThread implements Runnable {

    private final BoundedBuffer buffer;
    private final int consumptions;

    public consumerThread(BoundedBuffer buffer, int consumptions) {
        this.buffer = buffer;
        this.consumptions = consumptions;
    }

    /**
     * Overriding the Runnable run() member function
     * Runs a consumerThread, fetching a string from the BoundedBuffer
     *
     */
    @Override
    public void run() {
        for (int i = 0; i < consumptions; i++) {
            try {
                String data = buffer.fetch();
                System.out.println("Consumed: " + data);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
