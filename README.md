Linux System Programming
========================

-	[How to use Git](./how-to-git.md)
-	[License 정책](./license.md)
-	[Shell Script](./shell-script.md)
-	[Boot Flow](./boot-flow.md)
-	[짚고 넘어가야할 개념들](./알아야할_개념들.md)
-	[kernel](./kernel.md)
-	[gcc / Makefile](./makefile.md)

## Proccess
- [Process](./process.md)
- [Signal](./signal.md)

### IPC(Inter Proccess Communication)
- [File Descriptor](./File-Descriptor.md)
- [dup()](./dup함수.md)
- [IPC/Pipe](./IPC(Pipe).md)
- [IPC/Shared Memory](./IPC(SharedMemory).md)
  - **공유메모리를 통해서 프로세스간 데이터 전송시에는 반드시 세마포어 기법을 병행해서 사용해야 한다.**
  - 프로세스에서의 동기화 방법 ==> Semaphore
- [IPC/Message Queue](./IPC(MsgQ).md)

## Thread
- [Thread](./Thread.md)
  - 쓰레드에서의 동기화 방법 ==> Mutex

## Synchronization Technic
- [Mutex](./Mutex(pthread).md)
- [Semaphore](./Semaphore.md)
  - System V 방식
- [Unnamed Semaphore](./UnnamedSemaphore.md)
  - POSIX 방식
