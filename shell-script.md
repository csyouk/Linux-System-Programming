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

-	환경변수의 등록

```bash

```
