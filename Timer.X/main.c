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

void __attribute__((interrupt, auto_psv)) _T1Interrupt( void );
void config_init(void);             //configuraciones de bits

int main(void) 
{
    config_init(); // Inicializar dsPIC
    LATBbits.LATB0=0;
    while (1) 
    {
    }
}
void config_init()
{
    ADPCFG = 0X1FFF; //todo los pines digitales
    TRISB = 0;
    LATB = 0;
    //Interrupciones
    IEC0bits.T1IE = 1;//Enable timer1
    IFS0bits.T1IF = 0;//Bandera int tim en 0
    //con fig Timer1
    T1CON = 0x0030; //Prescaler de 256
    T1CONbits.TCKPS = 0b11; //prescaler 256
    //TCY =1/30MHz = 3.33E-8
    TMR1 = 0;// 5ms
    PR1 = 2343;//registro maximo al que llega el TMR1
    T1CONbits.TON = 1;
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt( void )
{
    LATBbits.LATB0=~LATBbits.LATB0;
    TMR1 = 0;
    PR1 = 2343;
    IFS0bits.T1IF = 0;//Bandera int tim en 0
}