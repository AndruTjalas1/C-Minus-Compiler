int x = 10;
int y;
int sum;
int product;
int difference;
int quotient;

char apple = 'B';
/*apple = 'A';*/

write("Testing character variable:");
write(apple);

char c = 'A';
string msg = "Hello World";
write("Testing character 'A':");
write(c);
write("Testing string message:");
write(msg);

x = 5;
y = 10;
sum = y - x * 6 / 3;
product = y * x;
difference = y - x;
quotient = y / x;

write("Testing arithmetic - sum:");
write(sum);
write("Testing arithmetic - product:");
write(product);
write("Testing arithmetic - difference:");
write(difference);
write("Testing arithmetic - quotient:");
write(quotient);

int arr1[3];
arr1[0] = 1;
arr1[1] = 2;
arr1[2] = arr1[0] + arr1[1];

write("Testing array element addition result:");
write(arr1[2]);

int arr[5] = {10, 20, 30, 40, 50};
char carr[3] = {'A', 'B', 'C'};
write("Testing array element [0]:");
write(arr[0]);
write("Testing array element [1]:");
write(arr[1]);
write("Testing char array element [0]:");
write(carr[0]);
write("Testing char array element [1]:");
write(carr[1]);
write("Testing char array element [0] again:");
write(carr[0]);
write("Testing char array element [1] again:");
write(carr[1]);

int matrix[2][3];
matrix[0][0] = 1;
matrix[0][1] = 2;

write("Testing 2D array element [0][0]:");
write(matrix[0][0]);
write("Testing 2D array element [0][1]:");
write(matrix[0][1]);

char cmatrix[2][2];
cmatrix[0][0] = 'M';
cmatrix[0][1] = 'N';
cmatrix[1][0] = 'O';
cmatrix[1][1] = 'P';

write("Testing char matrix element [0][0]:");
write(cmatrix[0][0]);
write("Testing char matrix element [0][1]:");
write(cmatrix[0][1]);
write("Testing char matrix element [1][0]:");
write(cmatrix[1][0]);
write("Testing char matrix element [1][1]:");
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
write("Testing initialized 2D array matrix2[0][0]:");
write(matrix2[0][0]);
write("Testing initialized 2D array matrix2[0][1]:");
write(matrix2[0][1]);
write("Testing initialized 2D array matrix2[1][2]:");
write(matrix2[1][2]);
write("Testing initialized 2D array grid[2][1]:");
write(grid[2][1]);

write("Testing partial initialization sparse[0][0]:");
write(sparse[0][0]);
write("Testing partial initialization sparse[1][1] (should be 0):");
write(sparse[1][1]);
write("Testing manually assigned matrix1[0][0]:");
write(matrix1[0][0]);
write("Testing manually assigned matrix1[1][1]:");
write(matrix1[1][1]);

if (x > y) {
    write("Testing if x > y: print x");
    write(x);
}

if (x < y) {
    write("Testing if x < y: print y");
    write(y);
} else {
    write("Testing else: print x");
    write(x);
}

if (x == 5) {
    write("Testing if x == 5: print 1");
    write(1);
} elseif (x == 10) {
    write("Testing elseif x == 10: print 2");
    write(2);
} else {
    write("Testing else: print 3");
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
    write("Testing AND operator: both conditions true");
    write(1);
}

/* Test OR operator (||) */
int myX = 2;
int myY = 20;

if (myX < 1 || myY > 15) {
    write("Testing OR operator: at least one condition true");
    write(2);
}

/* Test NOT operator (!) */
bool flag = true;

if (!(flag == true)) {
    write("Testing NOT operator: flag is not true");
    write(3);
}

/* Test XOR operator */
int myP = 5;
int myQ = 8;

if ((myP > 3) ^ (myQ < 5)) {
    write("Testing XOR operator: only one condition true");
    write(4);
}

/* Complex example with multiple operators */
int age = 25;
int hasLicense = 1;
int hasInsurance = 1;

if ((age >= 18 && hasLicense == 1) && hasInsurance == 1) {
    write("Testing complex AND: all conditions true");
    write(5);
}

/* Nested logical operators */
int score = 85;
int bonus = 10;

if ((score > 80 && bonus > 5) || score > 90) {
    write("Testing nested logical operators");
    write(6);
}

/* XOR with complex expressions */
int val1 = 10;
int val2 = 5;

if ((val1 > 8 && val2 < 10) ^ (val1 < 12 && val2 > 3)) {
    write("Testing XOR with complex expressions");
    write(7);
}

/* NOT with compound condition */
int enabled = 0;
int ready = 1;

if (!(enabled == 1 && ready == 1)) {
    write("Testing NOT with compound condition");
    write(8);
}

/* Simple loop test - counts 1 to 5 three different ways */

