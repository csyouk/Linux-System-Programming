# IPC - Shared Memory
- 매우 오래된 IPC 방법이다.
- 대량의 데이터를 주고 받기에 좋은 방식.
- 독립적인 n개의 프로세스가 공유자원을 접근할때 생기는 문제를 해결하기 위해서 `Semaphore 혹은 Mutex`
와 같은 기법을 병행해서 사용한다.

- 다음은 메세지 큐에서 사용하는 함수들의 목록이다.
  - `shmget()`
  - `shmat()` : `at`, `attach`
  - `shmdt()` : `dt`, `detach`
  - `shmctl()`

### 공유 메모리를 사용하기 위한 흐름.
- **공유 메모리** 의 **고유 키** 를 사용, 커널로부터 **공유메모리 id** 를 부여받는다.
- 커널로부터 부여받은 id를 이용, 공유자원을 프로세스의 주소 공간에 **연결(attach)** 시킨다.
- 연결후에 공유자원의 시작주소를 커널로부터 받으면, 해당 시작주소를 통해서 공유 메모리에 데이터를 Read/Write 한다.
- 공유 메모리 사용이 끝나거나, 프로세스가 종료되기 직전, 커널로부터 부여받은 id를 이용,
공유자원을 프로세스의 주소공간으로 부터 **해제(detach)** 시킨다.

### shmget()
- `int shmget(key_t key, size_t size, int shm_flg);`
- 공유 메모리를 할당한다.
- 리턴
  - 성공 시 공유 메모리 ID 반환.
  - 실패시 `errno` 설정후 -1
- 인자
  - `key` : 공유 메모리에 접근하기 위한 키.
  - `size` : 할당할 공유 메모리 크기.
  - `shm_flg` :
    - `IPC_CREAT` 사용시 공유 메모리가 없으면 새로 생성.
    - `IPC_CREAT | IPC_EXCL` 사용시 공유 메모리 있으면 에러.


### shmat()
- `void * shmat(int shmid, const void * shmaddr, int shmflg);`
- 프로세스의 주소 공간에 공유메모리를 **부착** 한다.
- 리턴
  - 성공 시 부착된 공유 메모리의 주소를.
  - 실패시 `errno` 설정후 -1
- 인자
  - `shmid` : 공유 메모리의 ID
  - `shmaddr` :
    - 일반적으로 `NULL`을 쓴다.
    - `NULL` 이면 커널이 관리하는 메모리 중 임의의 주소를 공유 메모리에 부착한다.
    - `NULL` 이 아니면, 특정 주소의 공유 메모리를 얻어온다.
  - `shmflg` :
    - `SHM_RDONLY` 옵션을 주면, 읽기 전용으로 읽어온다.
    - 일반적으로 `0` 을 쓴다.(**READ/WRITE**)

### shmdt()
- `int shmat(const void * shmaddr);`
- 공유메모리를 프로세스의 주소 공간으로 부터 **분리** 한다.
- 리턴
  - 성공 시 0
  - 실패시 `errno` 설정후 -1
- 인자
  - `shmaddr` : 분리할 공유 메모리의 주소.

### shmctl()
- `int shmctl(int shmid, int cmd, strcut shmid_ds *buf);`
- 공유 메모리 제어
- 리턴
  - 성공 시 cmd에 따라 값이 다름.
  - 실패시 `errno` 설정후 -1
- 인자
  - `shmid` : 공유 메모리의 ID
  - `cmd`
    - `IPC_STAT` : 공유 메모리 정보를 buffer에 얻어옴.
    - `IPC_RMID` : 공유메모리의 완전 제거.
  - `buf` 자료 검색.
