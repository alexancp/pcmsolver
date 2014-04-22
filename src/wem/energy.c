/* warning-disabler-start */

#if (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wextra"
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#pragma warning push
#pragma warning disable "-Wall"
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wall"
#pragma clang diagnostic ignored "-Weffc++"
#pragma clang diagnostic ignored "-Wextra"
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wdeprecated-register"
#pragma clang diagnostic ignored "-Wincompatible-pointer-types"
#pragma clang diagnostic ignored "-Wempty-body"
#endif

/* warning-disabler-end */

/**************
 *  Energy.c  *
 **************/


/*=====================================*
 * Berechnet die potentielle Energie.  *
 *=====================================*/


#include <math.h>
#include <stdio.h>
#include "vector2.h"
#include "vector3.h"
#include "molecule.h"
#include "cubature.h"
#include "interpolate.h"
#include "gauss_square.h"
#include "energy.h"
#include "kern.h"


#if !defined pi
#define pi 3.1415926535897932385
#endif


double energy_orig(u, F, T, p, m)
double *u;                      /* vorgegebene Dichte                          */
unsigned int **F;               /* Patchliste                                  */
vector3 ****T;                  /* Koeffizienten zur Oberflaecheninterpolation */
unsigned int p;                 /* Anzahl der Parametergebiete                 */
unsigned int m;                 /* Zahl der Level                              */
{
    unsigned int n = 1 << m;    /* n*n Patches pro Parametergebiet             */
    unsigned int i1, i2, i3;    /* Laufindizes fuer Ansatzfunktion             */
    unsigned int zi = 0;        /* Zeilenindex hieraus: zi = i1*(n*n)+i2*n+i3  */
    cubature *Q;                /* Kubatur-Formeln                             */
    unsigned int g = 1;         /* Quadraturgrad                               */
    unsigned int l;             /* Laufindex fuer Quadratur                    */
    vector2 s;                  /* Linker, unterer Eckpunkt des Patches zi     */
    vector2 t;                  /* Auswertepunkte der Gaussquadratur           */
    double E = 0;               /* Energie                                     */
    double h = 1. / n;          /* Schrittweite                                */
    double C = 0;               /* surface meassure                            */

/* Initialisierung */
    init_Gauss_Square(&Q, g + 1);       /* Kubatur-Formeln */

/* Berechnung des Fehlers */
    for (i1 = 0; i1 < p; i1++) {
        s.y = 0;
        for (i2 = 0; i2 < n; i2++) {
            s.x = 0;
            for (i3 = 0; i3 < n; i3++) {        /* zeilenweise Durchnumerierung der Patches zi = (i1,i2,i3) */
                for (l = 0; l < Q[g].nop; l++) {
                    t = vector2_add(s, vector2_Smul(h, Q[g].xi[l]));
                    E += Q[g].w[l] * u[zi] * potmol(Chi(t, T[i1], m));
                    C += Q[g].w[l] * u[zi];
                }
                s.x += h;
                zi++;
            }
            s.y += h;
        }
    }
    E = -0.5 * h * E;           /* correct scaling */

/* Datenausgabe */
//    printf("    Computed energy:            %f10\n", E);
//    printf("    Computed charge:            %f10\n", C*h);
    free_Gauss_Square(&Q, g + 1);
    return (E);
}

