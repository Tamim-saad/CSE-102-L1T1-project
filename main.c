#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "utils.h"

Image *read_PPM(char *filename)
{
    /* opens a PPM file, constructs an Image object and returns a pointer to it.
    Use fopen(), fscanf(), fprintf(), and fclose().*/

    char str[300];
    FILE *ptoy;
    ptoy=fopen("toy","r");
    FILE *ptf;
    ptf=fopen("toyfile","w");
     while(!feof(toy)){
      fgets(str,300,ptoy);
      fputs(str,toyfile);}
}

void write_PPM(Image *image, char *filename)
{
	/* takes an Image object and writes to filename in PPM format.*/

}

void free_image(Image *image)
{
	/* takes an Image object and frees all the memory associated with it.
    This involves not only calling free on image but also on the appropriate
    members of it.
    */
}


Color *evaluate_one_pixel(Image *image, int row, int col)
{
	/* Takes an Image object and returns what color the pixel at the given row/col
    should be in the secret image. This function should not change image*/

}

Image *get_secret_image(Image *image)
{
	/* takes an Image object, and constructs the secret image from it by extracting
    the LSB of the B channel. You should call evaluate_one_pixel() here. */
}

int main()
{
    /* Call read_PPM(), write_PPM(), free_image(), get_secret_image() in some order
    to obtain the hidden message.*/
    read_PPM(toy);
	return 0;
}


