Boot Flow
=========

![Diagram](./img/diagram.JPG)

-	u-boot프로그램이 실습키트(WT4412)에 설치되어 있는 상태이다.
-	환경변수들을 설정한다.(부팅에 필요한)
-	booting image는 vm에 띄워져 있는 ubuntu에 있다.
-	vm과 실습보드가 네트워크 통신을 하기위해서 네트워크 세팅을 해야 한다.
-	TFTP서버를 구축한 후, 실습보드가 부팅시 tftp서버에서 부팅이미지를 받아서 압축해제 한 후, RAM에 이미지를 올린다.
-	NFS 서버를 구축한 후, 실습보드에 마운팅 시킨다.
-	필요한 파일을 실습보드로 옮기기 위해서는 다음과 같은 flow를 거친다.
