/**
 * Problem set from CS50 lecture 4 - Memory
 * This program recovers JPEG photos from card.raw
 * 
 * "https://cs50.harvard.edu/x/2023/psets/4/recover/"
 * */




#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

  int main(int argc, char *argv[]) {


    if (argc != 2) {
      printf("Usage: recover filename");
      return 1;
    }

    char *card_file = argv[1];
    BYTE buffer[BLOCK_SIZE];

    FILE *raw_file = fopen(card_file, "r");

    if (raw_file == NULL) {
      printf("could not open file");
      return 2;
    }

    int file_count = 0;
    int file_count_tracker = 0;
    FILE *img;



// when encounter jpg header bytes of 4, starting writing the tailing bytes into file

 while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE) {
  // determine if its start of jpg
  // create a file with malloc with size 215 plus some byte to represent %%%.jpg
  // sprintf()
  // file *img = fopen(filename, 'w');
  // start using img - fwrite to write the bytes from buffer of 215
  // if detected start of jpg header bytes
  // repeats above steps to create a new jpg file and starts writing again.
    char filename[8];


    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {

      file_count_tracker = 1;
      //char filename[8];

      //Here, filename is a string literal, which you will use to name your file, and access mode can have one of the following values −
      if (file_count < file_count_tracker) {
        sprintf(filename, "%03i.jpg", file_count);
        file_count = file_count + 1;
        img = fopen(filename, "w");
        fwrite(buffer, 1, BLOCK_SIZE, img);

      }
      else {
        fclose(img);
        sprintf(filename, "%03i.jpg", file_count);
        file_count = file_count + 1;
        img = fopen(filename, "w");
        fwrite(buffer, 1, BLOCK_SIZE, img);
      }

    }
    else if (file_count > 0) {

      //img = fopen(filename, "w");
      fwrite(buffer, 1, BLOCK_SIZE, img);
    }



 }

fclose(img);
fclose(raw_file);




}