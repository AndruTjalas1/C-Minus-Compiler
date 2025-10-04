/* Test file demonstrating for, while, and do-while loops */

/* Test 1: Simple for loop - count from 0 to 4 */
int i;
for (i = 0; i < 5; i = i + 1) {
    write(i);
}

/* Test 2: For loop with declaration */
for (int j = 10; j > 5; j = j - 1) {
    write(j);
}

/* Test 3: While loop - countdown */
int count;
count = 5;
while (count > 0) {
    write(count);
    count = count - 1;
}

/* Test 4: Do-while loop - executes at least once */
int x;
x = 1;
do {
    write(x);
    x = x * 2;
} while (x < 10);

/* Test 5: Nested loops */
int outer;
int inner;
for (outer = 0; outer < 3; outer = outer + 1) {
    for (inner = 0; inner < 2; inner = inner + 1) {
        write(outer);
        write(inner);
    }
}

/* Test 6: While loop with array */
int arr[5];
arr[0] = 10;
arr[1] = 20;
arr[2] = 30;
arr[3] = 40;
arr[4] = 50;

int idx;
idx = 0;
while (idx < 5) {
    write(arr[idx]);
    idx = idx + 1;
}

/* Test 7: For loop with complex condition */
int a;
int b;
a = 0;
b = 10;
for (a = 0; a < 5 && b > 5; a = a + 1) {
    write(a);
    write(b);
    b = b - 1;
}

/* Test 8: Do-while that executes once */
int test;
test = 100;
do {
    write(test);
    test = test + 1;
} while (test < 100);
