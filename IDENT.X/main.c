// DSPIC30F4013 Configuration Bit Settings
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

#include <xc.h>
#define FCY 30000000UL //UL unsigned long
#include <libpic30.h> // necesita FCY= frecuencia de ciclos
#include <stdio.h>
#include <string.h>
#include <p30F4013.h>
// FINTERNA = 7.5 MHz 
// PLL X16 // 7.5*16= 120 MHz
// FCY = FOSC/4 = 30 MHz
 
void config(void);
//UART
void UART1_Write(char data);
void UART1_Write2(int cont);
void UART1_Write3(int cont);
void UART1_Write4(int cont);
char UART1_Read(void);
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt( void );
//interrup Velocidad
void _ISR _INT0Interrupt(void);
void _ISR _INT1Interrupt(void);
void _ISR _INT2Interrupt(void);
void __attribute__((interrupt, auto_psv)) _T1Interrupt( void );
void __attribute__((interrupt, auto_psv)) _T4Interrupt( void );
void __attribute__((interrupt, auto_psv)) _T5Interrupt( void );
//Motores 
void M1(unsigned int PWM,char rot);
void M2(unsigned int PWM,char rot);
void M3(unsigned int PWM,char rot);

//variables generales
unsigned int i=0;
//variables de velocidad
short statevel1=0,statevel2=0,statevel3=0;
unsigned int Vel1=0,Vel2=0,Vel3=0;
//Variables UART
char received, text[15];
//variables ADC
unsigned int adc_val;
short enable_ident=0;
void main(void)
{
    config();    
    OC1RS=0;
    OC2RS=0;
    OC3RS=0;
    /*
    M1(5000,'I');
    __delay_ms(500);
    M1(5000,'S');
    __delay_ms(500);
    M1(5000,'D');
    __delay_ms(500);
    M1(5000,'S');
    __delay_ms(500);
    M2(5000,'I');
    __delay_ms(500);
    M2(5000,'S');
    __delay_ms(500);
    M2(5000,'D');
    __delay_ms(500);
    M2(5000,'S');
    __delay_ms(500);
    M3(5000,'I');
    __delay_ms(500);
    M3(5000,'S');
    __delay_ms(500);
    M3(5000,'D');
    __delay_ms(500);
    M3(5000,'S');
    __delay_ms(500);
    */
    M1(0,'I');
    M2(0,'S');
    M3(0,'S');
    while(1)
    {   
        //.......................................................................................
        //LATDbits.LATD3=1;
        if(enable_ident==1)
        {
            M3(10000,'I');
            UART1_Write2((4687500/Vel3));
            __delay_ms(15);
        }
        else
        {
            M3(0,'S');
            UART1_Write2((0));
            __delay_ms(15);
        }
        
        //UART1_Write2((4687500/Vel1));
        //UART1_Write3((4687500/Vel2));
        //UART1_Write4((4687500/Vel3));
        //LATDbits.LATD3=0;
        //__delay_ms(500)
                
        /*
        ADCON1bits.SAMP=1;//iniciar muestreo
        __delay_ms(10);
        ADCON1bits.SAMP=0;//Finalizar muestreo
        while(!ADCON1bits.DONE);
        ADCON1bits.DONE=0;
        adc_val=ADCBUF0;//0-4095 12bits
        
        if(adc_val<3900)
        {
            LATDbits.LATD3=1;
        }
        else 
        {
            LATDbits.LATD3=0;
        }
        */        
    }
    return;
}
void _ISR _INT0Interrupt(void)
{
    if(statevel3 == 0)
    {
        //iniciar timer
        TMR1 = 0;
        PR1 = 65535;
        statevel3=1;
    }
    else if(statevel3 == 1)
    {
        Vel3=TMR1;
        //print velocidad    
        statevel3=0;
    }
    IFS0bits.INT0IF=0; //bandera de interrupcion
}
void _ISR _INT1Interrupt(void)
{
    if(statevel1 == 0)
    {
        //iniciar timer
        TMR4 = 0;
        PR4 = 65535;
        statevel1=1;
    }
    else if(statevel1 == 1)
    {
        Vel1=TMR4;
        //print velocidad    
        statevel1=0;
    }
    IFS1bits.INT1IF=0; //bandera de interrupcion  
}
void _ISR _INT2Interrupt(void)
{
    if(statevel2 == 0)
    {
        //iniciar timer
        TMR5 = 0;
        PR5 = 65535;
        statevel2=1;
    }
    else if(statevel2 == 1)
    {
        Vel2=TMR5;
        //print velocidad    
        statevel2=0;
    }
    IFS1bits.INT2IF=0; //bandera de interrupcion  
}
void __attribute__((interrupt, auto_psv)) _T1Interrupt( void )
{
    TMR1 = 0;
    PR1 = 65535;
    IFS0bits.T1IF = 0;//Bandera int tim en 0
}
void __attribute__((interrupt, auto_psv)) _T4Interrupt( void )
{
    TMR4 = 0;
    PR4 = 65535;
    IFS1bits.T4IF = 0;//Bandera int tim en 0
}
void __attribute__((interrupt, auto_psv)) _T5Interrupt( void )
{
    TMR5 = 0;
    PR5 = 65535;
    IFS1bits.T5IF = 0;//Bandera int tim en 0
}
void UART1_Write(char data) 
{
    while (U1STAbits.UTXBF); // Esperar hasta que el buffer de transmisión esté lleno
    U1TXREG = data;          // Enviar el dato
}
void UART1_Write2(int cont) 
{
    //sprintf(text,"cont1= %u \n",cont);
    if(cont!=0)
    {
        sprintf(text,"%u,10000\n",cont);
    }
    else
    {
        sprintf(text,"%u,0\n",cont);
    }
    for(i=0;i<=strlen(text);i++)       //sterlen agraga caracteres para completar 
    {
        while (U1STAbits.UTXBF); // Esperar hasta que el buffer de transmisión esté lleno
        U1TXREG = text[i];          // Enviar el dato
        __delay_us(50);
    }
    
}
void UART1_Write3(int cont) 
{
    sprintf(text,"cont2= %u \n",cont);
    for(i=0;i<=strlen(text);i++)       //sterlen agraga caracteres para completar 
    {
        while (U1STAbits.UTXBF); // Esperar hasta que el buffer de transmisión esté lleno
        U1TXREG = text[i];          // Enviar el dato
        __delay_us(50);
    }
    
}
void UART1_Write4(int cont) 
{
    sprintf(text,"cont3= %u \n",cont);
    for(i=0;i<=strlen(text);i++)       //sterlen agraga caracteres para completar 
    {
        while (U1STAbits.UTXBF); // Esperar hasta que el buffer de transmisión esté lleno
        U1TXREG = text[i];          // Enviar el dato
        __delay_us(50);
    }
    
}
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt( void )               
{
    received = U1RXREG;
    if( received=='A')
    {
        enable_ident=1;
    }
    else if( received=='B')
    {
        enable_ident=0;
    }
    if ( U1STAbits.OERR = 1 )
    {
        U1STAbits.OERR = 0;
    }
    IFS0bits.U1RXIF = 0;
} 
void M1(unsigned int PWM,char rot)
{
    OC1RS=PWM;//10000 ->100%
    if(rot=='I')
    {
        LATBbits.LATB12=0;//EM1B
        LATBbits.LATB11=1;//EM1A
    }
    else if(rot=='D')
    {
        LATBbits.LATB11=0;//EM1B
        LATBbits.LATB12=1;//EM1A
    }
    else
    {
        LATBbits.LATB11=0;//EM1A
        LATBbits.LATB12=0;//EM1B
    }    
    
}
void M2(unsigned int PWM,char rot)
{
    OC2RS=PWM;//10000 ->100%
    if(rot=='I')
    {
        LATBbits.LATB9=0;//EM2B
        LATBbits.LATB10=1;//EM2A
    }
    else if(rot=='D')
    {
        LATBbits.LATB10=0;//EM2B
        LATBbits.LATB9=1;//EM2A
    }
    else
    {
        LATBbits.LATB9=0;//EM2A
        LATBbits.LATB10=0;//EM2B
    }    
}
void M3(unsigned int PWM,char rot)
{
    OC3RS=PWM;//10000 ->100%
    if(rot=='I')
    {
        LATFbits.LATF5=0;//EM3B
        LATFbits.LATF4=1;//EM3A
    }
    else if(rot=='D')
    {
        LATFbits.LATF4=0;//EM3B
        LATFbits.LATF5=1;//EM3A
    }
    else
    {
        LATFbits.LATF4=0;//EM3A
        LATFbits.LATF5=0;//EM3B
    }    
}
void config(void)
{
    //Config I/O
    ADPCFG = 0X1FFE; //pinea a trabajar como ADC AN0
    TRISB = 0;
    TRISD = 0;
    LATB = 0;
    LATD = 0;
    TRISAbits.TRISA11=1;//INT0
    TRISDbits.TRISD8=1;//INT1
    TRISDbits.TRISD9=1;//INT2
    TRISDbits.TRISD0=0;//oc1
    TRISDbits.TRISD1=0;//oc2
    TRISDbits.TRISD2=0;//oc3
    TRISBbits.TRISB0=1;//AN0
    TRISBbits.TRISB9=0;//EM1A
    TRISBbits.TRISB10=0;//EM1B
    TRISBbits.TRISB11=0;//EM2A
    TRISBbits.TRISB12=0;//EM2B
    TRISFbits.TRISF4=0;//EM3A
    TRISFbits.TRISF5=0;//EM3B
    LATB = 0;
    LATD = 0;
    LATF = 0;
    __delay_ms(500);
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
    IEC1bits.T4IE = 1;//Enable timer4
    IFS1bits.T4IF = 0;//Bandera int tim en 0
    IEC1bits.T5IE = 1;//Enable timer5
    IFS1bits.T5IF = 0;//Bandera int tim en 0
    //connfig Timer1
    T1CON = 0x0020; //Prescaler de 64
    T1CONbits.TCKPS = 0b10; //prescaler 64
    //TCY =1/30MHz = 3.33E-8
    TMR1 = 0;// 5ms
    PR1 = 0;//registro maximo al que llega el TMR1
    T1CONbits.TON = 1;
    //connfig Timer4
    T4CON=0x0020; 
    T4CONbits.T32=0; //trabajar a 16 bits
    T4CONbits.TCKPS = 0b10;//prescaler 64
    TMR4=0;
    PR4 = 0;//registro maximo al que llega el TMR4
    T4CONbits.TON = 1;
    
    //connfig Timer5
    T5CON=0x0020; 
    T5CONbits.TCKPS = 0b10;//prescaler 64
    TMR5=0;
    PR5 = 0;//registro maximo al que llega el TMR4
    T5CONbits.TON = 1;
    
    
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
    
    //ADC
    ADCON2bits.VCFG=0b000;//fuente de referencia Vdd y Vss
    ADCHSbits.CH0NA=0; //negative input is VREF-
    ADCHSbits.CH0SA=0; //CHANEl AN0  01 1111
    ADCON3bits.ADCS=0b011111;//ADCS a 31 para un TAD de 533ns
    ADCON1bits.ASAM=0;//modo de muestreo manual
    ADCON1bits.SSRC=0b000;//Trigger Manual al limpiar SAMP bit
    ADCON1bits.ADON=1;//Habilitar el ADC
}