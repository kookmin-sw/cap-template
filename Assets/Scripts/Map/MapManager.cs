using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;


public class MapManager : MonoBehaviour
{
    GameObject[] gameObjs;

    private void Awake()
    {
        gameObjs = FindObjectsOfType<GameObject>();

        for(int i = 0; i < gameObjs.Length; i++)
        {
            if (gameObjs[i].name.Contains("Door") && !gameObjs[i].name.Contains("Frame"))
            {
                addDoorScript(gameObjs[i]);
                gameObjs[i].tag = "door";
                gameObjs[i].layer = LayerMask.NameToLayer("Interact");
                gameObjs[i].isStatic = false; // 이걸 해줘야 회전함!!

                // 문에 PhotonView 컴포넌트 추가
                gameObjs[i].AddComponent<PhotonView>();
            }
        }

    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void addDoorScript(GameObject obj)
    {
        //Door 컴포넌트가 있으면 그냥 활성화
        if (obj.gameObject.GetComponent<Door>() != null)
        {
            obj.gameObject.GetComponent<Door>().enabled = true;
        }
        else
        {
            //없으면 찾아서 넣어줌
            Door door = obj.gameObject.AddComponent<Door>();
            door.enabled = true;
            //obj.gameObject.GetComponent<Outline>().OutlineColor = Color.white;
            //obj.gameObject.GetComponent<Outline>().OutlineWidth = 5.0f;
        }
    }
}
