/* ============================================
   TEST: Functions with Loops and Conditionals
   ============================================ */

/* Helper function: Check if number is even (returns "true" or "false") */
function string isEven(int num) {
    if (num % 2 == 0) {
        return "true";
    }
    return "false";
}

/* Helper function: Calculate factorial */
function int factorial(int n) {
    int result = 1;
    int i = 2;
    while (i <= n) {
        result = result * i;
        i = i + 1;
    }
    return result;
}

/* Helper function: Sum of numbers */
function int sumNumbers(int a, int b) {
    int total = 0;
    total = a + b;
    return total;
}

/* Function with if-else inside loop */
function int countLoop(int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            count = count + 1;
        }
    }
    return count;
}

/* Function with while loop and conditionals */
function int processLoop(int max) {
    int sum = 0;
    int i = 0;
    while (i < max) {
        if (i > 2) {
            sum += i;
        }
        i++;
    }
    return sum;
}

/* Function with do-while */
function int doWhileTest(int start) {
    int current = start;
    do {
        current = current - 1;
    } while (current > 0);
    return current;
}

/* Main program testing all features */
int testNum;
int intResult;
string stringResult;

write(100);

/* TEST 1: Simple function call - check if 6 is even */
testNum = 6;
stringResult = isEven(testNum);
write(stringResult);

/* TEST 2: Function with while loop - factorial(5) */
intResult = factorial(5);
write(intResult);

/* TEST 3: Function calls combined */
intResult = sumNumbers(3, 5);
write(intResult);

/* TEST 4: Function with loop and if statements */
intResult = countLoop(10);
write(intResult);

/* TEST 5: Function with while and conditionals */
intResult = processLoop(8);
write(intResult);

/* TEST 6: Function with do-while */
intResult = doWhileTest(10);
write(intResult);

/* TEST 7: Nested function calls in conditional */
testNum = 4;
stringResult = isEven(testNum);
write(stringResult);

write(999);
    