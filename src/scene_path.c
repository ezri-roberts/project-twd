#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/raylib/src/raylib.h"
#include "scene_builder.h"
#include "scene_path.h"
#include "assets.h"
#include <stdio.h>


//==================================================================================================================================
void gen_random_path(Scene *scene) {
    int anchor[2] = {8, 1};  // Initial anchor position
    int index = 0;
    char last; // S = Sideways, D = Down, U = Up
    char new;
    scene->tilemap.tiles[anchor[0]][anchor[1]] = 5; //Always set first tile to be sideways path
    while(anchor[1]+2 < TILEMAP_WIDTH)
    {
    index = save_waypoint(scene, anchor, index);   
    gen_section(scene, anchor, &last, &new);
    }
}
//==================================================================================================================================
void gen_section(Scene *scene, int *anchor, char *last, char *new) {

    int distance = GetRandomValue(2,6);
    int UpOrDown = GetRandomValue(1,2);
    char last_val = *last;

        if (last_val == 'S'){ //PATH WAS GOING SIDE
            if (UpOrDown == 1){ //PATH IS GOING UP
            distance = check_for_edge(anchor, distance, UpOrDown);
            path_up(scene, anchor, distance, last, new);
            }
            if (UpOrDown == 2){ //PATH IS GOING DOWN
            distance = check_for_edge(anchor, distance, UpOrDown);
            path_down(scene, anchor, distance, last, new);
            }
        }
        else{
            UpOrDown = 0; //PATH IS GOING RIGHT
            distance = check_for_edge(anchor, distance, UpOrDown);
            path_right(scene, anchor, distance, last, new);
            }
}
//==================================================================================================================================
int check_for_edge(int *anchor, int distance, int UpOrDown) {
    int NewDistance = 0;
        switch(UpOrDown) {
            case 0: //PATH IS GOING RIGHT
                for(int i=0; i<distance; i++){
                    if (anchor[1]+i < TILEMAP_WIDTH-2){
                    NewDistance++;
                    }
                }
                break;
            case 1: //PATH IS GOING UP
                for(int i=0; i<distance; i++){
                    if (anchor[0]-i > 1){
                    NewDistance++;
                    }
                }
                break;
            case 2: //PATH IS GOING DOWN
                for(int i=0; i<distance; i++){
                    if (anchor[0]+i < TILEMAP_HEIGHT-2){
                    NewDistance++;
                    }
                }
                break;
            default:
                printf("Invalid Direction\n");
                break;
        }
    return NewDistance;
}
//==================================================================================================================================
void path_right(Scene *scene, int *anchor, int distance, char *last, char *new) {
    *new = 'S'; // S = Sideways, D = Down, U = Up
    scene->tilemap.tiles[anchor[0]][anchor[1]] = anchor_turn(last, new); 

    for (int i = 0; i < distance; i++) {
        anchor[1]++;
        scene->tilemap.tiles[anchor[0]][anchor[1]] = 5;
    }

    set_last(last, new);
}
//==================================================================================================================================
void path_up(Scene *scene, int *anchor, int distance, char *last, char *new) {
    if (distance == 0){*new = 'S';}
    else{*new = 'U';} // S = Sideways, D = Down, U = Up
    scene->tilemap.tiles[anchor[0]][anchor[1]] = anchor_turn(last, new);

    for (int i = 0; i < distance; i++) {
        anchor[0]--;
        scene->tilemap.tiles[anchor[0]][anchor[1]] = 7;
    }
    set_last(last, new);
}
//==================================================================================================================================
void path_down(Scene *scene, int *anchor, int distance, char *last, char *new) {
    if (distance == 0){*new = 'S';}
    else{*new = 'D';} // S = Sideways, D = Down, U = Up

    scene->tilemap.tiles[anchor[0]][anchor[1]] = anchor_turn(last, new);

    for (int i = 0; i < distance; i++) { 
        anchor[0]++;
        scene->tilemap.tiles[anchor[0]][anchor[1]] = 7;
    }
    set_last(last, new);
}
//==================================================================================================================================
int anchor_turn(char *last, char *new) {
    int BendType;
    if (*last == 'S' && *new == 'R') { // S = Sideways, D = Down, U = Up
        BendType = 5;
    } else if (*last == 'S' && *new == 'U') {
        BendType = 9;
    } else if (*last == 'S' && *new == 'D') {
        BendType = 6;
    } else if (*last == 'D' && *new == 'S') {
        BendType = 8;
    } else if (*last == 'U' && *new == 'S') {
        BendType = 4;
    } else {
        BendType = 5;
    }
    return BendType;
}
//==================================================================================================================================
int save_waypoint(Scene *scene, int *anchor, int index) {
    float x = (anchor[1] * 16) + 8;
    float y = (anchor[0] * 16) + 8;
    scene->tilemap.waypoints[index].x = x;
    scene->tilemap.waypoints[index].y = y;
    printf("Index: %d ---- Waypoint: %f , %f\n",index,x,y);
    index++;
    return index;
}
//==================================================================================================================================
char set_last(char *last, char *new) {
    *last = *new;
    return *last;
}
