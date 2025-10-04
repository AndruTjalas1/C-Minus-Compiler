/* Simple loop test - counts 1 to 5 three different ways */

/* For loop */
int i;
for (i = 1; i <= 5; i = i + 1) {
    write(i);
}

/* While loop */
int j;
j = 1;
while (j <= 5) {
    write(j);
    j = j + 1;
}

/* Do-while loop */
int k;
k = 1;
do {
    write(k);
    k = k + 1;
} while (k <= 5);
