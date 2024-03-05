using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class outlineInteract : MonoBehaviour
{

    public GameObject image_F;

    //for sigleton
    //static outlineInteract instance = null;
    Transform selectedTarget;

    //public static outlineInteract Instance
    //{
    //    get
    //    {
    //        if (instance == null) instance = FindObjectOfType<outlineInteract>(); //null 이면 outlineInteract 스크립트를 가지고 있는 오브젝트를 찾아서 instance로 반환 
    //        return instance;
    //    }
    //}

    //void Awake()
    //{
    //    if (instance == null) instance = this;
    //}

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
        if (obj.gameObject.GetComponent<Outline>() != null)
        {
            obj.gameObject.GetComponent<Outline>().enabled = true;
        }
        else
        {
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
            Debug.Log("onTriggerEnter is activated for " + other.name);

            Transform obj = other.transform;
            selectTarget(obj);

            image_F.GetComponent<UIpressF>().show_image();
        }
    }

    private void OnTriggerStay(Collider other)
    {
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
