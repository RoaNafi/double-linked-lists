#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//ro'a zaki
//prject #2
// 2023

typedef struct List {
    int number;
    struct List *next;
} List;

typedef struct Number {
    List *head;
    char sign;
    int size;
} Number;

Number n1;
Number n2;
Number res;

// Function to free the memory allocated for a linked list
void free_list(List *head);

// Function to remove the newline character from a string
void remove_newline(char *str) {
    size_t len = strcspn(str, "\n");
    str[len] = '\0';
}

// Function to load numbers from strings into the program's data structures
void load_numbers(char *num1, char *num2) {
    remove_newline(num1);
    remove_newline(num2);

    // Determine the sign of num1
    if (num1[0] == '-') {
        n1.sign = '-';
        num1++; // Skip the '-' character
    } else {
        n1.sign = '+';
    }

    // Determine the sign of num2
    if (num2[0] == '-') {
        n2.sign = '-';
        num2++; // Skip the '-' character
    } else {
        n2.sign = '+';
    }

    // Count the size of num1 and num2
    n1.size = (int) strlen(num1);
    n2.size = (int) strlen(num2);

    // Initialize the head pointers of the lists
    n1.head = NULL;
    n2.head = NULL;

    // Load num1 into the linked list n1.head
    List *current = NULL;
    for (int i = 0; i < n1.size; i++) {
        int digit = num1[i] - '0';
        List *node = (List *) malloc(sizeof(List));
        node->number = digit;
        node->next = NULL;

        if (n1.head == NULL) {
            n1.head = node;
            current = node;
        } else {
            current->next = node;
            current = current->next;
        }
    }

    // Load num2 into the linked list n2.head
    current = NULL;
    for (int i = 0; i < n2.size; i++) {
        int digit = num2[i] - '0';
        List *node = (List *) malloc(sizeof(List));
        node->number = digit;
        node->next = NULL;

        if (n2.head == NULL) {
            n2.head = node;
            current = node;
        } else {
            current->next = node;
            current = current->next;
        }
    }
}

// Function to compare two numbers and return the result
int compare_numbers() {
    // Compare the sizes of the numbers
    if (n1.size > n2.size) {
        return 1; // n1 is bigger
    } else if (n1.size < n2.size) {
        return -1; // n2 is bigger
    }

    // Compare the individual digits
    List *current1 = n1.head;
    List *current2 = n2.head;
    while (current1 != NULL && current2 != NULL) {
        if (current1->number > current2->number) {
            return 1; // n1 is bigger
        } else if (current1->number < current2->number) {
            return -1; // n2 is bigger
        }

        current1 = current1->next;
        current2 = current2->next;
    }

    // If the loop ends without a clear winner, the numbers are equal
    return 0;
}

// Function to choose two numbers from a file
void choose_two_numbers(char filename[]) {
    char num1[512], num2[512];
    free_list(n1.head);
    free_list(n2.head);
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("ERROR: File does not exist or is empty. Please try again.");
        exit(1);
    }

    printf("Choose from the numbers below:\n");
    int temp_inc = 1;
    char number[512];
    int idx1, idx2;

    while (fgets(number, sizeof(number), f)) {
        printf("%d. %s\n", temp_inc, number);
        temp_inc++;
    }
    fclose(f);
    f = fopen(filename, "r");
    
    printf("Choose the first number:");
    scanf("%d", &idx1);
    while (idx1 > temp_inc - 1) {
        printf("Wrong input. Please try again:");
        scanf("%d", &idx1);
    }

    printf("Choose the second number:");
    scanf("%d", &idx2);
    while (idx2 > temp_inc - 1) {
        printf("Wrong input. Please try again:");
        scanf("%d", &idx2);
    }

    temp_inc = 1;

    while (fgets(number, sizeof(number), f)) {
        if (temp_inc == idx1) {
            strcpy(num1, number);
        }
        if (temp_inc == idx2) {
            strcpy(num2, number);
        }
        temp_inc++;
    }
    fclose(f);

    load_numbers(num1, num2);
}

