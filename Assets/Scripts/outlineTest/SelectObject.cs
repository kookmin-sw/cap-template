using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectObject : MonoBehaviour
{
    public float interactDiastance = 3f;
    Material outline;

    Renderer renderers;
    List<Material> materialList = new List<Material>();


    void Start()
    {
        outline = new Material(Shader.Find("Custom/outline"));
    }
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.F))
        {
            selectObject();
        }
    }

    void selectObject()
    {
        RaycastHit hit;
        Debug.DrawRay(transform.position, transform.forward * interactDiastance, Color.blue, interactDiastance);

        if (Physics.Raycast(transform.position, transform.forward, out hit, interactDiastance))
        {
            string objectName = hit.collider.gameObject.name;
            Debug.Log(objectName);

            BlockMove block = hit.transform.GetComponent<BlockMove>();
            if (block == null) return;

            block.selected = !block.selected;
            Debug.Log(block.selected);
        }
    }

}
