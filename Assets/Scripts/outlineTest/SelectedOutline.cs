using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectedOutline : MonoBehaviour
{
    Material outline;

    Renderer renderers;
    List<Material> materialList = new List<Material>();

    private void OnMouseDown()
    {
        Debug.Log("clickDown");

        renderers = this.GetComponent<Renderer>();

        materialList.Clear();
        materialList.AddRange(renderers.sharedMaterials);
        materialList.Add(outline);

        renderers.materials = materialList.ToArray();
    }

    private void OnMouseUp()
    {
        Debug.Log("clickUp");
        Renderer renderer = this.GetComponent<Renderer>();

        materialList.Clear();
        materialList.AddRange(renderer.sharedMaterials);
        materialList.Remove(outline);

        renderer.materials = materialList.ToArray();
    }

    void Start()
    {
        //outline = new Material(Shader.Find("Custom/outline"));
        //outline = new Material(Shader.Find("Custom/outline2"));

        //outline = new Material(Shader.Find("Custom/Outline Fill"));
        outline = new Material(Shader.Find("Custom/Outline Mask"));


    }
}