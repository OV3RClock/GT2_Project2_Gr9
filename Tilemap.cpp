#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Tilemap.h"

using namespace sf;
using namespace std;

/*
Dans cet example, vous allez devoir charger et afficher un tileset
Vous devrez charger plusieurs sprites, de prfrences dans un vector<>.
Vous devrez utiliser la fonction Sprite::setTextureRect() qui prend un IntRect en argument.

Un IntRect est un struct POD (plain old data type) contenant une origine et une taille, en entier.

Cette fonction permet de n'afficher que une certaine région de texture dans votre Sprite.

Je vous ai fourni un niveau chargé, une std::map<string,string> 
et une std::map<string, Vector2i> préremplies, et une image qui permet de visualiser la disposition des tiles.

Votre travail consiste ecrire la fonction load_level(), qui doit:
* instancier les Sprite et appeler la fonction setTextureRect() sur chacun d'entre eux.
* positionner les Sprites
Les tiles font 16x16px, il faudra donc multiplier par 16 les offset fournis dans la map
Il sera ncessaire de charger deux grilles de tiles, la premire tant celle du sol, et l'autre des objets.
*/

map<string, Vector2i> tile_offsets = {
    { "convex_angle1", {0,0}},    //
    { "convex_angle2", {1,0}},    //

    { "convex_side1", {0,1}},     //
    { "convex_side2", {1,1}},     //

    { "convex_angle3", {0,2}},    //
    { "convex_angle4", {1,2}},    //


    { "forest_NW", {2,0}},        //
    { "forest_N", {3,0}},         //
    { "forest_NE", {4,0}},        //

    { "forest_W", {2,1}},         //
    { "forest_C", {3,1}},         //
    { "forest_E", {4,1}},         //

    { "forest_SW", {2,2}},        //
    { "forest_S", {3,2}},         //
    { "forest_SE", {4,2}},        //

    { "forest_S2", {0,5}},        //


    { "tree_big_1", {0,3}},       //
    { "tree_big_2", {1,3}},       //
    { "tree_big_3", {0,4}},       //
    { "tree_big_4", {1,4}},       //


    { "stump1", {2,3}},           //
    { "stump2", {2,4}},           //
    { "flowers", {3,3}},          //
    { "grass", {1,5}},            //

    { "ground", {4,6}},           //

    { "pool", {3,3}},  //
    { "river_corner_BL", {1,6}},  //
    { "river_corner_BR", {0,6}},  //

    { "river_corner_TR", {2,6}},  //
    { "river_corner_TL", {3,6}},  //

    { "river_vert", {2,5}},       //
    { "river_horiz", {3,5}},      //


    { "tree_base", {4,5}},        //
    { "tree_middle", {4,4}},      //
    { "tree_top", {4,3}},         //
    { "nothing", {0,7}}
};
map<string, string> aliasses = {

    { "A1", "convex_angle1" },
    { "A2", "convex_angle2" },

    { "S1", "convex_side1" },
    { "S2", "convex_side2" },

    { "A3", "convex_angle3" },
    { "A4", "convex_angle4" },


    { "F1", "forest_NW" },
    { "FN", "forest_N" },
    { "F2", "forest_NE" },

    { "FW", "forest_W" },
    { "FC", "forest_C" },
    { "FE", "forest_E" },

    { "F7", "forest_SW" },
    { "FS", "forest_S" },
    { "F4", "forest_SE" },

    { "FZ", "forest_S2" },


    { "T1", "tree_big_1" },
    { "T2", "tree_big_2" },
    { "T3", "tree_big_3" },
    { "T4", "tree_big_4" },


    { "d1", "stump1" },
    { "d2", "stump2" },
    { "FL", "flowers" },
    { "GS", "grass" },

    { "GD", "ground" },
    { "PL", "pool" },

    { "R2", "river_corner_BL" },
    { "R1", "river_corner_BR" },

    { "R3", "river_corner_TR" },
    { "R4", "river_corner_TL" },

    { "RH", "river_horiz" },
    { "RV", "river_vert" },


    { "tb", "tree_base" },
    { "tm", "tree_middle" },
    { "tt", "tree_top" },
    { "--", "nothing" },

};
vector<string> tile_strings = {
    "   GS GS                FW FC A2 -- "
    "      GS GS       tt    F7 FS S2 -- "
    "                  tb    tt    FW FC "
    "   T1 T2    FL          tm    F7 FS "
    "   T3 T4          GS    tb    F1 FN "
    "                     F1 FN FN A4 -- "
    "      R1 R2    F1 FN A4 -- -- -- -- "
    "R1 RH R4 R3 R2 FW -- -- -- -- -- -- "
};
vector<string> ground_strings = {
    "GD GD GD GD GD GD GD GD GD GD GD GD "
    "GD GD GD GD GD GD GD GD GD GD GD GD "
    "GD GD GD GD GD GD GD GD GD GD GD GD "
    "GD GD GD GD GD GD GD GD GD GD GD GD "
    "GD GD GD GD GD GD GD GD GD GD GD GD "
    "GD GD GD GD GD GD GD GD GD GD GD GD "
    "GD GD GD GD GD GD GD GD GD GD GD GD "
    "GD GD GD GD GD GD GD GD GD GD GD GD "
};

vector<Sprite> Tilemap::loadLevel(int dim, int scale, Texture &t)
{
    int j = 0;
    int k = 0;
    for (auto & str : tile_strings) 
    {
        for (int i = 0; i<str.length(); i+=3)
        {
            String sbstr = str.substr(i, 2);
            Sprite s = loadtile(dim, scale, sbstr, t);
            s.setPosition(dim*scale * k, dim*scale * j);
            Tiles.push_back(s);
            k += 1;
            if (k >= 12)
            {
                k = 0;
                j += 1;
            }
        }
    }
    return Tiles;
}

vector<Sprite> Tilemap::loadGround(int dim, int scale, Texture& t)
{
    int j = 0;
    int k = 0;
    for (auto& str : ground_strings)
    {
        for (int i = 0; i < str.length(); i += 3)
        {
            String sbstr = str.substr(i, 2);
            Sprite s = loadtile(dim, scale, sbstr, t);
            s.setPosition(dim*scale * k, dim*scale * j);
            Ground.push_back(s);
            k += 1;
            if (k >= 12)
            {
                k = 0;
                j += 1;
            }
        }
    }
    return Ground;
}

Sprite Tilemap::loadtile(int dim, int scale,  string s, Texture& t)
{
    Sprite sprite;
    if (s != "  ") 
    {
        Vector2i v = tile_offsets.find(aliasses.find(s)->second)->second;
        sf::IntRect rect(v*dim, { dim,dim });
        sprite.Sprite::setTextureRect(rect);
        sprite.setTexture(t);
        sprite.scale(scale, scale);
    }
    return sprite;
}



