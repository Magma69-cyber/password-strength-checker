#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Function to check password strength
void check_pwd(char *password) {
    int strength = 0;
    int lower_count = 0, upper_count = 0, num_count = 0, wspace_count = 0, special_count = 0;
    char remarks[5][50] = {""};

    // Iterate through each character in the password
    for (int i = 0; i < strlen(password); i++) {
        if (islower(password[i])) {
            lower_count++;
        } else if (isupper(password[i])) {
            upper_count++;
        } else if (isdigit(password[i])) {
            num_count++;
        } else if (isspace(password[i])) {
            wspace_count++;
        } else {
            special_count++;
        }
    }

    // Calculate password strength
    if (lower_count >= 1) strength++;
    if (upper_count >= 1) strength++;
    if (num_count >= 1) strength++;
    if (wspace_count >= 1) strength++;
    if (special_count >= 1) strength++;

    // Check for common patterns
    if (strstr(password, "abc") || strstr(password, "123") || strstr(password, "qwerty")) {
        strcpy(remarks[0], "Password contains common pattern.");
    }

    // Determine password strength remarks
    if (strength == 1) {
        strcpy(remarks[1], "Very Bad Password!!! Change ASAP");
    } else if (strength == 2) {
        strcpy(remarks[1], "Not A Good Password!!! Change ASAP");
    } else if (strength == 3) {
        strcpy(remarks[1], "It's a weak password, consider changing");
    } else if (strength == 4) {
        strcpy(remarks[1], "It's a hard password, but can be better");
    } else if (strength == 5) {
        strcpy(remarks[1], "A very strong password");
    }

    // Print password analysis
    printf("Your password has: \n");
    printf("%d lowercase characters\n", lower_count);
    printf("%d uppercase characters\n", upper_count);
    printf("%d numeric characters\n", num_count);
    printf("%d whitespace characters\n", wspace_count);
    printf("%d special characters\n", special_count);
    printf("Password Strength: %d\n", strength);
    for (int i = 0; i < 5; i++) {
        if (strlen(remarks[i]) > 0) {
            printf("Hint: %s\n", remarks[i]);
        }
    }
}

// Function to generate a strong password
void generate_strong_pwd(int length) {
    char password[length + 1];
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+";

    srand(time(0));
    while (1) {
        for (int i = 0; i < length; i++) {
            password[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
        }
        password[length] = '\0';

        int has_lower = 0, has_upper = 0, has_digit = 0, has_special = 0;
        for (int i = 0; i < length; i++) {
            if (islower(password[i])) has_lower = 1;
            else if (isupper(password[i])) has_upper = 1;
            else if (isdigit(password[i])) has_digit = 1;
            else has_special = 1;
        }
        if (has_lower && has_upper && has_digit && has_special) {
            break;
        }
    }
    printf("Generated strong password: %s\n", password);
}

// Function to ask user if they want to check another password
int ask_pwd(int another_pwd) {
    char choice[2];
    int valid = 0;

    if (another_pwd) {
        printf("Do you want to enter another pwd (y/n): ");
    } else {
        printf("Do you want to check pwd (y), generate strong pwd (g) or quit (q): ");
    }

    while (!valid) {
        scanf(" %1s", choice);
        if (strcmp(choice, "y") == 0) {
            return 1;
        } else if (strcmp(choice, "n") == 0) {
            return 0;
        } else if (strcmp(choice, "g") == 0) {
            generate_strong_pwd(12);
            return 0;
        } else if (strcmp(choice, "q") == 0) {
            return 0;
        } else {
            printf("Invalid, Try Again\n");
            if (another_pwd) {
                printf("Do you want to enter another pwd (y/n): ");
            } else {
                printf("Do you want to check pwd (y), generate strong pwd (g) or quit (q): ");
            }
        }
    }
    return 0;
}

// Main program
int main() {
    printf("+++ welcome to PWD checker +++\n");

    // Ask user if they want to check a password
    int ask_pw = ask_pwd(0);

    // Check password strength
    while (ask_pw) {
        char password[100];
        printf("Enter Password: ");
        scanf("%99s", password);
        check_pwd(password);
        ask_pw = ask_pwd(1);
    }

    return 0;
}
