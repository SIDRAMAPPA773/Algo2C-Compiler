#include <stdio.h>
#include <string.h>

int main() {

    int i, x, total, m1, m2, m3, avg;
    char student[100];

    scanf("%99s", student);
    scanf("%d", &m1);
    scanf("%d", &m2);
    scanf("%d", &m3);
    total = m1 + m2 + m3;
    avg = total / 3;
    printf("%s\n", student);
    printf("%d\n", total);
    printf("%d\n", avg);
    if(avg >= 90) {
        printf("%d\n", avg);
    }
    else {
        if(avg >= 35) {
            printf("%d\n", total);
        }
        else {
            printf("%d\n", 0);
        }
    }
    for(i = 1; i <= 3; i++) {
        printf("%d\n", i);
    }
    x = 0;
    while(x < 5) {
        printf("%d\n", x);
        x = x + 1;
    }

    return 0;
}
