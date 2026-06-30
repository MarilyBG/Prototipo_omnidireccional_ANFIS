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

// FINTERNA = 7.5 MHz 
// PLL X16 // 7.5*16= 120 MHz
// FCY = FOSC/4 = 30 MHz
// TCY = 3.33E-8

void config_init(void);             //configuraciones de bits
//UART
void UART1_Write(char data) ;
char UART1_Read(void);
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt( void );
//Interrupciones
void _ISR _INT0Interrupt(void);
void _ISR _INT1Interrupt(void);
void _ISR _INT2Interrupt(void);
//variables
char received;

int main(void) 
{
    config_init(); // Inicializar dsPIC
    LATBbits.LATB0=0;
    OC1RS=5000;
    OC2RS=2500;
    OC3RS=7500;
    while (1) 
    {
    }
}
void config_init()
{
    //I/O config
    ADPCFG = 0X1FFF; //todo los pines digitales
    TRISDbits.TRISD0=0;//oc1
    TRISDbits.TRISD1=0;//oc2
    TRISDbits.TRISD2=0;//oc3
    TRISAbits.TRISA11=1;//INT0
    TRISDbits.TRISD8=1;//INT1
    TRISDbits.TRISD9=1;//INT1
    TRISB = 0;
    LATB = 0;
    LATD = 0;
    //PWM
    PR2=9999;//TPWM=3.33E-4 --> 3 kHz
    TMR2=0;//CONTADOR A 0
    OC1R=0;//DUTY CYCLE INICIO 0 
    OC1RS=0; 
    OC1CONbits.OCM=0b110; //MODO PWM
    OC1CONbits.OCTSEL=0;//ELEGIR TIMER 2
    OC2R=0;//DUTY CYCLE INICIO 0 
    OC2RS=0; 
    OC2CONbits.OCM=0b110; //MODO PWM
    OC2CONbits.OCTSEL=0;//ELEGIR TIMER 2
    OC3R=0;//DUTY CYCLE INICIO 0 
    OC3RS=0; 
    OC3CONbits.OCM=0b110; //MODO PWM
    OC3CONbits.OCTSEL=0;//ELEGIR TIMER 2
    T2CONbits.T32=0;//MODO 16 bits mode
    T2CONbits.TCKPS=0b00;//PRESCALER 1:1
    T2CONbits.TCS=0; //ELEGIR FUENTE TCY
    T2CONbits.TON=1; //COMENZAR A CONTAR
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
    //interrupt 
    //UART
    IEC0bits.U1RXIE = 1;
    //interrupciones externas
    IFS0bits.INT0IF=0; //bandera de interrupcion
    IEC0bits.INT0IE=1; //Activa interrupcion
    INTCON2bits.INT0EP=0; //flanco positivo
    IFS1bits.INT1IF=0; //bandera de interrupcion
    IEC1bits.INT1IE=1; //Activa interrupcion
    INTCON2bits.INT1EP=0; //flanco positivo
    IFS1bits.INT2IF=0; //bandera de interrupcion
    IEC1bits.INT2IE=1; //Activa interrupcion
    INTCON2bits.INT2EP=0; //flanco positivo
}
void UART1_Write(char data) 
{
    while (U1STAbits.UTXBF); // Esperar hasta que el buffer de transmisión esté lleno
    U1TXREG = data;          // Enviar el dato
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
    UART1_Write(received);//received);        // Enviar de vuelta el mismo carácter (eco)
    __delay_ms(1);
    UART1_Write('\r');
    __delay_ms(1);
    UART1_Write('\n');
    __delay_ms(500);
    //..................................................
    if ( U1STAbits.OERR = 1 )
    {
        U1STAbits.OERR = 0;
    }
    IFS0bits.U1RXIF = 0;
}
void _ISR _INT0Interrupt(void)
{
    LATBbits.LATB0=1;
    __delay_ms(500);
    LATBbits.LATB0=0;
    IFS0bits.INT0IF=0; //bandera de interrupcion
}
void _ISR _INT1Interrupt(void)
{
    LATBbits.LATB0=1;
    __delay_ms(500);
    LATBbits.LATB0=0;
    IFS1bits.INT1IF=0; //bandera de interrupcion
}
void _ISR _INT2Interrupt(void)
{
    LATBbits.LATB0=1;
    __delay_ms(500);
    LATBbits.LATB0=0;
    IFS1bits.INT2IF=0; //bandera de interrupcion
}