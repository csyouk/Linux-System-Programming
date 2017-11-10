# IPC - Shared Memory
- 매우 오래된 IPC 방법이다.
- 대량의 데이터를 주고 받기에 좋은 방식.

- 다음은 메세지 큐에서 사용하는 함수들의 목록이다.
  - `shmget()`
  - `shmctl()`
  - `shmat()` : `at`, `attach`
  - `shmdt()` : `dt`, `detach`

### 공유 메모리를 사용하기 위한 흐름.
-
