#include"i2c"

void I2C_Init(void)
{
    TRISC = 0x18;        // RC3=SCL input, RC4=SDA input
    SSPADD = 0x0A;       // 400kh 
    SSPSTATbits.SMP = 1; // Slew rate disabled for 400kHz
    SSPCON1 = 0x28;      // I2C Master mode, MSSP enabled
    SSPCON2 = 0x00;      // Clear control register
    SSPCON1bits.SSPEN=1; // SERIAL PORT
}

void I2C_Start(void)
{
     SSPCON2bits.SEN = 1;
       
}
void I2C_Stop(void)
{
    
       SSPCON2bits.PEN = 1;
   
}

void I2C_Write_char(uint8_t data)
{
    
    SSPBUF = data;
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    return ;
}
void I2C_Write(uint8_t Address, uint8_t *data)
{
    
    I2C_Start();

    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;

    SSPBUF = (Address << 1);   // Write mode
    
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;  // Clear I2C interrupt flag
        
    while(*data != '\0')
    {
        I2C_Write_char(*data);
        data++;
    }
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;  // Clear I2C interrupt flag
    I2C_Stop();
} 

//   It can read upto 8 bit //
uint8_t I2C_Read(uint8_t Address)
{
    I2C_Start();
    
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;  // Clear I2C interrupt flag
    
    SSPBUF = (Address<<1)| 1;   // Read
    
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;  // Clear I2C interrupt flag
    
    SSPCON2bits.RCEN = 1;
    
    while(!SSPSTATbits.BF);       // Wait until buffer full
 
    uint8_t value = SSPBUF;
    
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;  // Clear I2C interrupt flag
    
    SSPCON2bits.ACKDT = 1;        // NACK
    SSPCON2bits.ACKEN = 1;
    while(SSPCON2bits.ACKEN);

    I2C_Stop();

    return value;
}

