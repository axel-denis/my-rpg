/*
** EPITECH PROJECT, 2022
** rpg - player animation dispatcher
** File description:
** give a number and it'll give the right animation
*/

#include "player_animation.h"
#include "my_csfml_utils.h"
#include "csfml_libs.h"
#include "my.h"
#include <stdlib.h>

static char *add_str(char *src1, char *src2)
{
    char *res = malloc(sizeof (char) * (my_strlen(src1) + my_strlen(src2) + 1));
    int i = 0;
    for (int j = 0; src1[j] != '\0'; j++) {
        res[i] = src1[j];
        i += 1;
    }
    for (int j = 0; src2[j] != '\0'; j++) {
        res[i] = src2[j];
        i += 1;
    }
    res[my_strlen(src1) + my_strlen(src2)] = '\0';
    return (res);
}

static animation_t create_animation(char *name, int hsize, int step_size, int animation_size)
{
    animation_t result;
    sfVector2f pos = {1, 1};
    sfVector2f scale = {4, 4};
    char *path = add_str("assets/img/player/", name);

    result.spritesheet = create_object(path, pos, scale);
    result.animation_size = animation_size;
    result.hsize = hsize;
    result.step_size = step_size;
    sfSprite_setOrigin(result.spritesheet->sprite, VCF {step_size / 2, hsize / 2});
    free (path);
    return (result);
}

static animation_t *get_player_animations(void)
{
    animation_t *result = malloc(sizeof(animation_t) * 3);

    result[0] = create_animation("run.png", 24, 16, 6);
    result[1] = create_animation("multi_attack.png", 24, 49, 34);
    result[2] = create_animation("dash.png", 24, 78, 11);
    return (result);
}

static void set_player_rect(animation_t player_animation, int step)
{
    sfIntRect rect = {step * player_animation.step_size, 0, player_animation.step_size, player_animation.hsize};

    sfSprite_setTextureRect(player_animation.spritesheet->sprite, rect);
}

animation_t *place_player(sfRenderWindow *window, sfVector2f pos, int state)
{
    static animation_t *player_animations = NULL;
    static float time = 0;
    static int previous_state = 0;
    static int step = 0;
    if (player_animations == NULL)
        player_animations = get_player_animations();
    if (previous_state != state) {
        step = 0;
        previous_state = state;
    }
    time += 1;
    if (time >= 5) {
        step += 1;
        time = 0;
    }
    step = step % player_animations[state].animation_size;
    set_player_rect(player_animations[state], step);
    sfSprite_setPosition(player_animations[state].spritesheet->sprite, pos);
    sfRenderWindow_drawSprite(window, player_animations[state].spritesheet->sprite, NULL);
    return (player_animations);
}
