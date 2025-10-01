/* Test conditional statements */

int x;
int y;

x = 10;
y = 5;

/* Simple if */
if (x > y) {
    write(x);
}

/* If-else */
if (x < y) {
    write(y);
} else {
    write(x);
}

/* If-elseif-else */
if (x == 5) {
    write(1);
} elseif (x == 10) {
    write(2);
} else {
    write(3);
}
