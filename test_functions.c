
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

/* Function that calculates factorial */
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

/* Function with no parameters */
function int getConstant() {
    return 42;
}

/* Main program */

int sum;
int product;
int fact;
int constant;

a = 5;
b = 3;

sum = add(a, b);
write(sum);

product = multiply(a, b);
write(product);

fact = factorial(5);
write(fact);

constant = getConstant();
write(constant);
