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
- [dup(), dup2()](./dup함수.md)


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


- 아래는 pipe의 예제 코드들이다.
  - [간단한 파이프 구현 - 파이프의 생성 방법](./system/EX03-01_pipe/pipe.c)
  - [파이프로 부모 자식 간 통신](./system/EX03-02_pipe_fork/pipe_fork.c)
  - [dup() 함수를 이용한 파이프](./system/EX03-03_dup/dup.c)




### mkfifo()
- `int mkfifo(const char *pathname, mode_t mode);`
- 기능
  - FIFO(이름이 있는 파이프) 파일을 생성.
  - 프로세스끼리 FIFO파일을 매체로 파이프 통신이 가능하다.
- 리턴
  - 성공시 0.
  - 실패시 errno 설정후 -1 리턴.
- 인자
  - `pathname` : 생성할 파일 이름.
  - `mode` : 생성할 FIFO 파일의 접근 권한.

- 아래는 mkfifo pipe의 예제 코드들이다.
  - [mkfifo 예제 - receiver](./system\EX03-05_fifo\rfifo.c)
  - [mkfifo 예제 - writer](./system\EX03-05_fifo\wfifo.c)
