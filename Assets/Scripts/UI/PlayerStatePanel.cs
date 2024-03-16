using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using Photon.Pun;

public class PlayerStatePanel : MonoBehaviour
{
    [SerializeField] private Slider staminaBar;
    [SerializeField] private Slider healthPointBar;
    [SerializeField] private TextMeshProUGUI healthPointCount;

    private MovementStateManager movement;
    private PhotonView pv;
    void Awake()
    {
        pv = GetComponent<PhotonView>();
        movement = GetComponent<MovementStateManager>();
    }

    // Update is called once per frame
    void Update()
    {
        if (pv.IsMine)
        {
            ManageStaminaBar();
        }
    }

    void ManageStaminaBar()
    {
        
        if (movement.currentState == movement.Run)
        {
            staminaBar.value -= 15f * Time.deltaTime;
            if (staminaBar.value == 0)
            {
                movement.Run.ExitState(movement, movement.Walk);
                movement.currentState = movement.Walk;
            }
        }
        else
        { 
            staminaBar.value += 15f * Time.deltaTime;
        }
    }
}
