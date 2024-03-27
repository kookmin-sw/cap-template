using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IdleState : MovementBaseState
{
    public override void EnterState(MovementStateManager movement)
    {
        movement.anim.SetBool("Idle", true);
    }

    public override void UpdateState(MovementStateManager movement)
    {
        // if(movement.moveDir.magnitude > 0.1f){
        //     if (Input.GetKey(KeyCode.LeftShift)) movement.SwitchState(movement.Run);
        //     else movement.SwitchState(movement.Walk);
        // }
        // if(Input.GetKeyDown(KeyCode.C)) movement.SwitchState(movement.Crouch);
        // if (Input.GetKeyDown(KeyCode.Space))
        // {
        //     movement.previousState = this;
        //     movement.SwitchState(movement.Jump);
        // }
        if(movement.moveDir.magnitude > 0.1f){
            if (Input.GetKey(KeyCode.LeftShift)) ExitState(movement, movement.Run);
            else ExitState(movement, movement.Walk);
        }
        if(Input.GetKeyDown(KeyCode.C)) ExitState(movement, movement.Crouch);
        if (Input.GetKeyDown(KeyCode.Space))
        {
            movement.previousState = this;
            ExitState(movement, movement.Jump);
        }
    }
    void ExitState(MovementStateManager movement, MovementBaseState state)
    {
        movement.anim.SetBool("Idle", false);
        movement.SwitchState(state);
    }
    
}