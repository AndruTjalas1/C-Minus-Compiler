int x = 10;
int y;
int sum;
int product;
int difference;
int quotient;

char apple = 'B';
/*apple = 'A';*/

writeln("Testing character variable:");
writeln(apple);

char c = 'A';
string msg = "Hello World";
writeln("Testing character 'A':");
writeln(c);
writeln("Testing string message:");
writeln(msg);

x = 5;
y = 10;
sum = y + x;
product = y * x;
difference = y - x;
quotient = y / x;
int operatorPrecedence = 10 + 4 / 2;

write("Testing arithmetic - sum: ");
writeln(sum);
write("Testing arithmetic - product: ");
writeln(product);
write("Testing arithmetic - difference: ");
writeln(difference);
write("Testing arithmetic - quotient: ");
writeln(quotient);
write("Testing operator precedence (10 + 5 * 2): ");
writeln(operatorPrecedence);

int arr1[3];
arr1[0] = 1;
arr1[1] = 2;
arr1[2] = arr1[0] + arr1[1];

write("Testing array element addition result: ");
writeln(arr1[2]);

int arr[5] = {10, 20, 30, 40, 50};
char carr[3] = {'A', 'B', 'C'};
write("Testing array element [0]: ");
writeln(arr[0]);
write("Testing array element [1]: ");
writeln(arr[1]);
write("Testing char array element [0]: ");
writeln(carr[0]);
write("Testing char array element [1]: ");
writeln(carr[1]);
write("Testing char array element [0] again: ");
writeln(carr[0]);
write("Testing char array element [1] again: ");
writeln(carr[1]);

int matrix[2][3];
matrix[0][0] = 1;
matrix[0][1] = 2;

write("Testing 2D array element [0][0]: ");
writeln(matrix[0][0]);
write("Testing 2D array element [0][1]: ");
writeln(matrix[0][1]);

char cmatrix[2][2];
cmatrix[0][0] = 'M';
cmatrix[0][1] = 'N';
cmatrix[1][0] = 'O';
cmatrix[1][1] = 'P';

write("Testing char matrix element [0][0]: ");
writeln(cmatrix[0][0]);
write("Testing char matrix element [0][1]: ");
writeln(cmatrix[0][1]);
write("Testing char matrix element [1][0]: ");
writeln(cmatrix[1][0]);
write("Testing char matrix element [1][1]: ");
writeln(cmatrix[1][1]);

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
write("Testing initialized 2D array matrix2[0][0]: ");
writeln(matrix2[0][0]);
write("Testing initialized 2D array matrix2[0][1]: ");
writeln(matrix2[0][1]);
write("Testing initialized 2D array matrix2[1][2]: ");
writeln(matrix2[1][2]);
write("Testing initialized 2D array grid[2][1]: ");
writeln(grid[2][1]);

write("Testing partial initialization sparse[0][0]: ");
writeln(sparse[0][0]);
write("Testing partial initialization sparse[1][1] (should be 0): ");
writeln(sparse[1][1]);
write("Testing manually assigned matrix1[0][0]: ");
writeln(matrix1[0][0]);
write("Testing manually assigned matrix1[1][1]: ");
writeln(matrix1[1][1]);

if (x > y) {
    write("Testing if x > y: print x ");
    writeln(x);
}

if (x < y) {
    write("Testing if x < y: print y ");
    writeln(y);
} else {
    write("Testing else: print x ");
    writeln(x);
}

if (x == 5) {
    writeln("Testing if x == 5: print 1");
    writeln(1);
} elseif (x == 10) {
    writeln("Testing elseif x == 10: print 2");
    writeln(2);
} else {
    writeln("Testing else: print 3");
    writeln(3);
}

/*
 * Test file for logical operators: &&, ||, !, xor
 * This demonstrates how to use logical operators in conditional statements
 */

/* Test AND operator (&&) */
int myA = 5;
int myB = 10;

if (myA > 3 && myB < 15) {
    writeln("Testing AND operator: both conditions true");
    writeln(1);
}

/* Test OR operator (||) */
int myX = 2;
int myY = 20;

if (myX < 1 || myY > 15) {
    writeln("Testing OR operator: at least one condition true");
    writeln(2);
}

/* Test NOT operator (!) */
bool flag = true;

if (!(flag == true)) {
    writeln("Testing NOT operator: flag is not true");
    writeln(3);
}

/* Test XOR operator */
int myP = 5;
int myQ = 8;

