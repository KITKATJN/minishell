#include "minishell.h"

char        *replace_dollar_que_into_code(char *str, t_untils *untils)
{
    char    *start;
    char    *temporary;
    char    *first_part;
    char    *second_part;

    if (str == 0)
        return (str);
    if (str[0] == '~' && str[1] == 0)
    {
        ft_free(str);
        return(my_get_env("HOME", untils->env));
    }
    while (1)
    {
        if ((start = ft_strnstr(str, "$?+?", ft_strlen(str))) == 0)
            return (str);
        first_part = ft_substr(str, 0, ft_strlen(str) - ft_strlen(start));
        second_part = ft_substr(str, ft_strlen(str) - ft_strlen(start) + 4, ft_strlen(str));
        temporary = ft_strjoin(first_part, ft_itoa(untils->status));
        //printf("temporary = %s int = %d\n", ft_itoa(untils->status), untils->status);
        ft_free(first_part);
        ft_free(str);
        str = ft_strjoin(temporary, second_part);
        ft_free(temporary);
        ft_free(second_part);
    }
    return (str);
}