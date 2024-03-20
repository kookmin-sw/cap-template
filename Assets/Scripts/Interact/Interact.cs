using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Interact : MonoBehaviour
{

    public GameObject image_F;
    public GameObject circleGauge;
    public Inventory quicSlot;

    public bool isInvetigating = false; //수색중인가?


    RaycastHit hit;
    float interactDiastance = 2.0f;
    Transform selectedTarget;

    // 레이케스트 시작점을 얼마나 변경할지 결정하는 벡터
    private Vector3 raycastOffset = new Vector3(0f, -0.5f, -1f);

    void Update()
    {
        Debug.DrawRay(transform.position, transform.forward * interactDiastance, Color.blue, interactDiastance);

        //LayerMask.GetMask("Interact") : raycast가 Interact 레이어와만 상호작용 
        Vector3 raycastStartingPoint = transform.position + transform.TransformDirection(raycastOffset);
        if (Physics.Raycast(raycastStartingPoint, transform.TransformDirection(Vector3.forward), out hit, interactDiastance, LayerMask.GetMask("Interact")))
        {
            //셀렉된 타겟이 없거나 새로운 오브젝트라면 새로 셀렉 
            if (selectedTarget == null || selectedTarget != hit.transform)
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

                if (selectedTarget.CompareTag("ItemSpawner"))
                {
                    Debug.Log("betterySpawner 와 상호작용");

                    circleGauge.GetComponent<InteractGaugeControler>().SetGuageZero();//수색 게이지 초기화하고
                    circleGauge.GetComponent<InteractGaugeControler>().AbleInvestinGaugeUI(); //게이지UI켜고 
                    isInvetigating = true;//수색시작
                }

                if (selectedTarget.CompareTag("Item"))
                {
                    Debug.Log(hit.collider.gameObject.name + " item과 상호작용");
                    ItemData itemdata = hit.collider.gameObject.GetComponent<ItemData>();
                    Item item = itemdata.itemData;
                    if (quicSlot.AddItem(item) == 1)
                    {
                        //아이템 넣기에 성공할때만 디스트로이
                        Destroy(hit.collider.gameObject);
                        image_F.GetComponent<UIpressF>().remove_image();
                    }
                }
            }

        }
        else
        {
            //레이캐스트가 Interactable 오브젝트와 충돌하지 않고 있다면


            //셀렉된 타겟이 있다면
            if (selectedTarget)
            {
                removeOutline(selectedTarget);
                clearTarget(selectedTarget);
                image_F.GetComponent<UIpressF>().remove_image();
            }
        }





        //수색여부(isInvetigating)에 따라 실행됨. 수색중이면 게이지 증g
        if (isInvetigating)
        {
            if (circleGauge.GetComponent<InteractGaugeControler>().FillCircle())
            {
                //수색을 성공적으로 마쳤다면 아이템 스폰 
                selectedTarget.GetComponent<ItemSpawner>().SpawnItem();

                //수색종료
                isInvetigating = false; 
                circleGauge.GetComponent<InteractGaugeControler>().EnableInvestinGaugeUI();
            }
        }

    }



    void clearTarget(Transform obj)
    {
        if (selectedTarget == null) return;

        Debug.Log(obj.name + " is unselected");
        removeOutline(obj);
        selectedTarget = null;

        isInvetigating = false; //수색중이라면 취소하고
        circleGauge.GetComponent<InteractGaugeControler>().EnableInvestinGaugeUI(); //게이지UI끄기 

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