if ((myP > 3) ^ (myQ < 5)) {
    writeln("Testing XOR operator: only one condition true");
    writeln(4);
}

/* Complex example with multiple operators */
int age = 25;
int hasLicense = 1;
int hasInsurance = 1;

if ((age >= 18 && hasLicense == 1) && hasInsurance == 1) {
    writeln("Testing complex AND: all conditions true");
    writeln(5);
}

/* Nested logical operators */
int score = 85;
int bonus = 10;

if ((score > 80 && bonus > 5) || score > 90) {
    writeln("Testing nested logical operators");
    writeln(6);
}

/* XOR with complex expressions */
int val1 = 10;
int val2 = 5;

if ((val1 > 8 && val2 < 10) ^ (val1 < 12 && val2 > 3)) {
    writeln("Testing XOR with complex expressions");
    writeln(7);
}

/* NOT with compound condition */
int enabled = 0;
int ready = 1;

if (!(enabled == 1 && ready == 1)) {
    writeln("Testing NOT with compound condition");
    writeln(8);
}

/* Simple loop test - counts 1 to 5 three different ways */

/* For loop */
int i;
writeln("Testing for loop 1 to 5:");
for (i = 1; i <= 5; i = i + 1) {
    writeln(i);
}

/* While loop */

writeln("Testing while loop 1 to 5:");
i = 1;
while (i <= 5) {
    writeln(i);
    i = i + 1;
}

/* Do-while loop */
int k;
writeln("Testing do-while loop 1 to 5:");
k = 1;
do {
    writeln(k);
    k = k + 1;
} while (k <= 5);

/* Test file demonstrating for, while, and do-while loops */

/* Test 1: Simple for loop - count from 0 to 4 */

writeln("Testing for loop 0 to 4:");
for (i = 0; i < 5; i = i + 1) {
    writeln(i);
}

/* Test 2: For loop with declaration */
writeln("Testing for loop with declaration (10 down to 6):");
for (int j = 10; j > 5; j = j - 1) {
    writeln(j);
}

/* Test 3: While loop - countdown */
int count;
writeln("Testing while countdown from 6:");
count = 6;
while (count > 0) {
    writeln(count);
    count = count - 1;
}

/* Test 4: Do-while loop - executes at least once */

writeln("Testing do-while with multiplication (doubles until >= 10):");
x = 1;
do {
    writeln(x);
    x = x * 2;
} while (x < 10);

/* Test 5: Nested loops */
int outer;
int inner;
writeln("Testing nested loops:");
for (outer = 0; outer < 3; outer = outer + 1) {
    for (inner = 0; inner < 2; inner = inner + 1) {
        writeln("outer:");
        writeln(outer);
        writeln("inner:");
        writeln(inner);
    }
}

/* Test 6: While loop with array */

arr[0] = 10;
arr[1] = 20;
arr[2] = 30;
arr[3] = 40;
arr[4] = 50;

int idx;
writeln("Testing while loop with array:");
idx = 0;
while (idx < 5) {
    writeln("arr[");
    write(idx);
    writeln("]:");
    write("Array index: ");
    writeln(arr[idx]);
    idx = idx + 1;
}

/* Test 7: For loop with complex condition */
int a;
int myb;
writeln("Testing for loop with complex condition:");
a = 0;
myb = 10;
for (a = 0; a < 5 && myb > 5; a = a + 1) {
    writeln("a:");
    writeln(a);
    writeln("myb:");
    writeln(myb);
    myb = myb - 1;
}

