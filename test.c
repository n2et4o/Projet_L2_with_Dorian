//
// Created by 20220848 on 23/11/2024.
//


/*
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
*/

/*
        // Efface et dessine la fenêtre arbre
        SDL_SetRenderDrawColor(treeRenderer, 0, 0, 255, 255); // Fond bleu pour la nuit
        SDL_RenderClear(treeRenderer);
        afficherArbreSDL(tree, treeRenderer, arbreX, arbreY, 0, scrollX, scrollY, font);
        SDL_RenderPresent(treeRenderer);
*/

