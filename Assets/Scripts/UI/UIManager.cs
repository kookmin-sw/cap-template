using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class UIManager : MonoBehaviour
{
    [SerializeField] private SelectedSlot[] slots;
    [SerializeField] private GameObject combinationSlots;
    [SerializeField] private GameObject systemEnvironment;
    [SerializeField] private GameObject gameOverBoard;

    private int selectSlot = 0;
    [HideInInspector] public bool isGameOver;
    [HideInInspector] public bool isUIActivate;

    // Start is called before the first frame update
    void Awake()
    {
        combinationSlots.SetActive(false);
        systemEnvironment.SetActive(false);
        gameOverBoard.SetActive(false);
        isGameOver = false;
        isUIActivate = false;
        ChangeSlot(0);
        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.Locked;
         
    }

    // Update is called once per frame
    void Update()
    {
        if(isGameOver == false)
        {
            ManageCombinationSlot();
            ManageSetting();
            SelectQuickSlot();
        }
        else
        {
            ManageGameOverBoard();
        }
    }

    void ManageCombinationSlot()
    {
        if (Input.GetKey(KeyCode.Tab))
        {
            combinationSlots.SetActive(true);
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.Confined;
            isUIActivate = true;

        }
        if (Input.GetKeyUp(KeyCode.Tab))
        {
            combinationSlots.SetActive(false);
            Cursor.visible = false;
            Cursor.lockState = CursorLockMode.Locked;
            isUIActivate = false;
        }
    }
    void ManageSetting()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (!systemEnvironment.activeSelf)
            {
                systemEnvironment.SetActive(true);
                Cursor.visible = true;
                Cursor.lockState = CursorLockMode.Confined;
                isUIActivate = true;
            }
            else
            {
                systemEnvironment.SetActive(false);
                Cursor.visible = false;
                Cursor.lockState = CursorLockMode.Locked;
                isUIActivate = false;

            }
        }
    }

    void ManageGameOverBoard()
    {
        if(isGameOver)
        {
            gameOverBoard.SetActive(true);
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.Confined;
        }
    }

    //퀵슬롯 1,2,3,4,5로 선택
    void SelectQuickSlot()
    {
        if (Input.GetKeyDown(KeyCode.Alpha1)) ChangeSlot(0);
        else if (Input.GetKeyDown(KeyCode.Alpha2)) ChangeSlot(1);
        else if (Input.GetKeyDown(KeyCode.Alpha3)) ChangeSlot(2);
        else if (Input.GetKeyDown(KeyCode.Alpha4)) ChangeSlot(3);
        else if (Input.GetKeyDown(KeyCode.Alpha5)) ChangeSlot(4);
    }
    //이전 선택 슬롯 비활성화, 현재 선택 슬롯 활성화
    void ChangeSlot(int pressValue)
    {
        slots[selectSlot].Deselected();
        slots[pressValue].Selected();
        selectSlot = pressValue;
    }


}
