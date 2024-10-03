/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 06:37:36 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/03 18:47:27 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_perror(char *msg, char *utils, char *s)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (utils)
		write(STDERR_FILENO, utils, ft_strlen(utils));
	if (s)
		write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, ".\n", 2);
	return (EXIT_FAILURE);
}



void	execute_simple_command(t_command *cmnd, t_env *envar)
{
	int		pid;
	int status = 0;

	pid = fork();
	if (pid == 0)
	{
		if (cmnd->cmd)
			exec_command(cmnd, envar);
		exit (1);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
}

void	exec_child(int *fd, t_command *smpl_cmd, t_env *envar)
{
	close(fd[0]);
	dup2(fd[1], 1);
	execute_simple_command(smpl_cmd, envar);
	close(fd[1]);
	exit(0);
}

void execute_piped_command(t_command *command, t_env *envar)
{
    int fd[2];
    int status;
    pid_t pid;
    t_command *smpl_cmd = command;

    while (smpl_cmd->next)
    {
        // Create a pipe for the current command
        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(1);
        }

        // Fork a new process
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }

        if (pid == 0) // Child process
        {
            // Redirect stdout to the pipe's write end
            if (dup2(fd[1], STDOUT_FILENO) == -1)
            {
                perror("dup2");
                exit(1);
            }
            close(fd[1]); // Close the write end after duplication
            close(fd[0]); // Close the read end in the child

            // Execute the current command
            execute_simple_command(smpl_cmd, envar);
			_free();
        }
        else // Parent process
        {
            // Close the write end in the parent
            close(fd[1]);

            // Redirect stdin to the pipe's read end for the next command
            if (dup2(fd[0], STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(1);
            }
            close(fd[0]); // Close the read end after duplication

            // Wait for the child process to finish
            waitpid(pid, &status, 0);
        }

        // Move to the next command in the pipeline
        smpl_cmd = smpl_cmd->next;
    }

    // Execute the last command in the pipeline
    execute_simple_command(smpl_cmd, envar);

    // Restore stdin to default
    dup2(STDIN_FILENO, STDIN_FILENO);
}


void nongnu(int i)
{
    if (i == SIGINT)
    {
        write(0,"\n", 1 );
        // rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}
int check_heredoc(char *cmd)
{
	int i = 0;
	while (cmd[i])
	{
		if(cmd[i] == '<' && cmd[i + 1] == '<')
			return(1);
		// if(!cmd[i + 1])
		// 	break;
		i++;
	}
	return(0);
	
}
void hayed_3liya(t_command **command)
{
    t_command *tmp = (*command);
	t_file	*tmp_file;
	while (tmp)
	{

		if (tmp->cmd)
		{
			int i = 0;
			while (tmp->cmd[i])
			{
				tmp->cmd[i] = remove_quotes(tmp->cmd[i]);
				i++;
			}
		}
		tmp_file = tmp->file;
		while (tmp_file)
		{
			tmp_file->file_name = remove_quotes(tmp_file->file_name);
			tmp_file = tmp_file->next;
		}
		tmp = tmp->next;
	}

}

int	ft_readline(char *line)
{
	line = readline("[minishell]~> ");
	if (!line)
	{
		printf("exit\n");
		exit(1);
	}
	if (ft_strcmp(line, "") == 0)
		return (1);
	if (ft_strlen(line) > 0)
		add_history(line);
	return (0);
}
void	loop_minishell(t_tool *data, t_env *env)
{
	t_command	*command_list;
	(void)env;

	signal(SIGINT, nongnu);
    signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		data->cmd = readline("minishell$ ");
		printf("hhhhhhh\n");
		if (data->cmd)
		{
			// if(!check_heredoc(data->cmd))
				add_history(data->cmd);
			lexer(data);
			if (syntax_error(data))
			{
				printf("syntax error\n");
				continue ;
			}
			expand(data->lexer_list, env);
			// display_token_lexer(data->lexer_list);
			command_list = parser(data->lexer_list);
			if(ambiguous(command_list))
			{
				printf("ambiguous redirect\n");
				continue ;
			}
			hayed_3liya(&command_list);
			// display_token_command(command_list);
			execute_piped_command(command_list, env);
			// free(data->cmd);
		}
		else if (!data->cmd)
		{
			_free();
			// ba9i leak
			break ;
		}
	}
}