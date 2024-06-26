#include "../includes/main.h"

int add_quote(t_db *db, int ascii, int start)
{
    t_quote *new;
    t_quote *tmp;

    new = gc_malloc(db, sizeof(t_quote));
    if (!new) return (FAILURE);
    new->ascii = ascii;
    new->start = start;
    new->end = -1;
    new->next = NULL;
    if (!db->quotes)
    {
        db->quotes = new;
        return (SUCCESS);
    }
    tmp = db->quotes;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (SUCCESS);
}

t_quote *last_quote(t_db *db)
{
    t_quote *tmp;

    if (!db->quotes) return (NULL);
    tmp = db->quotes;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

int track_quotes(t_db *db, char *line)
{
    int i;
    t_quote *last;

    i = 0;
    while (line[i])
    {
        last = last_quote(db);
        if ((line[i] == 34 || line[i] == 39) && (!db->quotes || !last))
        {
            if (add_quote(db, line[i], i) == FAILURE) return (FAILURE);
        }
        else if ((line[i] == 34 || line[i] == 39)
            && last->ascii == line[i]
            && last->end == -1)
        {
            last->end = i;
        }
        else if ((line[i] == 34 || line[i] == 39)
            && last->end != -1)
        {
            if (add_quote(db, line[i], i) == FAILURE) return (FAILURE);
        }
        i++;
    }
    last = last_quote(db);
    if (db->quotes && last->end == -1) return (error(db, "Quotes are not closed"));
    return (SUCCESS);
}

void    reset_quotes(t_db *db)
{
    t_quote *tmp;

    while (db->quotes)
    {
        tmp = db->quotes;
        db->quotes = db->quotes->next;
        gc_free(db, tmp);
    }
    gc_free(db, db->quotes);
    db->quotes = NULL;
}
