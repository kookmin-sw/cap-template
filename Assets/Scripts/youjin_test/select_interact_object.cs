using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class select_interact_object : MonoBehaviour
{

    /*SelectBlock은 카메라에만 존재하므로 싱글턴으로 만들면 좋다.-------------------------*/
    static select_interact_object instance = null;

    public static select_interact_object Instance
    {
        get
        {
            if (null == instance) instance = FindObjectOfType<select_interact_object>();
            return instance;
        }
    }

    void Awake()
    {
        if (null == instance) instance = this;
    }




    /*오브젝트가 선택된 경우, Outline이 나타남-----------------------------------------*/
    Material outline;
    Renderer renderers;
    List<Material> materialList = new List<Material>();

    void addOutline(Transform obj)
    {
        //Debug.Log("creat outline");
        //if (obj == null) return;

        //renderers = obj.GetComponent<Renderer>();

        //materialList.Clear();
        //materialList.AddRange(renderers.sharedMaterials);
        //materialList.Add(outline);

        //renderers.materials = materialList.ToArray();
    }

    void removeOutline(Renderer renderer)
    {
        //if (renderer != null)
        //{
        //    materialList.Clear();
        //    materialList.AddRange(renderer.sharedMaterials);
        //    materialList.Remove(outline);

        //    renderer.materials = materialList.ToArray();
        //}
    }



    /*오브젝트의 해제와 선택--------------------------------------------------------*/
    Transform selectedTarget;

    void clearTarget()
    {
        //현재 선택된 오브젝트를 null로 변경하고 outline 제거
        if (selectedTarget == null) return;

        selectedTarget = null;
        removeOutline(renderers);
    }


    //
    void selectTarget(Transform obj)
    {
        // selectedTarget을 선택한 오브젝트로 변경하고 outline을 추가
        if (obj == null) return;

        selectedTarget = obj;
        addOutline(obj);
    }


    /**/

    public float interactDiastance = 1f;
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.F))
        {
            //Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

            RaycastHit hit;
            Debug.DrawRay(transform.position, transform.forward * interactDiastance, Color.red, interactDiastance);

            int layer = 1 << LayerMask.NameToLayer("Interact");

            if (Physics.Raycast(transform.position,transform.forward, out hit, Mathf.Infinity, layer))
            {
                Transform obj = hit.transform;
                selectTarget(obj);
            }
        }
    }

}
