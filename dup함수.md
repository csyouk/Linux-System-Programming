# dup 함수
- 이 내용은 file descriptor 내용과 이어진다.
  - [File Descriptor 보러가기](./File-Descriptor.md)

```c
  int dup(int oldfd);
```
- 기능
  - 파일 식별자를 복제하여 새로운 파일 식별자를 생성한다.
  - 새로운 파일 식별자는 사용되지 않는 파일 식별자 중 가장 낮은 번호로 배정된다.
- 리턴
  - 성공시 새로운 파일 식별자를
  - 실패시 errno 설정 후 -1 리턴
- 인자
  - `oldfd` : 복제되는 파일 식별자


```c
    int dup2(int oldfd, int newfd);
```
- 기능
  - 파일 식별자를 복제하여 새로운 파일 식별자를 생성한다.
  - 새로운 파일 식별자는 newfd로 번호가 정해진다.
- 리턴
  - 성공시 새로운 파일 식별자를
  - 실패시 errno 설정 후 -1 리턴
- 인자
  - `oldfd` : 복제되는 파일 식별자
  - `newfd` : 새로운 파일 식별자

- [참고](./system/EX03-03_dup/dup.c)
