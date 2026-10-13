#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int dir_walk(int fd, int st){

    if(fstat(fd, &st) == 0){
        if (st.type == T_DIR){
            uint off, inum;
            struct dirent de;
            struct inode *dp = st.ino;

            for(off = 0; off < dp->size; off += sizeof(de)){
                if(read(dp, (uint64)&de, off, sizeof(de)) != sizeof(de))
                panic("dirlookup read");
                if(de.inum == 0)
                continue;

            }

        } else if(st.type == T_FILE){

        }
    }

}

int
main(int argc, char *argv[])
{
    struct stat st;
    int fd = open(argv[1], O_RDONLY);

    dir_walk(fd, st);

  exit(0);
}
