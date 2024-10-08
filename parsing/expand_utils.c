/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:48:03 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 23:32:27 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_value(char *str, int *i, int *index, char *env_variable)
{
	char			*new_val;
	t_env_var		*get_env;
	char			*value;
	char			*first;
	char			*last;

	env_variable = ft_substr(str, *i + 1, *index - *i - 1);
	get_env = env_bykey(*((get_collector())->env), env_variable);
	if (get_env == NULL)
		value = ft_strdup("");
	else
		value = ft_strdup(get_env->value);
	first = ft_substr(str, 0, *i);
	last = ft_strdup(&str[*index]);
	new_val = ft_strjoin(first, value);
	free(value);
	value = new_val;
	new_val = ft_strjoin(value, last);
	free(value);
	free(last);
	free(first);
	free(env_variable);
	free(str);
	return (new_val);
}

int	expand_helper(int index, int *i, char *str)
{
	index = *i;
	index++;
	if (str[index] == '?' || is_number(str[index]))
		index++;
	else
	{
		while (str[index] && is_word(str[index]))
			index++;
	}
	return (index);
}

int	not_alnum(char c)
{
	return (!is_alpha(c) && !is_number(c) && c != '_' && c != '?' && c != '`');
}
