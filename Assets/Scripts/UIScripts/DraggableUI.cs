using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class DraggableUI : MonoBehaviour, IBeginDragHandler, IDragHandler, IEndDragHandler
{
    private Transform canvas; //UI�� ���� �ֻ���� canvas Transform
    private Transform preSlot; //�ش� ������Ʈ�� ������ �ҼӵǾ� �־��� slot Transform
    private RectTransform itemIconRect;
    private CanvasGroup itemIcon;
    void Awake()
    {
        canvas = FindObjectOfType<Canvas>().transform;
        itemIconRect = GetComponent<RectTransform>();
        itemIcon = GetComponent<CanvasGroup>();
    }

    void Update()
    {
        
    }
    // ���� ������Ʈ �巡�� ���� �� 1ȸ ȣ��
    public void OnBeginDrag(PointerEventData eventData)
    {
        //�巡�� ������ �ҼӵǾ� �ִ� �θ�Slot Transform ���� ����
        preSlot = transform.parent;

        //���� �巡�� ���� �������� ȭ���� �ֻ�ܿ� ��µǵ���
        transform.SetParent(canvas); //�θ� ������Ʈ�� canvas�� ����
        transform.SetAsLastSibling(); // �������� ���� �տ� ���̵��� ������ �ڽ����� ����

        //�巡���� ������Ʈ ���� ���� / ���� �浹ó�� ���(slot �ܿ� ��ȣ�ۿ��ϸ� �ȵǱ� ������)
        itemIcon.alpha = 0.7f;
        itemIcon.blocksRaycasts = false;
    }
     
    // �巡�� ���� �� �� ������ ȣ��
    public void OnDrag(PointerEventData eventData)
    {
        // �巡�� ���� ������ ��ġ�� ���콺 ��ġ�� ����
        itemIconRect.position = eventData.position;
    }

    //���� ������Ʈ�� �巡�׸� ������ �� 1ȸ ȣ��
    public void OnEndDrag(PointerEventData eventData)
    {
        // �巡�� ����ÿ��� �θ� canvas�̸� slotâ �ܿ� ��ӵ� ���̾ �����ڸ���
        if(transform.parent == canvas)
        {
            // �������� �ҼӵǾ��ִ� slot�� �ڽ����� ����, �������� ��ġ�� �����ڸ���
            transform.SetParent(preSlot);
            itemIconRect.position = preSlot.GetComponent<RectTransform>().position;
        }

        // �巡�װ� ������ ���İ�/ ���� �浹ó�� �������
        itemIcon.alpha = 1.0f;
        itemIcon.blocksRaycasts = true;
    }
}
