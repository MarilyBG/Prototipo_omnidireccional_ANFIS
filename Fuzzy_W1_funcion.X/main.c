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
#include <stdlib.h>
#include <p30F4013.h>

//#define MAXBUFFER 64

// FINTERNA = 7.5 MHz 
// PLL X16 // 7.5*16= 120 MHz
// FCY = FOSC/4 = 30 MHz

void config(void);
//UART
void UART1_Write(char data);
void UART1_Write2(int cont);
void UART1_Write3(int v1,int v2,int v3,int sp1,int sp2,int sp3) ;
void UART1_Write4(signed int cont);
char UART1_Read(void);
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt( void );
//interrup Velocidad
void _ISR _INT0Interrupt(void);
void _ISR _INT1Interrupt(void);
void _ISR _INT2Interrupt(void);
void __attribute__((interrupt, auto_psv)) _T1Interrupt( void );
void __attribute__((interrupt, auto_psv)) _T4Interrupt( void );
void __attribute__((interrupt, auto_psv)) _T5Interrupt( void );
//Filtro EMA Velocidad
void EMAV(int sp1,int sp2,int sp3);
//Motores 
void M1(unsigned int PWM,char rot);
void M2(unsigned int PWM,char rot);
void M3(unsigned int PWM,char rot);
//PID
void Init_PID(void);
void PID1(unsigned int sp,char rot);
void PID2(unsigned int sp,char rot);
void PID3(unsigned int sp,char rot);
//cinematica
void CD(void);
void CI(void);
//logica difusa
float fuzzy(double X,double A,double B,double C);//fuzificacion
float W1_fuzzy(float Vx_,float Vy_,float Wp_);//Calculo de W1 por logica difuzza

//variables generales
unsigned int i=0;
//variables de velocidad
short statevel1=0,statevel2=0,statevel3=0;
unsigned int Vel1=0,Vel2=0,Vel3=0;
//variables EMA velocidad
unsigned int Vel1EMA=0,Vel1EMA_1=0,Vel2EMA=0,Vel2EMA_1=0,Vel3EMA=0,Vel3EMA_1=0;
//Variables UART
char received, text[30];//15
char rx_buffer1[10];
char rx_buffer2[10];
char rx_buffer3[10];
unsigned int buffer_index1 = 0;
unsigned int buffer_index2 = 0;
unsigned int buffer_index3 = 0;
short data =0;
//variables ADC
unsigned int adc_val;
//variabels ident
short enable_ident=0;
//variables PID_1
float M1_q0,M1_q1,M1_q2,M2_q0,M2_q1,M2_q2,M3_q0,M3_q1,M3_q2;
signed int error1=0,error2=0,error3=0;
float cv1=0.0,cv1_1=0.0,error1_1=0.0,error1_2=0.0;
float cv2=0.0,cv2_1=0.0,error2_1=0.0,error2_2=0.0;
float cv3=0.0,cv3_1=0.0,error3_1=0.0,error3_2=0.0;
float kp1=1.69;
float ki1=34.62;
float kd1=0.0;
float kp2=2.13;
float ki2=38.18;
float kd2=0.0;
float kp3=2.50;
float ki3=40.11 ;
float kd3=0.0;
float Ts=0.015;
//variables Cinematica
float R=21.2464;// R=radio plataforma=21.2464 cm
float r=3.0;//r=radio rueda cm
float Vx=0.0, Vy=0.0, Wp=63.5402, W1=0.0, W2=0.0, W3=0.0;
//Variables logica difuza
float Vx_=0.0, Vy_=0.0, Wp_=0.0;
float W1_=0.0,W2_=0.0,W3_=0.0;

