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

#ifndef INTEGRATE_PWL
#define INTEGRATE_PWL
/*****************
 *  Integrate.h  *
 *****************/


/*=============================================================*
 *  Enthaelt alle Routinen, die im Wavelet-Galerkin-Verfahren  *
 *  fuer das aufsplitten der Integrale benoetigt werden.       *
 *=============================================================*/


void element_element_interaction_pwl(double *c, vector3 *P, element_pwl * E, unsigned int ind1, unsigned int ind2, randwerte *RW, cubature *Q, vector3 ****R, unsigned int M, double prec, double SL(), double DL(), double I);
/* Zerlegungsalgorithmus fuer die Integration Element ind1 mit Element ind2 */
#endif
/* warning-disabler-start */

#if (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
#pragma GCC diagnostic pop
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#pragma warning pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

/* warning-disabler-end */

