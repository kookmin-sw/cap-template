using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;//UI 관련 라이브러리

public class UIpressF : MonoBehaviour
{
    public GameObject image_pressF;

    void Start()
    {
        image_pressF = transform.Find("F_UI").gameObject;
        //Find 함수는 해당 이름의 자식 오브젝트를 검색하고 트랜스폼을 반환
        image_pressF.SetActive(false);
    }

    private void OnTriggerStay(Collider other)
    {
        image_pressF.transform.LookAt(other.transform);
    }

    public void show_image()
    {
        image_pressF.SetActive(true);
    }

    public void remove_image()
    {
        image_pressF.SetActive(false);
    }
}
