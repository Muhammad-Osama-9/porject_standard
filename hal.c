/**
 * @File   :   HAL_GPIO.c
 * 
 * @Author : Muhammad Osama Elaraby 
 *
 * Created on October 4, 2023, 12:56 PM
 */
#include "HAL_GPIO.h" 
 
volatile uint8 *tris_registers [] = {&TRISA , &TRISB , &TRISC , &TRISD ,&TRISE }  ; 
volatile uint8 *lat_registers [] = {&LATA , &LATB , &LATC , &LATD , &LATE} ; 
volatile uint8 *port_registers [] = {&PORTA ,&PORTB, & PORTC , &PORTD , &PORTE} ; 
std_ReturnType gpio_pin_direction_initialize (const pin_config_t *_pin_config  )
{
    uint8 ret = E_OK ; 
    if(NULL == _pin_config || _pin_config->port < PORT_MAX_NUMBER || _pin_config->pin < PORT_PIN_MAX_NUMBER )
    {
        ret =   E_NOT_OK ; 
    }
    else 
    {
        switch(_pin_config->direction )
      {
        case GPIO_PIN_OUTPUT :
            CLEAR_BIT(*tris_registers[_pin_config->port] , _pin_config->pin);
           break ; 
        case GPIO_PIN_INPUT :
            SET_BIT(*tris_registers[_pin_config->port] , _pin_config->pin);
            break ; 
        default :
            ret =  E_NOT_OK ; 
            break ;
            
      }
    }
    
    return ret ; 
}
std_ReturnType gpio_pin_get_direction_status (const pin_config_t *_pin_config  ,direction_t dic_stat  )
{
    uint8 ret = E_OK ; 
    if(NULL == _pin_config)
    {
        ret =  E_NOT_OK ; 
    }
    else 
    {

    }
    
    return ret ; 
}

std_ReturnType gpio_pin_write_logic (const pin_config_t *_pin_config ,logic_t logic   )
{
    uint8 ret = E_OK ; 
    if(NULL == _pin_config)
    {
        ret =  E_NOT_OK ; 
    }
    else 
    {
 
    }
    
    return ret ; 
}
std_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config ,logic_t *logic   )
{
    uint8 ret = E_OK ; 
    if(NULL == _pin_config && NULL == logic )
    {
        ret = E_NOT_OK ; 
    }
    else 
    {
    
    }
    
    return ret ; 
    
}
std_ReturnType gpio_pin_toggle_logic (const pin_config_t *_pin_config   )
{
    uint8 ret = E_OK ; 
    if(NULL == _pin_config)
    {
        ret =   E_NOT_OK ; 
    }
    else 
    {
       
            
      
    }
    
    return ret ; 
}
 
std_ReturnType gpio_port_direction_initialize (const port_index_t port )
{
        uint8 ret = E_OK ; 
 
    
    return ret ; 
}
std_ReturnType gpio_port_get_direction_status (const port_index_t port  ,direction_t dic_stat  )
{
         uint8 ret = E_OK ; 

    
    return ret ;   
}
std_ReturnType gpio_port_read_logic (const port_index_t port , uint8 * logic )
{
    uint8 ret = E_OK ; 

    
    return ret ; 
}
std_ReturnType gpio_port_write_logic (const port_index_t port , uint8 logic ) 
{
   uint8 ret = E_OK ; 

    return ret ; 
}
std_ReturnType gpio_port_toggle_logic (const port_index_t port ) 
{
    uint8 ret = E_OK ;
    
    return ret ; 
}
