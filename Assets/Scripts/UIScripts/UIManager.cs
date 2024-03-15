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
        if (systemEnvironment.activeSelf == false && Input.GetKeyDown(KeyCode.Escape))
        {
            systemEnvironment.SetActive(true);
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.Confined;

        }
        if (systemEnvironment.activeSelf == true && Input.GetKeyDown(KeyCode.Escape))
        {
            systemEnvironment.SetActive(false);
            Cursor.visible = false;
            Cursor.lockState = CursorLockMode.Locked;
        }
    }
}
