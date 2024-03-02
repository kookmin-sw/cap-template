 using System.Collections;
 using System.Collections.Generic;
 using UnityEngine;

 public class JumpState : MovementBaseState
 {
     public override void EnterState(MovementStateManager movement)
     {

        if (movement.previousState == movement.Idle) movement.anim.SetTrigger("Jump");
        else if (movement.previousState == movement.Walk || movement.previousState == movement.Run) movement.anim.SetTrigger("RunJump");

     }

     public override void UpdateState(MovementStateManager movement)
     {
        

     }

 }
