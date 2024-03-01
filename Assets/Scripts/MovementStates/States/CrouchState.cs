using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CrouchState : MovementBaseState
{
    public override void EnterState(MovementStateManager movement)
    {
        movement.anim.SetBool("Crouching", true);
    }

    public override void UpdateState(MovementStateManager movement)
    {
        if (Input.GetKey(KeyCode.LeftShift)) ExitState(movement, movement.Run);
        //if(Input.GetKeyDown(KeyCode.C) || Input.GetKeyDown(KeyCode.Space))
        {
            if (movement.moveDir.magnitude < 0.1f) ExitState(movement, movement.Idle);
            else ExitState(movement, movement.Walk);
        }

        if (movement.zAxis < 0) movement.currentMoveSpeed = movement.crouchBackSpeed;
        else movement.currentMoveSpeed = movement.crouchSpeed;
    }
    void ExitState(MovementStateManager movement, MovementBaseState state)
    {
        movement.anim.SetBool("Crouching", false);
        movement.SwitchState(state);
    }
}
