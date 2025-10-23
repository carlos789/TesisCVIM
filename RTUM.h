/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANELG                           1
#define  PANELG_COMMANDBUTTON             2       /* control type: command, callback function: SalirG */
#define  PANELG_LED                       3       /* control type: LED, callback function: (none) */
#define  PANELG_STRING                    4       /* control type: string, callback function: (none) */
#define  PANELG_STRIPCHART                5       /* control type: strip, callback function: (none) */

#define  Principal                        2
#define  Principal_COMMANDBUTTON_1        2       /* control type: command, callback function: SalirF */
#define  Principal_PICTURE                3       /* control type: picture, callback function: (none) */

#define  Serial                           3
#define  Serial_COMMANDBUTTON_1           2       /* control type: command, callback function: SalirRS */
#define  Serial_LED                       3       /* control type: LED, callback function: (none) */
#define  Serial_STRING                    4       /* control type: string, callback function: (none) */
#define  Serial_Velocidad                 5       /* control type: slide, callback function: (none) */
#define  Serial_COMPORT                   6       /* control type: slide, callback function: (none) */
#define  Serial_WAIT                      7       /* control type: numeric, callback function: (none) */
#define  Serial_COMMANDBUTTON_2           8       /* control type: command, callback function: AbrirPuerto */
#define  Serial_COMMANDBUTTON_3           9       /* control type: command, callback function: CerrarPuerto */
#define  Serial_PICTURE_2                 10      /* control type: picture, callback function: (none) */

#define  VerDatos                         4
#define  VerDatos_COMMANDBUTTON_1         2       /* control type: command, callback function: SalirDa */
#define  VerDatos_PICTURE_2               3       /* control type: picture, callback function: (none) */
#define  VerDatos_LED_4                   4       /* control type: LED, callback function: (none) */
#define  VerDatos_LED_5                   5       /* control type: LED, callback function: (none) */
#define  VerDatos_COMMANDBUTTON_7         6       /* control type: command, callback function: Cerrar2 */
#define  VerDatos_COMMANDBUTTON_8         7       /* control type: command, callback function: Abrir2 */
#define  VerDatos_LED_3                   8       /* control type: LED, callback function: (none) */
#define  VerDatos_LED_2                   9       /* control type: LED, callback function: (none) */
#define  VerDatos_COMMANDBUTTON_5         10      /* control type: command, callback function: Cerrar1 */
#define  VerDatos_COMMANDBUTTON_6         11      /* control type: command, callback function: Abrir1 */
#define  VerDatos_TEXTMSG                 12      /* control type: textMsg, callback function: (none) */
#define  VerDatos_NUMERICTHERM_2          13      /* control type: scale, callback function: (none) */
#define  VerDatos_NUMERICTHERM            14      /* control type: scale, callback function: (none) */
#define  VerDatos_TEXTMSG_2               15      /* control type: textMsg, callback function: (none) */
#define  VerDatos_COMMANDBUTTON_9         16      /* control type: command, callback function: ConfT */
#define  VerDatos_COMMANDBUTTON_11        17      /* control type: command, callback function: CrearArch */
#define  VerDatos_COMMANDBUTTON_10        18      /* control type: command, callback function: Arch */
#define  VerDatos_COMMANDBUTTON           19      /* control type: command, callback function: LeerT */
#define  VerDatos_TIMER                   20      /* control type: timer, callback function: Disparo */
#define  VerDatos_STRING                  21      /* control type: string, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1                    2       /* callback function: AbrirSerie */
#define  MENUBAR_MENU2                    3       /* callback function: DatosM */
#define  MENUBAR_MENU3                    4       /* callback function: Grafico */
#define  MENUBAR_Salir                    5       /* callback function: SalirM */


     /* Callback Prototypes: */

int  CVICALLBACK Abrir1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Abrir2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AbrirPuerto(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK AbrirSerie(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Arch(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cerrar1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cerrar2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CerrarPuerto(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ConfT(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CrearArch(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK DatosM(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Disparo(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Grafico(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK LeerT(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SalirDa(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SalirF(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SalirG(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK SalirM(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK SalirRS(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif