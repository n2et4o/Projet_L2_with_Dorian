//
// Created by 20220848 on 31/10/2024.
//


#include "interfaces_graphiques.h"


SDL_Texture* chargerTexture(SDL_Renderer *renderer, const char *fichier) {
    SDL_Surface* surface = SDL_LoadBMP(fichier);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);  // On peut libérer la surface une fois la texture créée
    return texture;
}

// Fonction d'initialisation des textures
void initialiserTextures(SDL_Renderer *renderer, SDL_Texture **textures) {
    textures[0] = chargerTexture(renderer, "..\\images\\plaine.bmp");
    textures[1] = chargerTexture(renderer, "..\\images\\erg.bmp");
    textures[2] = chargerTexture(renderer, "..\\images\\reg.bmp");
    textures[3] = chargerTexture(renderer, "..\\images\\crevasse.bmp");
    textures[4] = chargerTexture(renderer, "..\\images\\tour.bmp");
    textures[5] = chargerTexture(renderer, "..\\images\\marc.bmp");
    textures[6] = chargerTexture(renderer, "..\\images\\exit_crevasse.bmp");
    textures[7] = chargerTexture(renderer, "..\\images\\exit_map.bmp");
    textures[8] = chargerTexture(renderer, "..\\images\\run_rover.bmp");
    textures[9] = chargerTexture(renderer, "..\\images\\Nord.bmp");
    textures[10] = chargerTexture(renderer, "..\\images\\Est.bmp");
    textures[11] = chargerTexture(renderer, "..\\images\\Sud.bmp");
    textures[12] = chargerTexture(renderer, "..\\images\\Ouest.bmp");
}

void afficherPlateau(SDL_Renderer *renderer, int plateau[NBR_LIGNES][NBR_COLONNES], SDL_Texture *textures[5],t_map map,int deca) {
    SDL_Rect position;
    int lc = LARGEUR_CASE, hc = HAUTEUR_CASE;
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {

            position.x = deca + j * LARGEUR_CASE;
            position.y = (HAUTEUR_BOUSSOLE * 2) + i * HAUTEUR_CASE;
            position.w = LARGEUR_CASE;
            position.h = HAUTEUR_CASE;

            // Sélection de la texture en fonction de la valeur de la case
            int valeur = plateau[i][j];
            SDL_Texture* texture;
            if (valeur == 0) {
                texture = textures[4];  // Tour
            }
            else if (valeur == 1) {
                texture = textures[0]; // Plaine
            }
            else if (valeur == 2) {
                texture = textures[1];  // Erg
            }
            else if (valeur == 3) {
                texture = textures[2];  // Reg
            }
            else if (valeur == 4) {
                texture = textures[3];  // Crevasse
            }
            else{
                texture = textures[0]; // Plaine
            }
            // Affichage de la texture
            SDL_RenderCopy(renderer, texture, NULL, &position);
        }
    }
}

void libererTextures(SDL_Texture *textures[13]) {
    for (int i = 0; i < 13; i++) {
        if (textures[i]) {
            SDL_DestroyTexture(textures[i]);
        }
    }
}


void afficherMARC(SDL_Renderer *renderer, SDL_Texture *marcTexture, t_localisation marc) {
    SDL_Rect positionMARC;
    positionMARC.x = LARGEUR_HISTORIQUE + marc.pos.x * LARGEUR_CASE;
    positionMARC.y = (HAUTEUR_BOUSSOLE * 2) + marc.pos.y * HAUTEUR_CASE;
    positionMARC.w = LARGEUR_CASE;
    positionMARC.h = HAUTEUR_CASE;
    SDL_RenderCopy(renderer, marcTexture, NULL, &positionMARC);
}

void afficherBoussole(SDL_Renderer *renderer, SDL_Texture *boussoleTextures[4], t_orientation ori) {
    SDL_Rect position = { .x = 0, .y = 0, .w = LARGEUR_BOUSSOLE + 67, .h = 67 + HAUTEUR_BOUSSOLE };
    SDL_RenderCopy(renderer, boussoleTextures[ori], NULL, &position);
}