/* For loop */
int i;
write("Testing for loop 1 to 5:");
for (i = 1; i <= 5; i = i + 1) {
    write(i);
}

/* While loop */

write("Testing while loop 1 to 5:");
i = 1;
while (i <= 5) {
    write(i);
    i = i + 1;
}

/* Do-while loop */
int k;
write("Testing do-while loop 1 to 5:");
k = 1;
do {
    write(k);
    k = k + 1;
} while (k <= 5);

/* Test file demonstrating for, while, and do-while loops */

/* Test 1: Simple for loop - count from 0 to 4 */

write("Testing for loop 0 to 4:");
for (i = 0; i < 5; i = i + 1) {
    write(i);
}

/* Test 2: For loop with declaration */
write("Testing for loop with declaration (10 down to 6):");
for (int j = 10; j > 5; j = j - 1) {
    write(j);
}

/* Test 3: While loop - countdown */
int count;
write("Testing while countdown from 6:");
count = 6;
while (count > 0) {
    write(count);
    count = count - 1;
}

/* Test 4: Do-while loop - executes at least once */

write("Testing do-while with multiplication (doubles until >= 10):");
x = 1;
do {
    write(x);
    x = x * 2;
} while (x < 10);

/* Test 5: Nested loops */
int outer;
int inner;
write("Testing nested loops:");
for (outer = 0; outer < 3; outer = outer + 1) {
    for (inner = 0; inner < 2; inner = inner + 1) {
        write("outer:");
        write(outer);
        write("inner:");
        write(inner);
    }
}

/* Test 6: While loop with array */

arr[0] = 10;
arr[1] = 20;
arr[2] = 30;
arr[3] = 40;
arr[4] = 50;

int idx;
write("Testing while loop with array:");
idx = 0;
while (idx < 5) {
    write("arr[");
    write(idx);
    write("]:");
    write(arr[idx]);
    idx = idx + 1;
}

/* Test 7: For loop with complex condition */
int a;
int myb;
write("Testing for loop with complex condition:");
a = 0;
myb = 10;
for (a = 0; a < 5 && myb > 5; a = a + 1) {
    write("a:");
    write(a);
    write("myb:");
    write(myb);
    myb = myb - 1;
}

/* Test 8: Do-while that executes once */
int test;
write("Testing do-while that executes once:");
test = 100;
do {
    write(test);
    test = test + 1;
} while (test < 100);

/* Test file for modulo, compound assignment, and unary operators */

/* Test 1: Modulo operator */
int a;
int b;
a = 17;
b = 5;
int result;
result = a % b;  /* Should be 2 */
write("Testing modulo operator (17 % 5):");
write(result);

/* Test 2: Compound assignment operators */
int x;
x = 10;
write("Testing initial value of x:");
write(x);

x += 5;   /* x = 15 */
write("Testing compound assignment += (x after adding 5):");
write(x);

x -= 3;   /* x = 12 */
write("Testing compound assignment -= (x after subtracting 3):");
write(x);

x *= 2;   /* x = 24 */
write("Testing compound assignment *= (x after multiplying by 2):");
write(x);

x /= 5;   /* x = 6 */
write("Testing compound assignment /= (x after dividing by 5):");
write(x);

x %= 4;   /* x = 2 */
write("Testing compound assignment %= (x after modulo 4):");
write(x);

/* Test 3: Post-increment and post-decrement */
int i;
i = 5;
write("Testing initial value of i:");
write(i);

i++;      /* i = 6 */
write("Testing post-increment (i after i++):");
write(i);

i--;      /* i = 5 */
write("Testing post-decrement (i after i--):");
write(i);

/* Test 4: Pre-increment and pre-decrement */
int j;
j = 10;
write("Testing initial value of j:");
write(j);

++j;      /* j = 11 */
write("Testing pre-increment (j after ++j):");
write(j);

--j;      /* j = 10 */
write("Testing pre-decrement (j after --j):");
write(j);

/* Test 5: Using in loops */
int k;
write("Testing loop with modulo (printing even numbers 0-9):");
for (k = 0; k < 10; k++) {
    if (k % 2 == 0) {
        write(k);
    }
}

/* Test 6: Combining operators */
int n;
n = 100;
n /= 10;   /* n = 10 */
n *= 3;    /* n = 30 */
n %= 7;    /* n = 2 */
write("Testing combined operators (100 / 10 * 3 % 7):");
write(n);

/* Test Boolean Variable Types */

/* Boolean declarations */
bool isReady;
bool isActive;

/* Initialize booleans with literals */
bool flag = true;
bool status = false;

/* Boolean in arithmetic */
int x = 5;
int y = x + flag;

/* Boolean in conditions */
if (flag == true) {
    write(1);
}

if (status == false) {
    write(0);
}

/* Boolean variable assignment */
isReady = true;
isActive = false;