// Function to print the numbers
void print_numbers(Number n) {
    List *current = n.head;
    printf("Number: ");
    printf(" %c", n.sign);
    while (current != NULL) {
        printf("%d", current->number);
        current = current->next;
    }
    printf("\n");
}

// Function to reverse a linked list
List *reverse_list(List *head) {
    List *prev = NULL;
    List *current = head;
    List *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;  // Return the new head of the reversed list
}

// Function to compare two integers and return the maximum
int cmp_size(int a, int b) {
    if (a > b)
        return a;
    return b;
}
// Function to perform addition of two numbers
void add() {
    res.size = cmp_size(n1.size, n2.size);
    res.size += 1;
    List *reversed1 = reverse_list(n1.head);
    List *reversed2 = reverse_list(n2.head);
    List *temp1 = reversed1;
    List *temp2 = reversed2;
    List *res_reversed = NULL;
    List *res_prev = NULL;
    int carry = 0;
    int res_temp;
    int num1, num2;
    for (int i = 0; i < res.size; i++) {
        if (reversed1 != NULL) {
            num1 = reversed1->number;
            reversed1 = reversed1->next;
        } else {
            num1 = 0;
        }
        if (reversed2 != NULL) {
            num2 = reversed2->number;
            reversed2 = reversed2->next;
        } else {
            num2 = 0;
        }
        res_temp = num1 + num2 + carry;
        carry = res_temp / 10;
        res_temp %= 10;

        List *new_node = (List *) malloc(sizeof(List));
        new_node->number = res_temp;
        new_node->next = NULL;

        if (res_reversed == NULL) {
            res_reversed = new_node;
            res_prev = new_node;
        } else {
            res_prev->next = new_node;
            res_prev = res_prev->next;
        }
    }

    res.head = reverse_list(res_reversed);
    n1.head = reverse_list(temp1);
    n2.head = reverse_list(temp2);
    res_reversed = NULL;  // No longer needed, as it is stored in res.head
}


// Function to perform subtraction of two numbers
void sub(Number c1, Number c2) {
    List *reversed2;
    List *reversed1;
    reversed1 = reverse_list(c1.head);
    reversed2 = reverse_list(c2.head);
    res.size = cmp_size(n1.size, n2.size);
    List *temp1 = reversed1;
    List *temp2 = reversed2;
    List *res_reversed = NULL;
    List *res_prev = NULL;
    int borrow = 0;
    int res_temp;
    int num1, num2;
    for (int i = 0; i < res.size; i++) {
        if (reversed1 != NULL) {
            num1 = reversed1->number;
            reversed1 = reversed1->next;
        } else {
            num1 = 0;
        }
        if (reversed2 != NULL) {
            num2 = reversed2->number;
            reversed2 = reversed2->next;
        } else {
            num2 = 0;
        }
        num1 -= borrow;
        if (num1 < num2) {
            borrow = 1;
            num1 += 10;
        } else {
            borrow = 0;
        }
        res_temp = num1 - num2;

        List *new_node = (List *) malloc(sizeof(List));
        new_node->number = res_temp;
        new_node->next = NULL;

        if (res_reversed == NULL) {
            res_reversed = new_node;
            res_prev = new_node;
        } else {
            res_prev->next = new_node;
            res_prev = res_prev->next;
        }
    }

    res.head = reverse_list(res_reversed);
    reverse_list(temp1);
    reverse_list(temp2);
    res_reversed = NULL;  // No longer needed, as it is stored in res.head
}

