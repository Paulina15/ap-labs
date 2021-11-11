#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <ftw.h>
#include <unistd.h>
#include "logger.h"

#define TAM_MON_EVENT (sizeof(struct inotify_event))
#define MONITOR_DE_EVENTOS 2048
#define BUFFER_LEN MONITOR_DE_EVENTOS*(TAM_MON_EVENT + LEN_NOMBRE)
#define LEN_NOMBRE 32

int main(int argc, char **argv){
    if(argc < 2){
        errorf("Wrong arguments");
        exit(2);
    }
    const char *path= argv[1];

    int fd, watch_desc;
    char buffer[BUFFER_LEN];

    fd = inotify_init();
    if (fd < 0){
        perror("Notify not initialize");
    }

    watch_desc = inotify_add_watch(fd, path, IN_CREATE|IN_MOVED_FROM|IN_DELETE);
    if (watch_desc == -1){
        warnf("Couldn't add watch to %s\n", path);
    }
    else {
        infof("Monitor added to path: %s\n", path);
    }
//basado en un video de youtube 
    int i = 0;
    while(1){
        i = 0;
        int total_read = read(fd, buffer, BUFFER_LEN);
        if (total_read < 0){
            perror("read error");
        }
        
        while(i < total_read){
            // (struct inotify_event)
            struct inotify_event *event = (struct inotify_event*)&buffer[i];
            if (event->len){
                if (event->mask & IN_CREATE){
                    if (event-> mask & IN_ISDIR){
                        infof("Directory %s was created\n", event->name);
                    }
                    else {
                        infof("File %s was created", event->name);
                    }
                }
                if (event->mask & IN_MOVED_FROM){
                    if (event-> mask & IN_ISDIR){
                        infof("Directory %s was renamed\n", event->name);
                    }
                    else {
                        infof("File %s was renamed", event->name);
                    }
                }
                if (event->mask & IN_DELETE){
                    if (event-> mask & IN_ISDIR){
                        infof("Directory %s was deleted\n", event->name);
                    }
                    else {
                        infof("File %s was deleted", event->name);
                    }
                }
                i += TAM_MON_EVENT + event->len;
            }
        }
    }
    inotify_rm_watch(fd, watch_desc);
    close(fd);
    return (EXIT_SUCCESS);
}