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
        // 달리기를 지속하는 도중 c를 누르면 잠시 웅크렸다가 다시 달리기 시작
        //if (Input.GetKey(KeyCode.LeftShift)) ExitState(movement, movement.Run); 
        if(Input.GetKeyDown(KeyCode.C) || Input.GetKeyDown(KeyCode.Space)) // 달리는 도중 c를 누르면 어떤 상태든 바로 crouching으로 변환
        {   
            if(movement.moveDir.magnitude > 0.1f){
                if (Input.GetKey(KeyCode.LeftShift)) ExitState(movement, movement.Run);
                else ExitState(movement, movement.Walk);
            }
            else ExitState(movement, movement.Idle);
        }

        
        // shift를 누르면 속도 더 빠르게
        if(Input.GetKey(KeyCode.LeftShift)) movement.currentMoveSpeed = movement.crouchFastBackSpeed;
        else movement.currentMoveSpeed = movement.crouchBackSpeed;

        // z축이 음수이면 뒤로가는 거니 뒤로가는 스피드로
        // if (movement.zAxis < 0) {
        //     if(Input.GetKey(KeyCode.LeftShift)) movement.currentMoveSpeed = movement.crouchFastBackSpeed;
        //     else movement.currentMoveSpeed = movement.crouchBackSpeed;
        // }
        // else {
        //     if(Input.GetKey(KeyCode.LeftShift)) movement.currentMoveSpeed = movement.crouchFastSpeed;
        //     else movement.currentMoveSpeed = movement.crouchSpeed;
        // }
    }
    void ExitState(MovementStateManager movement, MovementBaseState state)
    {
        movement.anim.SetBool("Crouching", false);
        movement.SwitchState(state);
    }
}
