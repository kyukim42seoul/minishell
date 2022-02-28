// #include "proto.h"

// char	**ft_mal_free(char **res)
// {
// 	char	**copy_res;

// 	copy_res = res;
// 	while (*res)
// 	{
// 		free(*res);
// 		*res = NULL;
// 		res++;
// 	}
// 	free(copy_res);
// 	copy_res = NULL;
// 	return (NULL);
// }

// char	*ft_str_p(char *pr, char const *s, int i, int p_len)
// {
// 	char	*c_pr;

// 	c_pr = pr;
// 	while (p_len > 0)
// 	{
// 		*pr = s[i - p_len];
// 		pr++;
// 		p_len--;
// 	}
// 	*pr = '\0';
// 	return (c_pr);
// }

// /*
// 쌍따옴표 혹은 따옴표를 만나면 그 다음 쌍따옴표나 따옴표를 만날 때까지 변수를 증가시키고,
// p_len 을 구해서 ft_str_p 로 보내 문자열 넣기.
// */


// char	**ft_fill_p(char const *s, char c, char **res, int pp_len)
// {
// 	int		i;
// 	int		p_len;
// 	char	**c_res;

// 	i = 0;
// 	c_res = res;
// 	while (s[i] && pp_len--)
// 	{
// 		p_len = 0;
// 		while (s[i] && s[i] == c)
// 			i++;
// 		while (s[i] && s[i] != c)
// 		{
// 			i++;
// 			p_len++;
// 		}
// 		*res = malloc(sizeof(char) * (p_len + 1));
// 		if (!res)
// 			return (ft_mal_free(res));
// 		ft_str_p(*res, s, i, p_len);
// 		res++;
// 	}
// 	return (c_res);
// }


// int	ft_pp_len(char const *s, char c)
// {
// 	int	len;

// 	len = 0;
// 	while (*s)
// 	{
// 		if (*s != c)
// 			len++;
// 		while (*s && *s != c)
// 			s++;
// 		if (*s == c && *s)
// 			s++;
// 	}
// 	return (len);
// }

// char	*ft_strchr(char *s, int c)
// {
// 	while (*s && *s != (char)c)
// 		++s;
// 	if (*s == (char)c)
// 		return (s);
// 	return (NULL);
// }

// int	ft_space_len(char const *s)
// {
// 	int	len;

// 	len = 0;
// 	while (*s)
// 	{
// 		if (*s != ' ')
// 		{
// 			len++;
// 			printf("\ns = %c len = %d\n", *s, len);
// 		}
// 		if (*s == '\"')
// 		{
// 			s++;
// 			while (*s && *s != '\"')
// 				s++;
// 			s++;
// 		}
// 		else if (*s == '\'')
// 		{
// 			s++;
// 			while (*s && *s != '\'')
// 				s++;
// 			s++;
// 		}
// 		while (*s && *s != ' ')
// 			s++;
// 		if (*s == ' ' && *s)
// 			s++;
// 	}
// 	printf("\nlen = %d\n", len);
// 	return (len);
// }










// int	check_command(char *s, int i, int *len)
// {
// 	if (s[i] == '|')
// 	{
// 		if (s[i + 1] == '|')
// 			i++;
// 		i++;
// 		len++;
// 	}
// 	else if (s[i] == '<')
// 	{
// 		if (s[i + 1] == '<')
// 			i++;
// 		i++;
// 		len++;
// 	}
// 	else if (s[i] == '>')
// 	{
// 		if (s[i + 1] == '>')
// 			i++;
// 		i++;
// 		len++;
// 	}
// 	else
// 	{
// 		if (i > 0 && (s[i - 1] == '|' || s[i - 1] == '>' || s[i - 1] == '<'))
// 			len++;
// 		i++;
// 	}
// 	return (i);
// }

// int space_len(char *s)
// {
// 	int len;
// 	int i;

// 	len = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != ' ')
// 		{
// 			len++;
// 			printf("\ns = %c len = %d\n", s[i], len);
// 		}
// 		if (s[i] == '\"')
// 		{
// 			i++;
// 			while (s[i] && s[i] !='\"')
// 				i++;
// 			i++;
// 		}
// 		else if (s[i] == '\'')
// 		{
// 			i++;
// 			while (s[i] && s[i] != '\'')
// 				i++;
// 			i++;
// 		}
// 		while (s[i] && s[i] != ' ')
// 			i = check_command(&s[i], i, &len);
// 		if (s[i] == ' ' && s[i])
// 			i++;
// 	}
// 	printf("len = %d\n", len);
// 	return (len);
// }


// int ft_check_next(char *s, int i)
// {
// 	while (s[i])
// 	{
// 		if (ft_strchr("|<> ", s[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	new_space_len(char *s)
// {
// 	int len;
// 	int i;