double energy_ext(u, potential, F, T, p, m)
double *u;                      /* vorgegebene Dichte                          */
double *potential;              /* electrostatic potential                     */
unsigned int **F;               /* Patchliste                                  */
vector3 ****T;                  /* Koeffizienten zur Oberflaecheninterpolation */
unsigned int p;                 /* Anzahl der Parametergebiete                 */
unsigned int m;                 /* Zahl der Level                              */
{
    unsigned int n = 1 << m;    /* n*n Patches pro Parametergebiet             */
    unsigned int i1, i2, i3;    /* Laufindizes fuer Ansatzfunktion             */
    unsigned int zi = 0;        /* Zeilenindex hieraus: zi = i1*(n*n)+i2*n+i3  */
    cubature *Q;                /* Kubatur-Formeln                             */
    unsigned int g = 1;         /* Quadraturgrad                               */
    unsigned int l;             /* Laufindex fuer Quadratur                    */
    vector2 s;                  /* Linker, unterer Eckpunkt des Patches zi     */
    vector2 t;                  /* Auswertepunkte der Gaussquadratur           */
    double E = 0;               /* Energie                                     */
    double h = 1. / n;          /* Schrittweite                                */

/* Initialisierung */
    init_Gauss_Square(&Q, g + 1);       /* Kubatur-Formeln */

/* Berechnung des Fehlers */
    for (i1 = 0; i1 < p; i1++) {
        s.y = 0;
        for (i2 = 0; i2 < n; i2++) {
            s.x = 0;
            for (i3 = 0; i3 < n; i3++) {        /* zeilenweise Durchnumerierung der Patches zi = (i1,i2,i3) */
                for (l = 0; l < Q[g].nop; l++) {
                    t = vector2_add(s, vector2_Smul(h, Q[g].xi[l]));
                    E += Q[g].w[l] * u[zi] * potential[Q[g].nop*zi+l];
                }
                s.x += h;
                zi++;
            }
            s.y += h;
        }
    }
    E = -0.5 * h * E;           /* correct scaling */

/* Datenausgabe */
//    printf("PWC Computed energy:            %f10\n", E);
    free_Gauss_Square(&Q, g + 1);
    return (E);
}

double charge_ext(u, charge, F, T, p, m)
double *u;                      /* vorgegebene Dichte                          */
double *charge;                 /* charge output chte                          */
unsigned int **F;               /* Patchliste                                  */
vector3 ****T;                  /* Koeffizienten zur Oberflaecheninterpolation */
unsigned int p;                 /* Anzahl der Parametergebiete                 */
unsigned int m;                 /* Zahl der Level                              */
{
    unsigned int n = 1 << m;    /* n*n Patches pro Parametergebiet             */
    unsigned int i1, i2, i3;    /* Laufindizes fuer Ansatzfunktion             */
    unsigned int zi = 0;        /* Zeilenindex hieraus: zi = i1*(n*n)+i2*n+i3  */
    cubature *Q;                /* Kubatur-Formeln                             */
    unsigned int g = 1;         /* Quadraturgrad                               */
    unsigned int l;             /* Laufindex fuer Quadratur                    */
    vector2 s;                  /* Linker, unterer Eckpunkt des Patches zi     */
    vector2 t;                  /* Auswertepunkte der Gaussquadratur           */
    double h = 1. / n;          /* Schrittweite                                */
    double C = 0;               /* surface meassure                            */

/* Initialisierung */
    init_Gauss_Square(&Q, g + 1);       /* Kubatur-Formeln */

/* Berechnung des Fehlers */
    for (i1 = 0; i1 < p; i1++) {
        s.y = 0;
        for (i2 = 0; i2 < n; i2++) {
            s.x = 0;
            for (i3 = 0; i3 < n; i3++) {        /* zeilenweise Durchnumerierung der Patches zi = (i1,i2,i3) */
                for (l = 0; l < Q[g].nop; l++) {
                    t = vector2_add(s, vector2_Smul(h, Q[g].xi[l]));
                    int index = Q[g].nop*zi+l;
                    charge[index] = Q[g].w[l] * u[zi] * h;
                    C += charge[index];
                }
                s.x += h;
                zi++;
            }
            s.y += h;
        }
    }

/* Datenausgabe */
//    printf("PWC Computed charge:            %f10\n", C);
    free_Gauss_Square(&Q, g + 1);
    return (C);
}
/* warning-disabler-start */

#if (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
#pragma GCC diagnostic pop
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#pragma warning pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

/* warning-disabler-end */

