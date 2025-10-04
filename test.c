int x = 10;
int y;
int sum;
int product;
int difference;
int quotient;

char apple = 'B';
/*apple = 'A';*/

write(apple);

 char c = 'A';
string msg = "Hello World";
write(c);
write(msg);

x = 5;
y = 10;
sum = y - x * 6 / 3;
product = y * x;
difference = y - x;
quotient = y / x;

write(sum);
write(product);
write(difference);
write(quotient);

int arr1[3];
arr1[0] = 1;
arr1[1] = 2;
arr1[2] = arr1[0] + arr1[1];

write(arr1[2]);

int arr[5] = {10, 20, 30, 40, 50};
char carr[3] = {'A', 'B', 'C'};
write(arr[0]);
write(arr[1]);
write(carr[0]);
write(carr[1]);
write(carr[0]);
write(carr[1]);

int matrix[2][3];
matrix[0][0] = 1;
matrix[0][1] = 2;

write(matrix[0][0]);
write(matrix[0][1]);

char cmatrix[2][2];
cmatrix[0][0] = 'M';
cmatrix[0][1] = 'N';
cmatrix[1][0] = 'O';
cmatrix[1][1] = 'P';

write(cmatrix[0][0]);
write(cmatrix[0][1]);
write(cmatrix[1][0]);
write(cmatrix[1][1]);

/* Test 2D Array Initialization */

/* 1D array initialization (already working) */
int arr1[5] = {1, 2, 3, 4, 5};

/* 2D array without initialization */
int matrix1[3][3];

/* 2D array with initialization - NEW FEATURE! */
int matrix2[2][3] = {1, 2, 3, 4, 5, 6};

/* Another 2D array with initialization */
int grid[3][2] = {10, 20, 30, 40, 50, 60};

/* Partial initialization (remaining elements will be 0) */
int sparse[2][2] = {1, 2};

/* Access and assign 2D array elements */
matrix1[0][0] = 10;
matrix1[1][1] = 20;
matrix1[2][2] = 30;

/* Print 2D array elements */
write(matrix2[0][0]);
write(matrix2[0][1]);
write(matrix2[1][2]);
write(grid[2][1]);

write(sparse[0][0]);
write(sparse[1][1]);
write(matrix1[0][0]);
write(matrix1[1][1]);

if (x > y) {
    write(x);
}

if (x < y) {
    write(y);
} else {
    write(x);
}

if (x == 5) {
    write(1);
} elseif (x == 10) {
    write(2);
} else {
    write(3);
}

/*
 * Test file for logical operators: &&, ||, !, xor
 * This demonstrates how to use logical operators in conditional statements
 */

/* Test AND operator (&&) */
int myA = 5;
int myB = 10;

if (myA > 3 && myB < 15) {
    write(1);  /* Should print: both conditions are true */
}

/* Test OR operator (||) */
int myX = 2;
int myY = 20;

if (myX < 1 || myY > 15) {
    write(2);  /* Should print: second condition is true */
}

/* Test NOT operator (!) */
int flag = 1;

if (!(flag == 1)) {
    write(3);  /* Should print: flag is not 1 */
}

/* Test XOR operator */
int myP = 5;
int myQ = 8;

if ((myP > 3) ^ (myQ < 5)) {
    write(4);  /* Should print: only first condition is true */
}

/* Complex example with multiple operators */
int age = 25;
int hasLicense = 1;
int hasInsurance = 1;

if ((age >= 18 && hasLicense == 1) && hasInsurance == 1) {
    write(5);  /* Should print: all conditions are true */
}

/* Nested logical operators */
int score = 85;
int bonus = 10;

if ((score > 80 && bonus > 5) || score > 90) {
    write(6);  /* Should print: first part is true */
}

/* XOR with complex expressions */
int val1 = 10;
int val2 = 5;

if ((val1 > 8 && val2 < 10) ^ (val1 < 12 && val2 > 3)) {
    write(7);  /* Should NOT print: both sides are true, XOR needs exactly one true */
}

/* NOT with compound condition */
int enabled = 0;
int ready = 1;

if (!(enabled == 1 && ready == 1)) {
    write(8);  /* Should print: compound condition is false */
}

/* Simple loop test - counts 1 to 5 three different ways */

/* For loop */
int i;
for (i = 1; i <= 5; i = i + 1) {
    write(i);
}

/* While loop */

i = 1;
while (i <= 5) {
    write(i);
    i = i + 1;
}

/* Do-while loop */
int k;
k = 1;
do {
    write(k);
    k = k + 1;
} while (k <= 5);

