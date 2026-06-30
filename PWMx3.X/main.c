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
    ADPCFG = 0X1FFF; //todo los pines digitales
    TRISDbits.TRISD0=0;//oc1
    TRISDbits.TRISD1=0;//oc2
    TRISDbits.TRISD2=0;//oc3
    LATBbits.LATB0=0;
    
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
}