/*
** EPITECH PROJECT, 2022
** rpg - misc objects actions
** File description:
** the other ones
*/

#include "my_game_struct.h"
#include "my_rpg.h"
#include "keyboard.h"
#include "enemies.h"
#include "particles.h"
#include "math.h"

void die(game_t *game)
{
    game->game->player->pos.x = 970;
    game->game->player->pos.y = 540;
    game->game->player->health = game->game->player->max_health;
    game->game->player->stamina = game->game->player->max_stamina;
    game->game->current = "house";
}

void fire_zone(game_t *game)
{
    static int time = 40;
    static sfClock *clock = NULL;
    float a = fmod(rand(), 100000000) / 100000000 * 2 * 3.141592;
    float r = 300 * sqrt(fmod(rand(), 100000000) / 100000000);
    sfVector2f pos = {CIRCLE_RANDOM};

    if (clock == NULL)
        clock = sfClock_create();
    if (game->LCLICK == 2 && game->items
        [game->game->player->hotbar_pos + 51].action == fire_zone)
        time = 40;
    if (time <= 0)
        game->game->player->status = NULL;
    if (time == 40)
        game->game->player->status = fire_zone;
    game->particles = add_particle(game->particles, pos, FIRE, 10);
    damage_enemy_zone(game, VCF {game->game->player->pos.x + PLAYER_OFFSET_X,
        game->game->player->pos.y + PLAYER_OFFSET_Y}, 300, 2);
    if (TIME(clock, 1))
        time -= 1;
}
