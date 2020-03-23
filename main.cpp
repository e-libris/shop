#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>

#include <curl/curl.h>

#include "src/get_resources.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    pid_t pid;
    if((pid = fork()) < 0)  {
        printf("fork error\n");
        exit(-1);
    }

    // runs the convert.sh script in ./data
    if(pid == 0)    {
        char cmd[255];
        getcwd(cmd, sizeof(cmd));
        strcat(cmd, "/convert.sh");
        printf("%s\n", cmd);
        cout << "cmd: " << cmd << endl;
        execl(cmd, cmd, (char*)NULL);
        printf("execl error\n");    // shouldn't get here
        exit(-1);
    }
    else    {
        int status;
        waitpid(pid, &status, 0);

        cout << "get_resources()" << endl;
        get_resources();
        cout << "end get_resources()" << endl;

        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
}
