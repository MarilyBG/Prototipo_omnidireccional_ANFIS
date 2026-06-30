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

void _ISR _INT0Interrupt(void);
void _ISR _INT1Interrupt(void);
void _ISR _INT2Interrupt(void);

void main(void)
{
    ADPCFG = 0X1FFF; //todo los pines digitales
    TRISB = 0;
    TRISD = 0;
    TRISF = 0;
    LATB = 0;
    LATD = 0;
    LATF = 0;
    while(1)
    {                                  
        LATBbits.LATB0=1;
        LATBbits.LATB10=1;
        LATBbits.LATB11=1;
        LATBbits.LATB12=1;
        LATBbits.LATB9=1;
        LATFbits.LATF2=1;
        LATFbits.LATF3=1;
        LATFbits.LATF4=1;
        LATFbits.LATF5=1;
        LATFbits.LATF6=1;
        LATDbits.LATD3=1;
        __delay_ms(500);
        LATBbits.LATB0=0;
        LATBbits.LATB10=0;
        LATBbits.LATB11=0;
        LATBbits.LATB12=0;
        LATBbits.LATB9=0;
        LATFbits.LATF2=0;
        LATFbits.LATF3=0;
        LATFbits.LATF4=0;
        LATFbits.LATF5=0;
        LATFbits.LATF6=0;
        LATDbits.LATD3=0;
        __delay_ms(500);
    }
    return;
}