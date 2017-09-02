/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

#define BLOCK_SIZE 512


bool headerCondition(char* buffer);

int main(void)
{

  // open input file 
  FILE* input = fopen("card.raw", "r");
  if (input == NULL)
  {
    fprintf(stderr, "Could not open file.\n");      
    return 1;
  }

  char buffer[BLOCK_SIZE];
  int fileCount = 0;
  char outfile[] = "000.jpg";

  FILE* output = fopen(outfile, "w");
  if (output == NULL)
    {
      fclose(input);
      fprintf(stderr, "Could not create %s.\n", outfile);
      return 3;
    }
  
  // read until EOF    
  while (fread(&buffer, BLOCK_SIZE, 1, input) == 1)
  {
    // write first file when encountered
    if (headerCondition(buffer) && fileCount == 0)       
    {
      fwrite(&buffer, BLOCK_SIZE, 1, output);
      fileCount++; 
    }
    
    // continue writing
    else if (!headerCondition(buffer) && fileCount > 0)
    {
      fwrite(&buffer, BLOCK_SIZE, 1, output);
    }
    
    // close previous file, start writing new one
    else if (headerCondition(buffer) && fileCount > 0)
    {
      fclose(output);
      sprintf(outfile,"%.3d.jpg", fileCount);
      output = fopen(outfile, "w");
      if (output == NULL)
      {
        fclose(input);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
      }
      fwrite(&buffer, BLOCK_SIZE, 1, output);
      fileCount++;
    }
  }

  fclose(input);
  fclose(output);
  return 0;  
}

// recognizes the beginning of a new jpeg file
bool headerCondition(char* buffer)
{
  char jpeg[]={0xff, 0xd8, 0xff}; 
  return (!strncmp(buffer, jpeg, 3) && (unsigned char) buffer[3] < 0xf0 && (unsigned char) buffer[3] > 0xdf);
}