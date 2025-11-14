/* Global array for sorting - initialized in declaration */
int num[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

/* Swap function - exchanges values at two indices */
function void swap(int index1, int index2) {
    int temp;
    temp = num[index1];
    num[index1] = num[index2];
    num[index2] = temp;
}

/* Main program variables */
int x;
int y;
int numLength;

numLength = 10;

/* Print unsorted array */
write("Unsorted array:");
writeln;
x = 0;
while (x < numLength) {
    write(num[x]);
    x = x + 1;
}

writeln;

/* Bubble sort using nested loops with swap function */
y = 0;
while (y < numLength) {
    x = 0;
    while (x < numLength - 1) {
        if (num[x] < num[x + 1]) {
            swap(x, x + 1);
        }
        x = x + 1;
    }
    y = y + 1;
}
writeln;
/* Print sorted array */
write("Sorted array:");
writeln;
x = 0;
while (x < numLength) {
    write(num[x]);
    x = x + 1;
}

writeln;