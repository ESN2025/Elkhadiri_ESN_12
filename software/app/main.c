#include "system.h"
#include "alt_types.h"
#include "opencores_i2c.h"           
#include "opencores_i2c_regs.h"     
#include "altera_avalon_pio_regs.h"   
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>



#define ADXL345_ADDRESS  0x1D  
#define DATA_FORMAT_REG  0x31  
#define POWER_CTL_REG    0x2D  
#define DATAX0_REG       0x32  
#define DATAY0_REG       0x34  
#define DATAZ0_REG       0x36  



int float_to_bcd(float float_value)
{
    int is_negative = 0;  

    if (float_value < 0) {
        is_negative = 1;  
        float_value = -float_value;  
    }

    // Partie entière
    int int_value = (int)float_value;

    // Partie fractionnaire (3 chiffres après la virgule)
    int fractional_value = (int)((float_value - int_value) * 1000);  

  
    char int_bcd[2];
    int_bcd[0] = int_value % 10;
    int_bcd[1] = int_value / 10 % 10;

   
    char frac_bcd[3];
    frac_bcd[0] = fractional_value / 100;
    frac_bcd[1] = (fractional_value / 10) % 10;
    frac_bcd[2] = fractional_value % 10;



    int bcd_value = 0;




    bcd_value = (int_bcd[1] << 12) + (int_bcd[0] << 8) + (frac_bcd[0] << 4) + (frac_bcd[1] << 0);

    // Mettre le bit de signe au bit 17
    if (is_negative==1) {
        bcd_value |= (1 << 16);  // Signe à 1 pour un nombre négatif
    }


    return bcd_value;
}


void display_number(float number) {

   
    IOWR_32DIRECT(AVALON_INTERFACE_0_BASE, 0, float_to_bcd(number));
}


void init_adxl345(alt_u32 base) {
    uint8_t data[2];
    

    data[0] = POWER_CTL_REG;
    data[1] = 0x08;  // Bit Measure = 1
    I2C_write(base, ADXL345_ADDRESS, data[0]);  
    I2C_write(base, ADXL345_ADDRESS, data[1]);  


    data[0] = DATA_FORMAT_REG;
    data[1] = 0x08;  // Full resolution, ±2g
    I2C_write(base, ADXL345_ADDRESS, data[0]);  
    I2C_write(base, ADXL345_ADDRESS, data[1]);  
}

void read_adxl345(alt_u32 base, float* x, float* y, float* z) {
    uint8_t buffer[6];

    
    int status = I2C_start(base, ADXL345_ADDRESS, 0);  // Retour de la fonction I2C_start
    if (status == I2C_NOACK) {
        printf("Erreur: ADXL345 non détecté sur l'adresse 0x%x\n", ADXL345_ADDRESS);
        return;  // Arrêter la fonction si l'appareil n'est pas détecté
    }
	else {printf(" ADXL345 détecté ");}
   
    I2C_write(base, DATAX0_REG, 0);  // Demande des données de X

    I2C_start(base, ADXL345_ADDRESS, 1);    // Passer en mode lecture
    for (int i = 0; i < 6; i++) {
        buffer[i] = I2C_read(base, (i == 5));  // Lire les 6 octets
    }


    int16_t raw_x = (int16_t)((buffer[1] << 8) | buffer[0]);  // Axe x
    int16_t raw_y = (int16_t)((buffer[3] << 8) | buffer[2]);  // Axe y
    int16_t raw_z = (int16_t)((buffer[5] << 8) | buffer[4]);  // Axe z

  
    const float scale_factor = 3.9;  // Scale factor for ±2 g range
    *x = (raw_x * scale_factor); //valeurs en mg
    *y = (raw_y * scale_factor);
    *z = (raw_z * scale_factor);

    // Print the values (optional)
    printf("Acceleration (g): X = %.3f, Y = %.3f, Z = %.3f\n", *x, *y, *z);
}




int main() {
    printf("Initialisation de l'ADXL345...\n");
   IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 1); //CS

    I2C_init(OPENCORES_I2C_0_BASE, 50000000, 100000); 
    init_adxl345(OPENCORES_I2C_0_BASE);

    int cle =0;
    
    int der_cle= 1;

  

   

    while (1) {
        

	float x, y, z;

	int key_mnt = IORD_ALTERA_AVALON_PIO_DATA(BOUTTON_AXES_BASE);

	if (der_cle==1 && key_mnt == 0 ) { if(cle<2){cle++;} 
						else{cle=0;} }
	



	der_cle = key_mnt;
     
        read_adxl345(OPENCORES_I2C_0_BASE, &x, &y, &z);

       
        printf("Acceleration (g): X = %.3f, Y = %.3f, Z = %.3f\n", x, y, z);

	
	
	if (cle==0){
	display_number(x); }

	if(cle==1){display_number(y); }
	if(cle==2){display_number(z); }	

		
	usleep(500000);
       
    }

    return 0;
}
