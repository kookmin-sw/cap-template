using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapManager : MonoBehaviour
{
    GameObject[] gameobjs;

    private void Awake()
    {
        gameobjs = FindObjectsOfType<GameObject>();

        for(int i = 0; i < gameobjs.Length; i++)
        {
            if (gameobjs[i].name.Contains("Door") && !gameobjs[i].name.Contains("Frame"))
            {
                addDoorScript(gameobjs[i]);
                gameobjs[i].tag = "door";
                gameobjs[i].layer = LayerMask.NameToLayer("Interact");
                gameobjs[i].isStatic = false; // 이걸 해줘야 회전함!!
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
