using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//여러 오브젝트 중 하나만 선택하도록 해보자
// 선택된 오브젝트는 위로 올라가고 아니면 내려가고

public class SelectBlock : MonoBehaviour
{
    static SelectBlock instance = null;
    Transform selectedTarget;
    Vector3 offset = new Vector3(0, 0.5f, 0);

    public static SelectBlock Instance
    {
        get
        {
            if (instance == null) instance = FindObjectOfType<SelectBlock>(); //null 이면 SelectBlock 스크립트를 가지고 있는 오브젝트를 찾아서 instance로 반환 
            return instance;
        }
    }

    void Awake()
    {
        if (instance == null) instance = this;
    }


    void addOutline(Transform obs)
    {
        obs.position += offset;
    }

    void removeOutline(Transform obs)
    {
        obs.position -= offset;
    }

    void clearTarget(Transform obs)
    {
        if (selectedTarget == null) return;

        removeOutline(obs);
        selectedTarget = null;
    }

    void selectTarget(Transform obj)
    {
        if (obj == null) return;

        clearTarget(selectedTarget); //이전에 이미 선택했던 오브젝트는 원래대로 

        selectedTarget = obj;
        addOutline(obj);
    }


    RaycastHit hit;
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            Debug.DrawRay(ray.origin, ray.direction * 100.0f, Color.red);

            int layer = 1 << LayerMask.NameToLayer("Interact");
            if (Physics.Raycast(ray, out hit, Mathf.Infinity, layer))
            {
                Transform obj = hit.transform;
                selectTarget(obj);
            }
        }
    }

}
