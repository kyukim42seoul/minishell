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
