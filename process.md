# Process

- 프로세스는 현재 실행중인 하나의 **프로그램** 이다.
- 리눅스에서 프로세스를 실행시키기 위해서는 반드시 **부모 프로세스** 가 필요하다.
- 모든 프로세스는 부모가 필요하다.

- 다음은 **ps -ef**의 실행결과를 나타낸 것이다.
  - UID : User ID
  - PID : Process ID
  - PPID : Parent Process ID
  - CMD : Command
    - **[ ]** 안에 표시된 것들 : daemon process라고 한다.
      - 운영체제에서 생성. 특정한 일들을 전담한다.
      - 멀티태스킹 운영 체제에서 데몬은 사용자가 직접적으로 제어하지 않고, 백그라운드에서 돌면서 여러 작업을 하는 프로그램을 말한다
    - k**


```bash
UID        PID  PPID  C STIME TTY     TIME     CMD
root         1     0  0 11월07 ?      00:00:01 /sbin/init
root         2     0  0 11월07 ?      00:00:00 [kthreadd]
root         3     2  0 11월07 ?      00:01:33 [ksoftirqd/0]
root         4     2  0 11월07 ?      00:00:00 [kworker/0:0]
user      2296  2288  0 11월07 pts/1  00:00:01 bash
user      3906  2296  0 09:15 pts/1    00:00:00 ps -ef
user      2288  1611  0 11월07 ?      00:00:15 gnome-terminal

```

- `sudo cat /proc/1/maps`
  - **/proc** : 장치 관리자
  - **/1** : process id
  - **/maps** : 메모리 정보.


#### 주소공간은 프로세스마다 독립적이다.
- 동일한 라이브러리이지만, 주소공간의 시작 주소가 다르다.
- 프로세스는 VA(virtual address)를 통해서 RAM을 온전히 자신이 다 쓴다고 생각한다.
  - 실제로 4G RAM을 운영하는 방식이, 1G는 kernel이 3G는 process가 올라간다.
  - 각각의 프로세스는 자신이 3G를 다 쓴다고 생각한다. 각각의 프로세스는 다른 프로세스의 존재에 대해서 신경쓰지 않는다.
  - 커널 내부에서는 VA를 쓴다.
  - MMU는 Memory translation table을 사용해서 각각의 프로세스의 가상 주소를 실제 물리주소를 변환시킨다.

```bash
    sudo cat /proc/1/maps

    start-end / permission / offset / major:minor / inode / file
    permission 부분을 자세히 살펴보면 메모리에 대한 정보를 알 수 있다.
    - r-x : code
    - r-- : read only
    - rw- : data

    b746d000-b7615000 r-xp 00000000 08:01 786531     /lib/i386-linux-gnu/libc-2.19.so
    b7615000-b7617000 r--p 001a8000 08:01 786531     /lib/i386-linux-gnu/libc-2.19.so
    b7617000-b7618000 rw-p 001aa000 08:01 786531     /lib/i386-linux-gnu/libc-2.19.so

    sudo cat /proc/871/maps

    b756a000-b7712000 r-xp 00000000 08:01 786531     /lib/i386-linux-gnu/libc-2.19.so
    b7712000-b7714000 r--p 001a8000 08:01 786531     /lib/i386-linux-gnu/libc-2.19.so
    b7714000-b7715000 rw-p 001aa000 08:01 786531     /lib/i386-linux-gnu/libc-2.19.so

```
