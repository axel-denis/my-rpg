/*
** EPITECH PROJECT, 2022
** rpg - menu prototypes
** File description:
** here be descriptions
*/

#pragma once

#include "inventory_structures.h"
#include "my_game_struct.h"

#include "inventory_structures.h"

int count_item(item_t *items, int type);
int get_competence(sfVector2f pos);
int get_slot(sfVector2f pos);
int is_adjacent_comp(int comp, int test);

int get_competence_state(int comp, competences_t competences);

sfVector2f get_comp_pos(int comp);
sfVector2f get_slot_pos(int slot, sfRenderWindow *window);

backgrounds_t setup_backgrounds(game_t *game);

item_t *add_items(int origin, int dest, item_t *items);
item_t *consume(item_t *items, int type, int quantity);
item_t *drop_items(item_t *items, int pressed, int slot);
item_t *level_items(int dest, int origin, int max, item_t *items);
item_t *pickup_item(item_t new_item, item_t *items);
item_t *pickup_items(item_t *items, char *keys, int *pressed, int);
item_t *split_item(int origin, int dest, item_t *items, int number);
item_t *swap_items(int origin, int dest, item_t *items);

object_t **setup_comp_sprites();

void disp_cmp(backgrounds_t bgs);
void draw_competences(sfRenderWindow *window, competences_t *comp);
void draw_descriptions(sfRenderWindow *window, competences_t *comp, sfText *);
void disp_inv(backgrounds_t bgs);
void disp_map(backgrounds_t bgs);
void draw_items(sfRenderWindow *window, item_t *items, txtobject_t);
void set_view_inv(game_t *game);

events_t evt_cmp(events_t events);
events_t evt_inv(events_t events);
events_t evt_map(events_t events);
events_t setup_events(game_t *game, int *page);

competences_t set_competence_state(int comp, competences_t, int);
