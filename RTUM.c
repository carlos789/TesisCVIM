#include <cvirte.h>		
#include <userint.h>
#include "RTUM.h"
#include <ansi_c.h>
#include <formatio.h>
#include <utility.h>
#include <rs232.h>
#pragma C99_extensions_on   
#include "ModbusFramework.h" 
static int panelHandle,panelHandleChild2, panelHandleChild3;
/*---------------------------------------------------------------------------*/
/* Internal function prototypes                                              */
/*---------------------------------------------------------------------------*/
void DisplayRS232Error (void);
unsigned int cal_crc16 (unsigned char*data,unsigned int length);

/*---------------------------------------------------------------------------*/
/* Registros y banderas                                                      */
/*---------------------------------------------------------------------------*/
 
int port_open=0; //Indica si hay un puerto serial abierto
int RS232Error,baudrate,comport, port_open,portindex;//Variables para  puerto serial
char devicename[30]="cerrado";//Indicacion estado puerto
char datoRS[8];// Vector 
char datoRX[55];
double espera=10;// Registro tiempo de espera comunicaciones del ModBus

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	
	if ((panelHandle= LoadPanel (0, "RTUM.uir", Principal)) < 0)
		return -1;
	Init_CRC ();//Genera las tablas para el CRC de Modbus
	DisplayPanel (panelHandle);
	//SetCtrlAttribute(panelHandle, Principal_PICTURE, ATTR_ZPLANE_POSITION, VAL_PANEL_BACK);

	RunUserInterface ();
	
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK SalirRS (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
	DiscardPanel (panelHandleChild2); 
			break;
	}
	return 0;
}

int CVICALLBACK SalirF (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		QuitUserInterface(0);  
			break;
	}
	return 0;
}

void CVICALLBACK AbrirSerie (int menuBar, int menuItem, void *callbackData,
							 int panel)
{
	if ((panelHandleChild2 = LoadPanel (0, "RTUM.uir", Serial)) < 0)
		return  ;
	
		InstallPopup (panelHandleChild2);
}

int CVICALLBACK AbrirPuerto (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int valor;    
			GetCtrlVal(panelHandleChild2 , Serial_COMPORT , &comport);
    		GetCtrlVal(panelHandleChild2, Serial_Velocidad, &baudrate);
			GetCtrlIndex(panelHandleChild2, Serial_COMPORT, &portindex);  
			GetLabelFromIndex(panelHandleChild2, Serial_COMPORT, portindex, devicename);
			GetCtrlVal (panelHandleChild2, Serial_WAIT ,  &espera); // Tiempo de espera de la repuesta del MODBUS    
			   port_open = 0;  /* Cierro Puerto */
			   SetCtrlVal (panelHandleChild2, Serial_LED , 0);
            //GetConfigParms ();
            DisableBreakOnLibraryErrors ();
            RS232Error = OpenComConfig (comport,devicename,baudrate,0,8,1,512,512);	
			// paridad par, 8 bits de datos 1 bit de stop 
			
			EnableBreakOnLibraryErrors ();
		 if (RS232Error)
		 {
			 DisplayRS232Error (); 
		 	 return 0;
		 }
			SetComTime(comport,1.0);  //Se cambia a 1  segundos
			 
			
            if (RS232Error == 0)
                {
            port_open = 1;
            SetCtrlVal (panelHandleChild2, Serial_LED , 1); 
			SetCtrlVal (panelHandleChild2, Serial_STRING , devicename);
               // EnablePanelControls (0); /* Enable: no errors */
			
			    }
            else
               // EnablePanelControls (1); /* Disable: errors found */
            DiscardPanel (panelHandleChild2);
			break;
	}
	return 0;
}

int CVICALLBACK CerrarPuerto (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 				port_open = 0;  /* Cierro Puerto */  
			   	SetCtrlVal (panelHandleChild2, Serial_LED ,0);  
			   	SetCtrlVal (panelHandleChild2, Serial_STRING ,  "Cerrado"); 
			   	CloseCom (comport); 
			break;
	}
	return 0;
}

//Significado de los datos: suma de comprobación CrC del marco de datos, utilizando 2 bytes.
//Checksum 
// calculo CRC:
unsigned int cal_crc16 (unsigned char*data,unsigned int length)
{
unsigned int i,crc_result = 0xffff;
while(length--)
{
crc_result^=*data++;
for(i=0;i<8;i++)
{
if(crc_result&0x01)
crc_result=(crc_result>>1)^0xa001;

else crc_result=crc_result>>1;

}
}
crc_result=((crc_result&0xff)<<8)|(crc_result>>8);
return(crc_result);
}


