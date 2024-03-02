using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    public GameObject combinationSlots;
    // Start is called before the first frame update
    void Awake()
    {
        combinationSlots.SetActive(false);
        Cursor.visible = false;
    }

    // Update is called once per frame
    void Update()
    {
        if(combinationSlots.activeSelf == false && Input.GetKey(KeyCode.Tab))
        {
            combinationSlots.SetActive(true);
            Cursor.visible = true;

        }
        if(Input.GetKeyUp(KeyCode.Tab))
        {
            combinationSlots.SetActive(false);
            Cursor.visible = false;
        }
    }
}