/* Test 8: Do-while that executes once */
int test;
writeln("Testing do-while that executes once:");
test = 100;
do {
    writeln(test);
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
writeln("Testing modulo operator (17 % 5):");
writeln(result);

/* Test 2: Compound assignment operators */
int x;
x = 10;
writeln("Testing initial value of x:");
writeln(x);

x += 5;   /* x = 15 */
writeln("Testing compound assignment += (x after adding 5):");
writeln(x);

x -= 3;   /* x = 12 */
writeln("Testing compound assignment -= (x after subtracting 3):");
writeln(x);

x *= 2;   /* x = 24 */
writeln("Testing compound assignment *= (x after multiplying by 2):");
writeln(x);

x /= 5;   /* x = 6 */
writeln("Testing compound assignment /= (x after dividing by 5):");
writeln(x);

x %= 4;   /* x = 2 */
writeln("Testing compound assignment %= (x after modulo 4):");
writeln(x);

/* Test 3: Post-increment and post-decrement */
int i;
i = 5;
writeln("Testing initial value of i:");
writeln(i);

i++;      /* i = 6 */
writeln("Testing post-increment (i after i++):");
writeln(i);

i--;      /* i = 5 */
writeln("Testing post-decrement (i after i--):");
writeln(i);

/* Test 4: Pre-increment and pre-decrement */
int j;
j = 10;
writeln("Testing initial value of j:");
writeln(j);

++j;      /* j = 11 */
writeln("Testing pre-increment (j after ++j):");
writeln(j);

--j;      /* j = 10 */
writeln("Testing pre-decrement (j after --j):");
writeln(j);

/* Test 5: Using in loops */
int k;
writeln("Testing loop with modulo (printing even numbers 0-9):");
for (k = 0; k < 10; k++) {
    if (k % 2 == 0) {
        writeln(k);
    }
}

/* Test 6: Combining operators */
int n;
n = 100;
n /= 10;   /* n = 10 */
n *= 3;    /* n = 30 */
n %= 7;    /* n = 2 */
writeln("Testing combined operators (100 / 10 * 3 % 7):");
writeln(n);

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
    writeln(1);
}

if (status == false) {
    writeln(0);
}

/* Boolean variable assignment */
isReady = true;
isActive = false;

/* Use boolean in expressions */
int resul = isReady + isActive;
writeln("Boolean isReady + isActive result: ");
writeln(resul);

/* Loop with boolean */
bool done = false;
int count = 0;
while (done == false) {
    count = count + 1;
    if (count == 5) {
        done = true;
    }
}
writeln("Boolean loop count: ");
writeln(count);

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
        writeln(0);
        return 0;
    }
    writeln(n);
    int next;
    next = n - 1;
    return countdown(next);
}

/* Main program */
int resut;

writeln("===== RECURSIVE FUNCTION TESTS =====");
writeln(999);

/* Test factorial */
writeln("Factorial(5) = ");
resut = factorial(5);
writeln(resut);

/* Test fibonacci */
writeln("Fibonacci(7) = ");
resut = fibonacci(7);
writeln(resut);

/* Test sumToN */
writeln("Sum from 1 to 10 = ");
resut = sumToN(10);
writeln(resut);

/* Test power */
writeln("2^5 = ");
resut = power(2, 5);
writeln(resut);

/* Test GCD */
writeln("GCD(48, 18) = ");
resut = gcd(48, 18);
writeln(resut);

/* Test countdown */
writeln("Countdown from 5:");
writeln(888);
resut = countdown(5);

writeln("===== SIMPLE FUNCTION TESTS =====");
writeln(777);

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
writeln("Sum of 5 + 3 = ");
writeln(sum);

product = multiply(a, b);
writeln("Product of 5 * 3 = ");
writeln(product);

constant = getConstant();
writeln("Constant function result = ");
writeln(constant);

/* Test file for switch-case and break/continue statements */

int main;
int choice;
int counter;
int i;

choice = 2;

/* Switch statement with multiple cases */
writeln("===== SWITCH STATEMENT TEST =====");
writeln("Switch on choice (2), expect 200: ");
switch (choice) {
    case 1:
        writeln(100);
        break;
    case 2:
        writeln(200);
        break;
    case 3:
        writeln(300);
        break;
    default:
        writeln(999);
}

/* For loop with break */
writeln("For loop 0 to 5 (break at 5): ");
for (i = 0; i < 10; i++) {
    writeln(i);
    if (i == 5) {
        break;
    }
}

/* While loop with continue */
writeln("While loop 0 to 9 (skip 3): ");
counter = 0;
while (counter < 9) {
    counter++;
    if (counter == 3) {
        continue;
    }
    writeln(counter);
}

/* Switch with fall-through (no break) */
writeln("Switch with fall-through (1 -> 10,20): ");
choice = 1;
switch (choice) {
    case 1:
        writeln(10);
    case 2:
        writeln(20);
        break;
    default:
        writeln(30);
}

/* Nested loops with break and continue */
writeln("Nested loops with break/continue: ");
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
        writeln(counter);
    }
}

/* Test file for nested if/if-else statements */

int x;
int y;
int z;
int result;

writeln("===== NESTED IF/IF-ELSE STATEMENT TESTS =====");

/* Test 1: Simple nested if */
writeln("Test 1: Simple Nested If");
x = 10;
y = 5;
if (x > 5) {
    writeln("x is greater than 5");
    if (y < 10) {
        writeln("y is less than 10");
        if (x + y > 12) {
            writeln("x + y is greater than 12");
        }
    }
}

