using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    [SerializeField] private GameObject combinationSlots;
    [SerializeField] private GameObject systemEnvironment;
    // Start is called before the first frame update
    void Awake()
    {
        combinationSlots.SetActive(false);
        systemEnvironment.SetActive(false);
        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.Locked;
    }

    // Update is called once per frame
    void Update()
    {
        ManageCombinationSlot();
        ManageSetting();
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

    void SelectQuickSlot()
    {
        if(Input.GetKeyDown(KeyCode.Alpha1))
        {

        }
        else if (Input.GetKeyDown(KeyCode.Alpha2))
        {

        }
        else if (Input.GetKeyDown(KeyCode.Alpha3))
        {

        }
        else if (Input.GetKeyDown(KeyCode.Alpha4))
        {

        }
        else if (Input.GetKeyDown(KeyCode.Alpha5))
        {

        }
    }
}
