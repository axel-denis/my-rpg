/*
** EPITECH PROJECT, 2021
** myrpg
** File description:
** evolve_enemies.c
*/

#include "enemies.h"
#include "my.h"
#include "my_csfml_utils.h"
#include "my_game_struct.h"

//calculate enemy direction for x and y (0 <= x y <= 1)
static sfVector2f enemy_movement(enemy_t *enemy, game_t *game)
{
    sfVector2f player_pos = sfSprite_getPosition(game->game->player->sp_p);
    sfVector2f enemy_pos = sfSprite_getPosition(enemy->sprite);
    sfVector2f differential =
        {player_pos.x - enemy_pos.x, player_pos.y - enemy_pos.y};
    float max_range = MAX(differential.x, differential.y);

    differential.x = (differential.x / max_range) * enemy->speed;
    differential.y = (differential.y / max_range) * enemy->speed;
    return differential;
}

void displace_enemies(enemy_node_t *all, game_t *game)
{
    while (all->enemy.type != -1) {
        sfSprite_move(all->enemy.sprite, enemy_movement(&(all->enemy), game));
        all = all->next;
    }
}