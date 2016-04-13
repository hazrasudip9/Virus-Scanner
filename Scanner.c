//Scanner Program//
//Sudip Hazra//
//...................................//


#include<stdio.h>
#include<glob.h>
#include<stdlib.h>
#include<openssl/md5.h>
#include<string.h>

void checker()
{

FILE *temp;
temp = fopen("md5temp.txt","r");
if(temp==NULL)
	{
		printf("Error!\n");
		exit(2);
	}
FILE *fptr;
fptr=fopen("md5hash.txt","r");
if(fptr==NULL)
{
    printf("Error!\n");
    exit(1);
}
		

char filename[256];
char l1[1024];
char l2[1024];
char *c1;
char *c2;
char w1[1024];
char w2[1024];


while ((c1 = fgets(l1, 1024, fptr)),
       (c2 = fgets(l2, 1024, temp)),
       c1 != NULL && c2 != NULL)
{	
    int n1;
    int n2;

    char *line1 = l1;
    char *line2 = l2;

    int r1;
    int r2;
     while ((r1 = sscanf(line1, "%1023s%n", w1, &n1)),
           (r2 = sscanf(line2, "%1023s%n", w2, &n2)),
           r1 == 1 && r2 == 1)
    	{
		printf("Scanning\n");	

    		
    		
         if (strcmp(w1, w2) != 0)
         {              
         		FILE *pfile1;
			char filename[10];
			char temp[40];
			sscanf(line1,"%s%s",temp,filename);
			printf("%s\n",filename);
			pfile1 = fopen(filename,"r");
         		long lsize;
			fseek(pfile1, 0 ,SEEK_END);
			lsize=ftell(pfile1);
			rewind(pfile1);
			char curchar;
			char searchchars[12]="DEADBEEFDEAD";
    		        int pos = 0;
			int cursearch=0;
			while(pos<=lsize)
				{
				curchar = getc(pfile1);
			pos++;
			if(curchar == searchchars[cursearch])
					{
						cursearch++;
						if(cursearch == 11)
							{
								printf("Alert!The File Has Been Infected\n");
							}
					}
			}


         }
	
            
        line1 += n1;
        line2 += n2;


        }
            
        
       
	
    }
    
    
    fclose(temp);
    fclose(fptr);                                    
}

	

 int main(int argc, char const *argv[])
 {	
    
 	
	

	int datafresh=0;
	int k;
	glob_t pglob;
	const char *pattern = "*.bin";
	glob(pattern,GLOB_ERR,NULL,&pglob);
 	printf("Found %d .bin files\n",pglob.gl_pathc);
	if(pglob.gl_pathc==0)
	exit(0);
 	printf("First match: %s\n", pglob.gl_pathv[0]);



	
	while(1){
	if (datafresh == 0)
		{
		FILE *fptr;
   		fptr=fopen("md5hash.txt","w");
       		 if(fptr==NULL)
		{
      		printf("Error!\n");
      		exit(1);
		}
		
		printf("%d\n",datafresh);
		for(k=0;k<pglob.gl_pathc;k++)
	
			{	
				printf("Main Database Created\n");
				int j=0;
				unsigned char c[MD5_DIGEST_LENGTH];
 				char *filename =pglob.gl_pathv[k];
				FILE *inFile = fopen(filename,"rb");
 				MD5_CTX mdContext;
				int bytes;
 				unsigned char data[64];
 				if(inFile == NULL)
 					{
 						printf("%s can't be opened.\n",filename);
 						return 0;
					}
 				MD5_Init (&mdContext);
    				while ((bytes = fread (data, 1, 64, inFile)) != 0)
        			MD5_Update (&mdContext, data, bytes);
    				MD5_Final (c,&mdContext);
				for(j = 0; j < MD5_DIGEST_LENGTH; j++)
					{ 	
						fprintf(fptr,"%02x", c[j]);
						
					}
				fprintf(fptr," %s",filename);
					
				fprintf(fptr,"\n");
				
				fclose (inFile);
					  
    
		}

		rewind(fptr);
		fclose(fptr);
		datafresh = datafresh+1; 
		
	
	}
	


else{	
 	printf("%d\n",datafresh);
	FILE *temp;
	
	temp = fopen("md5temp.txt","w");
			if(temp==NULL)
				{
					printf("Error!\n");
					exit(2);
				}
    	for(k=0;k<pglob.gl_pathc;k++)
    	
		{		
   			
			
			int j;
 			unsigned char c[MD5_DIGEST_LENGTH];
 			char *filename =pglob.gl_pathv[k];
			FILE *inFile = fopen(filename,"rb");
 			MD5_CTX mdContext;
			int bytes;
 			unsigned char data[64];
 			if(inFile == NULL)
 				{
 					printf("%s can't be opened.\n",filename);
 					return 0;
				}
 			MD5_Init (&mdContext);
    			while ((bytes = fread (data, 1, 64, inFile)) != 0)
        		MD5_Update (&mdContext, data, bytes);
    			MD5_Final (c,&mdContext);
			for(j = 0; j < MD5_DIGEST_LENGTH; j++)
				{ 
					fprintf(temp,"%02x", c[j]);

				}

				fprintf(temp," %s",filename);
				fprintf(temp,"\n");
				fclose (inFile);
			}
			rewind(temp);
			fclose(temp);
			sleep(10);
			
			checker();
			
			
			

				
}
printf("Press Q to exit\n");
char Input;
scanf("%c",&Input);
printf("You Entered %c\n",Input);
if(Input=='Q')
exit(0);

}

							


	
	
   	return 0;
}

