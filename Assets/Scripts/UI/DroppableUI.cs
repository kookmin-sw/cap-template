using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Data.SqlTypes;
using ExitGames.Client.Photon;
using static UnityEditor.Progress;

public class DroppableUI : MonoBehaviour, IPointerEnterHandler, IDropHandler, IPointerExitHandler
{
    private Image slotImage;
    private Color preColor;
    private Color hoverColor;
    private RectTransform slotRect;

    [SerializeField] private RectTransform firstComSlotRect;
    [SerializeField] private RectTransform secondComSlotRect;
    [SerializeField] private Slot firstComSlot;
    [SerializeField] private Slot secondComSlot;
    [SerializeField] private CraftSlot craftSlot;
    void Awake()
    {
        slotImage = GetComponent<Image>();
        slotRect = GetComponent<RectTransform>();
        preColor = slotImage.color;
    }

    //마우스 포인터가 현재 아이템 슬롯 영역 내부로 들어갈 때 1회 호출
    public void OnPointerEnter(PointerEventData eventData)
    {
        hoverColor = Color.white;
        hoverColor.a = 0.6f;
        slotImage.color = hoverColor;
    }

    //마우스 포인터가 현재 아이템 슬롯 영역을 빠져나갈 때 1회 호출
    public void OnPointerExit(PointerEventData eventData)
    {
        slotImage.color = preColor;
    }

    // 현재 아이템 슬롯 영역 내부에서 드롭을 했을 때 1회 호출
    public void OnDrop(PointerEventData eventData)
    {
        // pointerDrag = 드래그중인 아이콘 / 드래그하고있는 아이콘이 있으면
        if(eventData.pointerDrag != null)
        {
            // 슬롯에 아이콘이 있으면 아이콘 교체
            DraggableUI draggedUI = eventData.pointerDrag.GetComponent<DraggableUI>();
            if (transform.childCount > 0)
            {
                Transform existingIcon = transform.GetChild(0);
                existingIcon.position = draggedUI.preSlot.position;
                existingIcon.SetParent(draggedUI.preSlot);
            }
            eventData.pointerDrag.transform.SetParent(transform);
            eventData.pointerDrag.GetComponent<RectTransform>().position = slotRect.position;

            //if (eventData.pointerDrag.GetComponent<RectTransform>().position == firstComSlotRect.position)
            //{
            //    craftSlot.items.Add() firstComSlot.item;
            //}
            //else if (eventData.pointerDrag.GetComponent<RectTransform>().position == secondComSlotRect.position)
            //{
            //    craftSlot.items[1] = secondComSlot.item;
            //}

        }
    }


}
