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
unsigned int adc_val;

int main(void) 
{
    config_init(); // Inicializar dsPIC
    while (1) 
    {             
        ADCON1bits.SAMP=1;//iniciar muestreo
        __delay_ms(10);
        ADCON1bits.SAMP=0;//Finalizar muestreo
        while(!ADCON1bits.DONE);
        ADCON1bits.DONE=0;
        adc_val=ADCBUF0;//0-4095 12bits
        
       
        
        if(adc_val<3820)
        {
            LATDbits.LATD3=1;
        }
        else 
        {
           LATDbits.LATD3=0;
        }
    }
}
void config_init()
{
    TRISB = 0;
    //TRISDbits.TRISD0=0;//oc1
    //TRISDbits.TRISD1=0;//oc2
    //TRISDbits.TRISD2=0;//oc3
    TRISDbits.TRISD3=0;//out led
    //TRISAbits.TRISA11=1;//INT0
    //TRISDbits.TRISD8=1;//INT1
    //TRISDbits.TRISD9=1;//INT1
    TRISBbits.TRISB0=1;//AN0
    LATB = 0;
    LATD = 0;
    //ADC
    ADCON2bits.VCFG=0b000;//fuente de referencia Vdd y Vss
    ADPCFGbits.PCFG0 = 0b0; //pinea a trabajar como ADC AN0
    ADCHSbits.CH0NA=0; //negative input is VREF-
    ADCHSbits.CH0SA=0b000; //CHANEl AN0  01 1111
    ADCON3bits.ADCS=0b011111;//ADCS a 31 para un TAD de 533ns
    ADCON1bits.ASAM=0;//modo de muestreo manual
    ADCON1bits.SSRC=0b000;//Trigger Manual al limpiar SAMP bit
    ADCON1bits.ADON=1;//Habilitar el ADC
}