# Signal
------------------------

## kill command(bash shell에서)
- 이 명령은 특정 프로세스에 특정 signal번호를 보내는 행위를 한다.
- `kill -9 1534` : PID 1534프로세스에게 9번 시그널(SIGKILL)을 보낸다.
- `kill -10 1234 2525`: PID 1234, 2525프로세스에게 SIGUSER1을 보낸다.

-----------------------

## 시그널 핸들러의 설정
### signal()
- 시그널의 동작을 규정한다.(signal handler라고 한다.)
- 다음은 **sighandler_t** 의 타입을 규정한 **typedef**이다.
- `typedef void(*sighandler_t)(int);`

- 다음은 **signal()** 함수의 프로토타입이다.
- `sighandler_t signal(int signum, sighandler_t handler);`
  - 인자
    - `int signum` : 시그널 번호
    - `handler` : 시그널 핸들러 함수 포인터.
  - 리턴 값(sighandler_t 타입)
    - 설정 성공 : 이전 시그널 핸들러.
    - 설정 실패 : `SIG_ERR` 리턴.

- 다음은 signal 함수의 리턴값의 예이다.
  - -1 정수값을 sighandler_t 타입으로 캐스팅 한다.
  - Error return
  - `#define SIG_ERR((sighandler_t) -1)`

-------------------------

## kill() (프로그램에서)
- `int kill(pid_t pid, int sig);`
- 이 명령은 특정 프로세스에 특정 signal번호를 보내는 행위를 한다.
- 리턴 값
  - 성공 시 : 0
  - 실패 시 : `errno` 설정 후 -1 리턴.
- 인자
  - `pid`
    - `pid > 0` : PID
    - `pid == 0` : 호출한 프로세스와 PGID(Proccess Group ID)가 같은 모든 프로세스에 sig 보냄.
    - `pid == -1` : 접근이 허용된 모든 프로세스에 sig보냄.
    - `pid < -1` : PGID가 `-pid`인 모든 프로세스에 sig 보냄.
  - `sig`
    - 시그널 번호.


## alarm()
- `unsigned int alarm(unsigned int seconds);`
- 시그널 전달 용 알람 시계 설정.
- 이전에 설정된 알람 시계가 있었다면, 남아있는 초를, 없었으면 0 리턴.
- argument 0 ==> 알람 시게 설정 무시됨.
- alarm()이 호출되면 이전에 설정된 알람 시계는 취소되고, 이전에 설정된 알람 시계의 남아있는 초를 리턴한다.
- `alarm(0)` 명령은 알람 시계의 설정이 무시된다.
- `alarm()` 함수는 `Non-Blocking` 방식이다.

## pause()
- `int pause(void);`
- 아무련 argument가 없다.
- 호출한 순간 멈춘다.
- 시그널을 받으면 깨어난다.
-----------------------

- [시그널 종합 문제](./system/EX02-14_sfind/sfind.c)

------------------------
- 시그널의 디폴트 동작
  - SIGALRM
  - SIGHUP
  - SIGINT
  - ...

- 시그널의 액션
  - exit : 프로세스 종료.
  - core : 코어 파일 만든 후 프로세스 종료.
    - core action을 발생할 때, 프로그램의 정보를 남기고 프로그램이 죽는다.
  - stop : 프로세스 정지.(=pause)
    - restart : 프로세스 시작
  - ignore : 시그널 무시.

- 다음은 시그널의 종류들이다.

```bash
1) SIGHUP	 2) SIGINT	 3) SIGQUIT	 4) SIGILL	 5) SIGTRAP
6) SIGABRT	 7) SIGBUS	 8) SIGFPE	 9) SIGKILL	10) SIGUSR1
11) SIGSEGV	12) SIGUSR2	13) SIGPIPE	14) SIGALRM	15) SIGTERM
16) SIGSTKFLT	17) SIGCHLD	18) SIGCONT	19) SIGSTOP	20) SIGTSTP
21) SIGTTIN	22) SIGTTOU	23) SIGURG	24) SIGXCPU	25) SIGXFSZ
26) SIGVTALRM	27) SIGPROF	28) SIGWINCH	29) SIGIO	30) SIGPWR
31) SIGSYS	34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
63) SIGRTMAX-1	64) SIGRTMAX
```
