/* Test file with various errors to demonstrate error handling */

/* Error 1: Undeclared variable */
/*x = 10;*/

/* Error 2: Missing semicolon */
int y = 20

/* Error 3: Trying to use an undeclared variable */
int z;
z = undeclaredVar + 5;

/* Error 4: Missing closing brace */
if (z > 0) {
    write(z);

/* This would be correct */
int correct;
correct = 100;
write(correct);
