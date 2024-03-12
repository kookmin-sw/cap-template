using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class outlineInteract : MonoBehaviour
{

    public GameObject image_F;
    public Inventory quicSlot;
    public Item battery_item;

    Transform selectedTarget;

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

    private void OnTriggerEnter(Collider other)
    {

        if (other.gameObject.layer == LayerMask.NameToLayer("Interact"))
        {
            if(selectedTarget != null)
            {
                clearTarget(selectedTarget);
            }

            Debug.Log("onTriggerEnter is activated for " + other.name);

            Transform obj = other.transform;
            selectTarget(obj);

            image_F.GetComponent<UIpressF>().show_image();
        }
    }

    
    private void OnTriggerStay(Collider other)
    {
        //만약 셀렉된 타겟이 없으면 지금 충돌중인 오브젝트를 셀
        if (selectedTarget == null && other.gameObject.layer == LayerMask.NameToLayer("Interact"))
        {
            Transform obj = other.transform;
            selectTarget(obj);
            image_F.GetComponent<UIpressF>().show_image();
        }

        //트리거 스테이 중에 F가 눌렸는데, 타겟이 있다면 상호작용 실행
        if (selectedTarget!=null && Input.GetKeyDown(KeyCode.F))
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
                //Item battery_ = Instantiate("Assets/Scripts/interact_test/UIInteract/battery");
                quicSlot.AddItem(battery_item);
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.layer == LayerMask.NameToLayer("Interact"))
        {
            Debug.Log("onTriggerExit is activated for " + other.name);
            image_F.GetComponent<UIpressF>().remove_image();

            clearTarget(selectedTarget);
        }


    }

    void Update()
    {
    }
}
