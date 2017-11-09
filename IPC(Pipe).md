# IPC - Pipe
- 프로세스는 VA를 사용하며, 자신의 존재 이외에는 다른 프로세스의 존재를 알지 못한다.
- 하지만, 실제로는 다른 프로세스가 존재한다.

- 다음은 IPC의 예이다.
  - **Pipe**
  - Semaphore
  - Shared Memory
  - Message Queue

### 선수지식
- [파일 디스크립터](./File-Descriptor.md)

### pipe()
- 파이프는 제일 오래된 IPC 방법이다.
- 파이프는 프로세스와 프로세스 간 연결통로이다.
- `int pipe(int pipefd[2]);`
- 단방향 데이터 채널(데이터가 들어가 있는 임시 메모리 공간)을 생성하는 함수.
  - 리턴
    - 성공시 0
    - 실패시 errno 설정후 -1
  - 인자
    - `pipe()` 를 호출할 때는 `int pipefd[2];` 를 인자로 넘겨야 한다.
    - `pipefd[0]` 에는 `pipe`의 **read** file descriptor index를 채운다.
    - `pipefd[0]` 에는 `pipe`의 **write** file descriptor index를 채운다.

- 다음은 pipe의 예제 코드이다.
  - 다음 2가지를 알아야 한다.
  - `ssize_t read(int fd, void *buf, size_t nbytes);`
    - fd 파일 디스크립터 id를 가진 파일에 nbytes 바이트 만큼 buf에 읽어와서 저장한다.
  - `ssize_t write(int fd, const void *buf, size_t count);`
  - fd 파일 디스크립터 id를 가진 파일에 count 바이트 만큼 buf에 내용을 write 한다.


```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_BUF 512

pid_t pid;

int main(int argc, char **argv)
{
  int fd_pipe[2];
  int ret;
  char wbuf[MAX_BUF];
  char rbuf[MAX_BUF];

  printf("[%d] running %s\n", pid = getpid(), argv[0]);

  /* open pipe */
  // 파이프를 생성하면서 fd_pipe에 내용을 채운다.
  ret = pipe(fd_pipe);
  if(ret == -1) {
    printf("[%d] error: %s\n", pid, strerror(errno));
    return EXIT_FAILURE;
  }

  /* write data to pipe */
  strcpy(wbuf, "hello");
  // fd_pipe[1] 에는 pipe write fd가 들어가 있다.
  ret = write(fd_pipe[1], wbuf, strlen(wbuf)+1);
  if(ret == -1) {
    printf("[%d] error: %s\n", pid, strerror(errno));
    return EXIT_FAILURE;
  }
  printf("[%d] wrote %d bytes to pipe [%s]\n", pid, ret, wbuf);

  /* read data from pipe */
  // fd_pipe[0] 에는 pipe read fd가 들어가 있다.
  ret = read(fd_pipe[0], rbuf, MAX_BUF);
  if(ret == -1) {
    printf("[%d] error: %s\n", pid, strerror(errno));
    return EXIT_FAILURE;
  }
  printf("[%d] read %d bytes from pipe [%s]\n", pid, ret, rbuf);

  printf("[%d] terminated\n", pid);

  return EXIT_SUCCESS;
}
```
