#include "minishell.h"

static int	check_cnt(char const *s, char c)
{
	int		cnt;
	int		index;

	cnt = 0;
	index = 1;
	if (sh_strlen(s) == (unsigned long)index && s[index - 1 != c])
		cnt++;
	while (s[index])
	{
		if (s[index - 1] != c && s[index] == c)
			cnt++;
		else if (s[index] != c
			&& (unsigned long)index == (sh_strlen(s) - 1))
			cnt++;
		index++;
	}
	return (cnt);
}

static char	*cpy_arr(char const *s, char c, int index)
{
	int		start;

	if (!s)
	{
		return (NULL);
	}
	start = index;
	while (s[index] && s[index] != c)
	{
		if ((unsigned long)index == sh_strlen(s))
			return (sh_substr(s, start, (index - start)));
		index++;
	}
	return (sh_substr(s, start, (index - start)));
}
/*
static int	check_output(char **output, int cnt)
{
	int		index;
	int		temp;

	index = 0;
	temp = cnt;
	while (temp)
	{
		if (!output[index])
		{
			index = 0;
			while (output[index] && index < cnt)
				free(output[index++]);
			free(output);
			return (0);
		}
		index++;
		temp--;
	}
	return (1);
}
*/
static char	**null_pointer_to_pointer(void)
{
	char	**output;

	output = (char **)malloc(sizeof(char *) * 1);
	output[0] = NULL;
	return (output);
}

char	**sh_split(char const *s, char c)
{
	int		index;
	int		cnt;
	char	**output;
	int		flag;

	flag = 0;
	if (!s)
		return (NULL);
	if (!*s)
		return (null_pointer_to_pointer());
	index = 1;
	output = (char **)malloc(sizeof(char *) * (check_cnt(s, c) + 1));
	if (!output)
		return (NULL);
	cnt = 0;
	if (s[index - 1] != c)
		output[cnt++] = cpy_arr(s, c, 0);
	//따움표 처리 임시
	printf("c\n");
	if (s[index - 1] == 39)
		flag = 1;
	printf("d\n");
	while (s[index])
	{
		if (flag == 1 && (s[index] == 39 || s[index] == '"'))
			flag = 0;
		else if (flag == 0 && (s[index] == 39 || s[index] == '"'))
			flag = 1;
		printf("sp : |%c|%d\n", s[index], flag);
		if (s[index - 1] == c && s[index] != c && flag != 1)	// 여기에 '"', ''' 플래그를 넣으면 될 듯?!
			output[cnt++] = cpy_arr(s, c, index);
		index++;
	}
	output[cnt] = NULL;
//	if (check_output(output, check_cnt(s, c)))
	return (output);
//	return (NULL);
}
