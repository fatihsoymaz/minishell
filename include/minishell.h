/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:20:38 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/17 12:06:36 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

enum						e_builtin
{
	CD = 1,
	ENV,
	PWD,
	ECO,
	EXIT,
	UNSET,
	EXPORT,
};

enum						e_token
{
	PIPE = 1,
	IN_RED,
	OUT_RED,
	APPEND,
	HEREDOC,
	WORD,
};

typedef struct s_token
{
	char					*str;
	enum e_token			type;
	struct s_token			*next;
	struct s_token			*prev;
}							t_token;

typedef struct s_redirection
{
	char					*redirect;
	enum e_token			type;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_execute
{
	char					*execute;
	struct s_execute		*next;
}							t_execute;

typedef struct s_command
{
	pid_t					pid;
	int						fd[2];
	t_execute				*execute;
	t_redirection			*redirects;
	t_execute				*tmp;
	t_redirection			*tmp2;
	struct s_command		*prev;
	struct s_command		*next;
}							t_command;

typedef struct s_glb
{
	int						parent_pid;
	int						cmd_count;
	int						token_count;
	char					**env;
	char					**paths;
	int						erorno;
	int						heredoc;
	t_token					*tokens;
	t_command				*commands;
}							t_glb;

extern t_glb				g_glb;

void						signals_init(void);
void						fill_env(char **env);
void						fill_paths(void);
int							is_operator(char *str);
int							tokens_count(char *line);
void						token_fill(char *line, t_token **tokens);
int							lst_add_back_token(t_token **lst, t_token *new_node,
								int count);
t_token						*lst_last_token(t_token *lst);
int							parse_token_string(char **str, t_token **tokens);
t_token						*lst_new_elem_token(enum e_token type, char *value);
char						*get_env_key(char *str);
void						dollar_fill(t_token *tokens);
char						*env_fill_init(char *str);
char						*env_fill_str(char *str);
char						*get_str(char *str, int *pos, int type);
char						*split_env2(char *str);
int							valid_op(char c);
void						new_str_fill(char **new_str, char *str);
char						*get_env(char *str);
char						*delete_quote(char *str);
t_redirection	*fill_redirect(t_token *tokens,
								t_redirection **redirects);
t_execute					*fill_execute(t_token *token, t_execute **execute);
void						fill_command(t_token *tokens, t_command **commands);
void						heredoc(int *fd, char *endline);
int							is_builtin(char *command);
void						output(char *file, int mode);
void						input(char *file);
void						redirect_inputs(t_command *cmd);
void						redirect_outputs(t_command *cmd);
void						start_builtin(t_execute *execute);
void						run_cmd(void);
void						builtin_cd(t_execute *execute);
void						builtin_echo(t_execute *execute);
void						builtin_env(void);
void						builtin_exit(t_execute *execute);
void						builtin_pwd(void);
int							is_builtin(char *command);
void						fill_heredoc(void);
void						command_err(char *str);
void						actuation_cmd(t_command *cmd);
void						close_all_fd(void);
int							contain_heredoc(t_command *cmd);
char						*get_path(char *cmd);
void						builtin_unset(t_execute *execute);
void						builtin_export(t_execute *execute);
int							is_parent(void);
int							check_pars_error(t_token *token);
void						free_cmd(void);
void						free_token(t_token *tokens);
void						free_env(void);
void						print_env_vars(void);
char						**get_arg_fill(t_execute *execute);
void						actuation_cmd(t_command *cmd);
void						cmd_route(t_command *cmd);
int							arg_count_ex(t_execute *execute);
void						del_quote(t_token *token);
int							control_env(char *str);
int							strcmp_while(const char *s1, const char *s2);
void						free_env(void);
int							env_position(char *str);
int							strcmp_while(const char *s1, const char *s2);
char						*get_var_name(char *var);
void						check_dir(char *cmd);
void						directory_err(char *str);
void						no_file_err(char *str);
void						add_env(char *str);
void						without_quote_parse(char **str);
void	words_and_op(char *line, int *i, int *count);
#endif