# UnnamedSemaphore
- POSIX 방식의 세마포어이다.
- 특징
  - System V 방식의 세마포어 대비 접근권한이 없고, 프로세스 내에서 사용하기 적합하다.
  - 한번에 세마포어를 하나씩 만든다.
  
```c
#include <semaphore.h>

int sem_init(sem_t * sem, int pshared, unsigned int value);
int sem_wait(sem_t * sem);
int sem_post(sem_t * sem);
int sem_destroy(sem_t * sem);
```

- `sem_init()` : 세마포어 초기화
- `sem_wait()` : 세마포어 획득(세마포어 1 증가)
- `sem_post()` : 세마포어 반납(세마포어 1 감소)
- `sem_destroy()` : 세마포어 제거

- 리턴
  - 성공시 0
  - 에러시 errno 설정후 -1 리턴.

- 인자
  - `sem` : 세마포어 변수
  - `pshared`
    - **0 으로 설정하면 스레드간 공유(보통 이 옵션을 많이 쓴다.)**
    - 1 으로 설정하면 프로세스간 공유
  - `value` : 세마포어 초기값.
