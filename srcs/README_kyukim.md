syntax.c

pipe(3) 단독 -> 2(PIPE)
cmd(1, 2) : pipe(3) -> 10(BUILTIN), 12(CMD)
path, word(5) : pipe(3) cmd(1, 2) -> 0(CHARACTERS)
redir(4) : pipe(3) cmd(1, 2) {path, word(5)} + 뒤에 path, word(5) -> 3(<:LEFT_REDI), 4(>:RIGHT_REDI), 5(<<:LEFT_DOUBLE_REDI), 6(>>:RIGHT_DOUBLE_REDI)

	syntax_cmd()

	앞에 PIPE 가 있어야 한다.(x) -> 앞에 redir 가 있어도 된다. 프로세스 하나 당 하나만 존재한다.

	syntax_pipe()

	뒤에 BUILTIN 혹은 CMD 가 있어야 한다.(x) -> 뒤에 redir 가 있어도 된다. -> 뒤에 파이프가 오면 안 된다.

	syntax_redir()

	앞에 PIPE 혹은 BUILTIN 혹은 CMD 가 있어야 한다. 뒤에 cmd(못 오나??) 혹은 characters 가 있어야 한다.

	syntax_word()

	앞에 REDIR(or DOUBLE REDIR) 혹은 BUILTIN 혹은 CMD 가 있어야 한다.

execve.c

run_execve()

	절대경로(ex. /bin/cat)일 경우
		첫 check_path() 조건문에서 execve() 실행
	상대경로(ex. cat) 일 경우
		make_relative_path() 에서 $PATH 의 모든 경로와 cmd 를 조합 후 반환(t_list *head)
		find_valid_path() 에서 저장된 모든 경로(t_list *lst)를 확인하여 유효한 경로의 노드 반환(t_list *node)
		반환된 노드의 content 로 execve() 실행

heredoc.c

heredoc()

기능

EOF 까지 입력을 받아 저장 후 stdin 으로 전달
	입력된 문자열과 EOF 비교 : 완벽하게 일치해야 함(뒤에 공백 x)
	받는 쪽에서 gnl() 처럼 읽기
다른 히어독과 차례로 stdin(keyboard) 를 점유해야 함.

테스트 케이스
cat << EOF > a.txt | cat << EDF > b.txt | cat << EFF > c.txt

가설
1. 부모쪽에서 히어독용 파이프 준비 후 자식들이 공유
	* 첫째 자식이 EOF 를 만나서 파이프를 닫는다고 해도 다음 자식이 fd 를 들고 있을텐데 닫히나?
2. 자식들이 각자 히어독용 파이프 생성 및 사용
	* 이쪽으로 해보자
	* stdin 을 먼저 히어독 실행한 쪽이 점유하고 있고 다른 히어독은
3. 방법은 모르겠지만 부모쪽에서 히어독 처리 후 자식 실행