/* Test 2: Nested if-else with multiple branches */
writeln("Test 2: Nested If-Else");
x = 20;
y = 15;
if (x > 15) {
    writeln("x is greater than 15");
    if (y == 15) {
        writeln("y equals 15");
    } else {
        writeln("y does not equal 15");
    }
} else {
    writeln("x is not greater than 15");
}

/* Test 3: Triple nested if-else-if */
writeln("Test 3: Triple Nested If-Else-If");
x = 50;
y = 30;
z = 10;
if (x > 40) {
    writeln("x > 40");
    if (y > 20) {
        writeln("y > 20");
        if (z < 15) {
            writeln("z < 15: All conditions met");
        } else if (z == 15) {
            writeln("z equals 15");
        } else {
            writeln("z >= 15");
        }
    } else if (y == 20) {
        writeln("y equals 20");
    } else {
        writeln("y <= 20");
    }
} else if (x == 40) {
    writeln("x equals 40");
} else {
    writeln("x <= 40");
}

/* Test 4: Deeply nested if-else structure (5 levels) */
writeln("Test 4: Deeply Nested If-Else (5 Levels)");
x = 100;
y = 75;
z = 50;
if (x > 50) {
    writeln("Level 1: x > 50");
    if (y > 60) {
        writeln("Level 2: y > 60");
        if (z > 40) {
            writeln("Level 3: z > 40");
            if (x + y > 150) {
                writeln("Level 4: x + y > 150");
                if (z < 60) {
                    writeln("Level 5: z < 60 - DEEPEST LEVEL");
                } else {
                    writeln("Level 5: z >= 60");
                }
            } else {
                writeln("Level 4: x + y <= 150");
            }
        } else if (z == 40) {
            writeln("Level 3: z equals 40");
        } else {
            writeln("Level 3: z < 40");
        }
    } else if (y == 60) {
        writeln("Level 2: y equals 60");
    } else {
        writeln("Level 2: y < 60");
    }
} else if (x == 50) {
    writeln("Level 1: x equals 50");
} else {
    writeln("Level 1: x < 50");
}

/* Test 5: Multiple if-else chains at same level */
writeln("Test 5: Multiple If-Else Chains");
x = 25;
if (x < 10) {
    writeln("x is in range [0, 10)");
} else if (x < 20) {
    writeln("x is in range [10, 20)");
} else if (x < 30) {
    writeln("x is in range [20, 30)");
} else if (x < 40) {
    writeln("x is in range [30, 40)");
} else {
    writeln("x is 40 or greater");
}

/* Test 6: Nested if inside if-else */
writeln("Test 6: Nested If Inside If-Else");
x = 35;
y = 20;
if (x > 30) {
    writeln("x > 30");
    if (y > 15) {
        writeln("Both conditions true");
    } else {
        writeln("x > 30 but y <= 15");
    }
} else {
    writeln("x <= 30");
    if (y > 15) {
        writeln("x <= 30 but y > 15");
    }
}

/* Test 7: Complex logical combinations with nested structures */
writeln("Test 7: Complex Nested Logic");
x = 42;
y = 18;
z = 5;
if (x > 40) {
    if (y >= 15) {
        if (z > 0) {
            writeln("All conditions positive");
        } else {
            writeln("z is not positive");
        }
    } else {
        if (z < 10) {
            writeln("x > 40 and z < 10, but y < 15");
        } else {
            writeln("x > 40, but y < 15 and z >= 10");
        }
    }
} else {
    if (y >= 15) {
        writeln("x <= 40 but y >= 15");
    } else {
        writeln("Both x and y below threshold");
    }
}

/* Test 8: Nested if with sequential value changes */
writeln("Test 8: Sequential Nested Checks");
x = 1;
if (x == 1) {
    writeln("Step 1: x is 1");
    x = 2;
    if (x == 2) {
        writeln("Step 2: x is now 2");
        x = 3;
        if (x == 3) {
            writeln("Step 3: x is now 3");
            x = 4;
            if (x == 4) {
                writeln("Step 4: x is now 4 - Success");
            }
        }
    }
}

writeln("===== ALL TESTS COMPLETED =====");

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
        writeln(arr[i]);
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

writeln("Testing variable-length array parameters:");
writeln("Array contents:");
printArray(myArray);

writeln("Sum of array elements:");
result = sumArray(myArray);
writeln(result);

writeln("Testing fixed-size array parameter:");
result = processFixed(myArray);
writeln(result);

writeln("Test completed successfully!");
