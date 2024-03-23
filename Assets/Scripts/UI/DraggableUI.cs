using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class DraggableUI : MonoBehaviour, IBeginDragHandler, IDragHandler, IEndDragHandler
{
    private Transform canvas; //UI가 속한 최상단의 canvas Transform
    public Transform preSlot; //해당 오브젝트가 직전에 소속되어 있었던 slot Transform
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
    // 현재 오브젝트 드래그 시작 시 1회 호출
    public void OnBeginDrag(PointerEventData eventData)
    {
        //드래그 직전에 소속되어 있던 부모Slot Transform 정보 저장
        preSlot = transform.parent;


        //현재 드래그 중인 아이콘이 화면의 최상단에 출력되도록
        transform.SetParent(canvas); //부모 오브젝트를 canvas로 설정
        transform.SetAsLastSibling(); // 아이콘을 가장 앞에 보이도록 마지막 자식으로 설정

        //드래그한 오브젝트 투명도 조절 / 광선 충돌처리 블락(slot 외에 상호작용하면 안되기 때문에)
        //itemIcon.alpha = 0.7f;
        itemIcon.blocksRaycasts = false;
    }
     
    // 드래그 중일 때 매 프레임 호출
    public void OnDrag(PointerEventData eventData)
    {
        // 드래그 중인 아이콘 위치를 마우스 위치로 설정
        itemIconRect.position = eventData.position;
    }

    //현재 오브젝트의 드래그를 종료할 때 1회 호출
    public void OnEndDrag(PointerEventData eventData)
    {
        // 드래그 종료시에도 부모가 canvas이면 slot창 외에 드롭된 것이어서 원래자리로
        if(transform.parent == canvas)
        {
            // 마지막에 소속되어있던 slot의 자식으로 설정, 아이콘의 위치를 원래자리로
            transform.SetParent(preSlot);
            itemIconRect.position = preSlot.GetComponent<RectTransform>().position;
        }

        // 드래그가 끝나면 알파값/ 광선 충돌처리 원래대로
        itemIcon.alpha = 1.0f;
        itemIcon.blocksRaycasts = true;
    }
}
