using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    [SerializeField] private SelectedSlot[] slots;
    [SerializeField] private GameObject combinationSlots;
    [SerializeField] private GameObject systemEnvironment;
    [SerializeField] private GameObject gameOverBoard;

    private int selectSlot = 0;

    // Start is called before the first frame update
    void Awake()
    {
        combinationSlots.SetActive(false);
        systemEnvironment.SetActive(false);
        gameOverBoard.SetActive(false);
        ChangeSlot(0);
        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.Locked;
    }

    // Update is called once per frame
    void Update()
    {
        ManageCombinationSlot();
        ManageSetting();
        SelectQuickSlot();
        ManageGameOverBoard();
    }

    void ManageCombinationSlot()
    {
        if (Input.GetKey(KeyCode.Tab))
        {
            combinationSlots.SetActive(true);
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.Confined;

        }
        if (Input.GetKeyUp(KeyCode.Tab))
        {
            combinationSlots.SetActive(false);
            Cursor.visible = false;
            Cursor.lockState = CursorLockMode.Locked;
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
            }
            else
            {
                systemEnvironment.SetActive(false);
                Cursor.visible = false;
                Cursor.lockState = CursorLockMode.Locked;
            }
        }
    }

    void ManageGameOverBoard()
    {
        if(gameOverBoard.activeSelf)
        {
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.Confined;
            if (Input.GetKeyDown(KeyCode.Escape) || Input.GetKey(KeyCode.Tab)) return;
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
