#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 128

void generate_password(int length, int include_upper, int include_lower, int include_digits, int include_special, int exclude_similar) {
    char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower[] = "abcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    char special[] = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~";
    char exclude[] = "0O1Il";  

    char allowed_chars[MAX_PASSWORD_LENGTH];
    int index = 0;

    if (include_upper) {
        strcpy(&allowed_chars[index], upper);
        index += strlen(upper);
    }
    if (include_lower) {
        strcpy(&allowed_chars[index], lower);
        index += strlen(lower);
    }
    if (include_digits) {
        strcpy(&allowed_chars[index], digits);
        index += strlen(digits);
    }
    if (include_special) {
        strcpy(&allowed_chars[index], special);
        index += strlen(special);
    }

    if (exclude_similar) {
        int exclude_len = strlen(exclude);
        for (int i = 0; i < exclude_len; i++) {
            for (int j = 0; j < index; j++) {
                if (allowed_chars[j] == exclude[i]) {
                    for (int k = j; k < index - 1; k++) {
                        allowed_chars[k] = allowed_chars[k + 1];
                    }
                    index--;
                    j--;
                }
            }
        }
    }

    srand(time(NULL));

    printf("Generated Password: ");
    for (int i = 0; i < length; i++) {
        int random_index = rand() % index;
        printf("%c", allowed_chars[random_index]);
    }
    printf("\n");
}

int main() {
    int password_length, num_passwords;
    int include_upper, include_lower, include_digits, include_special, exclude_similar; 


    printf("Enter the desired password length (max %d): ", MAX_PASSWORD_LENGTH);
    scanf("%d", &password_length);
    if (password_length > MAX_PASSWORD_LENGTH) {
        password_length = MAX_PASSWORD_LENGTH;
        printf("Password length set to maximum (%d).\n", MAX_PASSWORD_LENGTH);
    }


    printf("Include uppercase letters (1 for Yes, 0 for No): ");
    scanf("%d", &include_upper);
    printf("Include lowercase letters (1 for Yes, 0 for No): ");
    scanf("%d", &include_lower);
    printf("Include digits (1 for Yes, 0 for No): ");
    scanf("%d", &include_digits);
    printf("Include special characters (1 for Yes, 0 for No): ");
    scanf("%d", &include_special);
    printf("Exclude similar characters (1 for Yes, 0 for No): ");
    scanf("%d", &exclude_similar);

    
    //printf("How many passwords would you like to generate? ");
    //scanf("%d", &num_passwords);

    //for (int i = 0; i < num_passwords; i++) {
        generate_password(password_length, include_upper, include_lower, include_digits, include_special, exclude_similar);
    //}

    return 0;
}