using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class outlineInteract : MonoBehaviour
{
    public GameObject image_F;


    RaycastHit hit;
    float interactDiastance = 2.0f;
    Transform selectedTarget;

    void Update()
    {
        Debug.DrawRay(transform.position, transform.forward * interactDiastance, Color.blue, interactDiastance);

        //LayerMask.GetMask("Interact") : raycast가 Interact 레이어와만 상호작용 
        if (Physics.Raycast(transform.position, transform.TransformDirection(Vector3.forward), out hit, interactDiastance,LayerMask.GetMask("Interact")))
        {
            //셀렉된 타겟이 없거나 새로운 오브젝트라면 새로 셀렉 
            if (selectedTarget==null || selectedTarget != hit.transform)
            {
                Transform obj = hit.transform;
                selectTarget(obj);
                addOutline(obj);
                image_F.GetComponent<UIpressF>().show_image();
            }

            //F를 누르면 상호작용 
            if (selectedTarget != null && Input.GetKeyDown(KeyCode.F))
            {
                if (selectedTarget.CompareTag("door"))
                {
                    Debug.Log("문 상호작용 ");
                    selectedTarget.GetComponent<Door>().ChangeDoorState();
                }

                if (selectedTarget.CompareTag("betteryspawner"))
                {
                    Debug.Log("betterySpawner 와 상호작용");
                    selectedTarget.GetComponent<betteryspawner>().Spawn_bettery();
                }

                if (selectedTarget.CompareTag("battery"))
                {
                    Debug.Log("bettery 와 상호작용");
                    selectedTarget.GetComponent<battery>().Destroy_battery();
                }
            }
        }
        else
        {
            //레이캐스트가 Interactable 오브젝트와 충돌하지 않았다면 실행됨
            if (selectedTarget)
            {
                removeOutline(selectedTarget);
                clearTarget(selectedTarget);
                image_F.GetComponent<UIpressF>().remove_image();

            }
        }
    }


    void clearTarget(Transform obj)
    {
        if (selectedTarget == null) return;

        Debug.Log(obj.name + " is unselected");
        removeOutline(obj);
        selectedTarget = null;
    }

    void selectTarget(Transform obj)
    {
        if (obj == null) return;

        clearTarget(selectedTarget); //이전에 이미 선택했던 오브젝트는 원래대로

        selectedTarget = obj;
        Debug.Log("selectTarget is " + obj.name);
        addOutline(obj);
    }


    void addOutline(Transform obj)
    {
        //Outline 컴포넌트가 있으면 그냥 활성화
        if (obj.gameObject.GetComponent<Outline>() != null)
        {
            obj.gameObject.GetComponent<Outline>().enabled = true;
        }
        else
        {
            //없으면 찾아서 넣어줌
            Outline outline = obj.gameObject.AddComponent<Outline>();
            outline.enabled = true;
            obj.gameObject.GetComponent<Outline>().OutlineColor = Color.white;
            obj.gameObject.GetComponent<Outline>().OutlineWidth = 5.0f;
        }
    }

    void removeOutline(Transform obj)
    {
        if (obj != null)
        {
            obj.gameObject.GetComponent<Outline>().enabled = false;
            obj = null;
        }
    }

}
