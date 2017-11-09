# Signal
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

- 다음은 시그널 매크로의 정의이다.

```c
typedef void(*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
#define SIG_ERR((sighandler_t) -1) /* Error return */
```
------------------------

## kill command(bash shell에서)
- 이 명령은 특정 프로세스에 특정 signal번호를 보내는 행위를 한다.
- `kill -9 1534` : PID 1534프로세스에게 9번 시그널(SIGKILL)을 보낸다.
- `kill -10 1234 2525`: PID 1234, 2525프로세스에게 SIGUSER1을 보낸다.

-------------------------

## kill() (프로그램에서)
- 이 명령은 특정 프로세스에 특정 signal번호를 보내는 행위를 한다.
- 위와 차이가 있다면, C로 만든 프로그램에서 사용하는 함수라는 점이다.


## alarm()
- 시그널 전달 용 알람 시계 설정.
- `unsigned int alarm(unsigned int seconds);`
- 이전에 설정된 알람 시계가 있었다면, 남아있는 초를, 없었으면 0 리턴.
- argument 0 ==> 알람 시게 설정 무시됨.
- alarm()이 호출되면 이전에 설정된 알람 시계는 취소되고, 이전에 설정된 알람 시계의 남아있는 초를 리턴한다.


## pause()
- `int pause(void);`
- 아무련 argument가 없다.
- 호출한 순간 멈춘다.
- 시그널을 받으면 깨어난다.

------------------------
