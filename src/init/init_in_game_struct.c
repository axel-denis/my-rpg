/*
** EPITECH PROJECT, 2022
** INIT_IN_GAME_STRUCT_C
** File description:
** init_in_game_struct
*/

#include <stdlib.h>
#include "json.h"
#include "my_game_struct.h"
#include "my.h"
#include "pnjs.h"
#include "my_rpg.h"

static maps_t **init_game_maps(void)
{
    maps_t **maps = malloc(sizeof(maps_t));
    json_obj_t *obj = create_json_object("config/maps.json");
    int i = 0;
    json_obj_t *tmp1 = get_obj_by_index(obj, i);
    json_obj_t *tmp = get_obj_by_index(tmp1, i);

    if (maps == NULL)
        return NULL;
    while (tmp != NULL)
        tmp = get_obj_by_index(tmp1, i++);
    maps = malloc(sizeof(maps_t *) * i);
    i = 0;
    tmp = get_obj_by_index(tmp1, i);
    while (tmp != NULL) {
        maps[i] = malloc(sizeof(maps_t));
        init_map_objects(maps, tmp, i++);
        tmp = get_obj_by_index(tmp1, i);
    }
    maps[i] = NULL;
    return maps;
}

void init_quest(in_game_t *ingame, game_t *game)
{
    ingame->quest = sfText_create();
    sfText_setString(ingame->quest, "Quest: kill 10 slimes\n\t\t0/10");
    sfText_setFont(ingame->quest, FONTG("Ancient.ttf"));
    sfText_setScale(ingame->quest, VCF{1, 1});
}

in_game_t *init_in_game_struct(game_t *main_game)
{
    in_game_t *game = malloc(sizeof(in_game_t));
    sfFloatRect cam_rect = {0, 0, 1920, 1080};

    game->maps = init_game_maps();
    game->enemies = NULL;
    game->player = init_game_player(game->maps[0]);
    game->current = my_strdup("house");
    game->cam_rect = cam_rect;
    game->in_dialogue = false;
    game->pnjs = create_pnjs();
    game->chat_box = create_object("assets/img/pnj/chat.png",
        VCF{0, 0}, VCF{2, 2});
    init_quest(game, main_game);
    game->cam = sfView_createFromRect(cam_rect);
    game->pos_cam = VCF {970, 540};
    game->clock = sfClock_create();
    game->weather = 3;
    if (game == NULL)
        return NULL;
    return game;
}
