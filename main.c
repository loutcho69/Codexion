#include "codexion.h"

#include "codexion.h"

int main(int argc, char **argv)
{
    t_params params;

    if (parse_args(argc, argv, &params) != 0)
        return (1);
    printf("OK: %d coders, sched=%d\n", params.nb_coders, params.scheduler);
    return (0);
}