using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UIElements;

public class NoneState : MovementBaseState
{    
    public override void EnterState(MovementStateManager movement)
    {
        movement.anim.SetBool("Attack", false);
    }

    public override void UpdateState(MovementStateManager movement)
    {   
        if(Input.GetKey(KeyCode.Mouse0)) movement.SwitchState(movement.Punch);
        // movement.anim.SetLayerWeight(1, 0);

            // if(movement.stateInfo.IsName("UnArmedAttack") && movement.stateInfo.normalizedTime >= 0.5f){
            //     if(temp >= 0){
            //         temp -= Time.deltaTime;
            //     }
            //     movement.anim.SetLayerWeight(0, temp);
            // }
    }
   void ExitState(MovementStateManager movement, MovementBaseState state)
    {
        movement.anim.SetBool("Attack", false);
        movement.anim.SetLayerWeight(1, 0);
        movement.SwitchState(state);
    }
}

    

    
