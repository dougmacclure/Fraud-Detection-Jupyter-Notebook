//********************************************************************
// Doug MacClure
// CSCI330-3 
// Assignment 9
// This program is designed to emulate the Unix command "tee" to a certain
// degree of functionality.  It takes input from standard input (file descriptor 0)
// and copies it into multiple files.  -a allows us to append the files.
// NOTE: This program expects command line arguments.
// COMMAND LINE FORMAT: ./z0125061 [-a] outFile1 [outFile2] [outFile3] ...
//
//********************************************************************


#

#include <regex.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <istream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

//we are given input from a command that is piped into or typed into this program
//we want to take that stream of input, and copy it into a list
//of files indicated as command line arguments

int main(int argc, char* argv[])
{

//this array holds the file descriptors for all files that are to be created/opened 
int filed[argc - 1];

//we use this C-string to copy data from standard input into the various outFiles
//char *line = NULL;
char buffer[100000] ={0};
char buff[1024];
int count = 1;
int k;
int j;
//size_t k = 0;
char option[] = "-a";
char rexpop[] = "-f";
regex_t regex;
int rs;

//if the only command line argument is the name of the program, send error message and exit
if(argc < 2)
	
		{
		
		cerr << "Not enough command line arguments.  Format: z0125061.tee [-a] outFile1 [outfile2] ...";
		exit(EXIT_FAILURE);
		
		}


//case 1: we do not want to append our output

if(strcmp(argv[1], option) != 0)

	{
		
	j = 0;
	//for(unsigned i = 0; i < sizeof(option); i++)
		
	for(int i = 1 + j; i < argc; i++)
	
		{
			cerr << argv[i];
		
			if(strcmp(argv[i],rexpop) == 0)
				
				i+=2;
		
			cerr << argv[i];
			//open the file indicated in argv[i], and store the resulting file
			//descriptor from calling the open system call into the file descriptor array
			filed[i-1] = open(argv[i], O_WRONLY | O_CREAT, 00666);
			//if we got a bad return status from open system call, indicate file can't be opened
			//and move onto next file
			if (filed[i-1] == -1)
		
				{
				
				cerr << argv[i] << " can't be opened.\n";
							
				}


		}
		
	}

//case 2: we want to append output to files
else

	{

	//if the command line only consists of the name of the file and the -a option, indicate error and exit

	if(argc < 3)
	
		{
		
		cerr << "Not enough command line arguments.  Format: z0125061.tee [-a] outFile1 [outfile2] ...";
		exit(EXIT_FAILURE);
		
		}

	//we now need to move where the first filename comes from on the command line by one to the right

	j = 1;

	for(int i = 1 + j; i < argc; i++)
	
		{
				
			if(strcmp(argv[i],rexpop) == 0)
				{
				//move index one over to check if next command line argument is a regular expression
				//regxarg[i] = 0;
				i++;
				//regxarg[i] = i;
				i++;
				//regxarg[i] = 0;
				}
				
			filed[i-1] = open(argv[i], O_WRONLY | O_APPEND | O_CREAT, 00666);
			
			//if we got a bad file descriptor, then we were unable to open file.  Indicate error and exit.
			if (filed[i-1] == -1)
		
				{
				
				cerr << argv[i] << " can't be opened.\n";
							
				}
			
						
		}
	
	}


	//count = getline(&line, &k, 0);
	//std::cin.getline(buffer, 1024);
	//cerr << "here";
	//this is our write loop. We will continue the loop as long as we have data to write to files
	cin.getline(buffer, 100000);
	for (int l = 0; buffer[l] != '\0'; l++)
		k = l+1;
	
	while (count > 0)
		{
			
		count = read(0, buff, k);
		//strcpy(buffer, line);
		//cerr << "successful read";
		//check to make sure that we have stuff left to read
		//count = read(0, buffer, 1024);
			
		//if we don't, exit loop
		//if(count <= 0) break;
		
		//loop through command line arguments that indicate the files we want
		//to write to
		
		
		
		for(int i = 1+j; i < argc; i++)
			{
		
			if(strcmp(rexpop, argv[i]) == 0)
		
				{
					
				i++;
				//prepare reg expression
				rs = regcomp(&regex, argv[i], 0);
				if (rs == 0)
				
					{
					//execute reg expression
					rs = regexec(&regex, buffer, 0, 0, 0);
					if( rs == 0 )
					
						{
					
							
						i++;	
						write(filed[i-1], buff, k);
					
						}
						
					}
					
				}
					
				else
				
					{
					
					if(filed[i-1] > 0)
					
						write(filed[i-1], buff, k);
						
					
					}
				
				//we also want to write to standard output
				
				
			
				//std::cin.getline(buffer, 1024);
				}
				
				write(1, buff, k);
		
			//for(unsigned i = 0; i < strlen(buffer); i++)
			
				//buffer[i] = 0;
		
		cin.getline(buffer, 100000);
		for (int l = 0; buffer[l] != '\0'; l++)
		k = l+1;
	
		
		}

	}
	

