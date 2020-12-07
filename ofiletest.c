#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  // checking valid input
  if(argc > 15 || argc < 1){
    printf(1, "can't close files, too many args\n");
    exit();
  }
  // file number declarartion
  int fileNum = 0;
  // opening/closing files for valid input
  if(argc <= 15){
    // naming files
    char *fileName = "ofile00";
    // getting the file(number) to open
    int argv1 = atoi(argv[1]);
    for(int i = 0; i < argv1; i++){
      // getting file names with single digit
      if(argv1 < 10){
        fileName[5] = i + '0';
        fileName[6] = '\0';
      }else{
        // getting file names with double digits
        fileName[5] = i / 10 + '0';
        fileName[6] = i % 10 + '0';
      }
      // opening files with flags
      fileNum = open(fileName, O_RDONLY | O_CREATE);
      // if error with opeining file
      if(fileNum < 0){
        return -1;
      }
    }
    // closing files by getting file(number)
    for(int j = 2 ; j < argc; j++){
      // getting file names with single digit
      if(atoi(argv[j]) < 10){
        fileName[5] = atoi(argv[j]) + '0';
        fileName[6] = '\0';
      } else{
        // getting file names with double digits
        fileName[5] = atoi(argv[j]) / 10 + '0';
        fileName[6] = atoi(argv[j]) % 10 + '0';
      }
      // closing file
      if(close(atoi(argv[j])+3) < 0){
        return -1;
      }
      // unlinking the closed files
      if(unlink(fileName) < 0){
        // if closed file fails to unlink
        printf(2, "rm: %s failed to delete\n", fileName);
      }
    }
    // printing system calls
    printf(1, "%d %d\n", getofilecnt(getpid()), getofilenext(getpid()));
  }
  exit();
}
