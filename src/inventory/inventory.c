/*
** EPITECH PROJECT, 2021
** menu - main loop
** File description:
** setup and main loop
*/

#include "keyboard.h"
#include "particles.h"
#include "pause_menu.h"
#include "csfml_libs.h"
#include "mouse.h"
#include "inventory_prototypes.h"
    #include "my_text.h"
    #include "particles.h"
#include "my_csfml_utils.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

object setup_mouse(void);
sfVector2f itofv2(sfVector2i vector);
void display_dialogue(sfRenderWindow *window, char *json_path, char *keys, font_t **fonts);

item_t *create_items(void)
{
    item_t *result = malloc(sizeof (item_t) * NB_SLOTS);
    for (int i = 0; i < NB_SLOTS; i++) {
        result[i].quantity = 0;
        result[i].type = NOTHING;
        result[i].sprite = sfSprite_create();
        result[i].texture = sfTexture_create(1, 1);
        result[i].stack_size = 1;
        result[i].armor_type = 5;
    }
    return (result);
}

void free_txtobject(txtobject_t object)
{
    sfText_destroy(object.text);
    sfFont_destroy(object.font);
}

int count_item(item_t *items, int type)
{
    int count = 0;

    for (int i = NB_SLOTS - 1; i >= 0; i--)
        if (items[i].type == type)
            count += items[i].quantity;
    return (count);
}

item_t *menu(sfRenderWindow *window, item_t *items, competences_t *comp, char *keys)
{
    backgrounds_t backgrounds = setup_backgrounds(items, comp, window, keys);
    static int page = 0;
    events_t events = {window, items, &page, keys, comp};
    static void (*disp[3])(backgrounds_t) = {disp_inv, disp_map, disp_cmp};
    events_t (*evt[3])(events_t) = {evt_inv, evt_map, evt_cmp};
    particle_t *start = create_particle((sfVector2f) {0, 0}, 0, 0);
    font_t **fonts = font_create_array();

    while (sfRenderWindow_isOpen(window)) {
        start = add_particle(start, (sfVector2f) {rand() % 1920, 0}, 0, 20);
        start = add_particle(start, (sfVector2f) {rand() % 1920, 0}, 1, 15);
        start = add_particle(start, (sfVector2f) {970, 540}, 2, 10);
        start = add_particle(start, (sfVector2f) {970, 740}, 12, 10);
        if (rand() % 100 == 0)
            for (int i = 0; i < 1000; i++)
                start = add_particle(start, (sfVector2f) {485, 540}, 3, 15);
        start = add_particle(start, (sfVector2f) {1465, 540}, 4, -10);
        start = add_particle(start, (sfVector2f) {1465, 540}, 5, -10);
        start = add_particle(start, (sfVector2f) {1465, 540}, 6, -10);
        start = add_particle(start, (sfVector2f) {1465, 540}, 7, -10);
        start = add_particle(start, (sfVector2f) {1465, 540}, 8, 10);
        start = add_particle(start, (sfVector2f) {1465, 540}, 9, 10);
        start = add_particle(start, (sfVector2f) {1465, 540}, 10, 10);
        start = add_particle(start, (sfVector2f) {1465, 540}, 11, 10);
        disp[page](backgrounds);
        events = evt[page](events);
        update_particles(window, start);
        if (P) {
            exterminate(start);
            return (items);
        }
        display_dialogue(window, "src/dialogue/example.json", keys, fonts);
        sfRenderWindow_display(window);
    }
    return (items);
}
