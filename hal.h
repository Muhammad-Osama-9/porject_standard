#ifndef HAL_GPIO 
#define HAL_GPIO
/*Section : Includes */

#include "../mcal_std_libraries.h"
/*Section : Macros */
#define PORT_PIN_MAX_NUMBER  8 
#define PORT_MAX_NUMBER      5
#define BIT_MASK             1 

/*Section : Macro Function */

#define SET_BIT(port,pin)     port&=~(BIT_MASK<<pin)
#define CLEAR_BIT(port,pin)   port|=(BIT_MASK<<pin)
#define GET_BIT(port,pin)     ((port >> pin) & (BIT_MASK))
#define TOGGLE_BIT(port,pin)  port^=(BIT_MASK<<pin)

/*Section : User defined Datatype*/
typedef enum {
    LOW ,
    HIGH        
    
}logic_t;
typedef enum {
    GPIO_PIN_OUTPUT ,
    GPIO_PIN_INPUT        
    
}direction_t;

typedef enum  {
    PIN0 = 0 , 
    PIN1 ,
    PIN2 ,
    PIN3 , 
    PIN4 , 
    PIN5 , 
    PIN6 , 
    PIN7 , 
              
}pins_t;
typedef enum {
    PORTA_INDEX = 0 , 
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}port_index_t;
typedef struct {
   uint8 port       :3; 
   uint8 pin        :3;
   uint8 direction  :1; 
   uint8 logic      :1; 
}pin_config_t; 

/*Section : Function Declaration */

std_ReturnType gpio_pin_direction_initialize (const pin_config_t *_pin_config  );
std_ReturnType gpio_pin_get_direction_status (const pin_config_t *_pin_config  ,direction_t dic_stat  );

std_ReturnType gpio_pin_write_logic (const pin_config_t *_pin_config ,logic_t logic   );
std_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config ,logic_t *logic   );
std_ReturnType gpio_pin_toggle_logic (const pin_config_t *_pin_config   );
 
std_ReturnType gpio_port_direction_initialize (const port_index_t port );
std_ReturnType gpio_port_get_direction_status (const port_index_t port  ,direction_t dic_stat  );

std_ReturnType gpio_port_read_logic (const port_index_t port , uint8 * logic ) ; 
std_ReturnType gpio_port_write_logic (const port_index_t port , uint8 logic ) ; 
std_ReturnType gpio_port_toggle_logic (const port_index_t port ) ; 

#endif /*HAL_GPIO.h*/
