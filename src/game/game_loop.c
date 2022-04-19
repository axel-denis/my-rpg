/*
** EPITECH PROJECT, 2022
** GAME_LOOP_C
** File description:
** game_loop
*/

#include "my_rpg.h"
#include "keyboard.h"
#include "my_game_struct.h"
#include "my.h"

static void poll_event_keys(game_t *game)
{
    game->keys = get_keyboard_input(game->keys, game->window->window);
    if (game->ESC)
        game->status->end_game = 1;
    if (game->P)
        game->status->end_game = 1;
    if (game->I)
        game->status->end_game = 1;
}

int game_loop(game_t *game)
{
    while (game->status->end_game == 0) {
        sfRenderWindow_clear(game->window->window, sfBlack);
        display_world(game);
        player_actions(game);
        poll_event_keys(game);
        sfRenderWindow_display(game->window->window);
    }
    game->game->pos_cam.x = 960;
    game->game->pos_cam.y = 540;
    sfView_setCenter(game->game->cam, game->game->pos_cam);
    sfRenderWindow_setView(game->window->window, game->game->cam);
    game->status->end_game = 0;
    return 0;
}