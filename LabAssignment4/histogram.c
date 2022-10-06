#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/mman.h>

FILE *open_file(char *filename);
void output_results(int *char_count);
int *count_letters(char *filename);

int main(int argc, char *argv[])
{
    	if (argc != 2)
    	{
        	printf("Syntax: %s <filename>\n", argv[0]);
        	return 1;
    	}

    	char *filename = argv[1];
    	FILE *file;

    	if((file = open_file(filename)) == NULL)
        	return 1;

    	output_results(count_letters(filename));

    	if (fclose(file) != 0)
    	{
        	printf("Error closing file!\n");
        	return 1;
    	}

    	return 0;
}

FILE *open_file(char *filename)
{
    	FILE *file;
    	file = fopen(filename, "r");

    	if (!file)
    	{
        	printf("Error opening file!\n");
        	return NULL;
    	}

    	return file;
}

void output_results(int *char_count)
{
    	long numbers_letters = 0;
    	long total_characters = 0;

    	for (int i = 32; i < 128; i = i+1)
    	{
        	total_characters = total_characters + char_count[i];
        	if (i >= 97 && i <= 122)
        	{
            		numbers_letters = numbers_letters + char_count[i];
    		}
    	}

    	printf("\n\t LETTER FREQUENCY STATISTICS \n\n");
    	printf("| Letter |  Count\t  [%%]\t\tGraphical\n");
    	printf("| ------ | --------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    	for (int i = 97; i < 123; i = i+1)
    	{
        	printf("|   %c    |  %0d ", i, char_count[i]);
        	printf("  \t%.2f%%\t\t", ((double)char_count[i] / numbers_letters) * 100);
        	
        	for(int j = 0; j < char_count[i]; j = j+1)
        	{
            		printf("♦");
            	}
        	printf("\n");
    	}

    	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    	printf("\n\t FILE DATA STATISTICS \n\n");
    	printf("| Char Type |  Count\t  [%%]\n");
   	printf("|---------- | ---------------------\n");

    	printf("|  Letters  |  %li", numbers_letters);
    	printf(" \t[%.2f%%]  |\n", ((double)numbers_letters / total_characters) * 100);
    	printf("|  Other    |  %li", total_characters - numbers_letters);
    	printf(" \t[%.2f%%]  |\n", ((double)(total_characters - numbers_letters) / total_characters) * 100);
    	printf("|  Total    |  %li\t\t  |\n\n", total_characters);
}

int *count_letters(char *filename)
{
    	int *char_count;
    	FILE *file;

    	char_count = mmap(NULL, 128 * sizeof(*char_count), PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    	for(int i = 0; i < 27; i = i+1)
    	{
        	int c;

        	if((file = open_file(filename)) == NULL)
        	{
			printf("Error opening file in child process %d!\n", getpid());
            		exit(1);
        	}	

        	pid_t pid = fork();

        	if(pid == -1)
        	{
			printf("Error forking process!\n");
			exit(1);
        	}
        	else if(pid == 0)
        	{
			while((c = tolower(fgetc(file))) != EOF)
            		{
                		if(i == 26 && (c < 97 || c > 122))
                		{
                			char_count[c] = char_count[c] + 1; 
                		}
                		else if (c == i + 97)
                		{
                    		char_count[i + 97] = char_count[i +97] + 1;
                    		} 
            		}

            	fclose(file);
            	exit(0);
        	}
        	else
        	{
            		rewind(file);
        	}
    	}

    	for (int i = 0; i < 27; i = i+1)
    	{
        	wait(NULL);
        }

    	return char_count;
}