/* Use boolean in expressions */
int resul = isReady + isActive;
write("Boolean isReady + isActive result: ");
write(resul);

/* Loop with boolean */
bool done = false;
int count = 0;
while (done == false) {
    count = count + 1;
    if (count == 5) {
        done = true;
    }
}
write("Boolean loop count: ");
write(count);

/* Comprehensive Recursive Functions Test */

/* Classic factorial - recursive */
function int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    int prev;
    prev = n - 1;
    int prevFact;
    prevFact = factorial(prev);
    return n * prevFact;
}

/* Fibonacci sequence - recursive */
function int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    int fib1;
    int fib2;
    int n1;
    int n2;
    n1 = n - 1;
    n2 = n - 2;
    fib1 = fibonacci(n1);
    fib2 = fibonacci(n2);
    return fib1 + fib2;
}

/* Sum of numbers from 1 to n - recursive */
function int sumToN(int n) {
    if (n <= 0) {
        return 0;
    }
    int prev;
    prev = n - 1;
    int prevSum;
    prevSum = sumToN(prev);
    return n + prevSum;
}

/* Power function x^n - recursive */
function int power(int x, int n) {
    if (n == 0) {
        return 1;
    }
    int n1;
    n1 = n - 1;
    int prevPower;
    prevPower = power(x, n1);
    return x * prevPower;
}

/* Greatest Common Divisor (GCD) - Euclidean algorithm */
function int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    int remainder;
    remainder = a % b;
    return gcd(b, remainder);
}

/* Countdown - simple recursive function */
function int countdown(int n) {
    if (n <= 0) {
        write(0);
        return 0;
    }
    write(n);
    int next;
    next = n - 1;
    return countdown(next);
}

/* Main program */
int resut;

write("===== RECURSIVE FUNCTION TESTS =====");
write(999);

/* Test factorial */
write("Factorial(5) = ");
resut = factorial(5);
write(resut);

/* Test fibonacci */
write("Fibonacci(7) = ");
resut = fibonacci(7);
write(resut);

/* Test sumToN */
write("Sum from 1 to 10 = ");
resut = sumToN(10);
write(resut);

/* Test power */
write("2^5 = ");
resut = power(2, 5);
write(resut);

/* Test GCD */
write("GCD(48, 18) = ");
resut = gcd(48, 18);
write(resut);

/* Test countdown */
write("Countdown from 5:");
write(888);
resut = countdown(5);

write("===== SIMPLE FUNCTION TESTS =====");
write(777);

/*Simple function that adds two numbers*/
function int add(int a, int b) {
    int result;
    result = a + b;
    return result;
}

/* Function that multiplies two numbers */
function int multiply(int x, int y) {
    return x * y;
}

/* Function with no parameters */
function int getConstant() {
    return 42;
}

/* Main program */
int constant;

a = 5;
b = 3;

sum = add(a, b);
write("Sum of 5 + 3 = ");
write(sum);

product = multiply(a, b);
write("Product of 5 * 3 = ");
write(product);

constant = getConstant();
write("Constant function result = ");
write(constant);

/* Test file for switch-case and break/continue statements */

int main;
int choice;
int counter;
int i;

choice = 2;

/* Switch statement with multiple cases */
write("===== SWITCH STATEMENT TEST =====");
write("Switch on choice (2), expect 200: ");
switch (choice) {
    case 1:
        write(100);
        break;
    case 2:
        write(200);
        break;
    case 3:
        write(300);
        break;
    default:
        write(999);
}

/* For loop with break */
write("For loop 0 to 5 (break at 5): ");
for (i = 0; i < 10; i++) {
    write(i);
    if (i == 5) {
        break;
    }
}

/* While loop with continue */
write("While loop 0 to 9 (skip 3): ");
counter = 0;
while (counter < 9) {
    counter++;
    if (counter == 3) {
        continue;
    }
    write(counter);
}

/* Switch with fall-through (no break) */
write("Switch with fall-through (1 -> 10,20): ");
choice = 1;
switch (choice) {
    case 1:
        write(10);
    case 2:
        write(20);
        break;
    default:
        write(30);
}

/* Nested loops with break and continue */
write("Nested loops with break/continue: ");
for (i = 0; i < 5; i++) {
    counter = 0;
    while (counter < 5) {
        counter++;
        if (counter == 2) {
            continue;
        }
        if (counter == 4) {
            break;
        }
        write(counter);
    }
}

/* Test file for nested if/if-else statements */

int x;
int y;
int z;
int result;

write("===== NESTED IF/IF-ELSE STATEMENT TESTS =====");

/* Test 1: Simple nested if */
write("Test 1: Simple Nested If");
x = 10;
y = 5;
if (x > 5) {
    write("x is greater than 5");
    if (y < 10) {
        write("y is less than 10");
        if (x + y > 12) {
            write("x + y is greater than 12");
        }
    }
}

