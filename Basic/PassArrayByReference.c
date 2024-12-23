#include <stdio.h>
// #include <conio.h>
/**the conio.h header is compiler-specific (Turbo C, Borland), and it's rarely used in modern compilers like GCC/Clang. It’s not required in this program, so you can remove it unless specifically needed.
 */
void showArrayElement(int *, int);
int main()
{

    int arr[] = {2, 4, 5, 6, 99};
    int i;

    int size = sizeof(arr) / sizeof(arr[0]);

    showArrayElement(arr, size);
    printf("Inside main \n");
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
void showArrayElement(int *arr, int size)
{ // C Sysntax
    int i;
    printf("Inside showArrayElement \n");
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
        arr[i] = arr[i] + 2;
    }

    printf("\n");
}