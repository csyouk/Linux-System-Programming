# IPC - MsgQ
- 부모 자식관계가 아닌, 상호 독립적인 프로세스간 메세지를 전달할 때 사용하는 방법이다.

- 다음은 시스템의 메세지 큐 정보를 확인하기 위한 `bash` 명령어들의 예이다.
  - `ipcs -l` : ipc show list
  - `ipcs -q` : ipcs show queue list
  - `ipcrm -q MSG_Q_ID` : message queue flush

- 다음은 메세지 큐에서 사용하는 함수들의 목록이다.
  - `msgget()`
  - `msgctl()`
  - `msgsnd()`
  - `msgrcv()`

- 메세지 큐를 사용하기 위한 흐름
  - `msgget()` 을 통해서 `unique key`를 가진 메세지 큐를 얻어온다.
  - `msgget()`의 결과물인 `msgq_id`를 통해서 메세지를 보내거나(`msgsnd()`) 메세지를 받는다.(`msgrcv()`)
