# IPC - MsgQ
- 부모 자식관계가 아닌, 상호 독립적인 프로세스간 메세지를 전달할 때 사용하는 방법이다.

- 다음은 시스템의 메세지 큐 정보를 확인하기 위한 `bash` 명령어들의 예이다.
  - `ipcs -l` : ipc show list
  - `ipcs -q` : ipcs show queue list
  - `ipcrm -q MSG_Q_ID` : message queue flush
  - `ipcrm -Q MSG_Q_KEY` : message queue flush

- 다음은 메세지 큐에서 사용하는 함수들의 목록이다.
  - `msgget()`
  - `msgctl()`
  - `msgsnd()`
  - `msgrcv()`

### 메세지 큐를 사용하기 위한 흐름
  - `msgget()` 을 통해서 `unique key`를 가진 메세지 큐를 얻어온다.
  - `msgget()`의 결과물인 `msgq_id`를 통해서 메세지를 보내거나(`msgsnd()`) 메세지를 받는다.(`msgrcv()`)

### msgget()
- `int msgget(key_t key, int msgflg);`
- 기능 : 메시지 큐를 커널에 요청해서 할당받는다.
- 리턴 :
  - 성공시 메시지 큐의 ID를,
  - 실패시 errno 설정 후, -1리턴.
- 인자 :
  - key : 메시지 큐에 접근하기 위한 키. 이 키를 사용하면 서로 다른 프로세스가 동일한 메시지 큐에 접근 가능하다.
  - msgflg :
    - `IPC_CREAT` 사용시 없으면 새로 생성.
    - `IPC_CREAT | IPC_EXECL` 사용 시 해당 메시지 큐가 있으면 에러.

- 다음은 메시지 큐를 얻어오는 과정의 코드이다.

```c
int msgq_id = msgget((key_t)KEY_MSG, 0666|IPC_CREAT);
if(msgq_id == -1) {
  printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
  return EXIT_FAILURE;
}
```

### msgctl()
- `int msgctl(int msgqid, int cmd, struct msgqid_ds * buf);`
- 기능 : 메세지 큐를 제어 함.
- 리턴 :
  - 성공시 `cmd`값에 따라 리턴값이 다르다.
  - 실패시 errno 설정 후, -1리턴.
- 인자 :
  - msqid : 메시지 큐의 ID
  - cmd :
    - `IPC_STAT` : 메시지 큐의 정보를 buf에 얻어옴.
    - `IPC_RMID` : 메시지 큐를 완전히 제거.
    - 이외에도 명령이 매우 많다.


- 다음은 메시지 큐를 얻어오는 과정의 코드이다.

```c
if(strcmp(argv[1], "IPC_STAT") == 0) {
  struct msqid_ds dsbuf;
  ret = msgctl(id_msg, IPC_STAT, &dsbuf);
  if(ret == -1) {
    printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
    return EXIT_FAILURE;
  }
  printf("[%d] IPC_STAT OK\n", pid);
  printf("    msg_perm.__key=%#x\n", dsbuf.msg_perm.__key);
  printf("    msg_perm.mode=%#o\n", dsbuf.msg_perm.mode);
  printf("    msg_qbytes=%ld\n", dsbuf.msg_qbytes);
}
```

### msgsnd()
- `int msgsnd(int msgqid, const void * msgp, size_t msgsz, int msgflg);`
- 기능 : 메시지 큐에 메세지를 보냄.
- 리턴 :
  - 성공시 0
  - 실패시 errno 설정 후 -1
- 인자
  - `msgqid` : 메시지 큐 ID
  - `msgp` : 메세지 큐에 보낼 데이터를 `(void * )` 타입으로 캐스팅 해서 주소를 보냄.
  - `msgz` : msgp가 가리키는 구조체에서 `mtype(4B)`을 제외한 크기.
  - `msgflg` :
    - 큐에 충분한 공간이 있다면, 즉시 메시지를 큐에 보냄.
    - 큐에 충분한 공간이 없다면, 공간이 생길 때까지 잠듬.
    - `IPC_NOWAIT` 로 설정시 잠들지 않고(Non-Blocking) 즉시 에러 리턴.
    - `default` 값은 0 이다.

### msgrcv()
