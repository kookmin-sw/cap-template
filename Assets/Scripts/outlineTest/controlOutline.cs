using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class controlOutline : MonoBehaviour
{
    Outline outline_;

    private void Start()
    {
        outline_.GetComponent<Outline>();
    }
    private void OnMouseDown()
    {
        Debug.Log("clickDown");
        outline_.OutlineMode = Outline.Mode.OutlineAll;
    }

    private void OnMouseUp()
    {
        Debug.Log("clickUp");
        outline_.OutlineMode = Outline.Mode.OutlineHidden;
    }
}
