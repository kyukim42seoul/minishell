# minishell

20220203(목) 20:15 ~
	PDF, 대현리 블로그 읽는 중...

20220204(금) 16:25 ~
	inshin 님에게 설명 듣기
	헤더 정리

20220206(일) 18:11 ~
	토크나이즈 시도 중
		t_info 에 커맨드, 인자를 전부 담아뒀다 cmd_s 에 한번에 할당하는 방법 염두에 두기
			cmd_s 와 arg 의 노드가 꼬이거나 중복해서 리스트를 도는 경우가 없는지 신경쓰기
		명령어로 시작하지 않으면 command not found 띄우고 계속 명령어 받기
		찾아야 할 부호
			', ", ' ', ;, -, >, <, >>, <<
	연결리스트를 여러 종류 쓰려면 각 리스트별로 초기화, addback, lstlast 함수가 필요하다.(에반데...)
		각 리스트가 포함하고 있는 컨텐츠가 다르기 때문에
		지금 사용 중인 리스트 종류 : t_env, t_arg, t_cmd
		서로 다른 타입(구조체)의 next 이기 때문에 각각이 다르게 인식된다ㅠㅠ
		차라리 리스트 하나에 void * 를 왕창 넣어서 쓸까?? (*****)

20220207(월) 12:40 ~ 개포동 이디야
	", ' 처리에서 미리 문자열을 스캔하고 한 번만 malloc 하는 방식 도입
		이유 : malloc 을 한 번만 한다.
		굳이 연결리스트로 스캔과 할당을 순차적으로 할 필요를 찾지 못했다.
			정 하겠다면 파편화시켜서 데이터를 보관하기 때문에 한번에 긴 메모리가 필요 없는 정도?
		저장할 데이터
			", ' 의 짝 수(짝이 안 맞으면 에러)
			' ', -, <, >, :, >> 유/무
			커맨드와 인자를 나누는 ' '(커맨드와 인자 분리 + 출력과는 무관) 와 인자와 인자 사이에 있는 ' '(' ' 한 칸 출력) 를 각각 인식해야 한다.
		의문
			'<', '>' 와 '<<', '>>' 가 동시에 쓰일 수 있나?
		발견
			'"' 나 ''' 가 홀수일 때, 에러 처리가 아니라 다시 프롬프트를 띄우며 입력을 기다린다.
				빌트인 커맨드 혹은 execve 를 실행하기 전까진 tokenize 된 부분을 가지고 있어야 겠다.
				커맨드 실행 전에 tokenize 가 완료되었다는 플래그 혹은 리턴값이 있어야 겠다.
					count_mark && tokenize_full_cmd 의 반환값
						0 : 완료
						1 : 에러
						2 or -1 : 미완성
				해결
					t_mark *mark 를 static t_mark *mark 로 변경
					if (mark == NULL) 일 때만 init_mark()
				추가(진행 중)
					'"' 나 ''' 는 단순히 수를 세는게 아니라 flag 로 0, 1 을 왔다갔다 하면서 한 번 왕복했을 때 카운터가 올라가게 해야겠다.
					그리고 두 플래그 중 하나가 서면 반대편 플래그를 무시한다.
			'"' 나 ''' 가 홀수로 들어 온 상태에서는 들어오는 모든 input 이 출력 문자열(혹은 인자)로 취급된다.
				echo "hi" "hello 이후에 ''' 가 들어오면 

# Project Title

minishell


## Description

간단하지만 아름다운 쉘 만들기.

## Getting Started

### Need

* bash shell for testing and compareing
* C Language

### Installing

* brew install readline

### Executing program

* MAC 환경 -> Makefile 의 LDFLAG, CPPFLAG 중 위에 두 개 주석처리 후 아래 두 개 오픈
* Makefile 의 CFLAG 주석처리
* Makefile 의 LIB_DIR -> ./lib 로 수정
* make
* run ./minishell
* and treat it like a bash shell ^0^
```
echo $USER
```


## Authors

42 seoul intra id

[kyukim](https://profile.intra.42.fr/users/kyukim)
[kbaek](https://profile.intra.42.fr/users/kbaek)

