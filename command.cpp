#include "command.h"
#include "vaisseau_data.h"
#include "option.h"

void handle_command(struct command *cmd)
{
	struct vaisseau_data *vaisseau=cmd->controlled_ship;
	
    if (!vaisseau->explode) 
    {
        
        if (!(vaisseau->landed)||(vaisseau->rebound))
        {
            if (cmd->left)										 // Left arrow?
                vaisseau->angle-=vaisseau->anglestep; 								     // yes, on tourne a droite
            
            if (cmd->right) 									 // Right arrow?
                vaisseau->angle+= vaisseau->anglestep; 										   // yes, on tourne a gauche
        }
        
        if (cmd->shield)
        {
            vaisseau->shield = cmd->shield ;										   // shield activ
            
            if (vaisseau->shield && vaisseau->shield_force>0) 	// test shield si pas thrust
                vaisseau->sprite_buffer = vaisseau->gfx->sprite_shield; 			   // oui shield 
            else
                vaisseau->sprite_buffer = vaisseau->gfx->sprite;					   // non, normal
            
            vaisseau->thrust = itofix(0);	  // pas de thrust

        }
        else
        {
            // thrust?
            if (vaisseau->fuel > 0 && cmd->thrust)
            {
                // pointe le sprite thrust
                if (vaisseau->option_type != OPT_THRUST) vaisseau->sprite_buffer = vaisseau->gfx->sprite_thrust; 
                else vaisseau->sprite_buffer = vaisseau->gfx->sprite_thrust2;
                vaisseau->thrust = vaisseau->thrust_max;						   // acceleration
                vaisseau->shield = FALSE;								   // shield desactiv
                vaisseau->landed = FALSE;										   // pas pos
            }
            else
            {
                vaisseau->thrust = itofix(0);	  // pas de thrust
                vaisseau->sprite_buffer = vaisseau->gfx->sprite;					   // non, normal
                vaisseau->shield = FALSE;								   // shield desactiv			
            }
        }
        
        if (cmd->fire && !vaisseau->fire && !vaisseau->shield)
            vaisseau->fire_delay=TRUE;
        else
            vaisseau->fire_delay=FALSE;
        
        if (cmd->fire && !vaisseau->shield)
            vaisseau->fire=TRUE;
        else
            vaisseau->fire=FALSE;
    }	
}
