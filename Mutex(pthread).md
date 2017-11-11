# Mutex
- Mutual Exclusive Binary Semaphore
- **뮤텍스를 이용하여 상호배제 구간을 만든다.**
  - **상호배제 구간** 이란, 하나의 스레드만 진입할 수 있는 **임계 영역** 을 뜻한다.
  - 임계영역에 하나의 스레드가 진입했다면 다른 스레드는 BLOCKING된 상태로 대기한다.

```c
  #include <pthread.h>

  int pthread_mutex_init(pthread_mutex_t * mutex, const pthread_mutex_attr *attr);
  int pthread_mutex_lock(pthread_mutex_t *mutex);
  int pthread_mutex_unlock(pthread_mutex_t *mutex);
  int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

- `pthread_mutex_init()` : 뮤텍스 초기화
- `pthread_mutex_lock()` : 뮤텍스 획득(임계영역 활성화)
- `pthread_mutex_unlock()` : 뮤텍스 반납(임계영역 비활성화)
- `pthread_mutex_destroy()` : 뮤텍스 제거

- 리턴
  - 성공시 0
  - 실패시 에러번호 리턴

- 인자
  - `mutex` : 뮤텍스 변수
  - `attr` : 뮤텍스 속성.


- [뮤텍스가 적용된 멀티 스레드 코드](./system/EX04-03_pthread_mutex/pthread_mutex.c)와 [적용되지 않은 멀티 스레드 코드](./system/EX04-02_pthread_multi/pthread_multi.c)를 비교해보고, 결과를 확인해 보자.!
