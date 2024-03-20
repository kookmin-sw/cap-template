using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemSpawner : MonoBehaviour
{
    //스포너 오브젝트 근처로 포물선 운동을 하며 스폰됨

    [SerializeField] private List<Item> Items; //스포너에서 스폰될 수 있는 아이템들. 인스펙터 창에서 골라 넣어주면 됨 
    [SerializeField] private GameObject ItemPrefab;


    public float maxDistance = 1f; // 아이템이 스폰될 최대 반경
    Vector3 offset_ = new Vector3(0, 1f, 0);

    //스폰 확률 
    //public int spawnRateMin = 1;
    //public int spawnRateMax = 5;

    //포물선 운동을 위한 변수들
    public float m_InitialAngle = 70f; // 처음 날라가는 각도
    private Rigidbody itemRigidbody;

    //interact 스크립트에서 호출됨
    public void SpawnItem()
    {
        int randomItemNumber = Random.Range(0, Items.Count);
        Debug.Log("randomItemNumber : " + randomItemNumber);
        ItemPrefab = Items[randomItemNumber].itemPrefab;

        // 스포너 근처의랜덤 위치를 가져옵니다.
        Vector3 spawnPosition = transform.position + (Random.insideUnitSphere * maxDistance); //현재 위치에서 maxDistance 반경 랜덤으로 원형자리에 Vector3를 구함

        GameObject item = Instantiate(ItemPrefab, transform.position + offset_, transform.rotation); //item 복제본 생성
        itemRigidbody = item.GetComponent<Rigidbody>();
        Vector3 velocity = GetVelocity(transform.position, spawnPosition, m_InitialAngle);
        itemRigidbody.velocity = velocity;

        Debug.Log("item is spawned");

    }




    //이건 그냥 가져옴..ㅋ 
    public Vector3 GetVelocity(Vector3 start_pos, Vector3 target_pos, float initialAngle)
    {
        float gravity = Physics.gravity.magnitude;
        float angle = initialAngle * Mathf.Deg2Rad;

        Vector3 planarTarget = new Vector3(target_pos.x, 0, target_pos.z);
        Vector3 planarPosition = new Vector3(start_pos.x, 0, start_pos.z);

        float distance = Vector3.Distance(planarTarget, planarPosition);
        float yOffset = start_pos.y - target_pos.y;

        float initialVelocity
            = (1 / Mathf.Cos(angle)) * Mathf.Sqrt((0.5f * gravity * Mathf.Pow(distance, 2)) / (distance * Mathf.Tan(angle) + yOffset));

        Vector3 velocity
            = new Vector3(0f, initialVelocity * Mathf.Sin(angle), initialVelocity * Mathf.Cos(angle));

        float angleBetweenObjects
            = Vector3.Angle(Vector3.forward, planarTarget - planarPosition) * (target_pos.x > start_pos.x ? 1 : -1);
        Vector3 finalVelocity
            = Quaternion.AngleAxis(angleBetweenObjects, Vector3.up) * velocity;

        return finalVelocity;
    }
}
