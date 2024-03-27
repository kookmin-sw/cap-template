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
        // �޸��⸦ �����ϴ� ���� c�� ������ ��� ��ũ�ȴٰ� �ٽ� �޸��� ����
        //if (Input.GetKey(KeyCode.LeftShift)) ExitState(movement, movement.Run); 
        if(Input.GetKeyDown(KeyCode.C) || Input.GetKeyDown(KeyCode.Space)) // �޸��� ���� c�� ������ � ���µ� �ٷ� crouching���� ��ȯ
        {   
            if(movement.moveDir.magnitude > 0.1f){
                if (Input.GetKey(KeyCode.LeftShift)) ExitState(movement, movement.Run);
                else ExitState(movement, movement.Walk);
            }
            else ExitState(movement, movement.Idle);
        }

        
        // shift�� ������ �ӵ� �� ������
        if(Input.GetKey(KeyCode.LeftShift)) movement.currentMoveSpeed = movement.crouchFastBackSpeed;
        else movement.currentMoveSpeed = movement.crouchBackSpeed;

        // z���� �����̸� �ڷΰ��� �Ŵ� �ڷΰ��� ���ǵ��
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