void main(void)
{
    config();    
    M1(0,'S');
    M2(0,'S');
    M3(0,'S');
    Init_PID();
    LATDbits.LATD3=1;
    
    Vx_=0.0;
    Vy_=0.0;
    Wp_=60.0;
    
    while(1)
    {
        W1_=W1_fuzzy(Vx_,Vy_,Wp_);
        UART1_Write4((signed int)(W1_*100.0));
        __delay_ms(5000);
    }
    /*
    while(1)
    {   
        
        //.......................................................................................
        if(enable_ident==1)
        {
            CI();
            //EMAV(1500,1500,1500);
            __delay_ms(15);
        }
        else
        {
            PID1(0,'S');
            PID2(0,'S');
            PID3(0,'S');
            __delay_ms(15);
        }       
    }
    */
}
void _ISR _INT0Interrupt(void)
{
    if(statevel3 == 0)
    {
        TMR1 = 0;
        PR1 = 65535;
        statevel3=1;
    }
    else if(statevel3 == 1)
    {
        Vel3=4687500/TMR1;
        if(Vel3<750)
        {
           Vel3=0;
        }
        statevel3=0;
    }
    IFS0bits.INT0IF=0; //bandera de interrupcion
}
void _ISR _INT1Interrupt(void)
{
    if(statevel1 == 0)
    {
        TMR4 = 0;
        PR4 = 65535;
        statevel1=1;
    }
    else if(statevel1 == 1)
    {
        Vel1=4687500/TMR4;
        if(Vel1<750)
        {
           Vel1=0;
        }  
        statevel1=0;
    }
    IFS1bits.INT1IF=0; //bandera de interrupcion  
}
void _ISR _INT2Interrupt(void)
{
    if(statevel2 == 0)
    {
        TMR5 = 0;
        PR5 = 65535;
        statevel2=1;
    }
    else if(statevel2 == 1)
    {
        Vel2=4687500/TMR5;
        if(Vel2<750)
        {
           Vel2=0;
        }   
        statevel2=0;
    }
    IFS1bits.INT2IF=0; //bandera de interrupcion  
}
void __attribute__((interrupt, auto_psv)) _T1Interrupt( void )
{
    TMR1 = 65535;
    PR1 = 65535;
    IFS0bits.T1IF = 0;//Bandera int tim en 0
}
void __attribute__((interrupt, auto_psv)) _T4Interrupt( void )
{
    TMR4 = 65535;
    PR4 = 65535;
    IFS1bits.T4IF = 0;//Bandera int tim en 0
}
void __attribute__((interrupt, auto_psv)) _T5Interrupt( void )
{
    TMR5 = 65535;
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
    if(enable_ident==1)
    {
        sprintf(text,"%u,1500\n",cont);
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
void UART1_Write3(int v1,int v2,int v3,int sp1,int sp2,int sp3) 
{
    sprintf(text,"%u,%u,%u,%u,%u,%u\n",v1,v2,v3,sp1,sp2,sp3);
    for(i=0;i<=strlen(text);i++)       //sterlen agraga caracteres para completar 
    {
        while (U1STAbits.UTXBF); // Esperar hasta que el buffer de transmisión esté lleno
        U1TXREG = text[i];          // Enviar el dato
        __delay_us(50);
    }
    
}
void UART1_Write4(signed int cont) 
{
    sprintf(text,"%d \n",cont);
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
    if(received=='E')
    {
        enable_ident = 1;
    }   
    else if(received=='D')
    {
        enable_ident = 0;
    }
    else
    {
        if (received != ';' ) 
        {
            if(received=='/')
            {
                data=data+1;
            }
            else if(data==0)
            {
                rx_buffer1[buffer_index1++] = received;
            }
            else if(data==1)
            {
                rx_buffer2[buffer_index2++] = received;
            }
            else if(data==2)
            {
                rx_buffer3[buffer_index3++] = received;
            }
            else
            {
                data=0;
            }
        } 
        else if (received == ';') 
        {
            data=0;
            buffer_index1=0;
            buffer_index2=0;
            buffer_index3=0;
            
            UART1_Write4(atoi(rx_buffer1));
            UART1_Write4(atoi(rx_buffer2));
            UART1_Write4(atoi(rx_buffer3));
        }
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
    __delay_ms(100);
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
    
    OC1RS=0;
    OC2RS=0;
    OC3RS=0;
    
    //ADC
    ADCON2bits.VCFG=0b000;//fuente de referencia Vdd y Vss
    ADCHSbits.CH0NA=0; //negative input is VREF-
    ADCHSbits.CH0SA=0; //CHANEl AN0  01 1111
    ADCON3bits.ADCS=0b011111;//ADCS a 31 para un TAD de 533ns
    ADCON1bits.ASAM=0;//modo de muestreo manual
    ADCON1bits.SSRC=0b000;//Trigger Manual al limpiar SAMP bit
    ADCON1bits.ADON=1;//Habilitar el ADC
}
void EMAV(int sp1,int sp2,int sp3)
{
    float alpha=0.20;   
    Vel1EMA=alpha*Vel1+((1.0-alpha)*Vel1EMA_1);
    Vel2EMA=alpha*Vel2+((1.0-alpha)*Vel2EMA_1);
    Vel3EMA=alpha*Vel3+((1.0-alpha)*Vel3EMA_1);
    Vel1EMA_1=Vel1EMA;
    Vel2EMA_1=Vel2EMA;
    Vel3EMA_1=Vel3EMA;
    UART1_Write3((int)Vel1EMA,(int)Vel2EMA,(int)Vel3EMA,sp1,sp2,sp3);
}
void PID1(unsigned int sp,char rot)
{
     if(sp<=75)
    {
        M1(0,'S');//---------------------------------------------------------------------
    }
    else
    {
        //..........................START/PID
        error1=sp-(Vel1);//---------------------------------------------------------------------
        float e=error1;

        cv1=cv1_1+kp1*(M1_q0*e+M1_q1*error1_1+M1_q2*error1_2);
        if(cv1>=10000.0)
        {
            cv1=10000.0;
        }
        if(cv1<=0.0)
        {
            cv1=0.0;
        }
        cv1_1=cv1;
        error1_1=e;
        error1_2=error1_1;
        M1((unsigned int)cv1,rot);//---------------------------------------------------------------------
    }
}
void PID2(unsigned int sp,char rot)
{
    if(sp<=75)
    {
        M2(0,'S');//---------------------------------------------------------------------
    }
    else
    {
        //..........................START/PID
        error2=sp-(Vel2);//---------------------------------------------------------------------
        float e=error2;

        cv2=cv2_1+kp2*(M2_q0*e+M2_q1*error2_1+M2_q2*error2_2);
        if(cv2>=10000.0)
        {
            cv2=10000.0;
        }
        if(cv2<=0.0)
        {
            cv2=0.0;
        }
        cv2_1=cv2;
        error2_1=e;
        error2_2=error2_1;
        M2((unsigned int)cv2,rot);//---------------------------------------------------------------------
    }    
}
void PID3(unsigned int sp,char rot)
{
    if(sp<=75)
    {
        M3(0,'S');//---------------------------------------------------------------------
    }
    else
    {
        //..........................START/PID
        error3=sp-(Vel3);//---------------------------------------------------------------------
        float e=error3;

        cv3=cv3_1+kp3*(M3_q0*e+M3_q1*error3_1+M3_q2*error3_2);
        if(cv3>=10000.0)
        {
            cv3=10000.0;
        }
        if(cv3<=0.0)
        {
            cv3=0.0;
        }
        cv3_1=cv3;
        error3_1=e;
        error3_2=error3_1;
        M3((unsigned int)cv3,rot);//---------------------------------------------------------------------
    }
}
void Init_PID(void)
{
    //EULER BACKWARD M1
    M1_q0=1+(ki1*Ts)+(kd1/Ts);
    M1_q1=-(1+(2*kd1/Ts));
    M1_q2=(kd1/Ts);
    //EULER BACKWARD M2
    M2_q0=1+(ki2*Ts)+(kd2/Ts);
    M2_q1=-(1+(2*kd2/Ts));
    M2_q2=(kd2/Ts);
    //EULER BACKWARD M3
    M3_q0=1+(ki3*Ts)+(kd3/Ts);
    M3_q1=-(1+(2*kd3/Ts));
    M3_q2=(kd3/Ts);
}
void CD(void)
{
    Vx=r*(W1-(0.5*W2)-(0.5*W3));
    Vy=r*((0.866*W2)-(0.866*W3));
    Wp=r*((W1/R)+(W2/R)+(W3/R));
}
void CI(void)
{
    W1=((0.6666*Vx)+(R*Wp/3.0))*10.0/r;
    W2=((-0.3333*Vx)+(0.5773*Vy)+(R*Wp/3.0))*10.0/r;
    W3=((-0.3333*Vx)-(0.5773*Vy)+(R*Wp/3.0))*10.0/r;
    //UART1_Write4((signed int)W1);
    //UART1_Write4((signed int)W2);
    //UART1_Write4((signed int)W3);
    
    if(W1<0.0)
    {
        W1=W1*(-1.0);
        PID1((unsigned int)W1,'I');
    }
    else if(W1==0.0)
    {
        PID1(0,'S');
    }
    else
    {
        PID1((unsigned int)W1,'D');
    }
    if(W2<0.0)
    {
        W2=W2*(-1.0);
        PID2((unsigned int)W2,'I');
    }
    else if(W2==0.0)
    {
        PID2(0,'S');
    }
    else
    {
        PID2((unsigned int)W2,'D');
    }
    if(W3<0.0)
    {
        W3=W3*(-1.0);
        PID3((unsigned int)W3,'I');
    }
    else if(W3==0.0)
    {
        PID3(0,'S');
    }
    else
    {
        PID3((unsigned int)W3,'D');
    }
}

float fuzzy(double X,double A,double B,double C)
{
    float m=0.0;
    if ((A<=X) && (X<=B))
    {
        m=(X-A)/(B-A);
    }
    else if ((B<=X) && (X<=C))
    {
        m=(C-X)/(C-B);
    }
    else
    {
        m=0.0;
    }
    return m;
}
float W1_fuzzy(float Vx_,float Vy_,float Wp_)
{
    float Vxb=0.0,Vxm=0.0,VxA=0.0,Vyb=0.0,Vym=0.0,VyA=0.0,Wpb=0.0,Wpm=0.0,WpA=0.0;
    float Rules[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    float min_pert[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    float Val_num[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    float Num=0.0, Val_min_pert=0.0, OUT=0.0;
    //Fuzificacion 
    Vxb=fuzzy(Vx_,-2912.0,-1461.0,-9.75);
    Vxm=fuzzy(Vx_,-1461.0,-9.75,1442.0);
    VxA=fuzzy(Vx_,-9.75,1442.0,2893.0);
    
    Vyb=fuzzy(Vy_,-2594,-1299,-3.897);
    Vym=fuzzy(Vy_,-1299,-3.897,1291);
    VyA=fuzzy(Vy_,-3.897,1291,2586);
    
    Wpb=fuzzy(Wp_,-207.6,-103.9,-0.2824);
    Wpm=fuzzy(Wp_,-103.9,-0.2824,103.4);
    WpA=fuzzy(Wp_,-0.2824,103.4,207);
    
    //reglas e inferencia
    //1
    if ((Vxb > 0) &&  (Vyb > 0) && (Wpb > 0))
    {
        Rules[0]=-570;
        min_pert[0]=(Vxb*Vyb*Wpb);
    }
    //2
    if ((Vxb > 0) &&  (Vyb > 0) && (Wpm > 0))
    {
        Rules[1]=-325.3;
        min_pert[1]=(Vxb*Vyb*Wpm);
    }
    //3
    if ((Vxb > 0) &&  (Vyb > 0) && (WpA > 0))
    {
        Rules[2]=-80.67;
        min_pert[2]=(Vxb*Vyb*WpA);
    }
    //4
    if ((Vxb > 0) &&  (Vym > 0) && (Wpb > 0))
    {
        Rules[3]=-570;
        min_pert[3]=(Vxb*Vym*Wpb);
    }
    //5
    if ((Vxb > 0) &&  (Vym > 0) && (Wpm > 0))
    {
        Rules[4]=-325.3;
        min_pert[4]=(Vxb*Vym*Wpm);
    }
    //6
    if ((Vxb > 0) &&  (Vym > 0) && (WpA > 0))
    {
        Rules[5]=-80.67;
        min_pert[5]=(Vxb*Vym*WpA);
    }
    //7
    if ((Vxb > 0) &&  (VyA > 0) && (Wpb > 0))
    {
        Rules[6]=-570;
        min_pert[6]=(Vxb*VyA*Wpb);
    }
    //8
    if ((Vxb > 0) &&  (VyA > 0) && (Wpm > 0))
    {
        Rules[7]=-325.3;
        min_pert[7]=(Vxb*VyA*Wpm);
    }
    //9
    if ((Vxb > 0) &&  (VyA > 0) && (WpA > 0))
    {
        Rules[8]=-80.67;
        min_pert[8]=(Vxb*VyA*WpA);
    }
    //10
    if ((Vxm > 0) &&  (Vyb > 0) && (Wpb > 0))
    {
        Rules[9]=-247.5;
        min_pert[9]=(Vxm*Vyb*Wpb);
    }
    //11
    if ((Vxm > 0) &&  (Vyb > 0) && (Wpm > 0))
    {
        Rules[10]=-2.833;
        min_pert[10]=(Vxm*Vyb*Wpm);
    }
    //12
    if ((Vxm > 0) &&  (Vyb > 0) && (WpA > 0))
    {
        Rules[11]=241.8;
        min_pert[11]=(Vxm*Vyb*WpA);
    }
    //13
    if ((Vxm > 0) &&  (Vym > 0) && (Wpb > 0))
    {
        Rules[12]=-247.5;
        min_pert[12]=(Vxm*Vym*Wpb);
    }
    //14
    if ((Vxm > 0) &&  (Vym > 0) && (Wpm > 0))
    {
        Rules[13]=-2.833;
        min_pert[13]=(Vxm*Vym*Wpm);
    }
    //15
    if ((Vxm > 0) &&  (Vym > 0) && (WpA > 0))
    {
        Rules[14]=241.8;
        min_pert[14]=(Vxm*Vym*WpA);
    }
    //16
    if ((Vxm > 0) &&  (VyA > 0) && (Wpb > 0))
    {
        Rules[15]=-247.5;
        min_pert[15]=(Vxm*VyA*Wpb);
    }
    //17
    if ((Vxm > 0) &&  (VyA > 0) && (Wpm > 0))
    {
        Rules[16]=-2.833;
        min_pert[16]=(Vxm*VyA*Wpm);
    }
    //18
    if ((Vxm > 0) &&  (VyA > 0) && (WpA > 0))
    {
        Rules[17]=241.8;
        min_pert[17]=(Vxm*VyA*WpA);
    }
    //19
    if ((VxA > 0) &&  (Vyb > 0) && (Wpb > 0))
    {
        Rules[18]=75;
        min_pert[18]=(VxA*Vyb*Wpb);
    }
    //20
    if ((VxA > 0) &&  (Vyb > 0) && (Wpm > 0))
    {
        Rules[19]=319.7;
        min_pert[19]=(VxA*Vyb*Wpm);
    }
    //21
    if ((VxA > 0) &&  (Vyb > 0) && (WpA > 0))
    {
        Rules[20]=564.3;
        min_pert[20]=(VxA*Vyb*WpA);
    }
    //22
    if ((VxA > 0) &&  (Vym > 0) && (Wpb > 0))
    {
        Rules[21]=75;
        min_pert[21]=(VxA*Vym*Wpb);
    }
    //23
    if ((VxA > 0) &&  (Vym > 0) && (Wpm > 0))
    {
        Rules[22]=319.7;
        min_pert[22]=(VxA*Vym*Wpm);
    }
    //24
    if ((VxA > 0) &&  (Vym > 0) && (WpA > 0))
    {
        Rules[23]=564.3;
        min_pert[23]=(VxA*Vym*WpA);
    }
    //25
    if ((VxA > 0) &&  (VyA > 0) && (Wpb > 0))
    {
        Rules[24]=75;
        min_pert[24]=(VxA*VyA*Wpb);
    }
    //26
    if ((VxA > 0) &&  (VyA > 0) && (Wpm > 0))
    {
        Rules[25]=319.7;
        min_pert[25]=(VxA*VyA*Wpm);
    }
    //27
    if ((VxA > 0) &&  (VyA > 0) && (WpA > 0))
    {
        Rules[26]=564.3;
        min_pert[26]=(VxA*VyA*WpA);
    }
    //defuzificacion
    
    for(i=0;i<27;i++)
    {
        Val_num[i]=Rules[i]*min_pert[i];
    }
    for(i=0;i<27;i++)
    {
        Num=Num+Val_num[i];
        Val_min_pert=Val_min_pert+min_pert[i];
    }
    
    OUT=Num/Val_min_pert;
    return OUT;
}