/*---------------------------------------------------------------------------*/
/* Display el error del puerto comunicaciones RS232                             */
/*---------------------------------------------------------------------------*/
void DisplayRS232Error (void)
{
    char ErrorMessage[200];
    switch (RS232Error)
        {
        default :
            if (RS232Error < 0)
                {  
                Fmt (ErrorMessage, "%s<RS232 error numero %i", RS232Error);
                MessagePopup ("Mensaje RS232 ", ErrorMessage);
                }
            break;
        case 0  :
            MessagePopup ("Mensaje RS232 ", "No hay errores.");
            break;
        case -2 :
            Fmt (ErrorMessage, "%s", "Invalido numero de puerto  (debe estar en el  "
                                     "rrango 1 a 8).");
            MessagePopup ("RS232 Message", ErrorMessage);
            break;
        case -3 :
            Fmt (ErrorMessage, "%s", "No hay puerto abierto.\n"
                 "Check COM Port setting in Configure.");
            MessagePopup ("Mensaje RS232 ", ErrorMessage);
            break;
			 case -6 :
            Fmt (ErrorMessage, "%s", "No encuentra un puerto serial.\n"
                 "Check COM Port setting in Configure.");
            MessagePopup ("Mensaje RS232 ", ErrorMessage);
            break;
			
        case -99 :
            Fmt (ErrorMessage, "%s", "Timeout error.\n\n"
                 "Either increase timeout value,\n"
                 "       check COM Port setting, or\n"
                 "       check device.");
            MessagePopup ("RS232 Message", ErrorMessage);
            break;
        }
}
 

int CVICALLBACK SalirDa (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		DiscardPanel (panelHandleChild3); //Salir del panel de Datos de Modbus
			break;
	}
	return 0;
}

int CVICALLBACK Abrir1 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		 	int valor; //es la salida del popup
			 if (port_open==0) 
			 {
				 MessagePopup (" Puerto de comunicaciones", "Falta seleccionar Puerto");
				 return 0; 
			 }
			// if (TimerOn()==0) return 0;  // es para evitar que se superponga con la pregunta periodica
			valor=ConfirmPopup ("Consulta de operación", "Realmente quiere abrir Las Lajas 2");
			if (valor==1)  //Si valor es =1 quiere hacer el comando
			{
			//Consultar1T(); 
			FlushInQ (comport); 
			FlushOutQ (comport); 
			Funcion05A(1,0x0,comport, espera );  // Esclavo 2 bobina 0x4004
			//Consultar1T();
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cerrar1 (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int valor; //es la salida del popup
			 if (port_open==0) 
			 {
				 MessagePopup (" Puerto de comunicaciones", "Falta seleccionar Puerto");
				 return 0; 
			 }
			// if (TimerOn()==0) return 0;  // es para evitar que se superponga con la pregunta periodica
			valor=ConfirmPopup ("Consulta de operación", "Realmente quiere abrir Las Lajas 2");
			if (valor==1)  //Si valor es =1 quiere hacer el comando
			{
			//Consultar1T(); 
			FlushInQ (comport); 
			FlushOutQ (comport); 
			Funcion05(1,0x0,comport, espera );  // Esclavo 2 bobina 0x4004
			//Consultar1T();
			}
			break;
	}
	return 0;
}

int CVICALLBACK Abrir2 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK Cerrar2 (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

void CVICALLBACK DatosM (int menuBar, int menuItem, void *callbackData,
						 int panel)
{
	if ((panelHandleChild3 = LoadPanel (0, "RTUM.uir", VerDatos)) < 0)
		return  ;
	
		InstallPopup (panelHandleChild3);
}

int CVICALLBACK LeerT (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			short	memAdr, nRegs, comerr = 0;    
			int		i, bSent, bRcvd, n;
			unsigned char	slave, buf[512];
			double Ti,Te;
			 if (port_open==0) 
			 {
				 MessagePopup (" Puerto de comunicaciones", "Falta seleccionar Puerto");
				 return 0; 
			 }
	 
			FlushInQ (comport); 
			comerr = QueryMem (slave, memAdr, nRegs, comport, espera);
			break;
	}
	return 0;
}
