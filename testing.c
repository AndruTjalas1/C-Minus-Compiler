/* Test file for switch-case and break/continue statements */

int main;
int choice;
int counter;
int i;

choice = 2;

/* Switch statement with multiple cases */
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
for (i = 0; i < 10; i++) {
    write(i);
    if (i == 5) {
        break;
    }
}

/* While loop with continue */
counter = 0;
while (counter < 9) {
    counter++;
    if (counter == 3) {
        continue;
    }
    write(counter);
}

/* Switch with fall-through (no break) */
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
