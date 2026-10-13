#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    link(argv[1], argv[2]);
    unlink(argv[1]);

  exit(0);
}
