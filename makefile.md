gcc, Makefile
=============

gcc
---

-	**gcc** 컴파일러 option, 대소문자 구분이 매우 중요하다.

	-	**-E** : preprocessor과정만 거친다.
	-	**-S** : 컴파일만 한다.
	-	**-c** : 컴파일을 한 후 assemblely까지만 한다.
	-	**-o <file>** : <file> 이름으로 output file응ㄹ 만든다.
	-	**-save-temp** : 중간 단계의 파일들을 지우지 않는다.
	-	**-O** : 최적화 옵션

-	**\*.i** : 전처리 만 수행된 결과

-	**\*.s** : 컴파일만 수행된 파일.

-	**\*.o** : 어셈블리까지만 수행되는 파일.(object 파일)

Makefile
--------

-	컴파일 과정을 자동화 시키는 설정 파일.

> target : 의존성 파일
>
> [tab]  command

-	다음은 Makefile 파일의 예이다.
- 다음과 같은 명령이 가능하다.
	- make
	- make main.o
	- make func.o

- 다음 기호들을 알아야 해석이 가능하다.
	- **$*** : Target 이름에서 확장자를 제외한 이름
	- **$@** : Target 이름
	- **$<** : 의존성 파일 중 첫 번째 파일
	- **@** 를 붙이면 터미널로 결과만 출력된다.(명령이 출력되는 것이 아니다.)
		- **@echo "hello world"** ==> **echo "hello world"**


--------------------------

```cmake

TARGET = hello    // makefile 에서 변수 선언
OBJS = main.o func.o
CC = arm-none-linux-gnueabi-gcc
CFLAGS = -c

$(TARGET): $(OBJS)     // makefile 에서 변수 사용
	$(CC) -o $@ $(OBJS)
main.o: main.c
	$(CC) $(CFLAGS) $<
func.o: func.c
	$(CC) $(CFLAGS) $<
clean:
	@rm -f $(TARGET) $(OBJS)        // -f 옵션 : force(오류 메세지 방지)
	@echo "all objects all deleted.."

```

--------------------------
