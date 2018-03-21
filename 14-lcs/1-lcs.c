/* AL2.2.1, Stanisław Juliusz Grams (251000 UG MFI), 20180320
 *
 * 1. USAGE
 *
 *   Compile with command `gcc -o 1-lcs 1-lcs.c
 *   `pkg-config --cflags glib-2.0 --libs glib-2.0`
 *
 *   Syntax: "./1-lcs"
 *
 *   Tested under kernel 4.15.7-1-ARCH and gcc 7.3.0
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

#define defaultStrBuffer 1001

gint lcs_length    (gchar *str1, gchar *str2, gint **c, gint **b);
void lcs_print     (gint **b, gchar *x, gint i, gint j);
void lcs_print_rec (gint **b, gchar *x, gint i, gint j);

gint main (void) {
  gint i, j, str1_len, str2_len;
  gint **b = NULL;
  gint **c = NULL;

  gchar *str1 = NULL, *str2 = NULL;
  gchar str_buf[defaultStrBuffer];

  /* Getting data from user */
  for (i=0; i<2; i++)
  {
    memset(str_buf, '\0', defaultStrBuffer*sizeof(gchar));
    scanf("%s", str_buf);
    if (!i) str1 = g_strdup(str_buf);
    else   str2 = g_strdup(str_buf);
  }

  str1_len = strlen(str1);
  str2_len = strlen(str2);
  
  /* Allocating memory for b and c tables */
  b = g_malloc0((str1_len+1)*sizeof(gint *));
  c = g_malloc0((str1_len+1)*sizeof(gint *));
  for (i=0; i<=str1_len; i++)
  {
    b[i] = g_malloc0((str2_len+1)*sizeof(gint));
    c[i] = g_malloc0((str2_len+1)*sizeof(gint));
  }

  lcs_length(str1, str2, c, b);
  lcs_print (b, str1, str1_len, str2_len);

  /* Freeing memory */
  g_free(str1);
  g_free(str2);

  for (i=0; i<=str1_len; i++)
  {
    g_free(b[i]);
    g_free(c[i]);
  }
  g_free(b);
  g_free(c);

  return 0;
}

gint lcs_length (gchar *str1, gchar *str2, gint **c, gint **b) {
  gint i, j;
  gint m = strlen(str1), n = strlen(str2);

  for (i=1; i<=m; i++)
  {
    c[i][0] = 0;
  }
  for (i=1; i<=n; i++)
  {
    c[0][i] = 0;
  }

  for (i=1; i<=m; i++)
  {
    for (j=1; j<=n; j++)
    {
      if (str1[i-1] == str2[j-1])
      {
        c[i][j] = c[i-1][j-1] + 1;
        b[i][j] = 1;
      }
      else if (c[i-1][j] >= c[i][j-1])
      {
        c[i][j] = c[i-1][j];
        b[i][j] = 2;
      }
      else {
        c[i][j] = c[i][j-1];
        b[i][j] = 0;
      }
    }
  }
  return c[m][n];
}

void lcs_print (gint **b, gchar *x, gint i, gint j) {
  lcs_print_rec (b, x, i, j);
  printf("\n");
}

void lcs_print_rec (gint **b, gchar *x, gint i, gint j) {
  if (!i || !j) return;
  if (b[i][j] == 1) {
    lcs_print_rec(b, x, i-1, j-1);
    printf("%c", x[i-1]);
  }
  else if (b[i][j] == 2)
    lcs_print_rec(b, x, i-1, j);
  else
    lcs_print_rec(b, x, i, j-1);
}
