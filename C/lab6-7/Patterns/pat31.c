#include <stdio.h>
int main(){
    printf("Enter no. of rows : ");
    int n; scanf("%d",&n);
    for (int i=0; i<n; i++){
        for (int j=1; j<=n-i; j++)
            printf("%d",j);
        printf("\n");
    }
    printf("\n");
    for (int i=1; i<=n; i++){
        for (int j=1; j<=i; j++)
            printf("%d",j);
        printf("\n");
    }
    return 0;
}