using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CraftSlot : MonoBehaviour
{
    public List<Item> items ; //아이템을 담을 리스트

    //[SerializeField] private Transform slotParent; // Slot의 부모를 담을 곳
    [SerializeField] private Slot[] slots;  //Iten Quick Slot의 하위에 있는 Slot을 담을 곳


#if UNITY_EDITOR
    //OnValidate()의 기능은 유니티 에디터에서 바로 작동을 하는 역할을 함. 
    private void OnValidate()
    {
        slots = GetComponentsInChildren<Slot>();
    }
#endif

    //아이템이 들어오거나 나가면 Slot의 내용을 다시 정리하여 화면에 보여 주는 기능
    public void FreshSlot()
    {
        int i = 0; //두 개의 For 문에 같은 i의 값을 사용하기 위해서 외부에 선언

        // items에 들어 있는 수만큼 slots에 차례대로 item을 넣어 줌
        //i 의 값이 items와 slots 두 개의 값 보다 작아야만 돌아가는 구조 -> items의 수가 slots 수보다 많으면 안 되니까 
        for (; i < items.Count && i < slots.Length; i++)
        {
            slots[i].item = items[i];
            //slot에 item이 들어가면 Slot.cs에 선언된 item의 set 안의 내용이 실행되어 해당 슬롯에 이미지를 표시하게 됨 
        }

        //slot에 아이템을 다 저장하고 난 후에도 slot이 남아 있다면 다음 for문이 실행되어 빈 슬롯들은 모두 null 처리
        for (; i < slots.Length; i++)
        {
            slots[i].item = null;
        }
    }


    //게임이 시작되면 items에 들어 있는 아이템을 인벤토리에 넣어줌 
    void Awake()
    {
        FreshSlot();
    }

    //아이템을 획득할 경우 AddItem을 불러와 넣어 주면 됨  성공하면 1 실패하면 0반환 
    public int AddItem(Item _item)
    {
        if (items.Count < slots.Length)
        {
            items.Add(_item);
            FreshSlot();
            return 1;
        }
        else
        {
            print("슬롯이 가득 차 있습니다.");
            return 0;
        }
    }

}