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
    textures[13] = chargerTexture(renderer, "..\\images\\ESTF.bmp");
}

void afficherPlateau(SDL_Renderer *renderer, int plateau[NBR_LIGNES][NBR_COLONNES], SDL_Texture *textures[5],t_map map,int deca) {
    SDL_Rect position;
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

void libererTextures(SDL_Texture *textures[14]) {
    for (int i = 0; i < 14; i++) {
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

void afficher_ESTF(SDL_Renderer *renderer, SDL_Texture *Textures,t_map map) {
    SDL_Rect position = { .x = LARGEUR_BOUSSOLE + 67, .y = 0, .w = map.x_max * LARGEUR_CASE + LARGEUR_HISTORIQUE, .h = LARGEUR_BOUSSOLE + 67  };
    SDL_RenderCopy(renderer, Textures, NULL, &position);
}

// Fonction pour afficher un texte à un endroit spécifique
void afficherTexte(SDL_Renderer* renderer, TTF_Font* font, const char* texte, int x, int y) {
    // Créer une texture de texte à partir de la police et du texte
    SDL_Color couleur = {255, 255, 255, 255}; // Couleur  pour le texte
    SDL_Surface* surface = TTF_RenderText_Solid(font, texte, couleur);
    if (surface == NULL) {
        printf("Erreur lors de la création de la surface de texte: %s\n", TTF_GetError());
        return;
    }

    // Créer une texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Erreur lors de la création de la texture de texte: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // Définir la position de texte
    SDL_Rect dstRect = {x, y, surface->w, surface->h};

    // Rendre la texture (afficher le texte)
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    // Libérer les ressources
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}


void run_rover(int plateau[NBR_LIGNES][NBR_COLONNES], t_localisation marc, t_map map,n_node *tree,const char* complex[MAX_TIMERS]) {
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

    TTF_Font *font = TTF_OpenFont("..\\SDL2_ttf-2.22.0\\font\\arial.ttf", 14);  // Taille de police : 16
    if (!font) {
        printf("\nErreur de chargement de la police : %s\n", TTF_GetError());
        exit(1);
    }
    TTF_Font *font2 = TTF_OpenFont("..\\SDL2_ttf-2.22.0\\font\\arial.ttf", 12);  // Taille de police : 16
    if (!font2) {
        printf("\nErreur de chargement de la police : %s\n", TTF_GetError());
        exit(1);
    }

    // Charger les textures
    SDL_Texture *textures[14];
    initialiserTextures(renderer, textures);
    SDL_Texture *marcTexture = textures[5];
    SDL_Texture *errorTexture1 = textures[6];
    SDL_Texture *errorTexture2 = textures[7];
    SDL_Texture *welcomeTexture = textures[8];
    SDL_Texture* boussoleTextures[4] = {textures[9],textures[10],textures[11],textures[12]};
    SDL_Texture *ESTF = textures[13];

    // Variables pour le défilement
    int scrollX = 0, scrollY = 0;


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
                switch (event.key.keysym.sym) {
                    case SDLK_UP:    scrollY -= 20; break; // Défilement vers le haut
                    case SDLK_DOWN:  scrollY += 20; break; // Défilement vers le bas
                }
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (event.button.button == SDL_BUTTON_LEFT) { // Clic gauche
                        scrollY -= 20; // Défilement vers le haut
                    } else if (event.button.button == SDL_BUTTON_RIGHT) { // Clic droit
                        scrollY += 20; // Défilement vers le bas
                    }
                }

                if (event.key.keysym.sym == SDLK_o) {
                    marc = move(marc, 0);  //  MARC avance de 10 m
                }
                else if (event.key.keysym.sym == SDLK_d) {
                    marc = move(marc, 1);  //  MARC avance de 20 m
                }
                else if (event.key.keysym.sym == SDLK_t) {
                    marc = move(marc, 2);  //  MARC si la touche Espace est pressée avance de 30 m
                }
                else if (event.key.keysym.sym == SDLK_b) {
                    marc = move(marc, 3);  //  MARC recule de 10 m
                }
                else if (event.key.keysym.sym == SDLK_r) {
                    marc = move(marc, 4);  // MARC tourne à droite (-90°)
                }
                else if (event.key.keysym.sym == SDLK_l) {
                    marc = move(marc, 5);  // MARC tourne à gauche (+90°)
                }
                else if (event.key.keysym.sym == SDLK_u) {
                    marc = move(marc, 6);  // MARC tourne
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

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);  // Effacer l'écran avec une couleur grise
        SDL_RenderClear(renderer);


        afficherArbreStyleTreeScrollable(tree, renderer, font, 0, 134, 0, 0, scrollX, scrollY,0);
        afficherPlateau(renderer, plateau, textures, map,LARGEUR_HISTORIQUE);  // Afficher le plateau
        afficherMARC(renderer, marcTexture, marc);  // Afficher MARC
        afficherBoussole(renderer, boussoleTextures, marc.ori);
        afficher_ESTF(renderer, ESTF,map);

        const char* text = complex[0];
        afficherTexte(renderer, font2, text, 150, 110);
        const char* text1 = complex[1];
        afficherTexte(renderer, font2, text1, 150, 90);
        const char* text2 = complex[2];
        afficherTexte(renderer, font2, text2, 150, 70);

        SDL_RenderPresent(renderer);  // Mettre à jour l'écran

        SDL_Delay(100);  // Pause pour réduire la charge CPU
    }

    // Libérer les textures et quitter SDL
    libererTextures(textures);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_CloseFont(font2);
    TTF_Quit();
}

void drawText(SDL_Renderer* renderer, const char* text, int x, int y,TTF_Font *font) {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void afficherArbreStyleTreeScrollable(n_node* arbre,SDL_Renderer* renderer,TTF_Font* font,int x,int y,int niveau,int isLast,int scrollX,int scrollY,int depth)
{
    if (arbre == NULL || depth >= 5 || arbre->cost > 11111) {
        return;
    }

    // Calcul des coordonnées avec décalage de défilement
    int posX = x - scrollX;
    int posY = y - scrollY;


    // Indentation : préfixes pour chaque niveau
    char buffer[256] = "";
    for (int i = 0; i < niveau - 1; i++) {
        strcat(buffer, "|   ");
    }
    if (niveau > 0) {
        strcat(buffer, isLast ? "--" : "|- ");
    }

    // Ajoute le coût du nœud au texte
    char temp[128];
    sprintf(temp, "%sCout: %d", buffer, arbre->cost);
    strcat(buffer, temp);

    // Afficher le texte si visible dans la fenêtre
    if (posX >= 0 && posX <= 800 && posY >= 0 && posY <= 600) { // Ajustez les dimensions selon votre fenêtre
        drawText(renderer, buffer, posX, posY, font);

    }

    // Position des enfants (ajusté verticalement)
    int childY = y + 30; // Décalage vertical entre les lignes
    for (int i = 0; i < arbre->nbson; i++) {
        // Appel récursif pour afficher les enfants
        afficherArbreStyleTreeScrollable(
                arbre->son[i],
                renderer,
                font,
                x,               // Garder la position horizontale du parent
                childY,          // Décalage vertical
                niveau + 1,      // Augmenter la profondeur
                i == arbre->nbson - 1, // Indique si c'est le dernier enfant
                scrollX,
                scrollY,
                depth + 1
        );
        childY += 30; // Décalage pour le prochain enfant
    }
}
