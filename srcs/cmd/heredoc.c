# include "../proto.h"
/*
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
*/

/*
int	heredoc(char *EOF)
{
	int		fd;
	int		cmp_result;
	char	*buf;
	char	*save_dir = "temp.txt";

	cmp_result = -1;
	buf = 0;
	fd = open(save_dir, O_RDWR|O_APPEND|O_CREAT, 0755);
	while (cmp_result != 0)
	{
		buf = readline("heredoc>");
		cmp_result = ft_strncmp(buf, EOF, ft_strlen(EOF));
		if (buf)
		{
			write(fd, buf, ft_strlen(buf));
			write(fd, "\n", 1);
		}
	}
	dup2(fd, STDIN_FILENO);
	return (EXIT(SUCCESS));
}
*/

/*
int	child_count(t_token *head)
{
	int		count;
	t_token	*cur;

	count = 0;
	cur = head->next;
	while (cur->next)
	{
		if (cur->type == PIPE)
			count++;
		cur = cur->next;
	}
	return (count);
}
*/

int	type_count(t_token *head, int type)
{
	int		count;
	t_token	*cur;

	count = 0;
	cur = 0;
	if (head == NULL)
		return (count);
	cur = head->next;
	while (cur)
	{
		if (cur->type == type)
			count++;
		cur = cur->next;
	}
	return (count);
}

int	heredoc(t_info *info)
{
	int		index;
	int		child_count;
	int		child_number;
	int		count;
	char	*eof;
	char	*line;
	t_token	*cur;

	index = 0;
	child_number = 0;
	line = (char *)malloc(sizeof(char));
		child_count = type_count(info->t_head, PIPE) + 1;
	count = type_count(info->t_head, LEFT_DOUBLE_REDI);
	info->heredoc = (t_heredoc *)malloc(sizeof(t_heredoc) * (count + 1));
	cur = info->t_head->next;
	while (count > 0)
	{
		cur = find_heredoc(cur);
		eof = cur->next->data;
		pipe(info->heredoc[index].pip);
		while (ft_strncmp(eof, line, 1000) != 0)
		{
			line = readline("test> ");
			write(info->heredoc[index].pip[1], line, ft_strlen(line));
			write(info->heredoc[index].pip[1], "\n", 1);
		}
		close(info->heredoc[index].pip[1]);
		free(line);
		cur = cur->next;
		if (child_count -  (type_count(cur, PIPE) + 1) > 0)
		{
			child_count = type_count(cur, PIPE) + 1;
			child_number++;
		}
		info->heredoc[index].use_number = child_number;
		index++;
		count--;
	}
	return (EXIT_SUCCESS);
}
