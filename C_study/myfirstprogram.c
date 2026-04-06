#include <stdio.h>

int main() {
    int arr[] = {0, 1, 2, 3};
    int *ptr = arr;
    printf("%d\n", *ptr++);
    printf("%d\n", *ptr + 1);

    return 0;
}