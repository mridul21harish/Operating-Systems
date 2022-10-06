#include <stdio.h>

int copy(char *, char *);
int main(int argc, char *argv[])
{
char *fn1 = argv[1]; //get the filename1 from the command line
char *fn2 = argv[2]; //get the filename2 from the command line

if (copy(fn2, fn1) == -1) 
{      
	printf("Error in copying\n");
	return 1;
}
    return 0;
}

int copy(char *fnDest, char *fnSrc)
{
int c;

FILE *fpDest, *fpSrc; //fpDest is the destination file pointer, fpSrc is the source file pointer    

if ((fpDest = fopen(fnDest, "w")) && (fpSrc = fopen(fnSrc, "r"))) 
{
	while ((c = getc(fpSrc)) != EOF)
		putc(c,fpDest);
	fclose(fpDest);
	fclose(fpSrc);	

	return 0;
}
    return -1;
}
