#include <stdio.h>
#include <stdlib.h> // For exit()
 
int main()
{
    FILE *fptr;
    char filename[100], c;
    int i=0;
    int file_no;
    printf("Enter The no.of Bin Files You Want To create:\n");
    scanf("%d",&file_no);
    for(i=0;i<file_no;i++)
{

    printf("Enter the filename to open for reading \n");
    scanf("%s", filename);
     fptr= fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }
   fclose(fptr);
}
return 0;
}
