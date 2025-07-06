#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define TEMPLATE "SWITCH_"

void inject_shell(const char* cmd){
  int i = 0;
  while (cmd[i] != '\0'){
    ioctl(0, TIOCSTI, &cmd[i++]);
  }
}

int main(int argc, char ** argv){
    char buffer[1024] = "\0";
    char target;

    if(argc == 4)
    {
        if(strcmp(argv[1],"set")==0)
        {
            strcat(buffer,TEMPLATE);
            target = (char) argv[2][0];
            buffer[7] = target;
            buffer[8] = '=';
            buffer[9] = '\0';
            strcat(buffer,argv[3]);
            strcat(buffer,"\r");
            inject_shell(buffer);
        }
    } else {
        if(argc == 2)
        {
            strcat(buffer,"cd $");
            strcat(buffer,TEMPLATE);
            target = (char) argv[1][0];
            buffer[11] = target;
            buffer[12] = '\r';

            // printf("%s\n",buffer);

            inject_shell(buffer);
        }
    }
}