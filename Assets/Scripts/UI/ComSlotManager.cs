using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ComSlotManager : MonoBehaviour
{
    // Start is called before the first frame update
    [SerializeField] private Inventory itemQuickSlot;
    [SerializeField] private Slot firstComSlot;
    [SerializeField] private Slot secondComSlot;

    // Update is called once per frame
    void Update()
    {
        ReturnItem();
    }

    void ReturnItem()
    {
        if (!gameObject.activeSelf && firstComSlot.item != null)
        {

            if (itemQuickSlot.AddItem(firstComSlot.item) == 1)
            {
                firstComSlot.item = null;
            }
        }
        if (!gameObject.activeSelf && secondComSlot.item != null)
        {
            if (itemQuickSlot.AddItem(secondComSlot.item) == 1)
            {
                secondComSlot.item = null;
            }
        }
    }

    void CombinationItem()
    {
    }
}
