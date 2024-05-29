#ifndef PARSING_H
#define PARSING_H

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

typedef struct s_expand_tokens
{
    char    *token;
    void    *next;
}   t_tokens;


/**
 * @details Defining the priority of the operators
*/
#define AND_OR_PRIORITY 1
#define PIPE_PRIORITY 2
#define REDIR_PRIORITY 3

/**
 * @details Defining the type of the operators
*/
#define OR 1
#define AND 2
#define PIPE 3
#define REDIR 4
#define APPEND 5
#define INPUT 6

/*string.c*/
void    skip_spaces(char *line, int *i);

/*parsing/quoting.c and parsing/quoting_utils.c*/
int     track_quotes(t_db *db, char *line);
int     is_inside_quotes(t_db *db, int i);
void    reset_quotes(t_db *db);
int     inside_single_quote(t_db *db, int   i);
int     is_inside_quotes(t_db *db, int i);

/*parsing/paranths.c && paranths2.c*/
int         track_paranthesis(t_db *db, char *line);
t_parnth    *last_unclosed_paranth(t_db *db);
int         is_inside_paranthesis(t_db *db, int i);

/*parsing/parser.c*/
int parser(t_db *db, char *line);

/*parsing/split.c*/
char    **whitespaces_split(t_db *db, char *str, int start);
int     is_whitespace(char c);

/*parsing/expanding.c*/
int expand(t_db *db, char **line);
char *get_env(t_db *db, char *name);

/*parsing/paranths.c and paranths2.c*/
int track_paranthesis(t_db *db, char *line);
int paranths_scopes_count(t_db *db);
int all_scopes_has_op_between(t_db *db, char *line);

/*op.c*/
int is_valid_op(char c, char next_c, int *i);
int unused_ops(char *line);

#endif