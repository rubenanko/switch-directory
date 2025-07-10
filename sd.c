#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __linux__
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/limits.h>
#endif


#define TEMPLATE "SWITCH_"

void inject_shell(const char* cmd){
    int i = 0;
    while (cmd[i] != '\0'){
      ioctl(0, TIOCSTI, &cmd[i++]);
    }
}

int main(int argc, char ** argv){
    char buffer[PATH_MAX] = "\0";
    char target;

    if(argc == 3)
    {
        strcat(buffer,TEMPLATE);
        target = (char) argv[1][0];
        buffer[7] = target;
        buffer[8] = '=';
        buffer[9] = '\0';
        if(strcmp(argv[2],".")==0)
        {
            char cwd[PATH_MAX];
            if(getcwd(cwd,PATH_MAX) != NULL)
            {
              strcat(buffer,cwd);
            } else {printf("sd : error fetching the current directory");return 1;}
        }
        else
        {
            strcat(buffer,argv[2]);
        }
        strcat(buffer,"\r");
        inject_shell(buffer);
    } else {
        if(argc == 2)
        {
            strcat(buffer,"cd $");
            strcat(buffer,TEMPLATE);
            target = (char) argv[1][0];
            buffer[11] = target;
            buffer[12] = '\0';
            strcat(buffer," && clear\r");

            inject_shell(buffer);
        }
    }
}