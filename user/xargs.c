#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
    char *xargs_argv[MAXARG];
    int xargs_argc = 0;

    for (int i = 1; i < argc; i++) {
        xargs_argv[xargs_argc] = argv[i];
        xargs_argc++;
    }

    char buf[512];
    char ch;
    int buf_idx = 0;

    while (read(0, &ch, 1) > 0) {
        if (ch == '\n') {
            buf[buf_idx] = '\0';
            xargs_argv[xargs_argc] = buf;
            xargs_argv[xargs_argc + 1] = 0;

            if (fork() == 0) {
                // Tiến trình con thực thi lệnh
                exec(xargs_argv[0], xargs_argv);
                exit(1);
            }
            wait(0);
            buf_idx = 0;
        } else {
            buf[buf_idx] = ch;
            buf_idx++;
        }
    }
    exit(0);
}
