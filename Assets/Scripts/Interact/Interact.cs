using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Interact : MonoBehaviour
{

    public GameObject image_F;
    public GameObject circleGaugeControler;
    public Inventory quicSlot;

    public bool isInvetigating = false; //수색중인가?


    RaycastHit hit;
    float interactDiastance = 4.0f;
    Transform selectedTarget;

    Vector3 raycastOffset = new Vector3(0f, 0f, 1.4f);

    void Update()
    {
        Vector3 raycastStartingPoint = transform.position + transform.TransformDirection(raycastOffset);

        Debug.DrawRay(raycastStartingPoint, transform.forward * interactDiastance, Color.blue, interactDiastance);

        //LayerMask.GetMask("Interact") : raycast가 Interact 레이어와만 상호작용 
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
                // 샌드백 치는 함수
                // 나중에 f 말고 떄리는 기능 구현하면 삭제해야함
                if (selectedTarget.CompareTag("tmp"))
                {
                    hit.collider.gameObject.GetComponent<HpManager>().OnDamage();
                }

                if (selectedTarget.CompareTag("door"))
                {
                    Debug.Log("문 상호작용 ");
                    selectedTarget.GetComponent<Door>().ChangeDoorState();
                }

                if (selectedTarget.CompareTag("ItemSpawner"))
                {
                    Debug.Log("betterySpawner 와 상호작용");

                    circleGaugeControler.GetComponent<InteractGaugeControler>().SetGuageZero();//수색 게이지 초기화하고
                    circleGaugeControler.GetComponent<InteractGaugeControler>().AbleInvestinGaugeUI(); //게이지UI켜고 
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
            if (circleGaugeControler.GetComponent<InteractGaugeControler>().FillCircle())
            {
                //수색을 성공적으로 마쳤다면 아이템 스폰 
                selectedTarget.GetComponent<ItemSpawner>().SpawnItem();

                //수색종료
                isInvetigating = false; 
                circleGaugeControler.GetComponent<InteractGaugeControler>().EnableInvestinGaugeUI();
            }
        }

    }



    void clearTarget(Transform obj)
    {
        if (selectedTarget == null) return;

        removeOutline(obj);
        selectedTarget = null;
        Debug.Log(obj.name + " is unselected");


        isInvetigating = false; //수색중이라면 취소하고
        circleGaugeControler.GetComponent<InteractGaugeControler>().EnableInvestinGaugeUI(); //게이지UI끄기 

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
        }
    }


}

