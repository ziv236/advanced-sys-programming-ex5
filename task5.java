// Task 5: Fixed with synchronized(this) block - functionally same as Task 4
// Run with: javac Foo.java && java Foo

class Foo {
    private int bar = 0;

    public void baz() {
        synchronized (this) {
            bar++;
        }
    }

    public int getBar() {
        return bar;
    }

    public static void main(String[] args) throws InterruptedException {
        Foo f = new Foo();
        Thread[] arr = new Thread[2];

        for (int i = 0; i < arr.length; i++) {
            arr[i] = new Thread(() -> {
                for (int j = 0; j < 10000; j++) {
                    f.baz();
                }
            });
            arr[i].start();
        }

        for (int i = 0; i < arr.length; i++) {
            arr[i].join();
        }

        System.out.println(f.getBar());
    }
}
