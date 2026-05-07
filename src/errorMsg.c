#include <stdio.h>

#include "game.h"

void    *ft_error(char *msg)
{
    printf("\e[0;31m|-\tERROR\t-|\n\t%s\n|-\tERROR\t-|\n\e[0m", msg);
    return (NULL);
}

int    ft_errorInt(char *msg, int ret)
{
    printf("\e[0;31m|-\tERROR\t-|\n\t%s\n|-\tERROR\t-|\n\e[0m", msg);
    return (ret);
}

