#include "codexion.h"
// es ce que j accepte le 0? 
// comment je les traites?

int is_valid_number(char *str)
{
    int i;
    i = 0;
    if(str[i] == '\0')
        return(0);
    while(str[i])
    {
        if(str[i] < '0' || str[i] > '9')
            return(0);
        i++;
    }
    return(1);
}

int ft_atoi_safe(char *str, int *result)
{
    int i;
    int digit;

    i = 0;
    *result = 0;
    while (str[i])
    {
        digit = str[i] - '0';
        if (*result > (INT_MAX - digit) / 10)
            return (1);
        *result = *result * 10 + digit;
        i++;
    }
    return (0);
}

int parse_one_int(char *str, int *dest)
{
    if (!is_valid_number(str))
        return (1);
    if (ft_atoi_safe(str, dest))
        return (1);
    return (0);
}
int parse_scheduler(char *argv, t_params *params)
{
    if (strcmp(argv, "fifo") == 0)
        params->scheduler = 1;
    else if (strcmp(argv, "edf") == 0)
        params->scheduler = 0;
    else
        return (1);
    return(0);     

}
int error_print(char *str)
{
    fprintf(stderr, "Error: %s.\n", str);
    return(1);
}
int parse_args(int argc, char **argv, t_params *params)
{
    if (argc != 9)
        return(error_print("not exacly 8 args"));
    if (parse_one_int(argv[1], &params->nb_coders))
        return(error_print("number_of_coders must be a positive integer"));
    if (parse_one_int(argv[2], &params->time_to_burnout))
        return(error_print("time_to_burnout must be a positive integer (in milliseconds)"));
    if (parse_one_int(argv[3], &params->time_to_compile))
        return(error_print("time_to_compile must be a positive integer (in milliseconds)"));
    if (parse_one_int(argv[4], &params->time_to_debug))
        return(error_print("time_to_debug must be a positive integer (in milliseconds)"));
    if (parse_one_int(argv[5], &params->time_to_refactor))
        return(error_print("time_to_refactor must be a positive integer (in milliseconds)"));
    if (parse_one_int(argv[6], &params->compiles_required))
        return(error_print("number_of_compiles_required must be a positive integer"));
    if (parse_one_int(argv[7], &params->dongle_cooldown))
        return(error_print("dongle_cooldown must be a non-negative integer (in milliseconds)"));
    if (parse_scheduler(argv[8], params))
        return(error_print("scheduler must be either 'fifo' or 'edf'"));
    return(0);
}