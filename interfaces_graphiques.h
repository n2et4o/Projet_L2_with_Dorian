//
// Created by 20220848 on 31/10/2024.
//


#ifndef UNTITLED1_INTERFACES_GRAPHIQUES_H
#define UNTITLED1_INTERFACES_GRAPHIQUES_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Code_fourni/map.h"
#include "Code_fourni/loc.h"
#include "Code_fourni/moves.h"
#define LARGEUR_CASE 67
#define HAUTEUR_CASE 67
#define NBR_COLONNES 6
#define NBR_LIGNES 7
#define LARGEUR_HISTORIQUE 200
#define HAUTEUR_HISTORIQUE 67
#define HAUTEUR_BOUSSOLE 67
#define LARGEUR_BOUSSOLE 67



SDL_Texture* chargerTexture(SDL_Renderer *renderer, const char *fichier);
void initialiserTextures(SDL_Renderer *renderer, SDL_Texture **textures);
void afficherPlateau(SDL_Renderer *renderer, int plateau[NBR_LIGNES][NBR_COLONNES], SDL_Texture *textures[5],t_map map,int deca);
void libererTextures(SDL_Texture *textures[5]);
void afficherMARC(SDL_Renderer *renderer, SDL_Texture *marcTexture, t_localisation marc);
void run_rover(int plateau[NBR_LIGNES][NBR_COLONNES],t_localisation marc,t_map map);

void afficherBoussole(SDL_Renderer *renderer, SDL_Texture *boussoleTextures[4], t_orientation ori);
void afficherHistorique(SDL_Renderer *renderer, TTF_Font *font, const char **mouvements[], int nbMouvements);

void size_map(t_map map);


#endif //UNTITLED1_INTERFACES_GRAPHIQUES_H

