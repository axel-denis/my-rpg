/*
** EPITECH PROJECT, 2022
** rpg - menu setups
** File description:
** setups structures for the menu
*/

#include "inventory_structures.h"
#include "inventory_prototypes.h"
#include "my_csfml_utils.h"
#include "my_game_struct.h"
#include "my_button.h"
#include "json.h"
#include <stdlib.h>

static object_t **setup_pages(void)
{
    object_t **result = malloc(sizeof(object_t *) * 4);
    sfVector2f scale = {4, 4};
    sfVector2f pos = {0, 0};

    result[0] = create_object
        ("assets/img/inventory_background.jpg", pos, scale);
    result[1] = create_object("assets/img/inventory.png", pos, scale);
    result[2] = create_object("assets/img/stats.jpg", pos, scale);
    result[3] = create_object("assets/img/competences.png", pos, scale);
    return (result);
}

static txtobject_t setup_text(font_t **fonts, game_t *game)
{
    txtobject_t result;
    result.font = FONTG("Ancient.ttf");
    result.text = sfText_create();
    return (result);
}

backgrounds_t setup_backgrounds(game_t *game)
{
    backgrounds_t result;

    result.items = game->items;
    result.pages = setup_pages();
    result.text = setup_text(game->fonts, game);
    result.window = game->window->window;
    result.keys = game->keys;
    result.comp = game->comp;
    result.player = game->game->player;
    return (result);
}

object_t **setup_comp_sprites(void)
{
    object_t **result = malloc(sizeof(object_t *) * 68);
    json_obj_t *json = create_json_object("src/inventory/comp_desc.json");
    sfVector2f pos = {0, 0};

    for (int i = 1; i <= 67; i++) {
        pos = get_comp_pos(i);
        pos.x += 16;
        pos.y += 16;
        result[i] = create_object(get_str_by_name
            (get_obj_by_index(json, i), "imgpath"), VCF {1, 1}, VCF {1, 1});
        sf_sprite_set_pixel_size(result[i]->sprite, VCF {104, 104});
        sfSprite_setPosition(result[i]->sprite, pos);
    }
    free_json(json, 0);
    return (result);
}

events_t setup_events(game_t *game, int *page)
{
    events_t result;

    result.window = game->window->window;
    result.items = game->items;
    result.page = page;
    result.keys = game->keys;
    result.button = button_create(VCF {1, 1}, VCF {280, 950}, 1);
    button_setup_texture_file(result.button, (sfIntRect) {0, 0, 263, 79}
        , "assets/img/button.jpg");
    button_setup_text(result.button, "aquire", FONTG("Ancient.ttf"), 20);
    button_setup_sounds(result.button, SOUNDG("hover.ogg")
        , SOUNDG("click.ogg"), 20);
    button_setup_offset(result.button,
        VCF {0.2, 0.2}, VCF {0.15, 0.15}, VCF{0, 0});
    result.comp = game->comp;
    sfRenderWindow_clear(game->window->window, sfBlack);
    return (result);
}
