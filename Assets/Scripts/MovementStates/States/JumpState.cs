// using System.Collections;
// using System.Collections.Generic;
// using UnityEngine;

// public class JumpState : MovementBaseState
// {
//     public override void EnterState(MovementStateManager movement)
//     {
//         movement.anim.SetBool("Jumping", true);
//     }

//     public override void UpdateState(MovementStateManager movement)
//     {
        
//         if(movement.isGrounded)
//         {
//             if (Input.GetKey(KeyCode.LeftShift)) ExitState(movement, movement.Run);
//             else if (movement.moveDir.magnitude < 0.1f) ExitState(movement, movement.Idle);
//             else ExitState(movement, movement.Walk);
//         }
//     }

//     void ExitState(MovementStateManager movement, MovementBaseState state)
//     {
//         movement.anim.SetBool("Jumping", false);
//         movement.SwitchState(state);
//     }
// }
