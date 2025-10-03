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
