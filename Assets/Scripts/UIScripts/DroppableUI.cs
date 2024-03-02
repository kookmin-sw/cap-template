using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class DroppableUI : MonoBehaviour, IPointerEnterHandler, IDropHandler, IPointerExitHandler
{
    private Image slotImage;
    private Color preColor;
    private Color hoverColor;
    private RectTransform slotRect;
    void Awake()
    {
        slotImage = GetComponent<Image>();
        slotRect = GetComponent<RectTransform>();

        preColor = slotImage.color;
    }



    //���콺 �����Ͱ� ���� ������ ���� ���� ���η� �� �� 1ȸ ȣ��
    public void OnPointerEnter(PointerEventData eventData)
    {
        hoverColor = Color.white;
        hoverColor.a = 0.6f;
        slotImage.color = hoverColor;
    }

    //���콺 �����Ͱ� ���� ������ ���� ������ �������� �� 1ȸ ȣ��
    public void OnPointerExit(PointerEventData eventData)
    {
        slotImage.color = preColor;
    }

    // ���� ������ ���� ���� ���ο��� ����� ���� �� 1ȸ ȣ��
    public void OnDrop(PointerEventData eventData)
    {
        // pointerDrag = �巡������ ������ / �巡���ϰ��ִ� �������� ������
        if(eventData.pointerDrag != null)
        {
            eventData.pointerDrag.transform.SetParent(transform);
            eventData.pointerDrag.GetComponent<RectTransform>().position = slotRect.position;
        }
    }
}
