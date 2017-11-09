# IPC - Pipe
- 프로세스는 VA를 사용하며, 자신의 존재 이외에는 다른 프로세스의 존재를 알지 못한다.
- 하지만, 실제로는 다른 프로세스가 존재한다.

- 다음은 IPC의 예이다.
  - **Pipe**
  - Semaphore
  - Shared Memory
  - Message Queue



## Pipe
- 제일 오래된 IPC방법이다.

### File Descriptor(파일 식별자)
- 각 프로세스는 각자 어떠한 파일을 열어서 사용하고 있는지에 대한 정보를 가지고 있다.
- 파일 식별자의 0번 1번 2번은 용도가 정해져 있다.
  - 0번 : `stdin`
  - 1번 : `stdout`
  - 2번 : `stderr`
  - 실제로는 0, 1번은 표준입출력으로 사용되는 **장치** 이다.
  - 0~2번은 모두 **파일** 이다.
- 리눅스의 시스템에서는 장치를 접근하던, 파일을 접근 하던 모두 **파일**의 개념으로 접근한다.
- 프로세스마다 파일 식별자를 관리하기 위한 테이블이 존재한다. 이 테이블을 **파일 식별자 테이블** 이라고 한다.
- 어떤 프로세스에서 파일을 열면 파일 식별자가 **3** 번 부터 배정된다.
- `fork()`에 의해 프로세스 복제 시 파일 식별자 테이블이 그대로 복사된다.


| fd  | 의미  |
|---|---|
| 0  | stdin  |
| 1  | stdout  |
| 2  | stderr  |
| 3  | **...**  |
| 4  | **...**  |


### pipe()
- 단방향 데이터 채널(데이터가 들어가 있는 임시 메모리 공간)을 생성하는 함수.
- `int pipe(int pipefd[2]);`


- 다음은 pipe의 예제 코드이다.

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
  ret = pipe(fd_pipe);
  if(ret == -1) {
    printf("[%d] error: %s\n", pid, strerror(errno));
    return EXIT_FAILURE;
  }

  /* write data to pipe */
  strcpy(wbuf, "hello");
  ret = write(fd_pipe[1], wbuf, strlen(wbuf)+1);
  if(ret == -1) {
    printf("[%d] error: %s\n", pid, strerror(errno));
    return EXIT_FAILURE;
  }
  printf("[%d] wrote %d bytes to pipe [%s]\n", pid, ret, wbuf);

  /* read data from pipe */
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


## Semaphore
  - 데이터를 주고받기 위한 방법이 아니다.
  -
## Shared Memory
## Message Queue