// Function to free the memory allocated for a linked list
void free_list(List *head) {
    List *current = head;
    while (current != NULL) {
        List *temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to perform multiplication of two numbers
void mul() {
    List *reversed1 = reverse_list(n1.head);
    List *reversed2 = reverse_list(n2.head);

    int max_size = n1.size + n2.size;
    int result[max_size];
    for (int i = 0; i < max_size; i++) {
        result[i] = 0;
    }

    List *current1 = reversed1;
    List *current2;
    int pos1 = 0, pos2;

    while (current1) {
        int carry = 0;
        int a = current1->number;

        pos2 = 0;
        current2 = reversed2;

        while (current2) {
            int b = current2->number;
            int sum = a * b + result[pos1 + pos2] + carry;

            carry = sum / 10;
            result[pos1 + pos2] = sum % 10;

            current2 = current2->next;
            pos2++;
        }

        if (carry > 0) {
            result[pos1 + pos2] += carry;
        }

        current1 = current1->next;
        pos1++;
    }

    // Create result list
    List *res_reversed = NULL;
    List *res_prev = NULL;
    int size = 0;
    for (int i = 0; i < max_size; i++) {
        if (result[i] > 0 || size > 0) {
            List *new_node = (List *) malloc(sizeof(List));
            new_node->number = result[i];
            new_node->next = NULL;
            size++;

            if (res_reversed == NULL) {
                res_reversed = new_node;
                res_prev = new_node;
            } else {
                res_prev->next = new_node;
                res_prev = res_prev->next;
            }
        }
    }

    res.head = reverse_list(res_reversed);
    res.size = size;

    // Determine the sign
    if (n1.sign == n2.sign) {
        res.sign = '+';
    } else {
        res.sign = '-';
    }

    // Reverse the input lists back
    reverse_list(reversed1);
    reverse_list(reversed2);
}

// Function to compare two numbers represented by linked lists
int compare_numbers_with_lists(List *num1, List *num2) {
    int size1 = 0, size2 = 0;
    List *temp1 = num1, *temp2 = num2;

    // Calculate the size of both numbers
    while (temp1) {
        size1++;
        temp1 = temp1->next;
    }
    while (temp2) {
        size2++;
        temp2 = temp2->next;
    }

    // If sizes are different, the longer number is greater
    if (size1 < size2) {
        return -1;
    } else if (size1 > size2) {
        return 1;
    }

    // Compare digits for numbers of the same size
    temp1 = num1;
    temp2 = num2;
    while (temp1) {
        if (temp1->number < temp2->number) {
            return -1;
        } else if (temp1->number > temp2->number) {
            return 1;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    // If all digits are the same, the numbers are equal
    return 0;
}

// Function to subtract two linked lists representing numbers
List *subtract_lists(List *num1, List *num2) {
    List *result = NULL, *temp = NULL, *prev = NULL;
    int borrow = 0;

    while (num1) {
        int sub = ((num1->number) - borrow);

        if (num2) {
            sub -= num2->number;
            num2 = num2->next;
        }

        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        temp = (List *) malloc(sizeof(List));
        temp->number = sub;
        temp->next = NULL;

        if (!result) {
            result = temp;
        } else {
            prev->next = temp;
        }
        prev = temp;

        num1 = num1->next;
    }

    return result;
}

// Function to perform division of two numbers
void division() {
    if (n2.head == NULL || (n2.head->number == 0 && n2.head->next == NULL)) {
        printf("Cannot divide by zero.\n");
        return;
    }

    List *num1 = n1.head;
    List *num2 = n2.head;

    int max_size = n1.size + 1;
    int quotient[max_size];
    for (int i = 0; i < max_size; i++) {
        quotient[i] = 0;
    }

    List *currentQuotient = NULL;
    List *lastQuotient = NULL;

    int idx = 0;

    List *currentDividend = NULL;
    List *lastDividend = NULL;

    while (num1) {
        List *newNode = (List *) malloc(sizeof(List));
        newNode->number = num1->number;
        newNode->next = NULL;

        if (!currentDividend) {
            currentDividend = newNode;
        } else {
            lastDividend->next = newNode;
        }
        lastDividend = newNode;

        int cmp = compare_numbers_with_lists(currentDividend, num2);

        if (cmp >= 0) {
            int count = 0;

            while (cmp >= 0) {
                currentDividend = subtract_lists(currentDividend, num2);
                count++;
                cmp = compare_numbers_with_lists(currentDividend, num2);
            }

            List *newQuotientNode = (List *) malloc(sizeof(List));
            newQuotientNode->number = count;
            newQuotientNode->next = NULL;

            if (!currentQuotient) {
                currentQuotient = newQuotientNode;
            } else {
                lastQuotient->next = newQuotientNode;
            }
            lastQuotient = newQuotientNode;

            quotient[idx] = count;
        } else {
            if (currentQuotient) {
                List *newQuotientNode = (List *) malloc(sizeof(List));
                newQuotientNode->number = 0;
                newQuotientNode->next = NULL;
                lastQuotient->next = newQuotientNode;
                lastQuotient = newQuotientNode;

                quotient[idx] = 0;
            }
        }
        num1 = num1->next;
        idx++;
    }

    res.head = currentQuotient;
    res.size = idx;

    if (n1.sign == n2.sign) {
        res.sign = '+';
    } else {
        res.sign = '-';
    }
}

// Function to save the result to a file
void save_to_file(Number result) {
    char ch;
    printf("Do you want to save this output to output.txt? [y/n]");
    scanf(" %c", &ch);
    while (ch != 'y' && ch != 'n') {
        printf("Wrong input. Please try again:");
        scanf(" %c", &ch);
    }
    if (ch == 'n')
        return;
    FILE *f = fopen("output.txt", "a");
    if (!f) {
        printf("Error opening file output.txt\n");
        return;
    }

    List *current = result.head;
    fprintf(f, "%c", result.sign);
    while (current != NULL) {
        fprintf(f, "%d", current->number);
        current = current->next;
    }
    fprintf(f,"\n");
    fclose(f);
}

int main() {
    char filename[50];
    printf("Please enter a file name:");
    scanf("%s", filename);
    choose_two_numbers(filename);
    print_numbers(n1);
    print_numbers(n2);
    int result;

    int ch = 0;
    while (1) {
        free_list(res.head);
        res.head = NULL;
        res.sign = '\0';
        res.size = 0;
        printf("Please choose from the menu below:\n"
             "1. Choose another 2 numbers\n"
             "2. Multiplication\n"
             "3. Addition\n"
             "4. Subtraction\n"
             "5. Division\n"
             "6. Exit\n");
        scanf("%d", &ch);
        while (ch < 1 || ch > 6) {
            printf("Wrong input. Please try again:");
            scanf("%d", &ch);
        }
        switch (ch) {
            case 1:
                choose_two_numbers(filename);
                break;
            case 2:
                mul();
                print_numbers(n1);
                print_numbers(n2);
                print_numbers(res);
                save_to_file(res);
                break;
            case 3://Addition
                if (n1.sign != n2.sign) {
                    result = compare_numbers();
                    if (result == -1) {
                        sub(n2, n1);
                        res.sign = n2.sign;

                    } else {
                        sub(n1, n2);
                        res.sign = n1.sign;
                    }
                } else {
                    add();
                    res.sign = n1.sign;
                }

                print_numbers(n1);
                print_numbers(n2);
                print_numbers(res);
                save_to_file(res);
                break;
            case 4://Subtraction
                if (n1.sign != n2.sign) {
                    add();
                    res.sign = n1.sign;
                } else {
                    result = compare_numbers();
                    if (result == -1) {
                        sub(n2, n1);
                        if (n2.sign == '-')
                            res.sign = '+';
                        else
                            res.sign = '-';
                    } else {
                        sub(n1, n2);
                        res.sign = n1.sign;
                    }
                }

                print_numbers(n1);
                print_numbers(n2);
                print_numbers(res);
                save_to_file(res);
                break;
            case 5:
                division();
                print_numbers(n1);
                print_numbers(n2);
                print_numbers(res);
                save_to_file(res);
                break;
            case 6:
                free_list(n1.head);
                free_list(n2.head);
                free_list(res.head);
                exit(1);
            default:
                break;
        }
    }

}
