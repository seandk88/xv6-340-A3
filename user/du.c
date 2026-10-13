#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "user/user.h"



int dir_walk(int fd, char *path){

    struct stat st;
    int size = 0;

    if(fstat(fd, &st) == 0){
        if (st.type == T_DIR){
            size += st.size;
            struct dirent de;
            while (read(fd, &de, sizeof(de)) == sizeof(de)){
                if(de.inum == 0)
                continue;

                char buf[512], *p;
                strcpy(buf, path);
                p = buf + strlen(buf);
                *p++ = '/';
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;

                struct stat subst;
                int subfd = open(buf, O_RDONLY);
                if(subfd < 0){
                    continue;
                }

                if(fstat(subfd, &subst) == 0){
                    if (subst.type == T_DIR){
                        if (strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0){
                            size += dir_walk(subfd, buf);
                        }
                    }
                    else if(subst.type == T_FILE){
                        size += subst.size;
                    }
                }
                close(subfd);
                
            }
        }

        else if(st.type == T_FILE){
            size += st.size;
        }

        printf("%d  %s\n",size, path);
    }
    return size;
}

int
main(int argc, char *argv[])
{
    
    int fd = open(argv[1], O_RDONLY);

    dir_walk(fd, argv[1]);

    close(fd);

  exit(0);
}