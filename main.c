#include "codexion.h"

#include "codexion.h"

int main(int argc, char **argv)
{
    t_table table;

    if (parse_args(argc, argv, &table.params))
        return (1);
    if (init_table(&table))
        return (1);
    printf("Init OK: %d coders\n", table.params.nb_coders);
    free(table.coders);
    free(table.dongles);
    return (0);
}