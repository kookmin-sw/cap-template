using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class betteryspawner : MonoBehaviour
{
    public GameObject batterytPrefab; //생성할 배터리의 원본 프리팹
    Vector3 position_offset = new Vector3(0, 0.5f, 0); // 스포너 위쪽에서 스폰되도록


    //스폰 확률 
    public int spawnRateMin = 1;
    public int spawnRateMax = 5;


    //player의 interact 스크립트에서 호출됨
    public void create_bettery()
    {
        Debug.Log("betteryspawner create_bettery() is activated");
        if (Random.Range(spawnRateMin, spawnRateMax) == 2)
        {
            //Instantiate(원본,위치,회전); 
            GameObject battery = Instantiate(batterytPrefab, transform.position + position_offset, transform.rotation); //battery 복제본 생성
            Debug.Log("bettery is spawned");
        }



    }
}
