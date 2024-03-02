 using System.Collections;
 using System.Collections.Generic;
 using UnityEngine;

 public class JumpState : MovementBaseState
 {
     public override void EnterState(MovementStateManager movement)
     {

       if (movement.previousState == movement.Run || movement.previousState == movement.Walk) movement.anim.SetTrigger("Jump");

     }

     public override void UpdateState(MovementStateManager movement)
     {
        //¡°«¡«ﬂ¥Ÿ∞° ∂•ø° ¥Í¿∏∏È
        if(movement.jumped == true && movement.IsGrounded())
        {
            movement.jumped = false;
            if (Input.GetKey(KeyCode.LeftShift)) movement.SwitchState(movement.Run);
            else movement.SwitchState(movement.Walk);
        }
     }
 }
