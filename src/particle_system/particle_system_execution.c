/*
** EPITECH PROJECT, 2022
** rpg - particle system execution
** File description:
** executes the particles int the chained list
*/

#include "csfml_libs.h"
#include "particles.h"
#include <stdlib.h>

void update_particles(sfRenderWindow *window, particle *start)
{
    static particle *(*tab[13])(sfRenderWindow *, particle *) = {snow, rain, fire, dust_circle, dust_up, dust_ur, dust_right, dust_dr, fire_up, fire_ur, fire_right, fire_dr, spark};

    while (start->next != NULL) {
        start = tab[start->type](window, start);
        start = start->next;
        if (start->next != NULL && start->next->age > start->next->lifetime)
            remove_particle(start);
    }
}
