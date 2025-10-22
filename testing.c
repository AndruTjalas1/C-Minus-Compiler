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
