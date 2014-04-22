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

#ifndef WEMPCG_PWL
#define WEMPCG_PWL
/**************
 *  WEMPCG_pwl.h  *
 **************/


/*=============================================================*
 *  WEMPCG_pwl(A,b,x,epsi,W,F,p,M)                                 *
 *	                                                       *
 *  Verfahren der konjugierten Gradienten zur Loesung des      *
 *  linearen Gleichungssystems                                 *
 *	                                                       *
 *	      A1*x = -(A2^(-1)/(epsilon-1)+I)*b.               *
 *	                                                       *
 *  Vorkonditionierung per Wavelet-Preconditioner.             *
 *	                                                       *
 *  Parameter :                                                *
 *		A    : Matrix im sparse2-Format                *
 *		G    : Massenmatrix                            *
 *		b    : rechte Seite                            *
 *		x    : Startwert und Endwert                   *
 *		epsi : Genauigkeit                             *
 *		W    : Liste der Wavelets                      *
 *		F    : Elementliste der Einskalenbasis         *
 *		p    : Zahl der Paramtergebiete                *
 *		M    : Zahl der Level                          *
 *=============================================================*/


unsigned int WEMPCG_pwl(sparse2 *A, double *b, double *x, double epsi, wavelet_pwl * W, unsigned int **F, unsigned int p, unsigned int M);
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

