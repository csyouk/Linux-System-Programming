shell script
============

-	shell script의 시작 부분에는 다음 구문을 넣어야 한다.

	-	`#!/bin/bash`
	-	**shebang** 이라고 부른다.

-	변수 사용

	```bash
	  echo $var    // 변수는 대소문자 구분. 사용시 $ 붙임.
	  echo "$var"  // ""안에 변수를 사용시 내용이 출력된다.
	  echo '$var'  // '' 안에 변수를 사용시 문자열 그대로 출력된다.


	read var     // scanf


	```

-	인자 전달

```bash

  argument.sh file
  chmod a+x argument.sh
  ./argument.sh linux world  // 실행시
  argument.sh, linux, world  // 가 순서대로 출려된다.
  #!/bin/bash

  echo "fist arg : $0"
  echo "second arg : $1"
  echo "third arg : $2"
```

-	환경변수의 등록/변경
-	shell 에서 변수 값 입력이 가능하게 하려면 `export` 키워드를 사용해야 한다.

```bash
    // in shell
    export name=linux
    ...
    name=programming
    ...
    echo $name  // programming
```

-	변수의 설정

	-	`set` 명령은 모든 환경변수를 보여준다.
	-	`env` 명령은 export된 환경변수만 보여준다.

-	특수 환경변수

	-	`$PATH` : 환경변수의 리스트가 저장된 변수.

-	if 구문

	-	if 조건문안의 [] 에서는 반드시 띄어쓰기를 해야 한다.(안할 시 오류)

```bash
    if [ $password = $var ]; then
      echo "correct"
    else
      echo "incorrect"
    fi

    exit 0

```

-	while 구문
	-	마찬가지로 띄어쓰기를 주의해야 한다.

```bash
    while [ $password != $var]; do
      echo "wrong. try again."
    done
```

-	함수
	-	함수 호출시에 ()를 붙이지 않아도 된다.
	-	문장 하나하나가 shell 명령어이다. (kernel에 내리는 명령어.)

```bash
    lsprt()
    {
        echo "invoked!"
        ls --color
    }

    lsprt
    cd ..
```
