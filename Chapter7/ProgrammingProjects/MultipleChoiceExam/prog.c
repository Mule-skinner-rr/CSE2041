/*
Name - Nikhil Ranjan Nayak
Regd No - 1641012040
Desc - Multiple Choice Exam
*/
#include <stdio.h>
void fgetAnswers(char[], int, FILE*);
void main()
{
	FILE *input = fopen("examdat.txt", "r");
	int n, i;

	char answers[20], space;
	
	fscanf(input, "%d", &n);
	fscanf(input, "%c", &space);
	
	for(i = 0; i < n ; i++)
	{
		fscanf(input, "%c", &answers[i]);
	}
	
	fgetAnswers(answers, n, input);
	
	fclose(input);
}


void fgetAnswers(char answers[], int n, FILE *input)
{
	FILE *output = fopen("report.txt", "w");
	
	int missed[n], i, id, correct;
	char choice;
	char space, y_or_n;
	
	/* BEGIN: Added functionality... */
	char space, y_or_n;

    printf("Do you have any more scores to enter?\n");
    printf("Please enter 'y' or 'n'> ");
    scanf(" %c", &y_or_n);

    if(y_or_n == 'y') {
        fclose(input);
        /* closing 'input' pointer so I can re-open it as an append file */
        
        input = fopen("examdat.txt", "a");
        /* This opens "examdat_1G" for more data.  "a" stands for append. */
        
        if(input == NULL)
            perror("input didn't open\n");
        /* checking if 'input' file opened. */
        
        fprintf(input, "\n");
        /* appends a line escape sequence to the end of "examdat_1G.txt", which assumes the insertion point is at the end of the last line instead of at the beginning of a new one. */
        do {
            printf("\nPlease enter the ID# > ");
            scanf("%d", &id);
            fprintf(input, "%d ", id);
            /* Scans in the id# with a space and appends it to the 'input' file. */
            
            for(i=0; i<n; ++i) {
                printf("\nPlease enter each letter answer followed by the \"return\" key\n> ");
                scanf(" %c", &choice);
                fprintf(input, "%c", choice);
            }
            fprintf(input,"\n");
            
            printf("Do you have any more scores to enter?\n");
            printf("Please enter 'y' or 'n'> ");
            scanf(" %c", &y_or_n);
            
        } while(y_or_n == 'y');
        
        fclose(input);
        /* closes 'input' so the program can re-open it as a read, "r", file. */
        
        input = fopen("examdat.txt", "r");
        
        if(input == NULL)
            perror("input didn't open\n");
        
        fscanf(input, "%d", &n);
        fscanf(input, "%c", &space);
        /* re-opens input file with appended information */
        
        for (i=0; i<n; ++i) {
            fscanf(input, "%c", &answers[i]);
        }
        /* Re-scans the first number and five letters in the file so that the program does not print them as a student ID and quiz responses. Closing and reopening "examdat.txt" as a read file causes the compiler to read from the beginning of the file instead of where it left off in in the main funciton. */
    }
	/* ...END: Added functionality */
	
	for(i = 0; i < n; i++)
	{
		missed[i] = 0;
	}
	
	fprintf(output, "%10c Exam Report %2c", ' ', ' ');
	fprintf(output, "\nQuestion %2c", ' ');

	for(i = 0; i < n ; i++)
	{
		fprintf(output, "%d ", i);
	}

	fprintf(output,"\nAnswer %3c", ' ');
	
	for(i = 0; i < n ; i++)
	{
		fprintf(output, "%c ", answers[i]);
	}
	
	fprintf(output, "\n\nID %2c Score(%%)\n", ' ');
	
	while(fscanf(input, "%d", &id) != EOF)
	{
		correct = 0;
		fprintf(output, "%d %2c", id, ' ');
		fscanf(input, "%c", &choice);
		
		for(i = 0; i < n ; i++)
		{
			fscanf(input, "%c", &choice);
			
			if(choice == answers[i])
				correct++;
			else
				missed[i]++;
		}
		fprintf(output, "%d\n", (correct * 100) / n);
	}

	fprintf(output, "\nQuestion %2c", ' ');
	
	for(i = 0; i < n ; i++)
	{
		fprintf(output, "%d ", i);
	}

	fprintf(output, "\nMissed by %2c", ' ');

	for(i = 0; i < n ; i++)
	{
		fprintf(output, "%d ", missed[i]);
	}
	
	fclose(output);
}
