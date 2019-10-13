/*******************************************************
// NAME: Aaron Kam
//
// HOMEWORK:
//
// CLASS:      ICS 212
//
// INSTRUCTOR: Ravi Narayan
//
// DATE:
//
// FILE: homework.c
//
// DESCRIPTION:
//    This file contains the program for printing the lines "Name: Aaron Kam",
//
//
********************************************************/

#include <stdio.h>



/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   A driver for the iofunctions file
//
//
//   Parameters:    argc (int) : contains the number of arguments
//                      which will be processed
//                   argV[] (char[]) : contains the arguments for the file
//
//   Return values:  0 : stops the no return warning when compiling
//
****************************************************************/

struct record
{
   int                accountno;
   char               name[25];
   char               address[80];
};

int readfile( struct record accarray[], int* numcust, char filename[] );
int writefile( struct record accarray[], int numcust, char filename[] );

int main(int argc, char ** argv)
{
    struct record bankone[5];
    int numcustomers = 0;
    char rfilename[] = "nope.txt";
    char wfilename[] = "write.txt";
    int option;
    int work = 0;
    int i = 0;
    int quit = 0;
    while(!quit)
    {
        printf("Press 1 to read a file or\nPress 2 to write a file\nPress enter to finalize option");
        scanf("%d", &option);
        if (option == 1)
        {
            printf("Reading file\n");
            readfile(bankone, &numcustomers, rfilename);
            if (work)
            {
                printf("%d", numcustomers);
                while(i < numcustomers)
                {
                    printf("numcustomers: %d\n", numcustomers);
                    printf("accountno: %d\nname: %s\naddress: %s\n", bankone[i].accountno, bankone[i].name, bankone[i].address);
                    i++;
                }
            }
            else
            {
                printf("Readfile failed\n");
            }
        }
        else if (option == 2)
        {
            printf("Writing file\n");
            work = writefile(bankone, numcustomers, wfilename);
            printf("%d", work);
        }
        else if (option == 3)
        {
            quit = 1;
        }
        while(getchar() != '\n');
    }

    return 0;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   reads a pre-formatted text file into a record struct
//
//
//   Parameters:     accarray (struct record[]) : contains the account pointers
//                      for the member variables
//
//                   numcust[] (int*) : contains the pointer for the number
//                      of customers in the file, and gets updated to reflect it
//
//                   filename (char[]) : the name of the file being read
//
//   Return values:  0 : stops the no return warning when compiling
//
****************************************************************/

int readfile(struct record accarray[], int* numcust, char filename[])
{
   
    FILE *file = fopen(filename, "r");
    int mode;
    int j = 0;
    int i = 0;
    int retval = 0;
    char c = '\0';
    
    if (file == NULL)
    {
        retval = -1;
    }

    while(retval == 0 && i < 5)
    {
        if (feof(file) != 0)
        {
            printf("EOF\n");
            retval = 1;
        }
        else
        {
            c = '\0';
            j = 0;
            mode = 0;
            accarray[i].accountno = -1;
            while(c != '@')
            {
                if (mode == 0)
                {
                    fscanf(file,"%d", &accarray[i].accountno);
                    mode++;
                }
                if (mode == 1)
                {
                    c = fgetc(file);
                    
                    if (c != '?')
                    {
                        accarray[i].name[j++] = c;
                    }
                    else
                    {
                        accarray[i].name[j] = '\0';
                        j = 0;
                        mode++;                     
                    }
                }
                if (mode == 2)
                {
                    c = fgetc(file);
                    if (c != '@')
                    {
                        accarray[i].address[j++] = c;
                    }
                    else if (accarray[i].accountno != -1 && c == '@')
                    {
                        accarray[i].address[j] = '\0';
                    }
                }
            }
            
        }
        i++;
    }
    fclose(file);
    return retval;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   reads a pre-formatted text file into a record struct
//
//
//   Parameters:     accarray (struct record[]) : contains the account pointers
//                      for the member variables
//
//                   numcust[] (int) : contains the number of records to write
//
//                   filename (char[]) : the name of the file being written
//
//   Return values:  0 : stops the no return warning when compiling
//
****************************************************************/

int writefile(struct record accarray[], int numcust, char filename[])
{
    FILE *file;
    int i = 0;
    int retval = 0;
    char accinfo[120];
    file = fopen(filename, "w+");
    while(i < numcust && retval >= 0)
    {
        retval = sprintf(accinfo, "%d%s?%s@", accarray[i].accountno, accarray[i].name, accarray[i].address);
        fputs(accinfo, file);
        i++;
    }
    
    fclose(file);
    return retval;
}
