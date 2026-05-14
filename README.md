# Week 5: Threads

**Repository:** https://github.com/ziv236/advanced-sys-programming-ex5/blob/main/README.md

---

## Task 1 – Basic std::thread (C++)

Ran the code from the multi-threading slides (page 22). The code creates 5 threads, each printing its ID to stdout.

**Compile & run:**
```bash
g++ -std=c++11 task1.cpp -o task1 -pthread
./task1
```

---

## Task 2 – Fixing thread interference with std::mutex (C++)

The original code from Task 1 sometimes produces garbled output because multiple threads write to `std::cout` simultaneously (e.g., two threads can interleave in the middle of a print statement).

**Fix:** Added a `std::mutex` and call `mtx.lock()` before printing and `mtx.unlock()` after. This ensures only one thread can print at a time, so each thread gets a clean, separate line.

**Compile & run:**
```bash
g++ -std=c++11 task2.cpp -o task2 -pthread
./task2
```

---

## Task 3 – Java Race Condition

**Run:**
```bash
javac task3.java && java Foo
```

**Why the result is NOT 20000:**

The program creates 2 threads, each incrementing `bar` 10,000 times, so the expected result is 20,000. However, the actual result is lower due to a race condition.
The operation bar++ is not atomic — at the CPU level it consists of 3 separate steps:

1. Read the current value of bar from memory
2. Add 1 to it
3. Write the new value back to memory

Since both threads run concurrently, the following scenario can occur: Thread A reads bar = `1000`. Before Thread A writes back 1000, Thread B also reads `bar = 1000`. Now both threads write 1001 — one increment is lost. This can repeat thousands of times throughout the execution, which is why the final result is consistently less than 20,000 and changes between runs.

---

## Task 4 – synchronized Methods

**Run:**
```bash
javac Foo.java && java Foo
```

**Why the result is 20000:**

Adding `synchronized` to `baz()` and `getBar()` fixes the race condition.
When a method is marked as `synchronized`, only one thread can run it at a time.
Before entering the method, the thread locks the object, and releases the lock when it exits.
This way, `bar++` always finishes completely before another thread can start — so the result is always exactly 20,000.

---

## Task 5 – synchronized(this) Block

**Run:**
```bash
javac Foo.java && java Foo
```

**Why the result is 20000:**

Instead of marking the whole method as `synchronized`, here we use a `synchronized(this)` block
inside the method. This means only the code inside the block is locked, not the entire method.
The difference from Task 4 is that in Task 4 the entire method is locked,
while here only a specific section is locked — which can be useful if the method
has other code that doesn't touch shared variables and doesn't need to be locked.
In this case the result is the same (always 20,000), since `baz()` only contains `bar++`.

---

## Task 6 – Performance: No Synchronization

**Run:**
```bash
javac Foo.java && java Foo
```

**Output explanation:**

This code runs 10 threads, each incrementing `bar` 10,000,000 times (expected result: 100,000,000).
The output shows two numbers: the final value of `bar` and the elapsed time in milliseconds. I took a screenshot of it, number 6

Results from a few runs:
- 42,267,718 in 75ms
- 43,292,020 in 69ms
- 29,063,772 in 78ms
- 35,862,695 in 72ms

The value is far from 100,000,000 due to the race condition on `bar++`.
The time is very short (~70ms) because threads run freely with no locking overhead.

---

## Task 7 – Performance: With synchronized(this)

**Run:**
```bash
javac Foo.java && java Foo
```

**Output explanation:**

Same as Task 6 but with `synchronized(this)` inside `baz()`.

Results from a few runs as I took screenshot at number 7:
- 100000000 in 6974ms
- 100000000 in 8935ms
- 100000000 in 5716ms
- 100000000 in 10243ms
- 100000000 in 4752ms

The result is now always exactly 100,000,000 — correct!
But the time jumped from ~70ms to ~7000ms, roughly 100x slower.

The reason: every one of the 100,000,000 calls to `baz()` must acquire and release a lock.
While one thread holds the lock, all 9 other threads are blocked and waiting.
This turns parallel execution into essentially serial execution — which is the cost of synchronization


