
#include <stdio.h>

int main() {
    int n;
    printf("Enter number of threads: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        printf("Hello, World from thread %d\n", i);
    }
    return 0;
}
