#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 3840
#define HEIGHT 2160
#define TAM (WIDTH * HEIGHT)

typedef unsigned char uchar;

void rainbow(int x, int y, uchar* r, uchar* g, uchar* b) {
    // Usa a posição horizontal para criar o gradiente
    double t = (double)x / WIDTH;
    
    // Ajusta as fases para criar cores do arco-íris
    *r = (uchar)(127.5 * (sin(2 * M_PI * t + 0) + 1));
    *g = (uchar)(127.5 * (sin(2 * M_PI * t + 2 * M_PI / 3) + 1));
    *b = (uchar)(127.5 * (sin(2 * M_PI * t + 4 * M_PI / 3) + 1));
}

struct pixel {
    uchar r;
    uchar g;
    uchar b;
};
typedef struct pixel pixel;

int main() {
    FILE* arq;
    pixel* imagem;
    imagem = (pixel*)malloc(TAM * sizeof(pixel));
    
    if (imagem == NULL) {
        printf("Error allocating memory!\n");
        return 1;
    }

    // Gera a imagem com gradiente horizontal
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int i = y * WIDTH + x;
            rainbow(x, y, &(imagem[i].r), &(imagem[i].g), &(imagem[i].b));
        }
    }

    // Abre arquivo para escrita
    arq = fopen("Rainbow.ppm", "wb");
    if (arq == NULL) {
        printf("Error opening file!\n");
        free(imagem);
        return 1;
    }

    // Escreve cabeçalho PPM
    fprintf(arq, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    
    // Escreve dados dos pixels
    fwrite(imagem, sizeof(pixel), TAM, arq);

    fclose(arq);
    free(imagem);
    
    printf("Rainbow image created successfully!\n");
    return 0;
}