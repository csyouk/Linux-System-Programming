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
> [tab]  command

-	다음은 Makefile 파일의 예이다.
- 다음과 같은 명령이 가능하다.
	- make
	- make main.o
	- make func.o
	
```cmake

TARGET = hello
OBJS = main.o func.o
CC = arm-none-linux-gnueabi-gcc
CFLAGS = -c

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
main.o: main.c
	$(CC) $(CFLAGS) $<
func.o: func.c
	$(CC) $(CFLAGS) $<
clean:
	@rm -f $(TARGET) $(OBJS)
	@echo "all objects all deleted.."

```