// 	len = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (ft_strchr("|<> ", s[i]))
// 		{
// 			if (s[i] == ' ')
// 			{
// 				if (i > 0 && (s[i - 1] == '<' || s[i - 1] == '>'))
// 					len--;
// 				while (s[i] && s[i] == ' ')
// 					i++;
// 			}
// 			else if (s[i] == '|')
// 			{
// 				if (i > 0 && s[i - 1] == ' ')
// 					len--;
// 				if (s[i + 1] == '|')
// 					i++;
// 				i++;
// 			}
// 			else if (s[i] == '>')
// 			{
// 				if (i > 0 && s[i - 1] == ' ')
// 					len--;
// 				if (s[i + 1] == '>')
// 					i++;
// 				i++;
// 			}	
// 			else if (s[i] == '<')
// 			{
// 				if (i > 0 && s[i - 1] == ' ')
// 					len--;
// 				if (s[i + 1] == '<')
// 					i++;
// 				i++;
// 			}
// 			len++;
// 			printf("\ns = %c len = %d\n", s[i], len);	
// 		}
// 		else if (ft_strchr("\"\'", s[i]))
// 		{
// 			if (s[i] == '\"')
// 			{
// 				i++;
// 				while (s[i] && s[i] !='\"')
// 					i++;
// 				i++;
// 			}
// 			else if (s[i] == '\'')
// 			{
// 				i++;
// 				while (s[i] && s[i] != '\'')
// 					i++;
// 				i++;
// 			}
// 		}
// 		else
// 			i++;	
// 	}
// 	//printf("\n\nlen = %d\n\n", len);
// 	return (len);
// }

// char *create_new_str(char *s, int i, int *len, char c)
// {
// 	t_new_line flag;
// 	char *str;
// 	int j;
// 	int index;
	
// 	flag.start = i;
// 	flag.num = 0;
// 	flag.left_space = 0;
// 	flag.left_space = 0;
// 	flag.new_len =* len;
// 	if (i > 0 && s[i - 1] != ' ')
// 	{
// 		flag.left_space = 1;
// 		flag.new_len++;
// 	}
// 	while (s[i] && s[i] == c)
// 	{
// 		flag.num++;
// 		i++;
// 	}
// 	if (i < *len && s[i] != ' ')
// 	{
// 		flag.right_space = 1;
// 		flag.new_len++;
// 	}
// 	if (flag.left_space == 0 && flag.right_space == 0)
// 		return (s);
// 	str = (char *)malloc(sizeof(char) * flag.new_len + 1);
// 	if (!str)
// 		exit(-1);
// 	str[flag.new_len] = '\0';
// 	j = -1;
// 	index = 0;
// 	while (++j < flag.start)
// 		str[j] = s[index++];
// 	if (flag.left_space > 0)
// 	{
// 		str[j] = ' ';
// 		j++;
// 	}
// 	while (flag.num)
// 	{
// 		str[j] = s[index++];
// 		flag.num--;
// 	}
// 	if (flag.right_space > 0)
// 	{
// 		str[j] = ' ';
// 		j++;
// 	}
// 	while (j < flag.new_len && index < *len)
// 	{
// 		str[j] = s[index];
// 		j++;
// 		index++;
// 	}
// 	*len = flag.new_len;
// 	return (str);
// }

// char *made_it_easy(char *s)
// {
// 	int i;
// 	int j;
// 	char *new_str;
// 	int len;
// 	t_new_line line;

// 	new_str = NULL;
// 	len = (int)strlen(s);
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '|')
// 			new_str = create_new_str(s, i, &len, '|');
// 		else if (s[i] == '>' || s[i] == '<')
// 		{
// 			if (s[i] == '>')
// 				new_str =  create_new_str(s, i, &len, '>');
// 			else
// 				new_str =  create_new_str(s, i, &len, '<');
// 		}
// 		i++;
// 	}



// 	while (s[i])
// 	{
// 		if (s[i] == '|')
// 			new_str = create_new_str(s, i, &len, '|');
// 		else if (s[i] == '>' || s[i] == '<')
// 		{
// 			if (s[i] == '>')
// 				new_str =  create_new_str(s, i, &len, '>');
// 			else
// 				new_str =  create_new_str(s, i, &len, '<');
// 		}
// 		i++;
// 	}
// }

// char	**command_split(char *s)
// {
// 	//char	**res;
// 	int		pp_len;
// 	char *new_s;

// 	if (!s)
// 		return (NULL);
// 	new_s = made_it_easy(s);
// 	pp_len = space_len(s);
// 	// res = (char **)malloc(sizeof(char *) * (pp_len + 1));
// 	// if (!res)
// 	// 	return (NULL);
// 	// res[pp_len] = NULL;
// 	// ft_fill_p(s, ' ', res, pp_len);
// 	return (NULL);
// }

// int quotation_check(char *s, int i)
// {
// 	int status;

// 	status = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'')
// 		{
// 			if (status == 0)
// 				status = 1;
// 			else if (status == 1)
// 				status = 0;
// 		}
// 		else if (s[i] == '\"')
// 		{
// 			if (status == 0)
// 				status = 2;
// 			else if (status == 2)
// 				status = 0;
// 		}
// 		i++;
// 		while (s[i] && (s[i] !=  '\"' &&  s[i] != '\''))
// 		 	i++;
// 	}
// 	return (status);
// }

// void	input_tokenize(char *full_command, t_info *info)
// {
// 	int		index;
// 	 char 	**splited;
// 	//t_token *current;
// 	//t_token	*check;

// 	index = 0;
// 	if (!full_command)
// 		return ;
// 	info->t_head = NULL;
// 	if (quotation_check(full_command, 0))
// 		return (exit(-1));
// 	splited = command_split(full_command);
// 	// while (**splited)
// 	// {
// 	// 	current->data = **splited;
// 	// 	current->type = check_type(**splited);
// 	// 	sh_lstadd_back(&info->t_head, current);
// 	// 	splited++;
// 	// }
// 	// check = info->t_head->next;
// }