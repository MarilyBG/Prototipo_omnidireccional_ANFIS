// DSPIC30F4013 Configuration Bit Settings
// 'C' source line config statements
// FOSC
#pragma config FOSFPR = FRC_PLL16       // Oscillator (FRC w/PLL 16x)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV42          // Brown Out Voltage (4.2V)
#pragma config BOREN = PBOR_OFF          // PBOR Enable (Enabled)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define FCY 30000000UL //UL unsigned long
#include <libpic30.h> // necesita FCY= frecuencia de ciclos
#include <stdio.h>
#include <string.h>
// FINTERNA = 7.5 MHz 
// PLL X16 // 7.5*16= 120 MHz
// FCY = FOSC/4 = 30 MHz

//UART
void UART1_Write(char data);
void UART1_Write2(int cont);
char UART1_Read(void);
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt( void );
//interrup
void _ISR _INT0Interrupt(void);
void _ISR _INT1Interrupt(void);
void _ISR _INT2Interrupt(void);
void __attribute__((interrupt, auto_psv)) _T1Interrupt( void );

short statevel1 = 0;
unsigned int Vel1=0,i=0;
char received, text[15];

void main(void)
{
    ADPCFG = 0X1FFF; //todo los pines digitales
    TRISAbits.TRISA11=1;
    TRISB = 0;
    TRISD = 0;
    LATB = 0;
    LATD = 0;
    // Configuración de UART1
    U1MODEbits.UARTEN = 1; //UART disabled
    U1MODEbits.USIDL = 0; //Run UART on IDLE mode
    U1MODEbits.ALTIO = 0; //Alternate pin is enabled
    U1MODEbits.WAKE = 0; //Wakeup is disabled
    U1MODEbits.LPBACK = 0; //Loopback mode is disabled
    U1MODEbits.ABAUD = 0; //U1RX to Capture
    U1MODEbits.PDSEL = 0; //No parity 8-bit
    U1MODEbits.STSEL = 0; //1STOP bit
    U1STAbits.UTXISEL = 1; //When buffer is empty
    U1STAbits.UTXBRK = 0; //Transfer break is normal mode
    U1STAbits.URXISEL = 0b00; //When accepting any character, interrupt is occured
    U1STAbits.ADDEN = 0; //Address detector is disabled
    U1STAbits.OERR = 0; //Not Overrun (First write only)
    U1BRG = 32; //(FCY / 16 / 57600) - 1; // Configura la velocidad a 57600 bps
    U1MODEbits.UARTEN = 1; // Habilitar UART
    U1STAbits.UTXEN = 1;   // Habilitar el transmisor
    //interrupt UART
    IEC0bits.U1RXIE = 1;
    //interrupciones
    IFS0bits.INT0IF=0; //bandera de interrupcion
    IEC0bits.INT0IE=1; //Activa interrupcion
    INTCON2bits.INT0EP=0; //flanco positivo
    IFS1bits.INT1IF=0; //bandera de interrupcion
    IEC1bits.INT1IE=1; //Activa interrupcion
    INTCON2bits.INT1EP=0; //flanco positivo
    IFS1bits.INT2IF=0; //bandera de interrupcion
    IEC1bits.INT2IE=1; //Activa interrupcion
    INTCON2bits.INT2EP=0; //flanco positivo
    //Interrupciones timer
    IEC0bits.T1IE = 1;//Enable timer1
    IFS0bits.T1IF = 0;//Bandera int tim en 0
    //connfig Timer1
    T1CON = 0x0010; //Prescaler de 256
    T1CONbits.TCKPS = 0b10; //prescaler 64
    //TCY =1/30MHz = 3.33E-8
    TMR1 = 0;// 5ms
    PR1 = 0;//registro maximo al que llega el TMR1
    T1CONbits.TON = 1;
    
    
    while(1)
    {                                  
        UART1_Write2((4687500/Vel1));
        __delay_ms(500)
    }
    return;
}

void _ISR _INT0Interrupt(void)
{
    if(statevel1 == 0)
    {
        //iniciar timer
        TMR1 = 0;
        PR1 = 65535;
        LATBbits.LATB0=1;
        statevel1=1;
    }
    else if(statevel1 == 1)
    {
        Vel1=TMR1;
        //print velocidad    
        LATBbits.LATB0=0;
        statevel1=0;
    }
    IFS0bits.INT0IF=0; //bandera de interrupcion
}
void _ISR _INT1Interrupt(void)
{
}
void _ISR _INT2Interrupt(void)
{
}
void __attribute__((interrupt, auto_psv)) _T1Interrupt( void )
{
    //LATBbits.LATB0=~LATBbits.LATB0;
    TMR1 = 0;
    PR1 = 65535;
    IFS0bits.T1IF = 0;//Bandera int tim en 0
}
void UART1_Write(char data) 
{
    while (U1STAbits.UTXBF); // Esperar hasta que el buffer de transmisión esté lleno
    U1TXREG = data;          // Enviar el dato
}
void UART1_Write2(int cont) 
{
    sprintf(text,"cont = %u \n",cont);
    for(i=0;i<=strlen(text);i++)       //sterlen agraga caracteres para completar 
    {
        while (U1STAbits.UTXBF); // Esperar hasta que el buffer de transmisión esté lleno
        U1TXREG = text[i];          // Enviar el dato
    }
    
}
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt( void )               
{
    received = U1RXREG;
    if(received=='A')
    {
        LATBbits.LATB0=1;
    }
    if(received=='B')
    {
        LATBbits.LATB0=0;
    }   
    if ( U1STAbits.OERR = 1 )
    {
        U1STAbits.OERR = 0;
    }
    IFS0bits.U1RXIF = 0;
}