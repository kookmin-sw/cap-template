using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SelectedSlot : MonoBehaviour
{
    public Shadow slotOutline;

    // Start is called before the first frame update
    void Awake()
    {
    }
    public void Selected()
    {
        slotOutline.enabled = true;
    }
    public void Deselected()
    {
        slotOutline.enabled = false;
    }

}