void afficherHistorique(SDL_Renderer *renderer, TTF_Font *font, const char ** mouvements [], int nbMouvements) {
    SDL_Color couleur = {255, 255, 255};  // Couleur du texte : blanc

    if (!font) {  // Vérifier que la police est chargée
        printf("Police non chargée\n");
        return;
    }

    for (int i = 0; i < nbMouvements; i++) {
        if (!mouvements[i]) {  // Vérifier que chaque élément de mouvements n'est pas NULL
            printf("Texte de mouvement NULL à l'index %d\n", i);
            continue;
        }

        SDL_Surface *surface = TTF_RenderText_Solid(font, &mouvements[i], couleur);
        printf("Texte de mouvement à l'index %d: %s\n", i, &mouvements[i]);
        if (!surface) {
            printf("Erreur de rendu de texte : %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);  // Libérer la surface après création de la texture

        if (!texture) {
            printf("Erreur de création de texture : %s\n", SDL_GetError());
            continue;
        }

        SDL_Rect position = { .x = 10, .y =  (2* HAUTEUR_BOUSSOLE) + i * 20, .w = surface->w, .h = surface->h };
        SDL_RenderCopy(renderer, texture, NULL, &position);
        SDL_DestroyTexture(texture);  // Libérer la texture après l'avoir utilisée
    }
}



void run_rover(int plateau[NBR_LIGNES][NBR_COLONNES], t_localisation marc, t_map map) {
    SDL_Init(SDL_INIT_EVERYTHING);

    // Initialisation de SDL_ttf
    if (TTF_Init() == -1) {
        printf("Erreur d'initialisation de SDL_ttf : %s\n", TTF_GetError());
        exit(1);  // Quitte le programme si SDL_ttf ne s'initialise pas
    }

    SDL_Window *window = SDL_CreateWindow("Run Rover",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          map.x_max * LARGEUR_CASE + LARGEUR_HISTORIQUE, // Inclure la largeur de l'historique
                                          map.y_max * HAUTEUR_CASE + HAUTEUR_BOUSSOLE + HAUTEUR_HISTORIQUE,   // Inclure la hauteur de la boussole
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("..\\SDL2_ttf-2.22.0\\font\\arial.ttf", 16);  // Taille de police : 16
    if (!font) {
        printf("\nErreur de chargement de la police : %s\n", TTF_GetError());
        exit(1);
    }


    // Charger les textures
    SDL_Texture *textures[13];
    initialiserTextures(renderer, textures);
    SDL_Texture *marcTexture = textures[5];
    SDL_Texture *errorTexture1 = textures[6];
    SDL_Texture *errorTexture2 = textures[7];
    SDL_Texture *welcomeTexture = textures[8];
    SDL_Texture* boussoleTextures[4] = {textures[9],textures[10],textures[11],textures[12]};

    int nbMouvements = 0;
    const char** mouvements[100][100];

    // Afficher l'image d'accueil
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, welcomeTexture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    int startGame = 0;
    int quitGame = 0;  // Flag pour détecter si l'utilisateur veut quitter le jeu

    // Boucle pour l'écran d'accueil
    while (!startGame && !quitGame) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitGame = 1;  // Détecte l'événement SDL_QUIT pour quitter le jeu
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    startGame = 1;  // Commencer le jeu lorsque Entrée est pressée
                }
            }
        }
        SDL_Delay(100);  // Petite pause pour éviter une charge CPU excessive
    }

    // Si l'utilisateur a cliqué sur "Quit", libérer les ressources et quitter SDL
    if (quitGame) {
        libererTextures(textures);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;  // Arrête la fonction ici pour éviter de lancer le reste du jeu
    }

    // Libérer la texture d'accueil
    SDL_DestroyTexture(welcomeTexture);

    // Logique principale du jeu
    int continuer = 1;

    while (continuer) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) continuer = 0;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    marc = move(marc, 2);  // Déplacer MARC si la touche Espace est pressée
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    marc = move(marc, 3);  // Déplacer MARC vers le bas
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    marc = move(marc, 4);  // Déplacer MARC vers la gauche
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                    marc = move(marc, 5);  // Déplacer MARC vers la droite
                }
            }
        }



        if (marc.pos.x < 0 || marc.pos.x >= map.x_max || marc.pos.y < 0 || marc.pos.y >= map.y_max) { // Sortie de la carte ou chute dans une crevasse
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, errorTexture2, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            break;
        }

        if (plateau[marc.pos.y][marc.pos.x] == 4) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, errorTexture1, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            break;
        }

        // Mettre à jour l'historique si MARC a bougé
        snprintf(mouvements[nbMouvements], 20, "Position : %d %d", marc.pos.x, marc.pos.y);
        nbMouvements++;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Effacer l'écran avec une couleur noire
        SDL_RenderClear(renderer);

        //(const char*)mouvements;

        afficherPlateau(renderer, plateau, textures, map,LARGEUR_HISTORIQUE);  // Afficher le plateau
        afficherMARC(renderer, marcTexture, marc);  // Afficher MARC
        afficherBoussole(renderer, boussoleTextures, marc.ori);
        afficherHistorique(renderer, font, mouvements, nbMouvements);


        SDL_RenderPresent(renderer);  // Mettre à jour l'écran

        SDL_Delay(100);  // Pause pour réduire la charge CPU
    }

    // Libérer les textures et quitter SDL
    libererTextures(textures);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
}