/* Test 2: Nested if-else with multiple branches */
write("Test 2: Nested If-Else");
x = 20;
y = 15;
if (x > 15) {
    write("x is greater than 15");
    if (y == 15) {
        write("y equals 15");
    } else {
        write("y does not equal 15");
    }
} else {
    write("x is not greater than 15");
}

/* Test 3: Triple nested if-else-if */
write("Test 3: Triple Nested If-Else-If");
x = 50;
y = 30;
z = 10;
if (x > 40) {
    write("x > 40");
    if (y > 20) {
        write("y > 20");
        if (z < 15) {
            write("z < 15: All conditions met");
        } else if (z == 15) {
            write("z equals 15");
        } else {
            write("z >= 15");
        }
    } else if (y == 20) {
        write("y equals 20");
    } else {
        write("y <= 20");
    }
} else if (x == 40) {
    write("x equals 40");
} else {
    write("x <= 40");
}

/* Test 4: Deeply nested if-else structure (5 levels) */
write("Test 4: Deeply Nested If-Else (5 Levels)");
x = 100;
y = 75;
z = 50;
if (x > 50) {
    write("Level 1: x > 50");
    if (y > 60) {
        write("Level 2: y > 60");
        if (z > 40) {
            write("Level 3: z > 40");
            if (x + y > 150) {
                write("Level 4: x + y > 150");
                if (z < 60) {
                    write("Level 5: z < 60 - DEEPEST LEVEL");
                } else {
                    write("Level 5: z >= 60");
                }
            } else {
                write("Level 4: x + y <= 150");
            }
        } else if (z == 40) {
            write("Level 3: z equals 40");
        } else {
            write("Level 3: z < 40");
        }
    } else if (y == 60) {
        write("Level 2: y equals 60");
    } else {
        write("Level 2: y < 60");
    }
} else if (x == 50) {
    write("Level 1: x equals 50");
} else {
    write("Level 1: x < 50");
}

/* Test 5: Multiple if-else chains at same level */
write("Test 5: Multiple If-Else Chains");
x = 25;
if (x < 10) {
    write("x is in range [0, 10)");
} else if (x < 20) {
    write("x is in range [10, 20)");
} else if (x < 30) {
    write("x is in range [20, 30)");
} else if (x < 40) {
    write("x is in range [30, 40)");
} else {
    write("x is 40 or greater");
}

/* Test 6: Nested if inside if-else */
write("Test 6: Nested If Inside If-Else");
x = 35;
y = 20;
if (x > 30) {
    write("x > 30");
    if (y > 15) {
        write("Both conditions true");
    } else {
        write("x > 30 but y <= 15");
    }
} else {
    write("x <= 30");
    if (y > 15) {
        write("x <= 30 but y > 15");
    }
}

/* Test 7: Complex logical combinations with nested structures */
write("Test 7: Complex Nested Logic");
x = 42;
y = 18;
z = 5;
if (x > 40) {
    if (y >= 15) {
        if (z > 0) {
            write("All conditions positive");
        } else {
            write("z is not positive");
        }
    } else {
        if (z < 10) {
            write("x > 40 and z < 10, but y < 15");
        } else {
            write("x > 40, but y < 15 and z >= 10");
        }
    }
} else {
    if (y >= 15) {
        write("x <= 40 but y >= 15");
    } else {
        write("Both x and y below threshold");
    }
}

/* Test 8: Nested if with sequential value changes */
write("Test 8: Sequential Nested Checks");
x = 1;
if (x == 1) {
    write("Step 1: x is 1");
    x = 2;
    if (x == 2) {
        write("Step 2: x is now 2");
        x = 3;
        if (x == 3) {
            write("Step 3: x is now 3");
            x = 4;
            if (x == 4) {
                write("Step 4: x is now 4 - Success");
            }
        }
    }
}

write("===== ALL TESTS COMPLETED =====");

/* Test Variable-Length Array Parameters */

/* Function that accepts arrays without predefined sizes */
function int sumArray(int arr[]) {
    int sum = 0;
    int i = 0;
    
    while (i < 5) {
        sum = sum + arr[i];
        i++;
    }
    
    return sum;
}

/* Function that prints array elements */
function void printArray(int arr[]) {
    int i = 0;
    
    while (i < 5) {
        write(arr[i]);
        i++;
    }
}

/* Function with fixed-size array parameter */
function int processFixed(int arr[10]) {
    return arr[0] + arr[1];
}

/* Main program */
int myArray[5] = {10, 20, 30, 40, 50};
int result;

write("Testing variable-length array parameters:");
write("Array contents:");
printArray(myArray);

write("Sum of array elements:");
result = sumArray(myArray);
write(result);

write("Testing fixed-size array parameter:");
result = processFixed(myArray);
write(result);

write("Test completed successfully!");
