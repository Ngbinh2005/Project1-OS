#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
    char *xargs_argv[MAXARG];
    int xargs_argc = 0;

    // Bỏ qua tên chương trình "xargs", copy các lệnh đi kèm (ví dụ: echo bye)
    for (int i = 1; i < argc; i++) {
        xargs_argv[xargs_argc] = argv[i];
        xargs_argc++;
    }

    char buf[512];
    char ch;
    int buf_idx = 0;

    // Đọc từng ký tự từ đầu vào chuẩn (0)
    while (read(0, &ch, 1) > 0) {
        if (ch == '\n') {
            buf[buf_idx] = '\0'; // Kết thúc chuỗi khi hết 1 dòng
            xargs_argv[xargs_argc] = buf; // Ghép dòng vừa đọc vào cuối lệnh
            xargs_argv[xargs_argc + 1] = 0; // Đánh dấu kết thúc mảng tham số

            if (fork() == 0) {
                // Tiến trình con thực thi lệnh
                exec(xargs_argv[0], xargs_argv);
                exit(1);
            }
            // Tiến trình cha đứng chờ tiến trình con làm xong
            wait(0);
            buf_idx = 0; // Reset lại bộ đệm để đọc dòng tiếp theo
        } else {
            buf[buf_idx] = ch;
            buf_idx++;
        }
    }
    exit(0);
}
