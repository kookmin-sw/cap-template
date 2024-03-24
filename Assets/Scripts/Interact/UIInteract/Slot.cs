using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Slot : MonoBehaviour
{
    [SerializeField] Image image; //Image Component를 담을 곳

    [SerializeField] private Item _item;
    public Item item
    {
        get { return _item; } //슬롯의 item 정보를 넘겨줄 때 사용

        set
        {
            _item = value; //item에 들어오는 정보의 값은 _item에 저장


            //아래부분은 Inventory 스크립트에서 addItem()과 FreshSlot() 함수에서 사용됨
            if (_item != null) 
            {
                //Inventory.cs 의 List<Item> items에 등록된 아이템이 있다면 itemImage를 image에 저장 그리고 Image의 알파 값을 1로 하여 이미지를 표시
                image.sprite = item.itemImage;
                image.color = new Color(1, 1, 1, 1);
            }
            else
            {
                //만약 item이 null 이면(빈슬롯 이면) Image의 알파 값 0을 주어 화면에 표시하지 않음 
                image.color = new Color(1, 1, 1, 0);
            }
        }
    }
}